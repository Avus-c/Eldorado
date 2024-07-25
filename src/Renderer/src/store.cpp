#include <Renderer/card.hpp>
#include <Renderer/store.hpp>

#include <raylib.h>

#include <array>
#include <print>
#include <string>

namespace Renderer
{

void DrawShop( const std::vector<Card> &entities )
{
	for ( const auto &item : entities )
	{
		auto       color    = GRAY;
		const auto cardData = Cards::Database::getCard( item.storeCard->id );

		switch ( cardData.type )
		{
		case Cards::Type::None: color = GRAY; break;
		case Cards::Type::Forest: color = GREEN; break;
		case Cards::Type::Water: color = BLUE; break;
		case Cards::Type::Gold: color = GOLD; break;
		case Cards::Type::Action: color = PURPLE; break;
		case Cards::Type::Joker: color = LIGHTGRAY; break;
		}

		DrawRectangle( item.posX, item.posY, Card::width, Card::height, color );

		if ( item.storeCard->id == Cards::ID::Empty )
		{
			continue;
		}

		const std::string str = std::to_string( item.storeCard->count ) + " Cards";
		DrawText( str.c_str(), item.posX + 10, item.posY + 5, 20, BLACK );
		DrawText( cardData.title.c_str(), item.posX + 10, item.posY + 25, 20, BLACK );

		const std::string kostet = std::to_string( cardData.cost ) + " Gold";
		DrawText( kostet.c_str(), item.posX + 10, item.posY + 45, 20, BLACK );
	}
}

auto createCardEntities( const Store::Store &store,
                         int                 totalWidth,
                         int                 totalHeight ) -> std::vector<Card>
{
	std::vector<Card> entities{};

	const int columnCount = 6;
	const int cardSpace_x = ( columnCount * ( Card::width + Card::margin ) ) - ( Card::margin );
	const int boarder_x   = ( totalWidth - cardSpace_x ) / 2;
	const int cardSpace_y = ( Card::height + Card::margin ) * 3;
	const int boarder_y   = ( totalHeight - cardSpace_y ) / 2;

	const int secondBlackMarketRow = boarder_y;
	const int firstBlackMarketRow  = boarder_y + Card::height + Card::margin;
	const int marketRow            = boarder_y + Card::height * 2 + Card::margin * 3;

	int i = 0;
	for ( const auto &item : store.market )
	{
		const Card card{
			.storeCard = &item,
			.posX      = boarder_x + ( i * Card::width ) + ( i * Card::margin ),
			.posY      = marketRow,
		};

		entities.push_back( card );
		i++;
	}

	int posYOffset = firstBlackMarketRow;
	i              = 0;
	for ( const auto &item : store.blackMarket )
	{
		const Card card{
			.storeCard = &item,
			.posX      = boarder_x + ( i % 6 * Card::width ) + ( i % 6 * Card::margin ),
			.posY      = posYOffset,
		};

		entities.push_back( card );

		if ( i >= 5 )
		{
			posYOffset = secondBlackMarketRow;
		}
		i++;
	}

	return entities;
}

} // namespace Renderer
