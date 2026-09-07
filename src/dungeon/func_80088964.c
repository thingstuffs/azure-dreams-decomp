#include "common.h"
#include "m2c_compat.h"

struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern void *D_8008ACDC[];
extern s32 D_80083460[3];
extern volatile s16 D_80013714[8];
extern u8 D_800E3CD0[9];
extern u16 D_80082E76;
M2C_UNK func_8008E1E4();
M2C_UNK func_8008E250();
M2C_UNK func_800945E8();
M2C_UNK func_800948BC();
M2C_UNK func_80099844();
extern M2C_UNK D_800E0672;


typedef struct S_8008E0C4_0 {
    u8 pad_00[0x8C];
    void ** unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
} S_8008E0C4_0;   /* arg0 in func_8008E0C4 */

typedef struct S_8008E0C4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8008E0C4_1;   /* arg2 in func_8008E0C4 */

typedef struct S_8008E0C4_2 {
    u8 unk_00;
} S_8008E0C4_2;   /* D_800E3CD0 in func_8008E0C4 */

typedef struct S_8008E0C4_3 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
    s16 unk_2A;
} S_8008E0C4_3;   /* arg3 in func_8008E0C4 */

typedef struct S_8008E0C4_4 {
    u8 pad_00[0xC8];
    u16 unk_C8;
} S_8008E0C4_4;   /* global_base in func_8008E0C4 */

typedef struct S_8008E0C4_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008E0C4_5;   /* counter_base in func_8008E0C4 */

void func_8008E0C4(S_8008E0C4_0 *arg0, void *unused, S_8008E0C4_1 *arg2, S_8008E0C4_3 *arg3) {
    S_8008E0C4_4 *global_base;
    S_8008E0C4_5 *counter_base;
    u16 temp_v0;
    s32 temp_v1;

    global_base = &D_80083160;
    temp_v1 = arg0->unk_9B.n;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        func_8008E250(arg3, global_base);
        return;
    }
    ASM_KEEP(temp_v1);   /* MATCH pin: retail delay-slot fill depends on it */
    if (temp_v1 == 2) {
        return;
    }
    if (temp_v1 == 0x10) {
        goto state_16;
    }
    func_8008E250(arg3, global_base);
    return;

state_0:
    if (arg2->unk_14 & 0xE000) {
        func_80099844(arg3, &D_800E0672);
        (void) arg0->unk_9B.v;
        temp_v1 = 0x80;
        arg0->unk_96 = temp_v1;
        func_8008E1E4();
    }
    return;

state_1:
    temp_v0 = arg0->unk_96 - 1;
    arg0->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        return;
    }
    ASM_KEEP(temp_v1);   /* MATCH pin: retail delay-slot fill depends on it */
    if ((u16) *D_80013714 & 4) {
        if (((S_8008E0C4_2 *)D_800E3CD0)->unk_00 == 0) {
            ((S_8008E0C4_2 *)D_800E3CD0)->unk_00 = temp_v1;
            func_80040AA0(3);
            func_8008E250();
        }
    } else {
        func_800945E8(arg0);
        func_800948BC();
        D_80082E76 = 0xC000;
        func_80041094(6, 0, 0, 0, 0xC000);
        arg0->unk_9B.n++;
        func_8008E250();
    }
    return;

state_16:
    if (arg2->unk_14 & 0xE000) {
        counter_base = D_80083460;
        arg3->unk_28 = arg3->unk_29;
        arg3->unk_2A = 0x400 - ((global_base->unk_C8 + 0x100) & 0xE00);
        arg0->unk_8C = D_8008ACDC;
        counter_base->unk_0A = counter_base->unk_0A - 1;
    }
}
