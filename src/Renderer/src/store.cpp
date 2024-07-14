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

void DrawShop( int screenHeight, int screenWidth, Store::Store &store, std::vector<Card> &entities )
{
	const int tmp        = 155;
	const int cardWidth  = 200;
	const int cardHeight = 300;

	for ( const auto &item : entities )
	{
		auto color = GRAY;
		switch ( item.card.type )
		{
		case Cards::Type::Forest: color = GREEN; break;
		case Cards::Type::Water: color = BLUE; break;
		case Cards::Type::Gold: color = GOLD; break;
		case Cards::Type::Action: color = PURPLE; break;
		case Cards::Type::Joker: color = LIGHTGRAY; break;
		default: break;
		}

		DrawRectangle( item.posX, item.posY, cardWidth, cardHeight, color );

		const std::string str = std::to_string( item.count ) + " Cards";
		DrawText( str.c_str(), item.posX + 10, item.posY + 5, 20, BLACK );
		DrawText( item.card.title.c_str(), item.posX + 10, item.posY + 25, 20, BLACK );

		const std::string kostet = std::to_string( item.card.cost ) + " Gold";
		DrawText( kostet.c_str(), item.posX + 10, item.posY + 45, 20, BLACK );
	}
	// market row
	int rowOffset = 400;

	// divider
	DrawRectangle( 90 + tmp,
	               screenHeight - rowOffset - 20,
	               ( cardWidth + cardMargin ) * columnCount + 15,
	               15,
	               RED );
}

auto createCardEntities( Store::Store &store, int totalWidth, int totalHeight ) -> std::vector<Card>
{
	std::vector<Card> entities{};

	const int tmp     = ( columnCount * Card::width ) + ( margin );
	const int boarder = ( totalWidth - tmp ) / 2;

	int i = 0;
	for ( const auto &item : store.market )
	{
		const auto &cardData = Cards::Database::getCard( item.id );

		Card entity{ cardData };
		entity.posX  = boarder + ( i * Card::width ) + ( i * cardMargin );
		entity.posY  = totalHeight - 400;
		entity.count = item.count;

		entities.push_back( entity );
		i++;
	}

	int posY = 725;
	i        = 0;
	for ( const auto &item : store.blackMarket )
	{
		const auto &cardData = Cards::Database::getCard( item.id );

		Card entity{ cardData };
		entity.posX  = boarder + ( i % 6 * Card::width ) + ( i % 6 * cardMargin );
		entity.posY  = totalHeight - posY;
		entity.count = item.count;

		entities.push_back( entity );
		if ( i >= 5 )
		{
			posY = 1030;
		}
		i++;
	}

	return entities;
}

} // namespace Renderer
