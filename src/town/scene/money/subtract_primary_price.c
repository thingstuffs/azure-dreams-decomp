#include "common.h"
#include "town/scene/money.h"

typedef struct { u8 pad[0x2D5C]; u32 value; } Counter;
typedef struct { u8 pad[0x38]; Counter *counter; } Work;
extern Work *town_scene_root;
extern u32 town_primary_price;
void subtract_primary_price(void) { town_scene_root->counter->value -= town_primary_price; }
