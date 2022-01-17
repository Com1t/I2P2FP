#ifndef TRANSPORT_H_INCLUDED
#define TRANSPORT_H_INCLUDED

#include "Block.h"

class Transport : public Block
{
public:
    Transport(int x, int y) : Block()
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
	
	~Transport(){
		al_destroy_bitmap(background);
	};

	int touch_response(Bear* player) { 
		for(int i = 0; i < 2; i++){
			player->Move(rand()%4);
		}
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
#endif // TRANSPORT_H_INCLUDED
