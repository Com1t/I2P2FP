#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>
#include "algif5/src/algif.h"

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 1187
#define window_height 671
#define field_width 1000
#define field_height 671

#define Num_TowerType 5
#define Num_MonsterType 4
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

#define Num_Road_Row 6
#define Num_Road_Col 9


extern int TowerRadius[];
extern char TowerClass[][20];
extern char RoleStatus[][20];
extern int TowerWidth[];
extern int TowerHeight[];

enum {ARCANE = 0, ARCHER, CANON, POISON, STORM};
enum {WOLF = 0, WOLFKNIGHT, DEMONNIJIA, CAVEMAN};

#endif // GLOBAL_H_INCLUDED
