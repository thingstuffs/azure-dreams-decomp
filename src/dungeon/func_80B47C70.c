#include "common.h"


typedef s32 M2C_UNK;

extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern u16 D_8008000A;
extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 *D_800DCEEC[];
extern s32 D_800DCF5C;
extern u8 D_8014A000[200000];
extern void *D_80170858[];
extern u8 D_8017458C[];
extern u8 D_80175318[];
extern u8 D_80175B0C[];
extern s32 D_80175B14[];
extern s16 D_80175B20;
extern u8 D_80175B24;
extern u8 D_80175B25;
extern void *D_80175B28;

M2C_UNK func_8003DB94();
M2C_UNK func_8003E4FC();
M2C_UNK func_8003F540();
void *func_8003FC64();
M2C_UNK func_80041588();
s32 func_800445E0();
M2C_UNK func_8004491C();
M2C_UNK func_80047738();
s32 func_800498A0();
s32 func_80069EF8();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A18E8();
void *func_800A504C();
M2C_UNK func_800A56E0();
s32 func_800ADC4C();
M2C_UNK func_800C77D0();
M2C_UNK func_80175180();
void func_801757E4(void) __attribute__((noreturn));
void func_801759B8(void) __attribute__((noreturn));


typedef struct S_80175470_0_pre {
    u16 unk_00;
} S_80175470_0_pre;   /* the 0x2 bytes before arg0 in func_80175470, addressed as arg0[-1] */

typedef struct S_80175470_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0xC];
    void * unk_A8;
    s16 unk_AC;
} S_80175470_0;   /* arg0 in func_80175470 */

typedef struct S_80175470_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80175470_1;   /* arg3 in func_80175470 */

typedef struct S_80175470_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    union { void * p; u32 i; } unk_10;   /* accessed as both */
    u8 pad_14[0x16];
    s16 unk_2A;
} S_80175470_2;   /* node in func_80175470 */

typedef struct S_80175470_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80175470_3;   /* model in func_80175470 */

typedef struct S_80175470_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80175470_4;   /* arg2 in func_80175470 */

typedef struct S_80175470_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80175470_5_pre;   /* the 0x14 bytes before ((S_80175470_1 *)arg3)->unk_60 in func_80175470, addressed as ((S_80175470_1 *)arg3)->unk_60[-1] */

typedef struct S_80175470_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175470_5;   /* ((S_80175470_1 *)arg3)->unk_60 in func_80175470 */

void func_80175470(void *arg0, void *arg1, S_80175470_4 *arg2, void *arg3) {
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8
    };
    u8 *color = D_80083160;
    S_80175470_2 *node;
    S_80175470_3 *model;
    void *child;
    u8 *target;
    s32 direction;
    s32 index;
    s32 raw_index;
    u32 fill;
    u32 state;
    u8 ready;
    u16 timer;
    u16 next_timer;
    u16 *counter_base;
    s32 next_state;
    register s32 rem_index ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    state = ((S_80175470_0 *)arg0)->unk_9B.n;
    if (state >= 9U) {
        return;
    }
    (void)jt_keep;
    goto *D_80170858[state];

jt_c0:
    next_state = ((S_80175470_0 *)arg0)->unk_9B.v + 1;
    ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail delay-slot contents depend on it */
    func_801757E4();

jt_c1:
    func_80041588(D_80175B0C, &D_80175B24, 0);
    ((S_80175470_0 *)arg0)->unk_AC = 0;
    ((S_80175470_0 *)arg0)->unk_9B.n++;
    ((S_80175470_1 *)arg3)->unk_8A = ((S_80175470_1 *)arg3)->unk_2A.u;
    func_801759B8();

jt_c2:
    direction = ((D_80083228 + ((S_80175470_1 *)arg3)->unk_2A.s + 0x100) >> 9) & 7;
    if (D_80175B24 == 0) {
        goto block_non_special;
    }
    if (direction == 2) {
        goto block_special;
    }
block_non_special:
    if (direction == 2) {
        return;
    }
    ((S_80175470_1 *)arg3)->unk_2A.u += 0x200;
    func_801759B8();

