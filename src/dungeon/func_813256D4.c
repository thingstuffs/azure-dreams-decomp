#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 check_actor_floor_trap();            /* extern */
extern M2C_UNK D_8016B778;

typedef struct S_8016CED4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_8016CED4_0;   /* arg0 in finish_linked_actor_motion */


s32 update_linked_actor_motion(void *, void *, void *, void *);
/* Runs the follow-up handler and assigns the shared record data when the check succeeds. */
void finish_linked_actor_motion(S_8016CED4_0 *record, M2C_UNK check_context, M2C_UNK source, M2C_UNK target) {
    if (update_linked_actor_motion(record, check_context, source, target) != 0) {
        check_actor_floor_trap(source, target);
        record->unk_8C = &D_8016B778;
    }
}
