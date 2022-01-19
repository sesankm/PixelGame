#include "GameObject.h"

Player::Player(SDL_Renderer* rend, char* sprite_sheet_path) : GameObject(rend, sprite_sheet_path, 6, 8, 300, 300, 70, 70) {
	max_vel = 10;
	dir = Direction::Right;
	frame_tick = 0;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
	vel_x = 0;
	vel_y = 0;
	update_position();
}

void Player::update_position() {
	if (vel_x > 0 && camera.x + camera.w <= 900)
		pos_rect.x += vel_x;
	else if (vel_x < 0 && camera.x >= 0)
		pos_rect.x += vel_x;

	if (vel_y > 0 && camera.y + camera.h <= 700)
		pos_rect.y += vel_y;
	else if (vel_y < 0 && camera.y >= 0)
		pos_rect.y += vel_y;

	collision_rect = { pos_rect.x + 10, pos_rect.y + 20, pos_rect.w - 20, pos_rect.h - 20 };
	camera.x = pos_rect.x + 70 - camera.w / 2;
	camera.y = pos_rect.y + 70 - camera.h / 2;
}

void Player::update_frame() {
	frame_rect.y = 0;
	frame_tick++;
	if (vel_x != 0 || vel_y != 0)
		frame_rect.y = frame_rect.h * 2;
	if (frame_tick == 3) {
		frame_rect.x += frame_rect.w;
		frame_tick = 0;
	}
	if (frame_rect.x > frame_rect.w * 3)
		frame_rect.x = 0;
}

void Player::update() {
	Player::update_position();
	Player::update_frame();

	SDL_RenderCopyEx(renderer, texture, &frame_rect, &pos_rect, 0, 0, flip);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &collision_rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &camera);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Player::key_down(SDL_Keycode code) {
	if (code == SDLK_d) {
		dir = Direction::Right;
		vel_x = max_vel;
		flip = SDL_FLIP_NONE;
	}
	else if (code == SDLK_a) {
		dir = Direction::Left;
		vel_x = -max_vel;
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (code == SDLK_w) {
		dir = Direction::Up;
		vel_y = -max_vel;
	}
	else if (code == SDLK_s) {
		dir = Direction::Down;
		vel_y = max_vel;
	}
}

void Player::key_up(SDL_Keycode code) {
	if (code == SDLK_d && dir != Direction::Left) {
		vel_x = 0;
	}
	else if (code == SDLK_a && dir != Direction::Right) {
		vel_x = 0;
	}
	else if (code == SDLK_w && dir != Direction::Down) {
		vel_y = 0;
	}
	else if (code == SDLK_s && dir != Direction::Up) {
		vel_y = 0;
	}
}
