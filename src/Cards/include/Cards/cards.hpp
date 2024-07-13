#ifndef CARDS_CARDS_HPP
#define CARDS_CARDS_HPP

#include <cstdint>
#include <string>

namespace Cards
{

enum class ID : uint8_t
{
	Empty,
	// Base-Cards
	Researcher, // Forscher
	Traveller,  // Reisende
	Sailor,     // Matrose

	// Inital-Market
	Telephone,       // Fernsprechgerät
	TreasureChest,   // Schatztruhe
	Photographer,    // Fotografin
	Scout,           // Kundschafter
	Explorer,        // Entdecker
	JackOfAllTrades, // Tausendsassa

	// Black-Market
	Compass,        // Kompass
	Cartographer,   // Kartograph
	Indigenous,     // Ureinwohner
	Scientist,      // Wissenschaftlerin
	TravelDiary,    // Reisetagebuch
	Captain,        // Kapitän
	Pioneer,        // Pionier
	MightyMachete,  // Mächtige Machete
	Millionaire,    // Millionärin
	Journalist,     // Journalistin
	Adventurer,     // Abenteurerin
	PropellerPlane, // Propeller-Flugzeug
};

enum class Type : uint8_t
{
	None,
	Action,
	Gold,
	Forest,
	Water,
	Joker,
};

struct Card
{
	ID          id    = ID::Empty;
	Type        type  = Type::None;
	uint8_t     value = 0; // 0 on action cards
	uint8_t     cost  = 0;
	std::string title;
	bool        singleUse = false;
	std::string desc      = "";
};

namespace Database
{
auto getCard( ID cardId ) -> const Card &;
} // namespace Database

struct Entity
{
	Card     card{};
	uint32_t posX   = 0;
	uint32_t posY   = 0;
	uint32_t width  = 0;
	uint32_t height = 0;
};

} // namespace Cards

#endif // CARDS_CARDS_HPP
