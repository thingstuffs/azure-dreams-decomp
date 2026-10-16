#include "common.h"
#include "m2c_compat.h"
M2C_UNK func_800A4ACC(M2C_UNK);                     /* extern */
s32 func_800AB1C0(void *,void *,void *,void *);                                /* extern */
M2C_UNK func_800AD594(M2C_UNK, M2C_UNK);            /* extern */
s32 func_800AD9B4(void *,void *);                /* extern */
extern void func_8017102C(void *,void *,void *,void *);


typedef struct S_801723DC_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *,void *,void *,void *);
    s32 unk_90;
} S_801723DC_0;   /* state in func_801723DC */

void func_801723DC(void *state_arg,void *position,void *render_state,void *entity) {
    S_801723DC_0 *state=state_arg;
    if (func_800AB1C0(state,position,render_state,entity) != 0) {
        func_800AD594(entity, 4);
        func_800A4ACC(entity);
        if ((func_800AD9B4(render_state, entity) << 0x10) > 0) {
            state->unk_8C = func_8017102C;
            state->unk_90 = 0;
        }
    }
}
