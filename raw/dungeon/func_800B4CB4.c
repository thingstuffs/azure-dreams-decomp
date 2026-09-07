#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *,
                        void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_800666E0(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s8 D_80083160[];

void func_800BA414(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    u8 *scratch;
    u8 *prim;
    u8 **global;
    void *owner;
    s16 depth;
    u8 *call_a0;
    u8 *call_a1;
    u8 *call_a2;
    u8 *call_a3;
    u8 *call_v0;
    u8 *call_v1;
    u8 *state;
    u8 *old_prim;
    u8 *packet;
    u32 index;
    u32 visible_temp;
    s32 visible0;
    s32 visible2;
    s32 visible2_old;
    s32 visible_odd;

    (void)arg0;
    state = *(u8 **)D_80083160;
    scratch = (u8 *)0x1F800000;
    owner = arg2;
    depth = arg3;
    FIELD(scratch, u8 *, 0x20) = state + 0xB0;
    FIELD(scratch, s32, 0xE4) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0xE8) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0xEC) = FIELD(arg1, s16, 0xA);
    prim = FIELD(state, u8 *, 0x8D0);
    global = (u8 **)D_80083160;

    func_800649A0();
    call_a0 = scratch;
    call_a0 = (u8 *)((u32)call_a0 | 0x100);
    call_a1 = scratch;
    call_a1 = (u8 *)((u32)call_a1 | 0xD0);
    FIELD(scratch, u32, 0x100) = 0;
    FIELD(scratch, u16, 0x104) = 0;
    func_80065820(call_a0, call_a1);
    call_a0 = scratch;
    call_a0 = (u8 *)((u32)call_a0 | 0x11C);
    func_80064AE0(call_a0);
    call_a0 = scratch;
    call_a0 = (u8 *)((u32)call_a0 | 0x11C);
    call_a1 = scratch;
    call_a1 = (u8 *)((u32)call_a1 | 0xD0);
    call_a2 = scratch;
    call_a2 = (u8 *)((u32)call_a2 | 0x50);
    func_80064840(call_a0, call_a1, call_a2);
    call_a0 = scratch;
    call_a0 = (u8 *)((u32)call_a0 | 0x50);
    func_80064D80(call_a0);
    call_a0 = scratch;
    call_a0 = (u8 *)((u32)call_a0 | 0x50);
    func_80064CF0(call_a0);

    call_v1 = scratch;
    call_v1 = (u8 *)((u32)call_v1 | 0x90);
    call_v0 = scratch;
    call_v0 = (u8 *)((u32)call_v0 | 0x94);
    call_a0 = scratch;
    call_a0 = (u8 *)((u32)call_a0 | 0x70);
    call_a1 = scratch;
    call_a1 = (u8 *)((u32)call_a1 | 0x78);
    call_a2 = scratch;
    call_a2 = (u8 *)((u32)call_a2 | 0x80);
    call_a3 = scratch;
    call_a3 = (u8 *)((u32)call_a3 | 0x88);
    index = (func_80065590(call_a0, call_a1, call_a2, call_a3,
                           prim + 8, prim + 0xC, prim + 0x10, prim + 0x14,
                           call_v1, call_v0) -
             depth) - 8;
    FIELD(scratch, u32, 0xC0) = index;

    if (index < 0x1E0U) {
        visible0 = 0;
        visible_temp = FIELD(prim, u16, 8);
        visible_temp = (u16)(visible_temp + 0x20);
        if (visible_temp < 0x181U) {
            visible_temp = FIELD(prim, u16, 0xA);
            visible_temp = (u16)(visible_temp + 0x20);
            visible0 = visible_temp < 0x121U;
        }
        visible_odd = 0;
        visible_temp = FIELD(prim, u16, 0xC);
        visible_temp = (u16)(visible_temp + 0x20);
        if (visible_temp < 0x181U) {
            visible_temp = FIELD(prim, u16, 0xE);
            visible_temp = (u16)(visible_temp + 0x20);
            visible_odd = visible_temp < 0x121U;
        }
        visible2 = 0;
        visible0 |= visible_odd;
        visible_temp = FIELD(prim, u16, 0x10);
        visible_temp = (u16)(visible_temp + 0x20);
        if (visible_temp < 0x181U) {
            visible_temp = FIELD(prim, u16, 0x12);
            visible_temp = (u16)(visible_temp + 0x20);
            visible2 = visible_temp < 0x121U;
        }
        visible_odd = 0;
        visible2_old = visible2;
        visible2 = visible0 | visible2_old;
        visible_temp = FIELD(prim, u16, 0x14);
        visible_temp = (u16)(visible_temp + 0x20);
        if (visible_temp < 0x181U) {
            visible_temp = FIELD(prim, u16, 0x16);
            visible_temp = (u16)(visible_temp + 0x20);
            visible_odd = visible_temp < 0x121U;
        }
        visible_temp = visible2 | visible_odd;

        if (visible_temp != 0) {
            FIELD(prim, s32, 4) = FIELD(owner, s32, 0xC);
            func_800666E0(prim);
            old_prim = prim;
            packet = prim + 0x18;
            FIELD(prim, u8, 7) |= 2;
            prim += 0x24;
            func_8006658C(FIELD(scratch, u8 *, 0x20) +
                              FIELD(scratch, u32, 0xC0) * 4,
                          old_prim);
            call_a0 = packet;
            call_a1 = 0;
            func_80067F20(call_a0, (s32)call_a1, (s32)call_a1, 0x20, 0);
            func_8006658C(FIELD(scratch, u8 *, 0x20) +
                              FIELD(scratch, u32, 0xC0) * 4,
                          packet);
        }
    }

    FIELD(*global, u8 *, 0x8D0) = prim;
    func_80064A40();
}
