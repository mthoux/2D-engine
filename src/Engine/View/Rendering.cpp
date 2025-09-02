
#include "../Model/Tile.hpp"
#include "../Model/TileMap.hpp"
#include "Rendering.hpp"

sf::VertexArray renderTile(Tile tile) {
    sf::VertexArray vertices(sf::PrimitiveType::Triangles, 6);

    sf::Vector2f position = tile.position;
    sf::Vector2f size = tile.size;
    sf::Color color = tile.color;

    vertices[0].position = position;                                  // haut-gauche
    vertices[1].position = position + sf::Vector2f(size.x, 0);        // haut-droite
    vertices[2].position = position + sf::Vector2f(0, size.y);        // bas-gauche
    vertices[3].position = position + sf::Vector2f(0, size.y);        // bas-gauche
    vertices[4].position = position + sf::Vector2f(size.x, 0);        // haut-droite
    vertices[5].position = position + sf::Vector2f(size.x, size.y);   // bas-droite

    // Appliquer la couleur à chaque sommet
    for (int i = 0; i < 6; ++i)
        vertices[i].color = color;

    return vertices;
}

sf::VertexArray renderTileMap(TileMap tileMap) {
    sf::VertexArray vertices(sf::PrimitiveType::Triangles, 6*tileMap.levelSize.x*tileMap.levelSize.y);

    for (const  std::vector<Tile>& row : tileMap.tiles) {
        for (const Tile& tile : row) {
            sf::VertexArray tileVertices = renderTile(tile);
            for (int j = 0; j < 6; ++j) {
                vertices.append(tileVertices[j]);
            }
        }
    }

    return vertices;
}
