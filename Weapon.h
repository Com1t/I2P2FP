#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED
#include <iostream>
#include "Block.h"

class Weapon : public Block
{
public:
    Weapon(int x, int y) : Block()
    {
		background = al_load_bitmap("./background/bgTreasure.jpg");
		weapon_it_self = al_load_bitmap("./background/weapon.png");
		
		response = false;
		
		damage = 0;

		acquired = 0;
		
	    worth = 100;
		
		strncpy(class_name, "Weapon", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		Draw();
    }
	
	~Weapon(){
		al_destroy_bitmap(background);
	};

	int touch_response(Bear* player) { 
		player->set_status(HAPPY);
		if(acquired == 0){
			acquired = 1;
			std::cout << "weapon++\n";
			player->weapon_inc();
		}
		discover();
		return response; 
	}
	
	
	void Draw(){
    	if(covered)
    		al_draw_scaled_bitmap(fog, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
		else{
    		al_draw_scaled_bitmap(background, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
    		al_draw_scaled_bitmap(weapon_it_self, 0, 0, 512, 442, 8+pos_y*130, 107+pos_x*74, 75, 66, 0);
		}
    };
private:
	ALLEGRO_BITMAP* weapon_it_self;
	int acquired = 0;
};
#endif // WEAPON_H_INCLUDED

