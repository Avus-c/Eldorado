#include <raylib.h>

const int screenWidth  = 1800;
const int screenHeight = 1200;

void DrawShop()
{
	int tmp = 155;
	DrawRectangle( 100 + tmp, screenHeight - 400, 200, 300, GRAY );
	DrawRectangle( 305 + tmp, screenHeight - 400, 200, 300, GRAY );
	DrawRectangle( 510 + tmp, screenHeight - 400, 200, 300, GRAY );
	DrawRectangle( 715 + tmp, screenHeight - 400, 200, 300, GRAY );
	DrawRectangle( 920 + tmp, screenHeight - 400, 200, 300, GRAY );
	DrawRectangle( 1125 + tmp, screenHeight - 400, 200, 300, GRAY );

	DrawRectangle( 50, screenHeight - 420, 1700, 15, RED );

	DrawRectangle( 100 + tmp, screenHeight - 725, 200, 300, GRAY );
	DrawRectangle( 305 + tmp, screenHeight - 725, 200, 300, GRAY );
	DrawRectangle( 510 + tmp, screenHeight - 725, 200, 300, GRAY );
	DrawRectangle( 715 + tmp, screenHeight - 725, 200, 300, GRAY );
	DrawRectangle( 920 + tmp, screenHeight - 725, 200, 300, GRAY );
	DrawRectangle( 1125 + tmp, screenHeight - 725, 200, 300, GRAY );

	DrawRectangle( 100 + tmp, screenHeight - 1050, 200, 300, GRAY );
	DrawRectangle( 305 + tmp, screenHeight - 1050, 200, 300, GRAY );
	DrawRectangle( 510 + tmp, screenHeight - 1050, 200, 300, GRAY );
	DrawRectangle( 715 + tmp, screenHeight - 1050, 200, 300, GRAY );
	DrawRectangle( 920 + tmp, screenHeight - 1050, 200, 300, GRAY );
	DrawRectangle( 1125 + tmp, screenHeight - 1050, 200, 300, GRAY );
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
		if ( CheckCollisionPointRec( mousePoint, turnBox ) && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
		{
			turnActive = !turnActive;
		}

		if ( CheckCollisionPointRec( mousePoint, shopBox ) && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
		{
			shopOpened = !shopOpened;
		}

		BeginDrawing();
		ClearBackground( RAYWHITE );

		DrawRectangleRec( turnBox, turnBoxColor );
		DrawRectangleRec( shopBox, shopBoxColor );

		if ( turnActive )
		{
			DrawText( "Finish Turn!", screenWidth - 145, 7, 20, RED );
		}
		else
		{
			DrawText( "Wait Opponent", screenWidth - 145, 7, 20, WHITE );
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
