#ifndef MAP_HPP
#define MAP_HPP

#include <string>

class Map {
private:
  std::string textureId;
  int scale;
  int tileSize;

public:
  Map(std::string textureId, int scale, int tilesize);
  ~Map();
  void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
  void AddTile(int sourceX, int sourceY, int x, int y);
};

#endif // MAP_HPP