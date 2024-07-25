#ifndef RENDERER_CARD_HPP
#define RENDERER_CARD_HPP

#include <Cards/cards.hpp>
#include <Store/store.hpp>

#include <cstdint>

namespace Renderer
{
struct Card
{
	const Store::StoreCard *const storeCard;
	int                           posX = 0;
	int                           posY = 0;

	static const int width  = 180;
	static const int height = 250;
	static const int margin = 5; // space between cards
};

} // namespace Renderer

#endif // RENDERER_CARD_HPP
