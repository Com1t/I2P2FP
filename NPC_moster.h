#ifndef NPC_MONSTER_H_INCLUDED
#define NPC_MONSTER_H_INCLUDED

#include "Block.h"

class NPCmonster : public Block
{
public:
    NPCmonster(int x, int y) : Block()
    {
		background = al_load_bitmap("./background/bgTreasure.jpg");
		weapon_it_self = al_load_bitmap("./role/NPC.png");
		
		response = false;
		
		damage = 0;

		acquired = 0;
		
	    worth = 100;
		
		strncpy(class_name, "NPCmonster", 20);
		
	    // position
	    pos_x = x;
		pos_y = y;

		Draw();
    }
	
	~NPCmonster(){
		al_destroy_bitmap(background);
	};

	int touch_response(Bear* player) { 
		player->set_status(SHAKE);
		if(player->getWeaponAmt() > 0){
			// NOTE: trigger pokemon
			// remember to set the response here
		}
		else{
			response = 1;
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
#endif // NPC_MONSTER_H_INCLUDED


