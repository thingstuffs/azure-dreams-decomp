#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"

#include "dungeon/actor/state.h"
#include "dungeon/actor.h"

extern u8 actor_motion_resume_address;

   /* entity in advance_actor_movement_to_tile */

typedef struct S_800CAAC8_1 {
    u8 pad_00[0x71];
    u8 unk_71;
    u8 pad_72[0x18];
    s16 unk_8A;
} S_800CAAC8_1;   /* actor in advance_actor_movement_to_tile */

/* Updates the actor and entity counter, then advances the entity or sets its callback. */
void advance_actor_movement_to_tile(ActorRecord *entity_ptr, void *input_arg_1, void *input_arg_2, void *actor_ptr)
{
    void *update_arg_1 = input_arg_1;
    void *update_arg_2 = input_arg_2;
    void *actor = actor_ptr;
    u16 remaining_count;

    if (update_actor_movement_to_tile(entity_ptr, update_arg_1, update_arg_2, actor) != 0) {
        advance_status_timers(actor);
        remaining_count = entity_ptr->unk_B4.halves.high.u - 1;
        entity_ptr->unk_B4.halves.high.u = remaining_count;

        if (((remaining_count << 16) <= 0 || ((*(u16 *)0x80013714) & 8)) &&
            ((S_800CAAC8_1 *)actor)->unk_71 == ((S_800CAAC8_1 *)actor)->unk_8A) {
            set_actor_action_state_eight(entity_ptr, update_arg_1, update_arg_2);
            return;
        }
        entity_ptr->unk_8C.address = &actor_motion_resume_address;
    }

    if (g_dungeon_status.flags & 0x80) {
        entity_ptr->unk_90.parts.high.s = -0x20;
    }
}

