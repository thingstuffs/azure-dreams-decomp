#include "common.h"

typedef struct { u8 pad[0x2D5C]; u32 value; } Counter;
typedef struct { u8 pad[0x38]; Counter *counter; } Work;
extern Work *town_scene_root;
extern u32 town_primary_price;
s32 test_town_counter_threshold(void) { return town_scene_root->counter->value >= town_primary_price; }
