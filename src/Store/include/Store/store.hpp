#ifndef STORE_STORE_HPP
#define STORE_STORE_HPP

#include <Cards/cards_mock.hpp>

#include <array>

namespace Store
{

struct StoreCard
{
	Cards::Type type  = Cards::Type::Empty;
	uint8_t     count = 3;
};

struct Store
{
	std::array<StoreCard, 6>  market;
	std::array<StoreCard, 12> blackMarket;
};

constexpr auto initializeStore() -> Store;

constexpr void
buy( Store &store, Cards::Type card, bool blackMarket = false, bool justTake = false );

} // namespace Store

#endif // STORE_STORE_HPP
