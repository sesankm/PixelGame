#pragma once
#include "GameObject.h"

Tile::Tile(SDL_Renderer* rend,
	char* tileset_path,
	int tile_width, int tile_height,
	int tile_num,
	int rend_x, int rend_y, int rend_width, int rend_height) 
{
	renderer = rend;
	texture = IMG_LoadTexture(renderer, tileset_path);
	SDL_QueryTexture(texture, 0, 0, &texture_width, &texture_height);

	int n_cols = texture_width / tile_width;
	int n_rows = texture_height / tile_height;
	int row = tile_num / n_cols;
	int col = tile_num % n_cols;

	frame_rect = { col * tile_width, row * tile_height, tile_width, tile_height };
	pos_rect = { rend_x, rend_y, rend_width, rend_height };
}

void Tile::check(SDL_Rect camera, int vel_x, int vel_y) {
	if (camera.x + camera.w >= 900 && vel_x > 0)
		pos_rect.x -= 10;
	if (camera.x <= 0 && vel_x < 0)
		pos_rect.x += 10;
	if (camera.y <= 0 && vel_y < 0)
		pos_rect.y += 10;
	if (camera.y + camera.h >= 700 && vel_y > 0)
		pos_rect.y -= 10;
}

void Tile::update() {
	SDL_RenderCopy(renderer, texture, &frame_rect, &pos_rect);
}

SDL_Texture* Tile::getTexture() {
	return texture;
}
SDL_Rect* Tile::getPos() {
	return &pos_rect;
}
SDL_Rect* Tile::getFrame() {
	return &frame_rect;
}
