#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

enum class Direction {
	Up,
	Down,
	Left,
	Right
};

class GameObject {
protected:
	SDL_Renderer* renderer;
	SDL_Rect frame_rect;
	SDL_Texture* texture;
	int texture_width, texture_height;
	SDL_RendererFlip flip;
public:
	SDL_Rect pos_rect;
	GameObject();
	GameObject(SDL_Renderer* rend, char* sprite_sheet_path, int texture_rows, int texture_cols, int start_x, int start_y, int width, int height);
	SDL_Rect collision_rect;
	void update();
	SDL_Rect get_pos();
};

class Player : public GameObject {
private:
	int max_vel;
	int frame_tick;
	Direction dir;
	GameObject weapon;
	int weapon_offset;
public:
	int vel_x, vel_y;
	SDL_Rect camera;

public:
	Player(SDL_Renderer* rend, char* sprite_sheet_path) ;
	void update();
	void key_down(SDL_Keycode code);
	void key_up(SDL_Keycode code);
	void update_position();
private:
	void update_frame();
};

class Tile : public GameObject {
public:
	Tile(SDL_Renderer*, char*, int, int, int, int, int, int, int);
	void reposition(SDL_Rect, int, int);
};

class Child : public GameObject {
	GameObject parent;
public:
	Child(GameObject o) {
		parent = o;
	}
};
