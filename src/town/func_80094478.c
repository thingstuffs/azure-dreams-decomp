#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


M2C_UNK func_80095C80();
M2C_UNK func_80095094();
s16 func_80095978();
M2C_UNK func_80094378();
M2C_UNK func_80095A94();
M2C_UNK func_80094984();
M2C_UNK func_800941D8();

extern u8 D_800CFCEF;
extern M2C_UNK D_800D00E0;
extern M2C_UNK D_800FE488;


/* Update the entity, handle a large value change, and advance the state countdown. */
void func_80091BD8(Rec_func_80094268_arg0 *state, Rec_D_800E3D7C *entity, M2C_UNK context) {
    s16 sampled_value;
    s16 ticks_left;

    func_80095C80(entity);
    func_80095094(entity);
    sampled_value = func_80095978(entity, &D_800FE488);
    if ((sampled_value - entity->unk_08.at02_s16.v) >= 4) {
        if (D_800CFCEF == 0) {
            func_80094378(state, entity, context);
            return;
        }
    } else if (D_800CFCEF == 0) {
        func_80095A94(entity, sampled_value, &D_800FE488);
    }
    if (state->unk_0A.as_s16 == 0) {
        func_80094984(&D_800D00E0, state, context);
    }
    ticks_left = (u16) state->unk_0A.as_s16 - 1;
    state->unk_0A.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_800941D8(state, entity, context);
    }
}
