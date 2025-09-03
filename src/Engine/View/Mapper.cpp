#include "Mapper.hpp"
#include <SFML/Graphics.hpp>

VertexObject Mapper::vmap(Tile tile) {

    sf::VertexArray vertices(sf::PrimitiveType::Triangles, 6);

    sf::Vector2f position = toSFML(tile.getPosition());
    sf::Vector2f size = toSFML(tile.getSize());
    sf::Color color = tile.getColor();

    vertices[0].position = position;                                  
    vertices[1].position = position + sf::Vector2f(size.x, 0);     
    vertices[2].position = position + sf::Vector2f(0, size.y);     
    vertices[3].position = position + sf::Vector2f(0, size.y);     
    vertices[4].position = position + sf::Vector2f(size.x, 0);     
    vertices[5].position = position + sf::Vector2f(size.x, size.y);

    for (int i = 0; i < 6; ++i)
        vertices[i].color = color;
    
    VertexObject vo;
    vo.vertices = vertices;
    return vo;
}

VertexObject Mapper::vmap(TileMap tileMap) {
    sf::VertexArray vertices(sf::PrimitiveType::Triangles, 6*tileMap.getLevelSize().x*tileMap.getLevelSize().y);

    for (const  std::vector<Tile>& row : tileMap.tiles) {
        for (const Tile& tile : row) {
            sf::VertexArray tileVertices = vmap(tile).vertices;
            for (int j = 0; j < 6; ++j) {
                vertices.append(tileVertices[j]);
            }
        }
    }

    VertexObject vo;
    vo.vertices = vertices;
    return vo;
}

VertexObject Mapper::vmap(Entity entity) {

    sf::VertexArray vertices(sf::PrimitiveType::Triangles, 6);

    sf::Vector2f position = toSFML(entity.getPosition());
    sf::Vector2f size = toSFML(entity.getSize());
    sf::Color color = entity.getColor();

    vertices[0].position = position;                                  
    vertices[1].position = position + sf::Vector2f(size.x, 0);     
    vertices[2].position = position + sf::Vector2f(0, size.y);     
    vertices[3].position = position + sf::Vector2f(0, size.y);     
    vertices[4].position = position + sf::Vector2f(size.x, 0);     
    vertices[5].position = position + sf::Vector2f(size.x, size.y);

    for (int i = 0; i < 6; ++i)
        vertices[i].color = color;
    
    VertexObject vo;
    vo.vertices = vertices;
    return vo;
}