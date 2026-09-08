#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800A2B04();
extern M2C_UNK func_800A56E0();
extern s32 D_8008346C;
extern M2C_UNK D_80170E94;


typedef struct S_8017346C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x12];
    s8 unk_AE;
} S_8017346C_0;   /* arg0 in func_8017346C */

typedef struct S_8017346C_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017346C_1;   /* arg2 in func_8017346C */


typedef struct S_8017346C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8017346C_3;   /* arg3 in func_8017346C */

/* Initialize actor motion and transition its handler when action flags are set. */
void func_8017346C(S_8017346C_0 *actor, Rec_D_800E3D7C *motion, S_8017346C_1 *action, S_8017346C_3 *status) {
    u8 phase;

    phase = actor->unk_9B;
    if (phase != 0) {
        if (phase != 1) {
            return;
        }
        goto apply_action;
    }
    if (action->unk_14 & 0x8000) {
        actor->unk_9B = 1U;
        action->unk_14 |= 0x6000;
        return;
    }
    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    actor->unk_9B = (u8) (actor->unk_9B + 1);
apply_action:
    if (((action->unk_04 == 5) && (action->unk_14 & 0x1000)) || (action->unk_14 & 0x8000)) {
        func_800A56E0(0x803);
    }
    if (action->unk_14 & 0xE000) {
        actor->unk_AE = 1;
        status->unk_14 = (s32) (status->unk_14 | 0x40000000);
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, action->unk_24, action->unk_25);
        actor->unk_8C = &D_80170E94;
        D_8008346C = 0;
    }
}
