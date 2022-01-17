#ifndef BEAR_H_INCLUDED
#define BEAR_H_INCLUDED
#include "Block.h"
class Bear{
public:
	Bear(int max_x, int max_y){
		player = al_load_bitmap("./role/role.png");
		this->max_x = max_x;
		this->max_y = max_y;
		this->cur_x = (rand() % 2)? 0: max_x;
		this->flip = (this->cur_x == 0)? ALLEGRO_FLIP_HORIZONTAL: 0;
		this->cur_y = rand() % max_y;
	};
	~Bear(){
		al_destroy_bitmap(player);
	};

    void Draw(){
		al_draw_scaled_bitmap(player, 0, 0, 202, 274, 60+cur_x*130, 100+cur_y*74, 50, 70, flip);
	};
	
    void Move(int direction){
		switch(direction){
			case LEFT:
				flip = 0;
				cur_x--;
				if(cur_x <= 0)
					cur_x = 0;
				break;
			case RIGHT:
				flip = ALLEGRO_FLIP_HORIZONTAL;
				cur_x++;
				if(cur_x >= max_x)
					cur_x = max_x;
				break;
			case UP:
				cur_y--;
				if(cur_y <= 0)
					cur_y = 0;
				break;
			case DOWN:
				cur_y++;
				if(cur_y >= max_y)
					cur_y = max_y;
				break;
		}
	};
	
    //int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }

    bool Subtract_HP(int);

private:
    int direction_count[4];
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
    char class_name[20];

	int flip = 0;
	
    unsigned int step;
	// player
	ALLEGRO_BITMAP* player;
	
	int cur_x, cur_y;
    int max_x, max_y;
	
    int counter;
	
    int sprite_pos;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    // path on map
    std::vector<int> path;

};

#endif // BEAR_H_INCLUDED
