#include <Renderer/card.hpp>
#include <Renderer/store.hpp>

#include <raylib.h>

#include <array>
#include <print>
#include <string>

namespace Renderer
{

const int cardMargin  = 5;
const int columnCount = 6;
const int margin      = cardMargin * ( columnCount - 1 );

void DrawShop( int screenHeight, const std::vector<Card> &entities )
{
	const int tmp = 155;

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
	// market row
	int rowOffset = 400;

	// divider
	DrawRectangle( 90 + tmp,
	               screenHeight - rowOffset - 20,
	               ( Card::width + cardMargin ) * columnCount + 15,
	               15,
	               RED );
}

auto createCardEntities( const Store::Store &store,
                         int                 totalWidth,
                         int                 totalHeight ) -> std::vector<Card>
{
	std::vector<Card> entities{};

	const int tmp     = ( columnCount * Card::width ) + ( margin );
	const int boarder = ( totalWidth - tmp ) / 2;

	int i = 0;
	for ( const auto &item : store.market )
	{
		const Card card{
			.storeCard = &item,
			.posX      = boarder + ( i * Card::width ) + ( i * cardMargin ),
			.posY      = totalHeight - 400,
		};

		entities.push_back( card );
		i++;
	}

	int posYOffset = 725;
	i              = 0;
	for ( const auto &item : store.blackMarket )
	{
		const Card card{
			.storeCard = &item,
			.posX      = boarder + ( i % 6 * Card::width ) + ( i % 6 * cardMargin ),
			.posY      = totalHeight - posYOffset,
		};

		entities.push_back( card );

		if ( i >= 5 )
		{
			posYOffset = 1030;
		}
		i++;
	}

	return entities;
}

} // namespace Renderer
