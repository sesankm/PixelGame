#include "GameObject.h"

GameObject::GameObject() {
	renderer = NULL;
	texture = NULL;
	pos_rect = {};
	frame_rect = {};
	collision_rect = {};
	texture_width = 0, texture_height = 0;
}

GameObject::GameObject(SDL_Renderer* rend, char* sprite_sheet_path, int texture_rows, int texture_cols, int start_x, int start_y, int width, int height) {
	renderer = rend;
	texture = IMG_LoadTexture(renderer, sprite_sheet_path);
	SDL_QueryTexture(texture, 0, 0, &texture_width, &texture_height);
	pos_rect = { start_x, start_y, width, height };
	frame_rect = { 0, 0, texture_width / texture_cols, texture_height / texture_rows };
	collision_rect = {};
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

void GameObject::update() {
	SDL_RenderCopyEx(renderer, texture, &frame_rect, &pos_rect, 0, 0, flip);
}

SDL_Rect GameObject::get_pos() {
	return pos_rect;
}
