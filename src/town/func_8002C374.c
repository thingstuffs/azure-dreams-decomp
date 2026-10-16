/* Relink of matched town/func_8009C3A0; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_80095388();                      /* extern */
extern void func_800C9D40(void *, s32, s32);        /* extern */


/* Advances and refreshes the state, then processes it when its increment is nonnegative. */
void func_800C9AD4(s32 context, EntityRec *state, s32 updateData) {
    state->z.v = (s32) (state->z.v + state->flags14);
    func_80095388(state);
    if (state->flags14 >= 0) {
        func_800C9D40(context, state, updateData);
    }
}
