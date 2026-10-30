
struct ObjectNodeHeader;
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#include "engine/script.h"

extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *entry);
extern u8 restore_actor_script[];
extern u8 *beldo_actor_nodes[3];

/* Reset state flags, relink the two attached objects, and submit the global buffer. */
void reset_multi_form_actor_state(s32 reset_arg_a, s32 reset_arg_b, s32 reset_arg_c, s32 reset_arg_d) {
    s32 object_index;
    s32 object;
    u8 *state;

    object_index = 0;
    state = beldo_actor_nodes[0] + 0x20;
    *(u16 *)(state + 0x46) &= 0x7FFF;
    system_update_flags &= 0xFFF6;
    set_monster_data_pointer();
    state[0xAF] = 0;
    do {
        object = *(s32 *)((object_index * 4) + ((u8 *)dungeon_actor_ring_anchor) + 0xAC);
        if (object != 0) {
            clear_entry_flag_and_link_owner(object - 0x20);
        }
        object_index++;
    } while (object_index < 2);
    call_script(restore_actor_script);
}
