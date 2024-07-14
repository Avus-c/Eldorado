#ifndef STORE_STORE_HPP
#define STORE_STORE_HPP

#include <Cards/cards.hpp>

#include <array>

namespace Store
{

struct StoreCard
{
	Cards::ID id          = Cards::ID::Empty;
	uint8_t   count       = 3;
	bool      blackMarket = false;
};

struct Store
{
	std::array<StoreCard, 6>  market;
	std::array<StoreCard, 12> blackMarket;
};

auto initializeStore() -> Store;

void buy( Store &store, Cards::ID card, bool blackMarket = false, bool justTake = false );

} // namespace Store

#endif // STORE_STORE_HPP
