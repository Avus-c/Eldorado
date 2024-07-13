#ifndef CARDS_CARDS_HPP
#define CARDS_CARDS_HPP

#include <cstdint>
#include <string>

namespace Cards
{

enum class Type : uint8_t
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
	Compass,          // Kompass
	Cartographer,     // Kartograph
	IndigenousPeople, // Ureinwohner
	Scientist,        // Wissenschaftlerin
	TravelDiary,      // Reisetagebuch
	Captain,          // Kapitän
	Pioneer,          // Pionier
	MightyMachete,    // Mächtige Machete
	Millionaire,      // Millionärin
	Journalist,       // Journalistin
	Adventurer,       // Abenteurerin
	PropellerPlane,   // Propeller-Flugzeug
};

struct Card
{
	Type        cardType = Type::Empty;
	std::string title;
	std::string desc;
	uint8_t     value     = 0; // 0 on action cards
	uint8_t     cost      = 0;
	bool        singleUse = false;
};

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
