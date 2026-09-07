#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

void func_80175470(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8
    };
    u8 *color = D_80083160;
    void *node;
    void *model;
    void *child;
    u8 *target;
    s32 direction;
    s32 index;
    register s32 raw_index ASM_REG("$2");
    register u32 fill ASM_REG("$7");
    u32 state;
    u8 ready;
    u16 timer;
    u16 next_timer;
    u16 *counter_base;
    register s32 next_state ASM_REG("$2");
    register s32 rem_index ASM_REG("$3");

    state = FIELD(arg0, u8, 0x9B);
    if (state >= 9U) {
        return;
    }
    (void)jt_keep;
    goto *D_80170858[state];

jt_c0:
    next_state = FIELD(arg0, volatile u8, 0x9B) + 1;
    ASM_TAILSLOT_PIN(next_state);
    func_801757E4();

jt_c1:
    func_80041588(D_80175B0C, &D_80175B24, 0);
    FIELD(arg0, s16, 0xAC) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg3, u16, 0x8A) = FIELD(arg3, u16, 0x2A);
    func_801759B8();

jt_c2:
    direction = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
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
    FIELD(arg3, u16, 0x2A) += 0x200;
    func_801759B8();

block_special:
    func_80041588(D_80175B0C, &D_80175B24, 1);
    func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
    func_8003E4FC(0x15, func_800445E0(), 0);
    D_80175B25 = 0;
    func_8003E4FC(0xFF, D_8003E140, &D_80175B25);
    func_800C77D0((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    FIELD(arg0, u16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    func_80175180(arg0, arg1, arg2);

jt_c3:
    timer = FIELD(arg0, u16, 0x96);
    next_timer = timer - 1;
    FIELD(arg0, u16, 0x96) = next_timer;
    if ((s16)next_timer <= 0) {
        ready = D_80175B25;
        FIELD(arg0, u16, 0x96) = timer;
        if (ready == 0) {
            return;
        }
        FIELD(arg0, u8, 0x9B)++;
        func_800A56E0(0x300);
        func_801759B8();
    }
    index = func_800498A0(arg3);
    target = D_800DCEEC[index];
    color[0xA8] += ((s32)target[0] - color[0xA8]) / FIELD(arg0, s16, 0x96);
    color[0xA9] += ((s32)target[1] - color[0xA9]) / FIELD(arg0, s16, 0x96);
    color[0xAA] += ((s32)target[2] - color[0xAA]) / FIELD(arg0, s16, 0x96);
    func_801759B8();

jt_c4:
    node = func_8003FC64(0x12);
    if (node == 0) {
        return;
    }
    FIELD(node, void *, 0x10) = D_80175318;
    func_8004491C(node, D_8017458C);
    FIELD(arg0, void *, 0xA8) = node;
    fill = 0x00808080;
    ASM_KEEP(fill);
    *(s32 *)FIELD(node, void *, 8) = ((s32 *)arg1)[0];
    ((s32 *)FIELD(node, void *, 8))[1] = ((s32 *)arg1)[1];
    ((s32 *)FIELD(node, void *, 8))[2] = ((s32 *)arg1)[2];
    D_80175B20 = -12;
    model = FIELD(node, void *, 0xC);
    FIELD(model, s16, 0x1E) = 0x1000;
    FIELD(model, s16, 0x1C) = 0x1000;
    FIELD(model, s32, 0xC) = fill;
    raw_index = func_800498A0(arg3) - 1;
    rem_index = raw_index;
    ASM_KEEP_NV(raw_index);
    if ((s16)raw_index < 0) {
        rem_index = func_80069EF8() % 3;
    }
    func_8003DB94(model, D_8014A000 + D_80175B14[(s16)rem_index], 0);
    FIELD(arg2, u16, 0x14) |= 0x80;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_801759B8();

jt_c5:
    node = FIELD(arg0, void *, 0xA8);
    model = FIELD(node, void *, 0xC);
    if (FIELD(model, u16, 0x14) & 0xE000) {
        FIELD(arg0, u16, 0x96) = 0x10;
        FIELD(arg0, u8, 0x9B)++;
        func_800A18E8(FIELD(arg3, u8, 0x13), 3);
        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
        func_8009A028(arg3);
        node = (u8 *)arg3 - 0x20;
        FIELD(node, u32, 0x10) |= 0x80000000;
    }

jt_c6:
    if (FIELD(arg0, u8, 0x9B) != 6) {
        return;
    }
    if (!func_800ADC4C(arg1, D_80175B28, D_80175B20, &D_800DCF5C)) {
        return;
    }
    FIELD(arg0, u16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    func_800A18E8(FIELD(arg3, u8, 0x13), 3);
    func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
    func_8009A028(arg3);
    node = (u8 *)arg3 - 0x20;
    FIELD(node, u32, 0x10) |= 0x80000000;
    func_801759B8();

jt_c7:
    FIELD(arg3, void *, 0x60) = func_800A504C(arg2, arg3);
    if (FIELD(arg3, void *, 0x60) == 0) {
        return;
    }
    FIELD(arg0, u16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(FIELD(arg3, void *, 0x60), u16, 0x2A) = FIELD(arg3, u16, 0x2A);
    model = FIELD(FIELD(arg3, void *, 0x60), void *, -0x14);
    node = FIELD(arg3, void *, 0x60);
    func_80047738(model, ((u8 *)FIELD(model, void *, 0x2C))[
                  ((D_80083228 + FIELD(node, s16, 0x2A) + 0x100) >> 9) & 7],
                  FIELD(model, s8, 4));
    FIELD(model, u16, 0x14) &= 0xFFFE;

jt_c8:
    next_timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = next_timer;
    if ((s16)next_timer > 0) {
        return;
    }
    FIELD(FIELD(arg3, void *, 0x60), u16, 0x2A) = FIELD(arg3, u16, 0x8A);
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    counter_base = (u16 *)&D_80083460;
    counter_base[5]--;
    FIELD(arg3, u8, 0x6D) = 0;
}
