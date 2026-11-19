#include "shared/actor_status_ids.h"
#include "dungeon/monster/beldo_large_data.h"

struct ObjectNodeHeader;
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/level.h"

extern void set_or_clear_actor_status_slot(void *, s32, s32);


/* Resets the encounter actor action, sets its transition status, and relinks up to two attached objects. */
void prepare_multi_form_actor_transition(s32 unused0, s32 unused1, s32 unused2, s32 unused3) {
    s32 i;
    u8 *body;
    BeldoScriptControl *control;
    ActorRecord *item;
            /* MATCH: keep the byte-store constant in v0, independent of outgoing a2. */
    s32 one;
            /* MATCH: prepare outgoing a0 before materializing the byte-store constant. */
    u8 *callp;

    i = 0;
    body = NODE_BODY(beldo_actor_nodes);
    control = (BeldoScriptControl *)body;
    *(u16 *)(body + 0x46) &= 0x7FFF;
    system_update_flags &= 0xFFF6;
    reset_timed_sequence_data();
    control->script_active = 0;
    control->field_B0 = 1;
    set_or_clear_actor_status_slot(body, STATUS_SPEED, 1);
    control->field_AE = 2;
    do {
        item = ((ActorRecord **)&dungeon_actor_ring_anchor->unk_AC)[i];
        if (item != 0) {
            insert_node_before_primary_actor(NODE_HEADER(item));
        }
        i++;
    } while (i < 2);
}
