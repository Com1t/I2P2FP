#include "GameWindow.h"
#include "Bear.h"
#include "Block.h"
#include "Entry.h"
#include "Road.h"
#include "treasure.h"
#include "fake_treasure.h"
#include "trap_0.h"
#include "trap_1.h"
#include "trap_2.h"
#include "Weapon.h"
#include "Transport.h"
#include "NPC_moster.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))


float Attack::volume = 1.0;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

bool compare(Tower *t1, Tower *t2)
{
    return (t1->getY() <= t2->getY());
}

void
GameWindow::game_init()
{
    printf("Game_init be called...\n");
    char buffer[50];
	
	// initialize character
	player = new Bear(8, 5);
    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./background/default0.jpg");
	
    for(int i = 0;i < Num_Road_Row;i++){
		for(int j = 0;j < Num_Road_Col;j++)
        {
        	road[i][j] = nullptr;
        }
    }
	/*
	if(!boss_level){
		int deploy_amt = 5;
	    for(int i = 0;i < Num_Road_Row;i++){
			int deploy_col = rand() % (Num_Road_Col - 2) + 1;
			for(int j = 0;j < Num_Road_Col;j++)
	        {
	            if(j == 0 || j == Num_Road_Col - 1)
	            {
	                road[i][j] = new Entry(i, j);
	            }
				else if(j == deploy_col && deploy_amt == 0){
					road[i][j] = new Treasure(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col && deploy_amt == 1){
					road[i][j] = new Trap_0(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col && deploy_amt == 2){
					road[i][j] = new Trap_1(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col && deploy_amt == 3){
					road[i][j] = new Trap_2(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col && deploy_amt >= 4){
					road[i][j] = new FakeTreasure(i, j);
					deploy_amt--;
				}
	            else
	            {
	                road[i][j] = new Road(i, j);
	            }
	        }
	    }
	}
	else{
		int deploy_amt = 8;
		int trans_out_x;
		int trans_out_y;
	    for(int i = 0;i < Num_Road_Row;i++){
			int deploy_col_1 = rand() % (Num_Road_Col - 2) + 1;
			int deploy_col_2 = rand() % (Num_Road_Col - 2) + 1;
			while(deploy_col_1 == deploy_col_2)
				deploy_col_2 = rand() % (Num_Road_Col - 2) + 1;
			
			for(int j = 0;j < Num_Road_Col;j++)
	        {
	            if(j == 0 || j == Num_Road_Col - 1)
	            {
	                road[i][j] = new Entry(i, j);
	            }
				/*else if(j == deploy_col_1 && deploy_amt == 0){
					road[i][j] = new Treasure(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_2 && deploy_amt == 1){
					road[i][j] = new Treasure(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_1 && deploy_amt == 2){
					road[i][j] = new Treasure(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_2 && deploy_amt == 3){
					road[i][j] = new Trap_2(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_1 && deploy_amt == 4){
					road[i][j] = new NPCmonster(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_1 && deploy_amt == 5){
					road[i][j] = new NPCmonster(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_2 && deploy_amt == 6){
					road[i][j] = new Weapon(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_1 && deploy_amt > 6){
					int trans_in_x = i;
					int trans_in_y = j;
				
					trans_out_y = rand() % (Num_Road_Row);

					trans_out_x = rand() % (Num_Road_Col - 2) + 1;
					while(trans_in_y == trans_out_x)
						trans_out_x = rand() % (Num_Road_Col - 2) + 1;
					
					road[i][j] = new Transport(i, j, trans_out_y, trans_out_x, 0);
//					road[trans_out_y][trans_out_x] = new Transport(trans_out_x, trans_out_y, i, j, 1);
					deploy_amt-=1;
				}
	            else
	            {
	                road[i][j] = new Road(i, j);
	            }
	        }
    	}
	}*/

    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sample = al_load_sample("growl.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("BackgroundMusic.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    level = new LEVEL(1);
    menu = new Menu();
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

bool
GameWindow::isOnRoad()
{
    int startx, starty;
    int widthOfTower;

    widthOfTower = TowerWidth[selectedTower];

    for(int i=0; i < NumOfGrid; i++)
    {
        startx = (i % 15) * 40;
        starty = (i / 15) * 40;

        if(level->isRoad(i)) {
            if((mouse_x + (widthOfTower/2) < startx) || (mouse_x - (widthOfTower/2) > startx + grid_width))
                continue;
            else if((mouse_y + (widthOfTower/2) < starty) || (mouse_y > starty + grid_height))
                continue;
            else
                return true;
        }
    }
    return false;
}

Tower*
GameWindow::create_tower(int type)
{
    Tower *t = NULL;

    if(isOnRoad())
        return t;

    switch(type)
    {
    case ARCANE:
        t = new Arcane(mouse_x, mouse_y);
        break;
    case ARCHER:
        t = new Archer(mouse_x, mouse_y);
        break;
    case CANON:
        t = new Canon(mouse_x, mouse_y);
        break;
    case POISON:
        t = new Poison(mouse_x, mouse_y);
        break;
    case STORM:
        t = new Storm(mouse_x, mouse_y);
        break;
    default:
        break;
    }

    menu->Change_Coin(menu->getTowerCoin(type));

    return t;
}

Monster*
GameWindow::create_monster()
{
    Monster *m = NULL;

    if(level->MonsterNum[WOLF])
    {
        level->MonsterNum[WOLF]--;
        m = new Wolf(level->ReturnPath());
    }
    else if(level->MonsterNum[WOLFKNIGHT])
    {
        level->MonsterNum[WOLFKNIGHT]--;
        m = new WolfKnight(level->ReturnPath());
    }
    else if(level->MonsterNum[DEMONNIJIA])
    {
        level->MonsterNum[DEMONNIJIA]--;
        m = new DemonNijia(level->ReturnPath());
    }
    else if(level->MonsterNum[CAVEMAN])
    {
        level->MonsterNum[CAVEMAN]--;
        m = new CaveMan(level->ReturnPath());
    }
    else
    {
        al_stop_timer(monster_pro);
    }

    return m;
}

void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    monster_pro = al_create_timer(1.0 / FPS);

    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));

    game_init();
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    draw_running_map();

    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
    al_start_timer(monster_pro);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{
    unsigned int i, j;
    std::list<Tower*>::iterator it;

    /*TODO:*/
    /*Allow towers to detect if monster enters its range*/
    /*Hint: Tower::DetectAttack*/
    for(auto _tower : towerSet)
            for(auto _monster : monsterSet)
                if(_tower->DetectAttack(_monster)) break;

    // update every monster
    // check if it is destroyed or reaches end point
    for(i=0; i < monsterSet.size(); i++)
    {
        bool isDestroyed = false, isReachEnd = false;

        /*TODO:*/
        /*1. For each tower, traverse its attack set*/
        /*2. If the monster collide with any attack, reduce the HP of the monster*/
        /*3. Remember to set isDestroyed to "true" if monster is killed*/
        /*Hint: Tower::TriggerAttack*/

        for(auto _tower : towerSet)
            isDestroyed = _tower->TriggerAttack(monsterSet[i]);

        isReachEnd = monsterSet[i]->Move();

        if(isDestroyed)
        {
            Monster *m = monsterSet[i];

            menu->Change_Coin(m->getWorth());
            menu->Gain_Score(m->getScore());
            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;

        }
        else if(isReachEnd)
        {
            Monster *m = monsterSet[i];

            if(menu->Subtract_HP())
                return GAME_EXIT;

            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;
        }
    }

    /*TODO:*/
    /*1. Update the attack set of each tower*/
    /*Hint: Tower::UpdateAttack*/
    for(auto _tower : towerSet)
            _tower->UpdateAttack();

    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{
    printf("Game_reset be called...\n");
    char buffer[50];
	al_stop_timer(timer);
	
	// initialize character
	delete player;
	player = new Bear(8, 5);
	found_treasure_amt = 0;

    for(int i = 0;i < Num_Road_Row;i++)
        for(int j = 0;j < Num_Road_Col;j++)
            delete road[i][j];

	if(!boss_level){
		int deploy_amt = 5;
	    for(int i = 0;i < Num_Road_Row;i++){
			int deploy_col = rand() % (Num_Road_Col - 2) + 1;
			for(int j = 0;j < Num_Road_Col;j++)
	        {
	            if(j == 0 || j == Num_Road_Col - 1)
	            {
	                road[i][j] = new Entry(i, j);
	            }
				else if(j == deploy_col && deploy_amt == 0){
					road[i][j] = new Treasure(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col && deploy_amt == 1){
					road[i][j] = new Trap_0(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col && deploy_amt == 2){
					road[i][j] = new Trap_1(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col && deploy_amt == 3){
					road[i][j] = new Trap_2(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col && deploy_amt >= 4){
					road[i][j] = new FakeTreasure(i, j);
					deploy_amt--;
				}
	            else
	            {
	                road[i][j] = new Road(i, j);
	            }
	        }
	    }
	}
	else{
		int deploy_amt = 8;
		int trans_out_x;
		int trans_out_y;
	    for(int i = 0;i < Num_Road_Row;i++){
			int deploy_col_1 = rand() % (Num_Road_Col - 2) + 1;
			int deploy_col_2 = rand() % (Num_Road_Col - 2) + 1;
			while(deploy_col_1 == deploy_col_2)
				deploy_col_2 = rand() % (Num_Road_Col - 2) + 1;
			
			for(int j = 0;j < Num_Road_Col;j++)
	        {
	            if(j == 0 || j == Num_Road_Col - 1)
	            {
	                road[i][j] = new Entry(i, j);
	            }
				else if(j == deploy_col_1 && deploy_amt == 0){
					road[i][j] = new NPCmonster(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_2 && deploy_amt == 1){
					road[i][j] = new Weapon(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_1 && deploy_amt == 2){
					road[i][j] = new NPCmonster(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_2 && deploy_amt == 3){
					road[i][j] = new Trap_2(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_1 && deploy_amt == 4){
					road[i][j] = new Treasure(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_2 && deploy_amt == 5){
					road[i][j] = new Treasure(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_2 && deploy_amt == 6){
					road[i][j] = new Treasure(i, j);
					deploy_amt--;
				}
				else if(j == deploy_col_1 && deploy_amt > 6){
					int trans_in_x = i;
					int trans_in_y = j;
				
					trans_out_y = rand() % (Num_Road_Row) - 1;
					
					trans_out_x = rand() % (Num_Road_Col - 2) + 1;
					while(trans_in_x == trans_out_x)
						trans_out_x = rand() % (Num_Road_Col - 2) + 1;
					
					road[i][j] = new Transport(i, j, trans_out_x, trans_out_y, 0);
					deploy_amt-=1;
				}
	            else
	            {
	                road[i][j] = new Road(i, j);
	            }
	        }
	    }
	}

/*
    // reset game and begin
    for(auto&& child : towerSet) {
        delete child;
    }
    towerSet.clear();
    monsterSet.clear();


    selectedTower = -1;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    Monster_Pro_Count = 0;
    mute = false;
    redraw = false;
    menu->Reset();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(monster_pro);*/al_start_timer(timer);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(monster_pro);

    for(int i = 0;i < Num_Road_Row;i++)
        for(int j = 0;j < Num_Road_Col;j++)
            delete road[i][j];

    for(int i=0;i<5; i++)
        al_destroy_bitmap(tower[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);

    delete level;
    delete menu;
}

int
GameWindow::process_event()
{
    int i;
    int instruction = GAME_CONTINUE;

    // offset for pause window
    int offsetX = field_width/2 - 200;
    int offsetY = field_height/2 - 200;

    al_wait_for_event(event_queue, &event);
    redraw = false;
    int pause = 0;
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;

            if(monsterSet.size() == 0 && !al_get_timer_started(monster_pro))
            {
                al_stop_timer(timer);
                return GAME_EXIT;
            }

        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
		printf("Keydown detected\n");
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_P:
                /*TODO: handle pause event here*/
                if(al_get_timer_started(timer)) al_stop_timer(timer), pause = 1;
                else    al_start_timer(timer), pause = 0;
                break;
            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_LEFT:
				printf("ALLEGRO_KEY_LEFT");
				player->Move(LEFT);
                break;
            case ALLEGRO_KEY_RIGHT:
				printf("ALLEGRO_KEY_RIGHT");
				player->Move(RIGHT);
                break;
            case ALLEGRO_KEY_UP:
				printf("ALLEGRO_KEY_UP");
				player->Move(UP);
                break;
            case ALLEGRO_KEY_DOWN:
				printf("ALLEGRO_KEY_DOWN");
				player->Move(DOWN);
                break;
        }
		for(int i = 0; i < Num_Road_Row; i++){
			for(int j = 0; j < Num_Road_Col; j++){
				
				if(road[i][j]->touched(player->getPos_y(), player->getPos_x())){
					
					int ret = road[i][j]->touch_response(player);
					cout << road[i][j]->getName() << "\n";
				
					if(ret == 0){
						if(strcmp(road[i][j]->getName(), "Treasure") == 0){
							// dynamic cast for parent point to child method
							Treasure *treasure = dynamic_cast<Treasure*>(road[i][j]);
							if(treasure->getFound() == 0){
								found_treasure_amt++;
								treasure->setFound(1);
								// find one entry as exit point
								int x = (rand() % 2)? Num_Road_Col - 1: 0;
								int y = rand() % Num_Road_Row;
								Entry *temp = dynamic_cast<Entry*>(road[y][x]);
								temp->setExit();
							}
						}
						else if(strcmp(road[i][j]->getName(), "Transport") == 0){
							// dynamic cast for parent point to child method
							Transport *transport = dynamic_cast<Transport*>(road[i][j]);
							if(transport->getInOut() == 0){
								road[transport->get_dest_y()][transport->get_dest_x()]->touch_response(player);
							}
						}
					}
					
					else if(ret == 1){
						// Game over
						game_reset();
					}
					
					else{
						// Go to next level
						if(boss_level && found_treasure_amt == 3)
							game_reset();
						else if(boss_level++ == 0)
							game_reset();
					}
				}
			}
		}
    }

    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_running_map()
{
    //printf("draw_running_map...\n");
    unsigned int i, j;

    al_clear_to_color(al_map_rgba(100, 100, 100, 128));
    al_draw_bitmap(background, 0, 0, 0);
	
    // render the background, entry point and the roads
    for(int i = 0;i < Num_Road_Row;i++)
        for(int j = 0;j < Num_Road_Col;j++)
            road[i][j]->Draw();
	
	player->Draw();

    for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->Draw();

    if(selectedTower != -1)
        Tower::SelectedTower(mouse_x, mouse_y, selectedTower);

    al_draw_filled_rectangle(0, 550, window_width, window_height, al_map_rgba(100, 100, 100, 128));

    menu->Draw();

    al_flip_display();
}
