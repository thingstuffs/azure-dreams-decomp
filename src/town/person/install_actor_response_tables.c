#include "common.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"

/* extern */
extern M2C_UNK D_800D55A0;
extern M2C_UNK D_800D55A8;
extern M2C_UNK D_800D55D0;
extern M2C_UNK D_800D55D4;

   /* arg2 in install_actor_response_tables */

typedef struct S_800C5D38_1 {
    u8 pad_00[0x58];
    s32 * unk_58;
    s32 * unk_5C;
    u8 pad_60[0x1C];
    s32 * unk_7C;
    s32 * unk_80;
} S_800C5D38_1;   /* arg0 in install_actor_response_tables */


void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Install the actor's response tables and process input when either masked flag is set. */
void install_actor_response_tables(S_800C5D38_1 *actor, s32 context, SpriteFlagsView *input) {
    if (input->flags & 0x6000) {
        actor->unk_58 = &D_800D55D0;
        actor->unk_5C = &D_800D55D4;
        actor->unk_7C = &D_800D55A0;
        actor->unk_80 = &D_800D55A8;
        apply_object_setup_and_update(actor, context, input);
    }
}
