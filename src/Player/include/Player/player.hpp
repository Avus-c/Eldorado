#ifndef PLAYER_PLAYER_HPP
#define PLAYER_PLAYER_HPP

#include <Cards/cards.hpp>

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
	std::vector<Cards::ID> inHand;
	std::vector<Cards::ID> played;
	std::vector<Cards::ID> discardPile;
	std::vector<Cards::ID> drawPile;
};

auto initialize() -> Player;

void reDraw( Player &player );
void draw( Player &player, size_t count );
void play( Player &player, Cards::ID toPlay );
void finishTurn( Player &player );
void shuffleDiscardPile( Player &player );

} // namespace Player

#endif // PLAYER_PLAYER_HPP
