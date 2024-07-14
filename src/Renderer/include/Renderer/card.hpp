#ifndef RENDERER_CARD_HPP
#define RENDERER_CARD_HPP

#include <Cards/cards.hpp>

#include <cstdint>

namespace Renderer
{
struct Card
{
	Cards::Card card{};
	uint32_t    posX  = 0;
	uint32_t    posY  = 0;
	uint8_t     count = 0;

	static const uint32_t width  = 200;
	static const uint32_t height = 300;
};

} // namespace Renderer

#endif // RENDERER_CARD_HPP
