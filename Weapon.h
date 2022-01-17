#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "Block.h"

class Weapon : public Block
{
public:
    Weapon(int x, int y) : Block()
    {
		background = al_load_bitmap("./background/bgTreasure.jpg");
		
		response = false;
		
		damage = 0;
		
	    worth = 100;
		
		strncpy(class_name, "Transport", 20);
		
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
		discover();
		return response; 
	}
	
	
	void Draw(){
    	if(covered)
    		al_draw_scaled_bitmap(fog, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
		else
    		al_draw_scaled_bitmap(background, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
    };
};
#endif // WEAPON_H_INCLUDED

