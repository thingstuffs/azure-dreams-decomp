#include "common.h"

#define F8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define FS8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define F16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define FS16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FPTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_801713A8[];
extern u8 D_8017449C[];
extern u8 D_801744B4[];
extern u8 D_801744BC[];
extern u8 D_801744C4[];
extern u8 D_801744CC[];

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

void func_80172700(void *input0, void *input1, void *input2, void *input3)
{
    register void *arg0 ASM_REG("$16");
    register void *arg1 ASM_REG("$17");
    register void *arg2 ASM_REG("$18");
    register void *arg3 ASM_REG("$19");
    s32 step_x;
    s32 step_y;
    register s32 four ASM_REG("$22");
    s32 state;
    s32 table_index;
    register s32 value ASM_REG("$2");
    register s32 value2 ASM_REG("$3");
    register void *call_a0 ASM_REG("$4");
    u16 flags;
    register u8 *effect ASM_REG("$5");
    register u8 *dir_x ASM_REG("$4");
    register u8 *dir_y ASM_REG("$2");

    arg0 = input0;
    arg1 = input1;
    arg2 = input2;
    arg3 = input3;
    ASM_KEEP4_NV(arg0, arg1, arg2, arg3);
    dir_x = D_8006CCD8;
    dir_y = D_8006CCE8;
    table_index = (F16(arg3, 0x2A) >> 8) & 0xE;
    ASM_USE(dir_x);
    step_x = *(s16 *)(dir_x + table_index);
    step_y = *(s16 *)(dir_y + table_index);
    state = F8(arg0, 0x9B);
    F16(arg0, 0x96)--;

    if (state == 2) goto state_2;
    if (state < 3) {
        if (state == 0) goto state_0;
        if (state == 1) goto state_1;
        goto done;
    }
    if (state == 4) goto state_4;
    if (state <= 3) goto state_3;
    if (state == 0xFF) goto state_ff;
    goto done;

state_0:
    flags = F16(arg2, 0x14);
    call_a0 = arg3;
    if (flags & 0x8000) {
        F8(arg0, 0x9B) = 0xFF;
        F16(arg2, 0x14) |= 0x6000;
        func_8009C12C(call_a0, arg2, FS16(call_a0, 0x2A), 1);
        goto done;
    }
    if (!(flags & 0xE000)) goto done;
    effect = D_801744B4;
    FPTR(arg2, 0x2C) = effect;
    value = (D_80083228 + FS16(arg3, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, effect[value & 7], 0);
    F32(arg1, 0xC) = (-step_x) << 18;
    F32(arg1, 0x10) = (-step_y) << 18;
    F16(arg0, 0x98) |= 8;
    F32(arg3, 0x1C) &= 0xF7FFFFFF;
    F32(arg3, 0x1C) &= 0xFFFBFFFF;
    F16(arg0, 0x96) = 4;
    F32(arg1, 0x14) = 0xFFFE8000;
    goto increment;

state_1:
    value = F32(arg1, 0x14);
    F32(arg1, 0x14) = value + (value >> 2);
    if (FS16(arg0, 0x96) > 0) goto done;
    value2 = 8;
    value = F8(arg0, 0x9B);
    F16(arg0, 0x96) = value2;
    goto increment_loaded;

state_2:
    value = F32(arg1, 0xC);
    value2 = F32(arg1, 0x10);
    value -= value >> 3;
    value2 -= value2 >> 3;
    F32(arg1, 0xC) = value;
    value = F32(arg1, 0x14);
    F32(arg1, 0x10) = value2;
    value -= value >> 3;
    F32(arg1, 0x14) = value;
    four = 4;
    if (FS16(arg0, 0x96) == four) {
        effect = D_801744BC;
        F32(arg1, 0xC) = 0;
        F32(arg1, 0x10) = 0;
        F32(arg1, 0x14) = 0;
        FPTR(arg2, 0x2C) = effect;
        value = (D_80083228 + FS16(arg3, 0x2A) + 0x100) >> 9;
        func_80047784(arg2, effect[value & 7], 0);
    }
    if (FS16(arg0, 0x96) > 0) goto done;
    if (!(F16(arg2, 0x14) & 0xE000)) goto done;
    F16(arg0, 0x96) = four;
    value = step_x << 18;
    value2 = step_x << 17;
    F32(arg1, 0xC) = value + value2;
    ASM_SCHED_BARRIER();
    value = step_y << 18;
    value2 = step_y << 17;
    value += value2;
    ASM_KEEP(value);
    F32(arg1, 0x10) = value;
    effect = D_801744C4;
    FPTR(arg2, 0x2C) = effect;
    value = (D_80083228 + FS16(arg3, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, effect[value & 7], 0);
    goto increment;

state_3:
    F32(arg0, 0x90) += 0x80000;
    F32(arg1, 0xC) += step_x << 18;
    F32(arg1, 0x10) += step_y << 18;
    if (FS16(arg0, 0x96) == 2) {
        func_800A56E0(0x809);
    }
    call_a0 = arg3;
    if (FS16(arg0, 0x96) > 0) goto done;
    func_8009C12C(call_a0, arg2, FS16(call_a0, 0x2A), 1);

increment:
    value = F8(arg0, 0x9B);
increment_loaded:
    value++;
    F8(arg0, 0x9B) = value;
    goto done;

state_4:
    F32(arg0, 0x90) += 0x80000;
    if (!(F16(arg2, 0x14) & 0xE000)) goto done;
    effect = D_801744CC;
    FPTR(arg2, 0x2C) = effect;
    value = (D_80083228 + FS16(arg3, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, effect[value & 7], 0);
    F32(arg1, 0x14) = 0;
    F32(arg0, 0x90) = 0;
    F16(arg0, 0x98) &= 0xFFF7;
    F32(arg3, 0x1C) |= 0x08000000;
    F8(arg0, 0x9B) = 0xFF;
    goto done;

state_ff:
    value = F8(arg2, 0x24) << 6;
    value2 = FS16(arg1, 2);
    value2 -= 0x20;
    value -= value2;
    value <<= 15;
    ASM_KEEP(value);
    value >>= 1;
    F32(arg1, 0xC) = value;
    value = F8(arg2, 0x25) << 6;
    value2 = FS16(arg1, 6);
    value2 -= 0x20;
    value -= value2;
    value <<= 15;
    ASM_KEEP(value);
    value >>= 1;
    F32(arg1, 0x10) = value;
    if (!(F16(arg2, 0x14) & 0xE000)) goto done;
    F32(arg1, 0x10) = 0;
    F32(arg1, 0xC) = 0;
    F32(arg3, 0x1C) |= 0x40000;
    func_800A2B04(arg1, F8(arg2, 0x24), F8(arg2, 0x25));
    func_800AD594(arg3, 0x100);
    FPTR(arg0, 0x8C) = D_801713A8;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    effect = D_8017449C;
    FPTR(arg2, 0x2C) = effect;
    value = (D_80083228 + FS16(arg3, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, effect[value & 7], 0);
    if (FS8(arg3, 0x6D) == 0) {
        F16(arg3, 0x46) &= 0x7FFF;
        goto done;
    }
    D_800E3DE8 = (u8 *)arg3 - 0x20;

done:
    ASM_USE(arg3);
    return;
}
