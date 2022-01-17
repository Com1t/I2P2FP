#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

#include "Block.h"

class Road : public Block
{
public:
    Road(int x, int y) : Block()
    {
		background = al_load_bitmap("./background/bg00.jpg");
		
		response = false;
		
		damage = 0;
		
	    worth = 100;
		
		strncpy(class_name, "Road", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		Draw();
    }
	
	~Road(){
		al_destroy_bitmap(background);
	};

	void Draw(){
    	if(covered)
    		al_draw_scaled_bitmap(fog, 0, 0, 1187, 671, 8+pos_y*130, 100+pos_x*74, 130, 74, 0);
		else
    		al_draw_scaled_bitmap(background, 0, 0, 1187, 671, 8+pos_y*130, 100+pos_x*74, 130, 74, 0);
    };
};
#endif // ROAD_H_INCLUDED

