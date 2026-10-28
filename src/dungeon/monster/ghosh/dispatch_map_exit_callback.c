
struct ObjectNodeHeader;
#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "dungeon/item.h"
#include "engine/graphics.h"

extern void allocate_and_initialize_object(void);
extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *entry);

extern u8 ghosh_frame_set_4[];

/* Resets the Ghosh actor action and animation, updates system flags, and relinks up to two attached
 * objects. */
void dispatch_map_exit_callback(s32 unused0, s32 unused1, s32 unused2, s32 unused3)
{
    s32 i;
    s32 object;
    u8 *base;
    SpriteFrameState *linked;

    allocate_and_initialize_object();
    base = (void *)(ghosh_actor_node + 1);
    linked = ghosh_actor_node->sprite;
    *(u16 *)(base + 0x46) &= 0x7FFF;
    system_update_flags &= 0xFFF6;
    set_monster_data_pointer();
    base[0xB3] = 1;
    base[0xB2] = 0;
    if (*(u8 **)&linked->frameTable != ghosh_frame_set_4) {
        linked->frameTable = ghosh_frame_set_4;
        select_sprite_entry(linked,
            ghosh_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(base + 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    i = 0;
    do {
        object = *(s32 *)(((u8 *)dungeon_actor_ring_anchor) + (i * 4) + 0xAC);
        if (object != 0) {
            clear_entry_flag_and_link_owner(object - 0x20);
        }
        i++;
    } while (i < 2);
}
