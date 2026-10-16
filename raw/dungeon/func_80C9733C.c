#include "common.h"
#include "m2c_compat.h"
s32 func_800A2BDC(void *);                          /* extern */
extern M2C_UNK D_80083460;
extern s16 D_800DCF5E;


typedef struct S_80174B3C_0 {
    u8 pad_00[0x6D];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80174B3C_0;   /* entity in func_80174B3C */

typedef struct S_80174B3C_1 {
    u8 pad_00[0x8C];
    void (*handler)();
    u8 pad_90[0xA];
    s8 action;
    s8 action_tick;
} S_80174B3C_1;   /* state in func_80174B3C */

typedef struct S_80174B3C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80174B3C_2;   /* &D_80083460 in func_80174B3C */

/* Enter action 23, then release the state handler when the entity action completes. */
void func_80174B3C(S_80174B3C_1 *state, void *unused_position, void *unused_render_state, S_80174B3C_0 *entity) {
    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    state->handler = func_80174B3C;
    state->action = 0x17;
    state->action_tick = 0;
    entity->unk_6D = 0;
    if (!(((S_80174B3C_2 *)(&D_80083460))->unk_02 & 0x2000) && ((func_800A2BDC(entity) << 0x10) == 0)) {
        state->handler = NULL;
        state->action = 0x17;
        state->action_tick = 0;
        D_800DCF5E = 0;
        ((S_80174B3C_2 *)(&D_80083460))->unk_0A = (u16) (((S_80174B3C_2 *)(&D_80083460))->unk_0A + 1);
    }
}
