#ifndef CARDS_CARDS_HPP
#define CARDS_CARDS_HPP

#include <cstdint>

namespace Cards
{

enum class Type : uint8_t
{
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

} // namespace Cards

#endif // CARDS_CARDS_HPP
