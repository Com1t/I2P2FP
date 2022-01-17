#ifndef BEAR_H_INCLUDED
#define BEAR_H_INCLUDED

enum {NORMAL=0, HAPPY, SHAKE};

class Bear{
public:
	Bear(int max_x, int max_y){
		set_status(this->status);
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
		// Need to debug
		// since the size for HAPPY is different from others
		// it's the only one that can print other image without trouble
		int original_length, original_width, length, width, x_offset, y_offset;
		switch(status){
			case NORMAL:
				original_width = 202;
				original_length = 274;
				width = 50;
				length = 70;
				x_offset = 50;
				y_offset = 100;
				break;
			case HAPPY:
				original_width = 321;
				original_length = 272;
				width = 80;
				length = 70;
				x_offset = 33;
				y_offset = 100;
				break;
			case SHAKE:
				original_width = 244;
				original_length = 285;
				width = 50;
				length = 70;
				x_offset = 50;
				y_offset = 100;
				break;
		}
		
		al_draw_scaled_bitmap(player, 0, 0, original_width, original_length, x_offset+cur_x*130, y_offset+cur_y*74, width, length, flip);
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

	void set_status(int status){
		if(player != nullptr)
			al_destroy_bitmap(player);
		switch(status){
			case NORMAL:
				status = NORMAL;
				player = al_load_bitmap("./role/normal.png");
				break;
			case HAPPY:
				status = HAPPY;
				player = al_load_bitmap("./role/happy.png");
				break;
			case SHAKE:
				status = SHAKE;
				player = al_load_bitmap("./role/shake.png");
				break;
		}
	}
    int setPos_x(int x) { cur_x = x; }
    int setPos_y(int y) { cur_y = y; }
    int getPos_x() { return cur_x; }
    int getPos_y() { return cur_y; }
	
    //int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }

	void weapon_inc() { weapon_count += 3; }
	int getWeaponAmt() { return weapon_count; }

	
	// return die
    bool Subtract_HP(int amount){
		HealthPoint -= amount;
		if(HealthPoint <= 0)
			return 1;
		return 0;
	};

private:
    int direction_count[4];
    int HealthPoint = 100;
    int speed = 1;
    int worth = 10;
    int score = 100;
    char class_name[20];

	int flip = 0;
	
    unsigned int step;
	// player
	ALLEGRO_BITMAP* player= nullptr;

	int status = NORMAL;
	
	int cur_x, cur_y;
    int max_x, max_y;

	int weapon_count = 0;
	
    int counter;
	
    int sprite_pos;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    // path on map
    std::vector<int> path;

};

#endif // BEAR_H_INCLUDED
