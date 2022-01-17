#ifndef TRAP_2_H_INCLUDED
#define TRAP_2_H_INCLUDED

#include "Block.h"

class Trap_2 : public Block
{
public:
    Trap_2(int x, int y) : Block()
    {
		background = al_load_bitmap("./background/bgTrap03.jpg");
		
		response = true;
		
		damage = 10;
		
	    worth = 100;
		
		strncpy(class_name, "Trap_2", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		Draw();
    }
	
	~Trap_2(){
		al_destroy_bitmap(background);
	};

	int touch_response(Bear* player) { 
		printf("TRAP2\n");
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
#endif // TRAP_2_H_INCLUDED

