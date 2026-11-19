
struct ObjectNodeHeader;
#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/level.h"


typedef struct S_8016ED98_1 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_8016ED98_1;   /* object in finish_multi_form_actor_sequence */

typedef struct S_8016ED98_2 {
    u8 pad_00[0xAC];
    u8 *unk_AC;
} S_8016ED98_2;   /* D_800E3D7C + i * 4 in finish_multi_form_actor_sequence */


extern void func_8016ECFC(void);

extern u16 system_update_flags[];

/* End the floor: clear the visible flags, run the two teardown passes and release both resident objects. */
void finish_multi_form_actor_sequence(void)
{
    s32 i;
    u8 *value;
    S_8016ED98_1 *object;

    object = NODE_BODY(beldo_actor_nodes);
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    object->unk_46 &= 0x7FFF;
    system_update_flags[0] &= 0xFFF6;
    reset_timed_sequence_data();
    func_8016ECFC();
    i = 0;
    do {
        value = ((S_8016ED98_2 *)(((u8 *)dungeon_actor_ring_anchor) + i * 4))->unk_AC;
        if (value != 0) {
            insert_node_before_primary_actor((void *)(value - 0x20));
        }
        i++;
    } while (i < 2);
}
