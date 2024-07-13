#include <Cards/cards.hpp>

#include <array>
#include <map>
#include <utility>

namespace Cards::Database
{

// clang-format off
const std::array<Card, 22> database{ {
	{},
	{ .id = ID::Researcher,		.type = Type::Forest, .value = 1, .cost = 0, .title = "Forscher" },
	{ .id = ID::Traveller,		.type = Type::Gold	, .value = 1, .cost = 0, .title = "Reisende" },
	{ .id = ID::Sailor,			.type = Type::Water	, .value = 1, .cost = 0, .title = "Matrose" },
	{ .id = ID::Telephone,		.type = Type::Action, .value = 0, .cost = 4, .title = "Fernsprechgerät", .singleUse = true, .desc = "Nimm ne Karte vom shop." },
	{ .id = ID::TreasureChest,	.type = Type::Gold	, .value = 4, .cost = 3, .title = "Schatztruhe", .singleUse = true },
	{ .id = ID::Photographer,	.type = Type::Gold	, .value = 2, .cost = 2, .title = "Fotografin" },
	{ .id = ID::Scout, 			.type = Type::Forest, .value = 2, .cost = 1, .title = "Kundschafter" },
	{ .id = ID::Explorer, 		.type = Type::Forest, .value = 3, .cost = 3, .title = "Entdecker" },
	{ .id = ID::JackOfAllTrades,.type = Type::Joker	, .value = 1, .cost = 2, .title = "Tausendsassa" },
	{ .id = ID::Compass, 		.type = Type::Action, .value = 0, .cost = 2, .title = "Kompass", .singleUse = true, .desc = "Zieh 3 Karten"},
	{ .id = ID::Cartographer,	.type = Type::Action, .value = 0, .cost = 4, .title = "Kartograph", .desc = "Zieh 2 Karten" },
	{ .id = ID::Indigenous,		.type = Type::Action, .value = 0, .cost = 5, .title = "Ureinwohner", .desc = "Lauf 1 Feld. Egal wohin."},
	{ .id = ID::Scientist,		.type = Type::Action, .value = 0, .cost = 4, .title = "Wissenschaftlerin", .desc = "Zieh 1 Karte. (Zerstöre 1 Karte)" },
	{ .id = ID::TravelDiary,	.type = Type::Action, .value = 0, .cost = 3, .title = "Reisetagebuch", .singleUse = true, .desc = "Zieh 2 Karten. (Zerstöre 2 Karten)" },
	{ .id = ID::Captain,		.type = Type::Water	, .value = 3, .cost = 2, .title = "Kapitän" },
	{ .id = ID::Pioneer,		.type = Type::Forest, .value = 5, .cost = 5, .title = "Pionier" },
	{ .id = ID::MightyMachete,	.type = Type::Forest, .value = 6, .cost = 3, .title = "Mächtige Machete", .singleUse = true },
	{ .id = ID::Millionaire,	.type = Type::Gold	, .value = 4, .cost = 5, .title = "Müllionärin" },
	{ .id = ID::Journalist,		.type = Type::Gold	, .value = 3, .cost = 3, .title = "Journalistin" },
	{ .id = ID::Adventurer,		.type = Type::Joker	, .value = 2, .cost = 4, .title = "Abenteurerin" },
	{ .id = ID::PropellerPlane,	.type = Type::Joker	, .value = 4, .cost = 4, .title = "Propeller-Flugzeug", .singleUse = true }
} };
// clang-format on

auto getCard( ID cardId ) -> const Card &
{
	return database.at( std::to_underlying<ID>( cardId ) );
}

} // namespace Cards::Database
