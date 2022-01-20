#pragma once
#include "GameObject.h"

Tile::Tile(SDL_Renderer* rend, char* tileset_path, int tile_width, int tile_height, int tile_num,
	int rend_x, int rend_y, int rend_width, int rend_height) : GameObject(rend, tileset_path, 19, 45, rend_x, rend_y, rend_width, rend_height)
{
	frame_rect = { tile_num % 19 * tile_height, tile_num / 19 * tile_width, tile_width, tile_height };
}

void Tile::reposition(SDL_Rect camera, int vel_x, int vel_y) {
	if (camera.x + camera.w >= 900 && vel_x > 0)
		pos_rect.x -= 10;
	if (camera.x <= 0 && vel_x < 0)
		pos_rect.x += 10;
	if (camera.y <= 0 && vel_y < 0)
		pos_rect.y += 10;
	if (camera.y + camera.h >= 700 && vel_y > 0)
		pos_rect.y -= 10;
}