block_special:
    func_80041588(D_80175B0C, &D_80175B24, 1);
    func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
    func_8003E4FC(0x15, func_800445E0(), 0);
    D_80175B25 = 0;
    func_8003E4FC(0xFF, D_8003E140, &D_80175B25);
    func_800C77D0((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    ((S_80175470_0 *)arg0)->unk_96.u = 0x10;
    ((S_80175470_0 *)arg0)->unk_9B.n++;
    func_80175180(arg0, arg1, arg2);

jt_c3:
    timer = ((S_80175470_0 *)arg0)->unk_96.u;
    next_timer = timer - 1;
    ((S_80175470_0 *)arg0)->unk_96.u = next_timer;
    if ((s16)next_timer <= 0) {
        ready = D_80175B25;
        ((S_80175470_0 *)arg0)->unk_96.u = timer;
        if (ready == 0) {
            return;
        }
        ((S_80175470_0 *)arg0)->unk_9B.n++;
        func_800A56E0(0x300);
        func_801759B8();
    }
    index = func_800498A0(arg3);
    target = D_800DCEEC[index];
    color[0xA8] += ((s32)target[0] - color[0xA8]) / ((S_80175470_0 *)arg0)->unk_96.s;
    color[0xA9] += ((s32)target[1] - color[0xA9]) / ((S_80175470_0 *)arg0)->unk_96.s;
    color[0xAA] += ((s32)target[2] - color[0xAA]) / ((S_80175470_0 *)arg0)->unk_96.s;
    func_801759B8();

jt_c4:
    node = func_8003FC64(0x12);
    if (node == 0) {
        return;
    }
    node->unk_10.p = D_80175318;
    func_8004491C(node, D_8017458C);
    ((S_80175470_0 *)arg0)->unk_A8 = node;
    fill = 0x00808080;
    *(s32 *)node->unk_08 = ((s32 *)arg1)[0];
    ((s32 *)node->unk_08)[1] = ((s32 *)arg1)[1];
    ((s32 *)node->unk_08)[2] = ((s32 *)arg1)[2];
    D_80175B20 = -12;
    model = node->unk_0C;
    model->unk_1E = 0x1000;
    model->unk_1C = 0x1000;
    model->unk_0C = fill;
    raw_index = func_800498A0(arg3) - 1;
    rem_index = raw_index;
    ASM_KEEP_NV(raw_index);   /* MATCH pin: retail delay-slot fill depends on it */
    if ((s16)raw_index < 0) {
        rem_index = func_80069EF8() % 3;
    }
    func_8003DB94(model, D_8014A000 + D_80175B14[(s16)rem_index], 0);
    arg2->unk_14 |= 0x80;
    ((S_80175470_0 *)arg0)->unk_96.u = 0;
    ((S_80175470_0 *)arg0)->unk_9B.n++;
    func_801759B8();

jt_c5:
    node = ((S_80175470_0 *)arg0)->unk_A8;
    model = node->unk_0C;
    if (model->unk_14 & 0xE000) {
        ((S_80175470_0 *)arg0)->unk_96.u = 0x10;
        ((S_80175470_0 *)arg0)->unk_9B.n++;
        func_800A18E8(((S_80175470_1 *)arg3)->unk_13, 3);
        func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
        func_8009A028(arg3);
        node = (u8 *)arg3 - 0x20;
        node->unk_10.i |= 0x80000000;
    }

jt_c6:
    if (((S_80175470_0 *)arg0)->unk_9B.n != 6) {
        return;
    }
    if (!func_800ADC4C(arg1, D_80175B28, D_80175B20, &D_800DCF5C)) {
        return;
    }
    ((S_80175470_0 *)arg0)->unk_96.u = 0x10;
    ((S_80175470_0 *)arg0)->unk_9B.n++;
    func_800A18E8(((S_80175470_1 *)arg3)->unk_13, 3);
    func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
    func_8009A028(arg3);
    node = (u8 *)arg3 - 0x20;
    node->unk_10.i |= 0x80000000;
    func_801759B8();

jt_c7:
    ((S_80175470_1 *)arg3)->unk_60 = func_800A504C(arg2, arg3);
    if (((S_80175470_1 *)arg3)->unk_60 == 0) {
        return;
    }
    ((S_80175470_0 *)arg0)->unk_96.u = 0x10;
    ((S_80175470_0 *)arg0)->unk_9B.n++;
    ((S_80175470_5 *)(((S_80175470_1 *)arg3)->unk_60))->unk_2A = ((S_80175470_1 *)arg3)->unk_2A.u;
    model = ((S_80175470_5_pre *)(((S_80175470_1 *)arg3)->unk_60))[-1].unk_00;
    node = ((S_80175470_1 *)arg3)->unk_60;
    func_80047738(model, ((u8 *)model->unk_2C)[
                  ((D_80083228 + node->unk_2A + 0x100) >> 9) & 7],
                  model->unk_04);
    model->unk_14 &= 0xFFFE;

jt_c8:
    next_timer = ((S_80175470_0 *)arg0)->unk_96.u - 1;
    ((S_80175470_0 *)arg0)->unk_96.u = next_timer;
    if ((s16)next_timer > 0) {
        return;
    }
    ((S_80175470_5 *)(((S_80175470_1 *)arg3)->unk_60))->unk_2A = ((S_80175470_1 *)arg3)->unk_8A;
    ((S_80175470_0_pre *)arg0)[-1].unk_00 |= 0x8000;
    D_800814A0 |= 0x8000;
    counter_base = (u16 *)&D_80083460;
    counter_base[5]--;
    ((S_80175470_1 *)arg3)->unk_6D = 0;
}
