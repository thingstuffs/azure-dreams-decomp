#include "common.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"

M2C_UNK func_8008F294();             /* extern */
M2C_UNK func_8008F664();             /* extern */
M2C_UNK func_8009539C();                 /* extern */
M2C_UNK func_8009C148(); /* extern */
extern s32 D_800D0428;


/* Update motion toward the shared target and advance state when the countdown expires. */
void func_8009B828(Rec_func_8009B828_arg0 *state, M2C_UNK context, EntityRec *motion, M2C_UNK transition_arg) {
    s32 position;
    u16 ticks_left;

    position = motion->z.v;
    motion->flags14 = (s32) ((s32) ((D_80083780.z.v + D_800D0428) - position) / 2);
    func_8009539C(motion, position);
    func_8008F294(context, motion);
    func_8008F664(context, motion);
    ticks_left = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_8009C148(state, context, motion, transition_arg);
    }
}
