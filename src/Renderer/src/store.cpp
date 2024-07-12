#include <Renderer/store.hpp>

#include <raylib.h>

#include <array>
#include <string>

void DrawShop( int screenHeight, int screenWidth, Store::Store &store )
{
	const int tmp        = 155;
	const int cardWidth  = 200;
	const int cardHeight = 300;
	const int cardMargin = 5;

	auto draw = [ tmp, cardHeight, cardWidth, cardMargin, screenHeight ](
	                int rowOffset, std::array<Store::StoreCard, 6> &cards )
	{
		for ( size_t i = 0; i < 6; i++ )
		{
			const auto posX = 100 + ( ( cardMargin + cardWidth ) * i ) + tmp;
			const auto posY = screenHeight - rowOffset;
			DrawRectangle( posX, posY, cardWidth, cardHeight, GRAY );
			const std::string str = std::to_string( cards[ i ].count ) + " Cards";
			DrawText( str.c_str(), posX + 10, posY + 5, 20, BLACK );
		}
	};

	// market row
	int rowOffset = 400;
	draw( rowOffset, store.market );

	// divider
	DrawRectangle(
	    90 + tmp, screenHeight - rowOffset - 20, ( cardWidth + cardMargin ) * 6 + 15, 15, RED );

	std::array<Store::StoreCard, 6> drawBuff{};

	const auto split = std::next( store.blackMarket.begin(), 6 );
	std::copy( store.blackMarket.begin(), split, drawBuff.begin() );
	rowOffset = 725;
	draw( rowOffset, drawBuff );

	std::copy( split, store.blackMarket.end(), drawBuff.begin() );
	rowOffset = 1030;
	draw( rowOffset, drawBuff );
}
