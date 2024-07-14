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

	static const int width  = 200;
	static const int height = 300;
};

} // namespace Renderer

#endif // RENDERER_CARD_HPP
