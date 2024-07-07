#include <print>
#include <raylib.h>

int main()
{
	std::print( "Welcome to eldorado" );

	InitWindow( 800, 400, "Eldorado" );

	while ( !WindowShouldClose() )
	{
		BeginDrawing();
		ClearBackground( RAYWHITE );
		DrawText( "Eldorado", 200, 200, 20, BLACK );
		DrawPoly( ( Vector2 ){ 160 / 4.0f * 2, 210 }, 6, 80, 30, BROWN );
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
