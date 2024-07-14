#include <Store/store.hpp>

#include <Cards/cards.hpp>

#include <algorithm>

namespace Store
{

auto initializeStore() -> Store
{
	constexpr Store store{ { {
		                       { Cards::ID::Telephone },
		                       { Cards::ID::TreasureChest },
		                       { Cards::ID::Photographer },
		                       { Cards::ID::Scout },
		                       { Cards::ID::Explorer },
		                       { Cards::ID::JackOfAllTrades },
		                   } },
		                   { {
		                       { .id = Cards::ID::Compass, .blackMarket = true },
		                       { .id = Cards::ID::Cartographer, .blackMarket = true },
		                       { .id = Cards::ID::Indigenous, .blackMarket = true },
		                       { .id = Cards::ID::Scientist, .blackMarket = true },
		                       { .id = Cards::ID::TravelDiary, .blackMarket = true },
		                       { .id = Cards::ID::Captain, .blackMarket = true },
		                       { .id = Cards::ID::Pioneer, .blackMarket = true },
		                       { .id = Cards::ID::MightyMachete, .blackMarket = true },
		                       { .id = Cards::ID::Millionaire, .blackMarket = true },
		                       { .id = Cards::ID::Journalist, .blackMarket = true },
		                       { .id = Cards::ID::Adventurer, .blackMarket = true },
		                       { .id = Cards::ID::PropellerPlane, .blackMarket = true },
		                   } } };

	return store;
}

void buy( Store &store, Cards::ID card, bool blackMarket, bool justTake )
{
	if ( blackMarket )
	{
		auto iter = std::ranges::find_if( store.blackMarket,
		                                  [ card ]( StoreCard scard )
		                                  {
			                                  return scard.id == card;
		                                  } );
		if ( iter == store.blackMarket.end() && iter->count == 0 )
		{
			return;
		}

		iter->count--;
		if ( iter->count == 0 )
		{
			iter->id = Cards::ID::Empty;
		};

		if ( justTake )
		{
			return;
		}

		auto empty_slot = std::ranges::find_if( store.market,
		                                        []( StoreCard scard )
		                                        {
			                                        return scard.count == 0;
		                                        } );
		if ( empty_slot == store.market.end() )
		{
			return;
		}
		*empty_slot             = *iter;
		empty_slot->blackMarket = false;

		iter->count = 0;
		iter->id    = Cards::ID::Empty;

		return;
	}

	auto iter = std::ranges::find_if( store.market,
	                                  [ card ]( StoreCard scard )
	                                  {
		                                  return scard.id == card;
	                                  } );

	if ( iter == store.market.end() || iter->count == 0 )
	{
		return;
	}

	iter->count--;
	if ( iter->count == 0 )
	{
		iter->id = Cards::ID::Empty;
	};
}

} // namespace Store
