#include "common.h"

typedef struct S_800BA414_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x9C];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u32 unk_100;
    u16 unk_104;
} S_800BA414_0;   /* scratch in func_800BA414 */

typedef struct S_800BA414_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BA414_1;   /* arg1 in func_800BA414 */

typedef struct S_800BA414_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BA414_2;   /* state in func_800BA414 */

typedef struct S_800BA414_3 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
} S_800BA414_3;   /* prim in func_800BA414 */

typedef struct S_800BA414_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BA414_4;   /* owner in func_800BA414 */

typedef struct S_800BA414_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BA414_5;   /* *global in func_800BA414 */


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

void func_800BA414(void *arg0, S_800BA414_1 *arg1, void *arg2, s16 arg3)
{
    u8 *scratch;
    u8 *prim;
    u8 **global;
    S_800BA414_4 *owner;
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
    ((S_800BA414_0 *)scratch)->unk_20 = state + 0xB0;
    ((S_800BA414_0 *)scratch)->unk_E4 = arg1->unk_02;
    ((S_800BA414_0 *)scratch)->unk_E8 = arg1->unk_06;
    ((S_800BA414_0 *)scratch)->unk_EC = arg1->unk_0A;
    prim = ((S_800BA414_2 *)state)->unk_8D0;
    global = (u8 **)D_80083160;

    func_800649A0();
    call_a0 = scratch;
    call_a0 = (u8 *)((u32)call_a0 | 0x100);
    call_a1 = scratch;
    call_a1 = (u8 *)((u32)call_a1 | 0xD0);
    ((S_800BA414_0 *)scratch)->unk_100 = 0;
    ((S_800BA414_0 *)scratch)->unk_104 = 0;
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
    ((S_800BA414_0 *)scratch)->unk_C0 = index;

    if (index < 0x1E0U) {
        visible0 = 0;
        visible_temp = ((S_800BA414_3 *)prim)->unk_08;
        visible_temp = (u16)(visible_temp + 0x20);
        if (visible_temp < 0x181U) {
            visible_temp = ((S_800BA414_3 *)prim)->unk_0A;
            visible_temp = (u16)(visible_temp + 0x20);
            visible0 = visible_temp < 0x121U;
        }
        visible_odd = 0;
        visible_temp = ((S_800BA414_3 *)prim)->unk_0C;
        visible_temp = (u16)(visible_temp + 0x20);
        if (visible_temp < 0x181U) {
            visible_temp = ((S_800BA414_3 *)prim)->unk_0E;
            visible_temp = (u16)(visible_temp + 0x20);
            visible_odd = visible_temp < 0x121U;
        }
        visible2 = 0;
        visible0 |= visible_odd;
        visible_temp = ((S_800BA414_3 *)prim)->unk_10;
        visible_temp = (u16)(visible_temp + 0x20);
        if (visible_temp < 0x181U) {
            visible_temp = ((S_800BA414_3 *)prim)->unk_12;
            visible_temp = (u16)(visible_temp + 0x20);
            visible2 = visible_temp < 0x121U;
        }
        visible_odd = 0;
        visible2_old = visible2;
        visible2 = visible0 | visible2_old;
        visible_temp = ((S_800BA414_3 *)prim)->unk_14;
        visible_temp = (u16)(visible_temp + 0x20);
        if (visible_temp < 0x181U) {
            visible_temp = ((S_800BA414_3 *)prim)->unk_16;
            visible_temp = (u16)(visible_temp + 0x20);
            visible_odd = visible_temp < 0x121U;
        }
        visible_temp = visible2 | visible_odd;

        if (visible_temp != 0) {
            ((S_800BA414_3 *)prim)->unk_04.at00.v = owner->unk_0C;
            func_800666E0(prim);
            old_prim = prim;
            packet = prim + 0x18;
            ((S_800BA414_3 *)prim)->unk_04.at03.v |= 2;
            prim += 0x24;
            func_8006658C(((S_800BA414_0 *)scratch)->unk_20 +
                              ((S_800BA414_0 *)scratch)->unk_C0 * 4,
                          old_prim);
            call_a0 = packet;
            call_a1 = 0;
            func_80067F20(call_a0, (s32)call_a1, (s32)call_a1, 0x20, 0);
            func_8006658C(((S_800BA414_0 *)scratch)->unk_20 +
                              ((S_800BA414_0 *)scratch)->unk_C0 * 4,
                          packet);
        }
    }

    ((S_800BA414_5 *)(*global))->unk_8D0 = prim;
    func_80064A40();
}
