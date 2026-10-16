#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
void func_80047784(void *, u8, M2C_UNK);         /* extern */
void func_8009C93C(void *, void *, s16, M2C_UNK, s32); /* extern */
s32 func_800A2B5C(void *);                          /* extern */
void func_800C7930(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

extern u16 D_80083462;
extern u8 D_801752B4[8];


typedef struct S_80172180_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172180_0;   /* entity in func_80172180 */

typedef struct S_80172180_1 {
    u8 pad_00[0x8C];
    s32 handler;
    u8 pad_90[0xA];
    s8 action;
    s8 action_tick;
} S_80172180_1;   /* state in func_80172180 */

typedef struct S_80172180_2 {
    u8 pad_00[0x2C];
    M2C_UNK * unk_2C;
} S_80172180_2;   /* render_state in func_80172180 */

/* Finish the pending action, restore animation, and advance its entity countdown. */
void func_80172180(S_80172180_1 *state, M2C_UNK position, S_80172180_2 *render_state, void *entity) {
    ((S_80172180_0 *)entity)->unk_71 = (u8) (((S_80172180_0 *)entity)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930(entity - 0x20, position, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            state->action = 0x11;
            state->handler = 0;
            state->action_tick = 0;
            render_state->unk_2C = D_801752B4;
            func_80047784(render_state, *((((s32) (gameWork.view.viewAngle + ((S_80172180_0 *)entity)->unk_2A + 0x100) >> 9) & 7) + D_801752B4), 0);
            ((S_80172180_0 *)entity)->unk_6D = (u8) (((S_80172180_0 *)entity)->unk_6D - 1);
            func_8009C93C(entity, render_state, ((S_80172180_0 *)entity)->unk_2A, 1, 0);
            ((S_80172180_0 *)entity)->unk_84 = 0x7C;
            ((S_80172180_0 *)entity)->unk_85 = 0;
        }
    }
}
