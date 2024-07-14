#include <raylib.h>

#include <Renderer/card.hpp>
#include <Renderer/store.hpp>
#include <Store/store.hpp>

#include <vector>

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

	std::vector<Renderer::Card> cardEntities{};

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
			shopOpened   = !shopOpened;
			cardEntities = Renderer::createCardEntities( store, screenWidth, screenHeight );
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
			Renderer::DrawShop( screenHeight, screenWidth, store, cardEntities );
		}
		else
		{
			DrawText( "Open Shop", screenWidth - 145 - 145, 7, 20, WHITE );
			cardEntities.clear();
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
