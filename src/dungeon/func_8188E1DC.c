#include "common.h"

typedef struct S_800259DC_0 {
    u8 pad_00[0x18];
    void * unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x4C];
    void * unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    void * unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    void * unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    void * unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
} S_800259DC_0;   /* scratch in func_800259DC */

typedef struct S_800259DC_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_800259DC_1_pre;   /* the 0x8 bytes before arg0 in func_800259DC, addressed as arg0[-1] */

typedef struct S_800259DC_1 {
    u8 pad_00[0x34];
    void * unk_34;
    u16 unk_38;
    u8 pad_3A[0x2];
    void * unk_3C;
    u16 unk_40;
    u8 pad_42[0x2];
    void * unk_44;
    u16 unk_48;
    u8 pad_4A[0x2];
    void * unk_4C;
    u16 unk_50;
    u8 pad_52[0x2];
    s32 unk_54;
    s32 unk_58;
} S_800259DC_1;   /* arg0 in func_800259DC */

typedef struct S_800259DC_2 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800259DC_2;   /* obj in func_800259DC */



extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

typedef struct GlobalState {
    u8 pad[0x8D0];
    void *next;
} GlobalState;

extern GlobalState *D_80083160[];

s32 func_800259DC(void *arg0) {
    GlobalState **global = D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    void *obj;
    u32 count;
    s32 value0;
    s32 value1;
    s32 next;
    void *value2;
    GlobalState *global_base;

    global_base = global[0];
    (*(void * *)((u8 *)scratch + 0x20)) = (u8 *)global_base + 0xB0;
    ((S_800259DC_0 *)scratch)->unk_18 = global_base->next;
    do {
        obj = ((S_800259DC_0 *)scratch)->unk_18;
        ((S_800259DC_0 *)scratch)->unk_18 = (u8 *)obj + 0x24;
        ((S_800259DC_0 *)scratch)->unk_70 = ((S_800259DC_1 *)arg0)->unk_34;
        ((S_800259DC_0 *)scratch)->unk_78 = ((S_800259DC_1 *)arg0)->unk_3C;
        ((S_800259DC_0 *)scratch)->unk_80 = ((S_800259DC_1 *)arg0)->unk_44;
        value2 = ((S_800259DC_1 *)arg0)->unk_4C;
        ((S_800259DC_0 *)scratch)->unk_74 = ((S_800259DC_1 *)arg0)->unk_38;
        ((S_800259DC_0 *)scratch)->unk_7C = ((S_800259DC_1 *)arg0)->unk_40;
        ((S_800259DC_0 *)scratch)->unk_84 = ((S_800259DC_1 *)arg0)->unk_48;
        ((S_800259DC_0 *)scratch)->unk_88 = value2;
        ((S_800259DC_0 *)scratch)->unk_8C = ((S_800259DC_1 *)arg0)->unk_50;
        count = func_800654B0(scratch + 0x70, scratch + 0x78,
                              scratch + 0x80, scratch + 0x88,
                              (u8 *)obj + 8, (u8 *)obj + 0x10,
                              (u8 *)obj + 0x18, (u8 *)obj + 0x20,
                              scratch + 0x90, scratch + 0x94) - 8;
        ((S_800259DC_0 *)scratch)->unk_C0 = count;
        if (count < 0x1E0U) {
            value0 = ((S_800259DC_1 *)arg0)->unk_54;
            ((S_800259DC_2 *)obj)->unk_0C = value0;
            ((S_800259DC_2 *)obj)->unk_04.at00.v = value0;
            value1 = ((S_800259DC_1 *)arg0)->unk_58;
            ((S_800259DC_2 *)obj)->unk_1C = value1;
            ((S_800259DC_2 *)obj)->unk_14 = value1;
            func_80066708(obj);
            ((S_800259DC_2 *)obj)->unk_04.at03.v = (u8)(((S_800259DC_2 *)obj)->unk_04.at03.v | 2);
            func_8006658C((u8 *)((S_800259DC_0 *)scratch)->unk_20 +
                              (((S_800259DC_0 *)scratch)->unk_C0 * 4), obj);
            obj = ((S_800259DC_0 *)scratch)->unk_18;
            ((S_800259DC_0 *)scratch)->unk_18 = (u8 *)obj + 0xC;
            func_80067F20(obj, 0, 0,
                          (u16)func_80066460(0, 1, 0, 0), 0);
            func_8006658C((u8 *)((S_800259DC_0 *)scratch)->unk_20 +
                              (((S_800259DC_0 *)scratch)->unk_C0 * 4), obj);
        }
        next = ((S_800259DC_1_pre *)arg0)[-1].unk_00;
        if (next == 0) {
            break;
        }
        arg0 = (void *)(next + 0x20);
    } while (1);
    global[0]->next =
        ((S_800259DC_0 *)scratch)->unk_18;
    return 0;
}

