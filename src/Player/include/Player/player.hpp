#ifndef PLAYER_PLAYER_HPP
#define PLAYER_PLAYER_HPP

#include <Cards/cards_mock.hpp>

#include <cstdint>
#include <vector>

namespace Player
{

constexpr size_t HandSize = 4;

enum class Phase : uint8_t
{
	Move,
	Buy,
	Discard,
	Draw
};

struct Player
{
	std::vector<Cards::Type> m_inHand;
	std::vector<Cards::Type> m_played;
	std::vector<Cards::Type> m_discardPile;
	std::vector<Cards::Type> m_drawPile;
};

void reDraw( Player &player );
void draw( Player &player, size_t count );
void play( Player &player, Cards::Type toPlay );
void finishTurn( Player &player );
void shuffleDiscardPile( Player &player );

} // namespace Player

#endif // PLAYER_PLAYER_HPP
