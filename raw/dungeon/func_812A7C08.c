#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80173698(void) __attribute__((noreturn));
extern void func_801738A0(void) __attribute__((noreturn));
extern void func_80173908(void) __attribute__((noreturn));
extern void func_801753DC(void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_80170848[];
extern s32 D_80171FA4;
extern u8 D_80175C48[];
extern u8 D_80175C50[];
extern u8 D_80175C58[];

void func_80173408(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 5) {
        return;
    }
    (void)jt_keep;
    goto *D_80170848[state];

L0:
    {
        register void *call_a0 ASM_REG("$4") = arg3;

        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            ASM_KEEP(call_a0);
            FIELD(arg0, u8, 0x9B) = 4;
            FIELD(arg2, u16, 0x14) |= 0x6000;
            func_8009C12C(call_a0, arg2, FIELD(call_a0, s16, 0x2A), 1);
            func_80173908();
        }
    }

L1:
    FIELD(arg1, s32, 0x0C) -=
        *(s16 *)((u8 *)&D_8006CCD8 +
                 (((u16)FIELD(arg3, u16, 0x2A) >> 8) & 0xE)) << 14;
    FIELD(arg1, s32, 0x10) -=
        *(s16 *)((u8 *)&D_8006CCE8 +
                 (((u16)FIELD(arg3, u16, 0x2A) >> 8) & 0xE)) << 14;
    FIELD(arg0, s32, 0xA0) += 0x60000;
    if (FIELD(arg0, s16, 0xA2) >= 0x31) {
        FIELD(arg0, s16, 0xA2) = 0x30;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    if (FIELD(arg0, s16, 0xA2) < 0x30) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80175C48;
    func_80047784(arg2,
        D_80175C48[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_801753DC((u8 *)arg0 - 0x20, (u8 *)arg3 + 0x2A);
    (void)FIELD(arg0, volatile u8, 0x9B);
    FIELD(arg0, s16, 0x96) = 0;
    func_80173698();

L2:
    {
        s16 *base_x;
        s16 *base_y;
        register s16 *addr_x ASM_REG("$4");
        register s16 *addr_y ASM_REG("$3");
        s32 arc;
        register s32 index ASM_REG("$3");
        register s32 direction_x ASM_REG("$2");
        register s32 direction_y ASM_REG("$3");
        register s32 shifted_x ASM_REG("$4");
        register s32 shifted_y ASM_REG("$5");
        s16 timer;

        base_x = (s16 *)&D_8006CCD8;
        base_y = (s16 *)&D_8006CCE8;
        index = ((u16)FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
        addr_x = (s16 *)(index + (u8 *)base_x);
        addr_y = (s16 *)(index + (u8 *)base_y);
        ASM_KEEP(addr_x);
        ASM_KEEP(addr_y);
        ASM_KEEP(index);
        direction_x = *addr_x;
        direction_y = *addr_y;
        ASM_KEEP(direction_x);
        ASM_KEEP(direction_y);
        shifted_x = direction_x << 16;
        shifted_y = direction_y << 16;
        ASM_KEEP(shifted_x);
        ASM_KEEP(shifted_y);
        FIELD(arg1, s32, 0x0C) += shifted_x;
        FIELD(arg1, s32, 0x10) += shifted_y;
        arc = -func_800644B8(FIELD(arg0, s16, 0x96) * 170);
        FIELD(arg0, s32, 0xA0) = ((arc * 5) << 8) + 0x300000;
        timer = FIELD(arg0, u16, 0x96) + 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer < 9) {
            return;
        }
    }
    FIELD(arg2, u8 *, 0x2C) = D_80175C50;
    func_80047784(arg2,
        D_80175C50[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x808);
    FIELD(arg0, u8, 0x9B)++;
    func_80173908();

L3:
    {
        s16 *base_x;
        s16 *base_y;
        register s16 *addr_x ASM_REG("$4");
        register s16 *addr_y ASM_REG("$2");
        s32 arc;
        register s32 direction_x ASM_REG("$3");
        register s32 direction_y ASM_REG("$2");
        register s32 index ASM_REG("$2");
        register s32 shifted_x ASM_REG("$4");
        register s32 shifted_y ASM_REG("$5");
        s16 timer;
        s32 velocity_x;
        s32 velocity_y;

        if (FIELD(arg0, s16, 0x96) == 10) {
            func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        }
        base_x = (s16 *)&D_8006CCD8;
        base_y = (s16 *)&D_8006CCE8;
        index = ((u16)FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
        addr_x = (s16 *)(index + (u8 *)base_x);
        addr_y = (s16 *)(index + (u8 *)base_y);
        ASM_KEEP(addr_x);
        ASM_KEEP(addr_y);
        ASM_KEEP(index);
        direction_x = *addr_x;
        direction_y = *addr_y;
        ASM_KEEP(direction_x);
        ASM_KEEP(direction_y);
        shifted_x = direction_x << 16;
        shifted_y = direction_y << 16;
        ASM_KEEP(shifted_x);
        ASM_KEEP(shifted_y);
        FIELD(arg1, s32, 0x0C) += shifted_x;
        FIELD(arg1, s32, 0x10) += shifted_y;
        arc = -func_800644B8(FIELD(arg0, s16, 0x96) * 170);
        FIELD(arg0, s32, 0xA0) = ((arc * 5) << 8) + 0x300000;
        timer = FIELD(arg0, u16, 0x96) + 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer < 13) {
            return;
        }
        FIELD(arg2, u8 *, 0x2C) = D_80175C58;
        func_80047784(arg2,
            D_80175C58[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);

        velocity_x = -*(s16 *)((u8 *)base_x +
            (((u16)FIELD(arg3, u16, 0x2A) >> 8) & 0xE)) << 18;
        velocity_x += velocity_x >> 2;
        FIELD(arg1, s32, 0x0C) = velocity_x;

        velocity_y = -*(s16 *)((u8 *)base_y +
            (((u16)FIELD(arg3, u16, 0x2A) >> 8) & 0xE)) << 18;
        velocity_y += velocity_y >> 2;
        FIELD(arg1, s32, 0x10) = velocity_y;
        FIELD(arg0, s32, 0xA8) = FIELD(arg1, s32, 0x0C) / 24;
        FIELD(arg0, s32, 0xAC) = FIELD(arg1, s32, 0x10) / 24;
    }
    FIELD(arg0, s16, 0x96) = 12;
    FIELD(arg0, u8, 0x9B)++;
    func_80173908();

L4:
    FIELD(arg1, s32, 0x0C) -= FIELD(arg0, s32, 0xA8);
    FIELD(arg1, s32, 0x10) -= FIELD(arg0, s32, 0xAC);
    if (FIELD(arg0, s16, 0xA2) > 0) {
        FIELD(arg0, u16, 0xA2) -= 0x10;
        func_801738A0();
    }
    FIELD(arg0, s16, 0xA2) = 0;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 0x100);
    FIELD(arg0, s32 *, 0x8C) = &D_80171FA4;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
}
