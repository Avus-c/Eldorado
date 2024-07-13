#ifndef RENDERER_STORE_HPP
#define RENDERER_STORE_HPP

#include <Cards/cards.hpp>
#include <Store/store.hpp>

#include <vector>

void DrawShop( int                         screenHeight,
               int                         screenWidth,
               Store::Store               &store,
               std::vector<Cards::Entity> &entities );
auto createCardEntities( Store::Store &store,
                         int           totalWidth,
                         int           totalHeight ) -> std::vector<Cards::Entity>;

#endif // RENDERER_STORE_HPP
