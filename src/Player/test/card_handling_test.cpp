#include <Player/player.hpp>

#include <gtest/gtest.h>

TEST( player, playing_cards )
{
	Player::Player player{ { Cards::Type::Adventurer,
		                     Cards::Type::Captain,
		                     Cards::Type::Cartographer,
		                     Cards::Type::Compass },
		                   {},
		                   {},
		                   {} };

	auto startingHandSize = player.inHand.size();

	ASSERT_TRUE( player.played.empty() );

	Player::play( player, Cards::Type::Adventurer );

	EXPECT_EQ( player.inHand.size(), --startingHandSize );
	EXPECT_EQ( player.played.size(), 1 );
	EXPECT_EQ( player.played[ 0 ], Cards::Type::Adventurer );

	Player::play( player, Cards::Type::Cartographer );

	EXPECT_EQ( player.inHand.size(), --startingHandSize );
	EXPECT_EQ( player.played.size(), 2 );
	EXPECT_EQ( player.played[ 1 ], Cards::Type::Cartographer );
}

TEST( player, drawing_cards )
{
	Player::Player player{ { Cards::Type::Adventurer, Cards::Type::Captain },
		                   {},
		                   {},
		                   { Cards::Type::Cartographer,
		                     Cards::Type::Compass,
		                     Cards::Type::Compass,
		                     Cards::Type::Compass } };

	auto startingHandSize     = player.inHand.size();
	auto startingDrawPileSize = player.drawPile.size();

	Player::draw( player, 1 );

	EXPECT_EQ( player.inHand.size(), ++startingHandSize );
	EXPECT_EQ( player.drawPile.size(), --startingDrawPileSize );

	Player::draw( player, 2 );

	startingHandSize++;
	startingDrawPileSize--;

	EXPECT_EQ( player.inHand.size(), ++startingHandSize );
	EXPECT_EQ( player.drawPile.size(), --startingDrawPileSize );
}

TEST( player, over_drawing_cards )
{
	Player::Player player{ { Cards::Type::Adventurer, Cards::Type::Captain },
		                   {},
		                   { Cards::Type::Compass, Cards::Type::Compass },
		                   { Cards::Type::Cartographer, Cards::Type::Compass } };

	Player::draw( player, 3 );

	ASSERT_TRUE( player.discardPile.empty() );
	EXPECT_EQ( player.drawPile.size(), 1 );
	EXPECT_EQ( player.inHand.size(), 5 );
}

TEST( player, over_drawing_not_enough_cards )
{
	Player::Player player{ { Cards::Type::Adventurer, Cards::Type::Captain },
		                   {},
		                   { Cards::Type::Compass },
		                   { Cards::Type::Cartographer } };

	Player::draw( player, 3 );

	ASSERT_TRUE( player.discardPile.empty() );
	EXPECT_EQ( player.drawPile.size(), 0 );
	EXPECT_EQ( player.inHand.size(), 4 );
}

TEST( player, end_of_turn_draw )
{
	Player::Player player{ { Cards::Type::Adventurer, Cards::Type::Captain },
		                   {},
		                   {},
		                   { Cards::Type::Cartographer, Cards::Type::Compass } };

	Player::reDraw( player );

	ASSERT_TRUE( player.discardPile.empty() );
	ASSERT_TRUE( player.drawPile.empty() );
	EXPECT_EQ( player.inHand.size(), 4 );

	player = { { Cards::Type::Adventurer,
		         Cards::Type::Captain,
		         Cards::Type::Cartographer,
		         Cards::Type::Compass },
		       {},
		       {},
		       { Cards::Type::Cartographer, Cards::Type::Compass } };

	Player::reDraw( player );

	ASSERT_TRUE( player.discardPile.empty() );
	EXPECT_EQ( player.drawPile.size(), 2 );
	EXPECT_EQ( player.inHand.size(), 4 );
}

TEST( player, finish_turn )
{
	Player::Player player{ { Cards::Type::Adventurer, Cards::Type::Captain },
		                   { Cards::Type::Cartographer, Cards::Type::Compass },
		                   {},
		                   { Cards::Type::Cartographer, Cards::Type::Compass } };

	Player::finishTurn( player );

	ASSERT_TRUE( player.played.empty() );
	EXPECT_EQ( player.discardPile.size(), 2 );
	ASSERT_TRUE( player.drawPile.empty() );
}
