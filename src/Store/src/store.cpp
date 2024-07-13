#include <Store/store.hpp>

#include <Cards/cards_mock.hpp>

#include <algorithm>

namespace Store
{

auto initializeStore() -> Store
{
	constexpr Store store{ { {
		                       { Cards::Type::Telephone },
		                       { Cards::Type::TreasureChest },
		                       { Cards::Type::Photographer },
		                       { Cards::Type::Scout },
		                       { Cards::Type::Explorer },
		                       { Cards::Type::JackOfAllTrades },
		                   } },
		                   { {
		                       { Cards::Type::Compass },
		                       { Cards::Type::Cartographer },
		                       { Cards::Type::IndigenousPeople },
		                       { Cards::Type::Scientist },
		                       { Cards::Type::TravelDiary },
		                       { Cards::Type::Captain },
		                       { Cards::Type::Pioneer },
		                       { Cards::Type::MightyMachete },
		                       { Cards::Type::Millionaire },
		                       { Cards::Type::Journalist },
		                       { Cards::Type::Adventurer },
		                       { Cards::Type::PropellerPlane },
		                   } } };

	return store;
}

void buy( Store &store, Cards::Type card, bool blackMarket, bool justTake )
{
	if ( blackMarket )
	{
		auto iter = std::ranges::find_if( store.blackMarket,
		                                  [ card ]( StoreCard scard )
		                                  {
			                                  return scard.type == card;
		                                  } );
		if ( iter == store.blackMarket.end() && iter->count == 0 )
		{
			return;
		}

		iter->count--;
		if ( iter->count == 0 )
		{
			iter->type = Cards::Type::Empty;
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
		iter->type  = Cards::Type::Empty;

		return;
	}

	auto iter = std::ranges::find_if( store.market,
	                                  [ card ]( StoreCard scard )
	                                  {
		                                  return scard.type == card;
	                                  } );

	if ( iter == store.market.end() || iter->count == 0 )
	{
		return;
	}

	iter->count--;
	if ( iter->count == 0 )
	{
		iter->type = Cards::Type::Empty;
	};
}

} // namespace Store
