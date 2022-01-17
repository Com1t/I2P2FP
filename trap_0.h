#ifndef TRAP_0_H_INCLUDED
#define TRAP_0_H_INCLUDED

#include "Block.h"

class Trap_0 : public Block
{
public:
    Trap_0(int x, int y) : Block()
    {
		background = al_load_bitmap("./background/bgTrap01.jpg");
		
		response = true;
		
		damage = 10;
		
	    worth = 100;
		
		strncpy(class_name, "Trap_0", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		Draw();
    }
	
	~Trap_0(){
		al_destroy_bitmap(background);
	};

	int touch_response(Bear* player) { 
		printf("TRAP0\n");
		player->set_status(SHAKE);
		discover();
		return player->Subtract_HP(damage);
	}
	

	void Draw(){
    	if(covered)
    		al_draw_scaled_bitmap(fog, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
		else
    		al_draw_scaled_bitmap(background, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
    };
};
#endif // TRAP_0_H_INCLUDED

