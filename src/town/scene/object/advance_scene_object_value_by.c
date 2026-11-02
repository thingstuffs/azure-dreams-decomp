#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/town_root.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

/* Add 0x20 to the linked object's 32-bit field at offset 8. */
void advance_scene_object_value_by_32(void)
{
    TownPositionState *object_data;
    object_data = ((town_scene_root->position));
    object_data->y = (s32) (object_data->y + 0x20);
}
