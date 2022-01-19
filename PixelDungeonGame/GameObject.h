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
	SDL_Rect pos_rect;
	SDL_Texture* texture;
	int texture_width, texture_height;
public:
	GameObject();
	GameObject(SDL_Renderer* rend, char* sprite_sheet_path, int texture_rows, int texture_cols, int start_x, int start_y, int width, int height);
	SDL_Rect collision_rect;
	virtual void update() = 0;
};


class Player : public GameObject {
private:
	int max_vel;
	int frame_tick;
	SDL_RendererFlip flip;
	Direction dir;

public:
	std::vector<int> vel{ 0, 0 };
	SDL_Rect camera;

public:
	Player(SDL_Renderer* rend, char* sprite_sheet_path) ;
	void update();
	void keyDown(SDL_Keycode code);
	void keyUp(SDL_Keycode code);
	int get_x_pos();
	int get_y_pos();
	std::vector<int> get_vel();
	std::vector<int> get_pos();
private:
	void update_position();
	void update_frame();
};

class Tile : public GameObject {
public:
	Tile(SDL_Renderer*, char*, int, int, int, int, int, int, int);
	void update();
	void check(SDL_Rect, int, int);
	SDL_Texture* getTexture();
	SDL_Rect* getPos();
	SDL_Rect* getFrame();
	bool show;
};

class Layer {
public:
	std::vector<std::vector<int>> map;
	std::vector<std::vector<Tile>> layer_tiles;
	Layer(SDL_Renderer* renderer, char* file_name, char* image_path);
	void read_file(char* file_name);
	void create_layer(char* image_path, SDL_Renderer* renderer);
	void update(Player player);
};
