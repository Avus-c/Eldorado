#include <Player/player.hpp>

#include <algorithm>
#include <random>

namespace Player
{

void reDraw( Player &player )
{
	if ( player.m_inHand.size() >= HandSize )
	{
		return;
	}

	size_t toDraw = HandSize - player.m_inHand.size();
	draw( player, toDraw );
}

void draw( Player &player, size_t count )
{
	while ( count > 0 && !player.m_drawPile.empty() )
	{
		player.m_inHand.push_back( player.m_drawPile.back() );
		player.m_drawPile.pop_back();
		count--;
	}

	if ( count == 0 )
	{
		return;
	}

	shuffleDiscardPile( player );

	while ( count > 0 && !player.m_drawPile.empty() )
	{
		player.m_inHand.push_back( player.m_drawPile.back() );
		player.m_drawPile.pop_back();
		count--;
	}
}

void play( Player &player, Cards::Type toPlay )
{
	if ( player.m_inHand.empty() )
	{
		return;
	}

	auto iter = std::ranges::find_if( player.m_inHand,
	                                  [ toPlay ]( Cards::Type type )
	                                  {
		                                  return toPlay == type;
	                                  } );

	if ( iter == player.m_inHand.end() )
	{
		return;
	}

	player.m_played.push_back( *iter );
	player.m_inHand.erase( iter );
}

void finishTurn( Player &player )
{
	player.m_discardPile.append_range( player.m_played );
	reDraw( player );
}

void shuffleDiscardPile( Player &player )
{
	if ( player.m_discardPile.empty() )
	{
		return;
	}
	player.m_drawPile.clear(); // make sure it's empty

	std::ranges::copy( player.m_discardPile, std::back_inserter( player.m_drawPile ) );

	player.m_discardPile.clear();

	std::random_device rd;
	std::mt19937       g( rd() );

	std::ranges::shuffle( player.m_drawPile, g );
}

} // namespace Player
