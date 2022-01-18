#include "GameObject.h"

Layer::Layer(SDL_Renderer* renderer, char* file_name, char* image_path) {
	read_file(file_name);
	create_layer(image_path, renderer);
}

void Layer::read_file(char* file_name) {
	std::string line;
	std::ifstream myfile(file_name);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			std::vector<int> row;
			std::string token;
			size_t pos = 0;
			std::string del = ",";
			while ((pos = line.find(del)) != std::string::npos) {
				token = line.substr(0, pos);
				row.push_back(stoi(token));
				line.erase(0, pos + del.length());
			}
			map.push_back(row);
		}
		myfile.close();
	}
}

void Layer::create_layer(char* image_path, SDL_Renderer* renderer) {
	layer_tiles.clear();
	for (int i = 0; i < map.size(); i++) {
		std::vector<Tile> tmp;
		for (int j = 0; j < map[i].size(); j++) {
			tmp.push_back(Tile(renderer, image_path, 16, 16, map[i][j], j * 50, i * 50, 50, 50));
		}
		layer_tiles.push_back(tmp);
	}
}

void Layer::update(Player player) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			layer_tiles[i][j].check(player.camera, player.vel[0], player.vel[1]);

			SDL_Rect tile_position = (*layer_tiles[i][j].getPos());
			if (tile_position.x >= player.camera.x - 70
				&& tile_position.x + tile_position.w <= player.camera.x + player.camera.w + 70
				&& tile_position.y >= player.camera.y - 70
				&& tile_position.y + tile_position.h <= player.camera.y + player.camera.h + 70)
			{
				layer_tiles[i][j].update();
			}
		}
	}
}
