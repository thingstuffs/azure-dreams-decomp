
struct ObjectNodeHeader;
#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#include "engine/script.h"
#include "dungeon/system/restore_actor_script_data.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/level.h"


/* Reset state flags, relink the two attached objects, and submit the global buffer. */
void reset_multi_form_actor_state(s32 reset_arg_a, s32 reset_arg_b, s32 reset_arg_c, s32 reset_arg_d) {
    s32 object_index;
    ActorRecord *object;
    u8 *body;
    BeldoScriptControl *control;

    object_index = 0;
    body = NODE_BODY(beldo_actor_nodes);
    control = (BeldoScriptControl *)body;
    *(u16 *)(body + 0x46) &= 0x7FFF;
    system_update_flags &= 0xFFF6;
    reset_timed_sequence_data();
    control->script_active = 0;
    do {
        object = ((ActorRecord **)&dungeon_actor_ring_anchor->unk_AC)[object_index];
        if (object != 0) {
            insert_node_before_primary_actor(NODE_HEADER(object));
        }
        object_index++;
    } while (object_index < 2);
    call_script(restore_actor_script);
}
