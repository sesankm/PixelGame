#include "GameObject.h"

GameObject::GameObject() {
	return;
}

GameObject::GameObject(SDL_Renderer* rend, char* sprite_sheet_path, int texture_rows, int texture_cols, int start_x, int start_y, int width, int height) {
	renderer = rend;
	texture = IMG_LoadTexture(renderer, sprite_sheet_path);
	SDL_QueryTexture(texture, 0, 0, &texture_width, &texture_height);

	pos_rect.x = 300;
	pos_rect.y = 300;
	pos_rect.w = 70;
	pos_rect.h = 70;

	frame_rect.x = 0;
	frame_rect.y = 0;
	frame_rect.w = texture_width / texture_cols;
	frame_rect.h = texture_height / texture_rows;

	// pos_rect.x = start_x;
	// pos_rect.y = start_y;
	// pos_rect.w = width;
	// pos_rect.h = height;
}

// GameObject::GameObject(SDL_Renderer* rend, char* sprite_sheet_path, int start_x, int start_y, int width, int height) {
// 	renderer = rend;
// 	texture = IMG_LoadTexture(renderer, sprite_sheet_path);
// 	SDL_QueryTexture(texture, 0, 0, &texture_width, &texture_height);
// 	frame_rect = {0, 0, texture_width / 16, texture_height / 16};
// 	frame_rect = {start_x, start_y, width, height};
// }
