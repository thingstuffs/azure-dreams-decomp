#include "common.h"
#include "dungeon/actor.h"
#include "m2c_compat.h"

/* extern */
            /* extern */
extern M2C_UNK ghosh_action_resume_address;

typedef struct S_8016CED4_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
} S_8016CED4_0;   /* arg0 in finish_linked_actor_motion */


s32 update_linked_actor_motion(void *, void *, void *, void *);
/* Runs the follow-up handler and assigns the shared record data when the check succeeds. */
void finish_linked_actor_motion(S_8016CED4_0 *record, s32 check_context, s32 source, s32 target) {
    if (update_linked_actor_motion(record, check_context, source, target) != 0) {
        check_actor_floor_trap(source, target);
        record->unk_8C = &ghosh_action_resume_address;
    }
}
