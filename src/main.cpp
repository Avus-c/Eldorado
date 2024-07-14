#include <raylib.h>

#include <Networking/networking.hpp>
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
	Rectangle fpsBox{ 0, 0, 150, 30 };

	int player = 0;

	SetTargetFPS( 30 );

	std::vector<Renderer::Card> shopCardEntities{};

	while ( !WindowShouldClose() )
	{
		const Vector2 mousePoint = GetMousePosition();
		if ( CheckCollisionPointRec( mousePoint, turnBox )
		     && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
		{
			std::string msg = "Player " + std::to_string( player ) + " finished turn.";
			player          = ( player + 1 ) % 4;
			msg             = msg + " Player " + std::to_string( player ) + " is next.";
			sendMessage( msg );
			turnActive = player == 0;
		}

		if ( CheckCollisionPointRec( mousePoint, shopBox )
		     && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
		{
			shopOpened = !shopOpened;
			if ( shopOpened )
			{
				shopCardEntities = Renderer::createCardEntities( store, screenWidth, screenHeight );
			}
			else
			{
				shopCardEntities.clear();
			}
		}

		if ( shopOpened )
		{
			for ( auto &item : shopCardEntities )
			{
				const Rectangle rec{ (float) item.posX,
					                 (float) item.posY,
					                 Renderer::Card::width,
					                 Renderer::Card::height };
				if ( CheckCollisionPointRec( mousePoint, rec )
				     && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && item.storeCard->count > 0 )
				{
					Store::buy( store, item.storeCard->id, item.storeCard->blackMarket );

					std::string msg = "Player " + std::to_string( player ) + " buys "
					                + Cards::Database::getCard( item.storeCard->id ).title;
					sendMessage( msg );
				}
			}
		}

		BeginDrawing();
		ClearBackground( RAYWHITE );

		DrawRectangleRec( turnBox, turnBoxColor );
		DrawRectangleRec( shopBox, shopBoxColor );

		DrawRectangleRec( fpsBox, RED );
		const std::string fps = std::to_string( GetFPS() ) + " FPS";
		DrawText( fps.c_str(), 10, 3, 20, BLACK );

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
			Renderer::DrawShop( screenHeight, shopCardEntities );
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
