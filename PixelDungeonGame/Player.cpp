#include "GameObject.h"

Player::Player(SDL_Renderer* rend, char* sprite_sheet_path) {
	renderer = rend;
	texture = IMG_LoadTexture(renderer, sprite_sheet_path);
	int cols = 8;
	int rows = 6;
	max_vel = 10;

	SDL_QueryTexture(texture, 0, 0, &texture_width, &texture_height);

	frame_rect.w = texture_width / cols;
	frame_rect.h = texture_height / rows;
	frame_rect.x = 0;
	frame_rect.y = 0;

	pos_rect.x = 300;
	pos_rect.y = 300;
	pos_rect.w = 70;
	pos_rect.h = 70;

	dir = Right;
}

void Player::update() {
	if (vel[0] > 0 && camera.x + camera.w <= 900) {
		pos_rect.x += vel[0];
	}
	else if (vel[0] < 0 && camera.x >= 0) {
		pos_rect.x += vel[0];
	}

	if (vel[1] > 0 && camera.y + camera.h <= 700) {
		pos_rect.y += vel[1];
	}
	else if (vel[1] < 0 && camera.y >= 0) {
		pos_rect.y += vel[1];
	}

	collision_rect = { pos_rect.x + 10, pos_rect.y + 20, pos_rect.w - 20, pos_rect.h - 20 };

	flip++;
	if (flip == 3) {
		frame_rect.x += frame_rect.w;
		flip = 0;
	}

	if (vel[0] != 0 || vel[1] != 0) {
		frame_rect.y = frame_rect.h * 2;
	}
	else {
		frame_rect.y = 0;
	}

	if (frame_rect.x > frame_rect.w * 3) {
		frame_rect.x = 0;
	}
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (dir == Left)
		flip = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(renderer, texture, &frame_rect, &pos_rect, 0, 0, flip);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &collision_rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	camera.x = pos_rect.x + 70 - camera.w / 2;
	camera.y = pos_rect.y + 70 - camera.h / 2;
}

void Player::keyDown(SDL_Keycode code) {
	if (code == SDLK_d) {
		dir = Right;
		vel[0] = max_vel;
	}
	else if (code == SDLK_a) {
		dir = Left;
		vel[0] = -max_vel;
	}
	else if (code == SDLK_w) {
		dir = Up;
		vel[1] = -max_vel;
	}
	else if (code == SDLK_s) {
		dir = Down;
		vel[1] = max_vel;
	}
}

void Player::keyUp(SDL_Keycode code) {
	if (code == SDLK_d && dir != Left) {
		vel[0] = 0;
	}
	else if (code == SDLK_a && dir != Right) {
		vel[0] = 0;
	}
	else if (code == SDLK_w && dir != Down) {
		vel[1] = 0;
	}
	else if (code == SDLK_s && dir != Up) {
		vel[1] = 0;
	}

}

int Player::getX() {
	return pos_rect.x;
}

int Player::getY() {
	return pos_rect.y;
}

int Player::get_vel_x() {
	return vel[0];
}

int Player::get_vel_y() {
	return vel[1];
}
