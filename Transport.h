#ifndef TRANSPORT_H_INCLUDED
#define TRANSPORT_H_INCLUDED

#include "Block.h"

class Transport : public Block
{
public:
    Transport(int x, int y, int dest_x, int dest_y, int in_out) : Block()
    {
    	this->in_out = in_out; // in = 0, out = 1
    	if(in_out)
			background = al_load_bitmap("./background/bgTransmitIn.jpg");
		else
			background = al_load_bitmap("./background/bgTransmitOut.jpg");
		
		response = false;
		
		damage = 0;
		
	    worth = 100;
		
		strncpy(class_name, "Transport", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		this->dest_x = dest_x;
		this->dest_y = dest_y;

		Draw();
    }
	
	~Transport(){
		al_destroy_bitmap(background);
	};

	int touch_response(Bear* player) { 
		if(in_out == 0){
			player->setPos_x(dest_x);
			player->setPos_y(dest_y);
		}
		discover();
		return response; 
	}
	int getInOut() {     return in_out; }
	int get_dest_x() { return dest_x; }
	int get_dest_y() { return dest_y; }
	
	void Draw(){
    	if(covered)
    		al_draw_scaled_bitmap(fog, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
		else
    		al_draw_scaled_bitmap(background, 0, 0, 1187, 671, 8+pos_y*130, 107+pos_x*74, 130, 74, 0);
    };
private:
	int in_out;
	int dest_x, dest_y;
};
#endif // TRANSPORT_H_INCLUDED
