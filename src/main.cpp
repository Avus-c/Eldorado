#include <raylib.h>

#include <Renderer/store.hpp>
#include <Store/store.hpp>

const int screenWidth  = 1800;
const int screenHeight = 1200;

int main()
{
	auto store = Store::initializeStore();

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
		const Vector2 mousePoint = GetMousePosition();
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
			DrawShop( screenHeight, screenWidth, store );
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
