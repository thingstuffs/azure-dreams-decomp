#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"

M2C_UNK func_80094330();     /* extern */
M2C_UNK func_80094910();                            /* extern */
void func_80094984(void *, void *, s32);           /* extern */
void func_80094C1C();                      /* extern */
void func_80094C74();                      /* extern */
void func_80095388();                      /* extern */
void func_800954F4();                      /* extern */
s16 func_80095978();               /* extern */
void func_80095A94();      /* extern */
void func_80095C80();                      /* extern */
void func_800ABD74();                      /* extern */
extern u8 D_800CFCEF;
extern M2C_UNK D_800D00B8;
extern M2C_UNK D_800FE488;

/* Advance the state counter and update the entity, handling threshold and flag transitions. */
void func_800920F4(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context) {
    s16 threshold;
    u16 counter;

    counter = state->unk_0A.as_u16 + 1;
    state->unk_0A.as_u16 = counter;
    if ((s16) counter == 6) {
        func_80094984(&D_800D00B8, state, context);
    }
    func_80095C80(entity);
    func_80094C1C(state);
    func_80094C74(entity);
    threshold = func_80095978(entity, &D_800FE488);
    if (entity->z.w.i >= threshold) {
        func_80094910();
        func_80095A94(entity, threshold, &D_800FE488);
        func_800ABD74(entity);
        func_80094330(state, entity, context);
        return;
    }
    if (D_800CFCEF != 0) {
        func_80094910();
        entity->flags14 = 0;
        func_800954F4(entity);
        func_80094330(state, entity, context);
        return;
    }
    func_80095388(entity);
}
