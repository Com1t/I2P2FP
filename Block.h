#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "global.h"

class Block {
public:
	Block(){};
    virtual ~Block(){};

    // Draw background
    virtual void Draw() = 0;
	
    // touched animation
    // void touched_Animation();

	// discover, literally, dis"cover"
	void discover() { covered = 0; }

    // functions that return informations of monster
    // return true: Kill character
    // return false: Not kill character
    int touch_response() { return response; }
	
    int getWorth() { return worth; }

	// special case:
	// only subtracts HP
	void Subtract_HP(int &HP){
    	HP -= damage;
    };

protected:
	int covered = 0;
	ALLEGRO_BITMAP* fog = al_load_bitmap("./background/fog.jpg");
	ALLEGRO_BITMAP* background;
	// animation pointer
	// (To Be Modified)
    std::vector<ALLEGRO_BITMAP*> animation;

	int response;
	
	int damage;
	
    int worth;
	
    char class_name[20];
	
    // position
    int pos_x, pos_y;
};


#endif // MONSTER_H_INCLUDED
