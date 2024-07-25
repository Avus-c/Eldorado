#include <raylib.h>

#include <Networking/networking.hpp>
#include <Player/player.hpp>
#include <Renderer/card.hpp>
#include <Renderer/store.hpp>
#include <Store/store.hpp>

#include <vector>

const int screenWidth  = 1800;
const int screenHeight = 1000;

void centerWindow( int windowWidth, int windowHeight )
{
	const auto monitor       = GetCurrentMonitor();
	const auto monitorWidth  = GetMonitorWidth( monitor );
	const auto monitorHeight = GetMonitorHeight( monitor );
	SetWindowPosition( ( monitorWidth - windowWidth ) / 2, ( monitorHeight - windowHeight ) / 2 );
}

void checkTurnButton( const Rectangle &turnBox, int *player, bool *turnActive )
{
	const Vector2 mousePoint = GetMousePosition();
	if ( CheckCollisionPointRec( mousePoint, turnBox )
	     && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
	{
		std::string msg = "Player " + std::to_string( *player ) + " finished turn.";
		*player         = ( *player + 1 ) % 4;
		msg             = msg + " Player " + std::to_string( *player ) + " is next.";
		sendMessage( msg );
		*turnActive = *player == 0;
	}
}

void checkShopButton( const Rectangle             &shopBox,
                      bool                        *shopOpened,
                      Store::Store                &store,
                      std::vector<Renderer::Card> &shopCardEntities )
{
	const Vector2 mousePoint = GetMousePosition();
	if ( CheckCollisionPointRec( mousePoint, shopBox )
	     && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
	{
		*shopOpened = !*shopOpened;
		if ( *shopOpened )
		{
			shopCardEntities = Renderer::createCardEntities( store, screenWidth, screenHeight );
		}
		else
		{
			shopCardEntities.clear();
		}
	}
}

auto main() -> int
{
	auto store = Store::initializeStore();

	InitWindow( screenWidth, screenHeight, "Eldorado" );
	centerWindow( screenWidth, screenHeight );

	const Rectangle turnBox{ screenWidth - 152, 2, 150, 30 };
	const Rectangle shopBox{ screenWidth - 152 - 152, 2, 150, 30 };
	const Rectangle fpsBox{ 0, 0, 150, 30 };

	auto turnBoxColor = DARKGRAY;
	auto shopBoxColor = DARKGREEN;

	bool shopOpened = false;
	bool turnActive = false;

	int player = 0;

	SetTargetFPS( 30 );

	std::vector<Renderer::Card> shopCardEntities{};

	auto _player = Player::initialize();

	while ( !WindowShouldClose() )
	{
		checkTurnButton( turnBox, &player, &turnActive );
		checkShopButton( shopBox, &shopOpened, store, shopCardEntities );

		if ( shopOpened )
		{
			for ( auto &item : shopCardEntities )
			{
				const Vector2   mousePoint = GetMousePosition();
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
