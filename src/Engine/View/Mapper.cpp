#include "Mapper.hpp"
#include "../Utils/Utils.hpp"

// --- TileMap ---
sf::VertexArray Mapper::vmap(const TileMap& tileMap) {
    sf::VertexArray vertices(sf::PrimitiveType::Triangles, 6 * tileMap.getLevelSize().x * tileMap.getLevelSize().y);

    for (const std::vector<Tile>& row : tileMap.tiles) {
        for (const Tile& tile : row) {
            sf::VertexArray tileVertices = vmap(tile.getShape(), tile.getPosition(), tile.getColor());
            for (int j = 0; j < 6; ++j) {
                vertices.append(tileVertices[j]);
            }
        }
    }

    return vertices;
}

// For Shapes
sf::VertexArray Mapper::vmap(const Shape& shape, Vec2f position, sf::Color color) {
    std::vector<Vec2f> worldVerts = computeWorldVertices(shape, position);

    // SFML veut des triangles, donc on fait une conversion simple pour rectangles
    sf::VertexArray vertices;

    if (worldVerts.size() == 4) { // rectangle
        vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        vertices.resize(6);
        vertices[0].position = toSFML(worldVerts[0]);
        vertices[1].position = toSFML(worldVerts[1]);
        vertices[2].position = toSFML(worldVerts[3]);
        vertices[3].position = toSFML(worldVerts[2]);
        vertices[4].position = toSFML(worldVerts[1]);
        vertices[5].position = toSFML(worldVerts[3]);
    } else { // polygone générique (pas triangulé)
        vertices.setPrimitiveType(sf::PrimitiveType::Points);
        vertices.resize(worldVerts.size());
        for (size_t i = 0; i < worldVerts.size(); ++i) {
            vertices[i].position = toSFML(worldVerts[i]);
        }
    }

    // Couleur
    for (size_t i = 0; i < vertices.getVertexCount(); ++i) {
        vertices[i].color = color;
    }

    return vertices;
}