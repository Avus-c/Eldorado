#include <raylib.h>

const int screenWidth  = 1800;
const int screenHeight = 1200;

void DrawShop()
{
	const int tmp        = 155;
	const int cardWidth  = 200;
	const int cardHeight = 300;
	const int cardMargin = 5;

	auto draw = [ tmp, cardHeight, cardWidth, cardMargin ]( int rowOffset )
	{
		for ( size_t i = 0; i < 6; i++ )
		{
			DrawRectangle( 100 + ( ( cardMargin + cardWidth ) * i ) + tmp,
			               screenHeight - rowOffset,
			               cardWidth,
			               cardHeight,
			               GRAY );
		}
	};

	int rowOffset = 400;
	draw( rowOffset );
	DrawRectangle(
	    90 + tmp, screenHeight - rowOffset - 20, ( cardWidth + cardMargin ) * 6 + 15, 15, RED );

	rowOffset = 725;
	draw( rowOffset );
	rowOffset = 1030;
	draw( rowOffset );
}

int main()
{
	InitWindow( screenWidth, screenHeight, "Eldorado" );

	bool      shopOpened = false;
	bool      turnActive = false;
	Rectangle turnBox{ screenWidth - 152, 2, 150, 30 };
	Color     turnBoxColor = DARKGRAY;
	Rectangle shopBox{ screenWidth - 152 - 152, 2, 150, 30 };
	Color     shopBoxColor = DARKGREEN;

	SetTargetFPS( 30 );

	while ( !WindowShouldClose() )
	{
		Vector2 mousePoint = GetMousePosition();
		if ( CheckCollisionPointRec( mousePoint, turnBox )
		     && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
		{
			turnActive = !turnActive;
		}

		if ( CheckCollisionPointRec( mousePoint, shopBox )
		     && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
		{
			shopOpened = !shopOpened;
		}

		BeginDrawing();
		ClearBackground( RAYWHITE );

		DrawRectangleRec( turnBox, turnBoxColor );
		DrawRectangleRec( shopBox, shopBoxColor );

		if ( turnActive )
		{
			DrawText( "Finish Turn!", screenWidth - 140, 7, 20, RED );
		}
		else
		{
			DrawText( "Wait for ...", screenWidth - 140, 7, 20, WHITE );
		}

		if ( shopOpened )
		{
			DrawText( "Exit Shop", screenWidth - 145 - 145, 7, 20, WHITE );
			DrawShop();
		}
		else
		{
			DrawText( "Open Shop", screenWidth - 145 - 145, 7, 20, WHITE );
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
