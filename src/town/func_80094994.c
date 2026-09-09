#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80094330();     /* extern */
M2C_UNK func_80094910();                            /* extern */
M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80094C74();                      /* extern */
M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_800ABD74();                      /* extern */
extern u8 D_800CFCEF;
extern M2C_UNK D_800D00B8;
extern M2C_UNK D_800FE488;

/* Advance the state counter and update the entity, handling threshold and flag transitions. */
void func_800920F4(Rec_func_80094268_arg0 *state, Rec_D_800E3D7C *entity, M2C_UNK context) {
    s16 threshold;
    u16 counter;

    counter = state->unk_0A.as_u16 + 1;
    state->unk_0A.as_u16 = counter;
    if ((s16) counter == 6) {
        func_80094984(&D_800D00B8, state);
    }
    func_80095C80(entity);
    func_80094C1C(state);
    func_80094C74(entity);
    threshold = func_80095978(entity, &D_800FE488);
    if (entity->unk_08.at02_s16.v >= threshold) {
        func_80094910();
        func_80095A94(entity, threshold, &D_800FE488);
        func_800ABD74(entity);
        goto shared_tail;
    }
    if (D_800CFCEF != 0) {
        func_80094910();
        entity->unk_14.as_s32 = 0;
        func_800954F4(entity);
shared_tail:
        func_80094330(state, entity, context);
        return;
    }
    func_80095388(entity);
}
