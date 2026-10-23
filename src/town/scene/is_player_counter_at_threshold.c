#include "common.h"
#include "shared/record_ptrs.h"
/* True when the scene state's counter has reached the -64 threshold. */
s32 is_player_counter_at_threshold(void)
{
    s8 *slot;
    slot = ((s8 *) town_scene_root) + 0x1C;
    return ((u32) (*((u32 *) (((s8 *) (*((void **) slot))) + 0xC)))) >= ((u32) (s32) - 64);
}
