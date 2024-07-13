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
		                       { Cards::ID::Compass },
		                       { Cards::ID::Cartographer },
		                       { Cards::ID::Indigenous },
		                       { Cards::ID::Scientist },
		                       { Cards::ID::TravelDiary },
		                       { Cards::ID::Captain },
		                       { Cards::ID::Pioneer },
		                       { Cards::ID::MightyMachete },
		                       { Cards::ID::Millionaire },
		                       { Cards::ID::Journalist },
		                       { Cards::ID::Adventurer },
		                       { Cards::ID::PropellerPlane },
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
		*empty_slot = *iter;

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
