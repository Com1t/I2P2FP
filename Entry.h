#ifndef ENTRY_H_INCLUDED
#define ENTRY_H_INCLUDED

#include "Block.h"

class Entry : public Block
{
public:
    Entry(int x, int y) : Block()
    {
    	char buffer[30];
    	sprintf(buffer, "./background/bgEntry%d_%d.jpg", x, y);
		background = al_load_bitmap(buffer);
		
		response = false;
		
		damage = 0;
		
	    worth = 100;
		
		strncpy(class_name, "Entry", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		Draw();
    }

	~Entry(){
		al_destroy_bitmap(background);
	};

	void Draw(){
    	if(covered)
    		al_draw_scaled_bitmap(fog, 0, 0, 1187, 671, 8+pos_y*130, 100+pos_x*74, 130, 74, 0);
		else
    		al_draw_scaled_bitmap(background, 0, 0, 1187, 671, 8+pos_y*130, 100+pos_x*74, 130, 74, 0);
    };
};
#endif //ENTRY_H_INCLUDED

