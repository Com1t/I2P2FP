#ifndef TRAP_1_H_INCLUDED
#define TRAP_1_H_INCLUDED

#include "Block.h"

class Trap_1 : public Block
{
public:
    Trap_1(int x, int y) : Block()
    {
		background = al_load_bitmap("./background/bgTrap02.jpg");
		
		response = true;
		
		damage = 10;
		
	    worth = 100;
		
		strncpy(class_name, "Trap_1", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		Draw();
    }
	
	~Trap_1(){
		al_destroy_bitmap(background);
	};

	int touch_response(Bear* player) { 
		printf("TRAP1\n");
		player->set_status(SHAKE);
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
#endif // TRAP_0_H_INCLUDED

