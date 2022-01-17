#ifndef TRAP_0_H_INCLUDED
#define TRAP_0_H_INCLUDED

#include "Block.h"

class Treasure : public Block
{
public:
    Treasure(int x, int y) : Block()
    {
		background = al_load_bitmap("./background/bgTreasure.jpg");
		
		response = false;
		
		damage = 0;
		
	    worth = 100;
		
		strncpy(class_name, "Treasure", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		Draw();
    }
	
	~Treasure(){
		al_destroy_bitmap(background);
	};

	void Draw(){
    	if(covered)
    		al_draw_scaled_bitmap(fog, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
		else
    		al_draw_scaled_bitmap(background, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
    };
};
#endif // TRAP_0_H_INCLUDED

