#include <Player/player.hpp>

#include <algorithm>
#include <random>

namespace Player
{

void reDraw( Player &player )
{
	if ( player.inHand.size() >= HandSize )
	{
		return;
	}

	size_t toDraw = HandSize - player.inHand.size();
	draw( player, toDraw );
}

void draw( Player &player, size_t count )
{
	while ( count > 0 && !player.drawPile.empty() )
	{
		player.inHand.push_back( player.drawPile.back() );
		player.drawPile.pop_back();
		count--;
	}

	if ( count == 0 )
	{
		return;
	}

	shuffleDiscardPile( player );

	while ( count > 0 && !player.drawPile.empty() )
	{
		player.inHand.push_back( player.drawPile.back() );
		player.drawPile.pop_back();
		count--;
	}
}

void play( Player &player, Cards::Type toPlay )
{
	if ( player.inHand.empty() )
	{
		return;
	}

	auto iter = std::ranges::find_if( player.inHand,
	                                  [ toPlay ]( Cards::Type type )
	                                  {
		                                  return toPlay == type;
	                                  } );

	if ( iter == player.inHand.end() )
	{
		return;
	}

	player.played.push_back( *iter );
	player.inHand.erase( iter );
}

void finishTurn( Player &player )
{
	player.discardPile.append_range( player.played );
	player.played.clear();
	reDraw( player );
}

void shuffleDiscardPile( Player &player )
{
	if ( player.discardPile.empty() )
	{
		return;
	}
	player.drawPile.clear(); // make sure it's empty

	std::ranges::copy( player.discardPile, std::back_inserter( player.drawPile ) );

	player.discardPile.clear();

	std::random_device rd;
	std::mt19937       g( rd() );

	std::ranges::shuffle( player.drawPile, g );
}

} // namespace Player
