#include "GameObject.h"

Player::Player(SDL_Renderer* rend, char* sprite_sheet_path) : GameObject(rend, sprite_sheet_path, 6, 8, 300, 300, 70, 70) {
	max_vel = 10;
	dir = Direction::Right;
	frame_tick = 0;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
	vel = { 0, 0 };
}

void Player::update_position() {
	if (vel[0] > 0 && camera.x + camera.w <= 900)
		pos_rect.x += vel[0];
	else if (vel[0] < 0 && camera.x >= 0)
		pos_rect.x += vel[0];

	if (vel[1] > 0 && camera.y + camera.h <= 700)
		pos_rect.y += vel[1];
	else if (vel[1] < 0 && camera.y >= 0)
		pos_rect.y += vel[1];

	collision_rect = { pos_rect.x + 10, pos_rect.y + 20, pos_rect.w - 20, pos_rect.h - 20 };
	camera.x = pos_rect.x + 70 - camera.w / 2;
	camera.y = pos_rect.y + 70 - camera.h / 2;
}

void Player::update_frame() {
	frame_rect.y = 0;
	frame_tick++;
	if (vel[0] != 0 || vel[1] != 0)
		frame_rect.y = frame_rect.h * 2;
	if (frame_tick == 3) {
		frame_rect.x += frame_rect.w;
		frame_tick = 0;
	}
	if (frame_rect.x > frame_rect.w * 3)
		frame_rect.x = 0;
}

void Player::update() {
	update_position();
	update_frame();
	SDL_RenderCopyEx(renderer, texture, &frame_rect, &pos_rect, 0, 0, flip);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &collision_rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &camera);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Player::keyDown(SDL_Keycode code) {
	if (code == SDLK_d) {
		dir = Direction::Right;
		vel[0] = max_vel;
		flip = SDL_FLIP_NONE;
	}
	else if (code == SDLK_a) {
		dir = Direction::Left;
		vel[0] = -max_vel;
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (code == SDLK_w) {
		dir = Direction::Up;
		vel[1] = -max_vel;
	}
	else if (code == SDLK_s) {
		dir = Direction::Down;
		vel[1] = max_vel;
	}
}

void Player::keyUp(SDL_Keycode code) {
	if (code == SDLK_d && dir != Direction::Left) {
		vel[0] = 0;
	}
	else if (code == SDLK_a && dir != Direction::Right) {
		vel[0] = 0;
	}
	else if (code == SDLK_w && dir != Direction::Down) {
		vel[1] = 0;
	}
	else if (code == SDLK_s && dir != Direction::Up) {
		vel[1] = 0;
	}
}

int Player::get_x_pos() {
	return pos_rect.x;
}

int Player::get_y_pos() {
	return pos_rect.y;
}

int Player::get_x_vel() {
	return vel[0];
}

int Player::get_y_vel() {
	return vel[1];
}
