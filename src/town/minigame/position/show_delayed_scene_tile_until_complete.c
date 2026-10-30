#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "town/minigame/position.h"

   /* the 0x2 bytes before arg0 in show_delayed_scene_tile_until_complete, addressed as arg0[-1] */


typedef struct S_80020360_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80020360_1;   /* data in show_delayed_scene_tile_until_complete */

typedef struct S_80020360_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80020360_2;   /* (void *)page in show_delayed_scene_tile_until_complete */


/* Advances the countdown state, then sets object and global flags when the status bit is set. */
void show_delayed_scene_tile_until_complete(SceneTileObject *object)
{
    s16 state;
    S_80020360_1 *status_data;
    u16 ticks_left;
    u16 flags;
    u16 next_state;
    u32 page;

    state = object->state.s;
    status_data = object->linked;
    switch (state) {
    case 0:
        ticks_left = object->delay - 1;
        object->delay = ticks_left;
        if ((ticks_left << 16) > 0) {
            return;
        }
        flags = object->flags;
        next_state = object->state.u;
        flags &= 0xFFFD;
        next_state++;
        object->flags = flags;
        object->state.u = next_state;
        break;
    case 1:
        if (status_data->unk_2A & 1) {
            page = 0x80080000;
            ((ObjectStatusPrefix16 *)object)[-1].flags |= 0x8000;
            ((S_80020360_2 *)((void *)page))->unk_14A0 |= 0x8000;
        }
        break;
    }
}
