#ifndef RENDERER_STORE_HPP
#define RENDERER_STORE_HPP

#include <Store/store.hpp>

#include <vector>

namespace Renderer
{

void DrawShop( int                screenHeight,
               int                screenWidth,
               Store::Store      &store,
               std::vector<Card> &entities );
auto createCardEntities( Store::Store &store,
                         int           totalWidth,
                         int           totalHeight ) -> std::vector<Card>;

} // namespace Renderer

#endif // RENDERER_STORE_HPP
