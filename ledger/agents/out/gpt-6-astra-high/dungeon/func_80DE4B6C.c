#include "common.h"

typedef struct S_8017236C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_8017236C_0;   /* arg3 in func_8017236C */

typedef struct S_8017236C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8017236C_1;   /* arg0 in func_8017236C */



extern s32 func_80047784();
extern s32 func_800A2B5C();
extern s32 func_800A4ACC();
extern s32 func_800C7930();
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80174558;

/* Updates actor flags and starts a directional animation when the actor is ready. */
void func_8017236C(void *actor_state, s32 action_param, void *sprite, void *actor) {
    ((S_8017236C_0 *)actor)->unk_71 = ((S_8017236C_0 *)actor)->unk_71 & 0x7F;
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930((u8 *)actor - 0x20, action_param, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((S_8017236C_1 *)actor_state)->unk_9A = 0x18;
            ((S_8017236C_1 *)actor_state)->unk_8C = 0;
            ((S_8017236C_1 *)actor_state)->unk_9B = 0;
            (*(s32 * *)((u8 *)sprite + 0x2C)) = &D_80174558;
            func_80047784(sprite,
                         *((((D_80083228 + ((S_8017236C_0 *)actor)->unk_2A + 0x100) >> 9) & 7)
                           + (u8 *)&D_80174558),
                         0);
            func_800A4ACC(actor);
            ((S_8017236C_0 *)actor)->unk_6D = ((S_8017236C_0 *)actor)->unk_6D - 1;
        }
    }
}
