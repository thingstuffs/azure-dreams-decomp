#include "common.h"

typedef struct S_80024A5C_0 {
    u8 pad_00[0x8B0];
    u32 unk_8B0;
    u8 pad_8B4[0x1C];
    u8 * unk_8D0;
} S_80024A5C_0;   /* ctx in func_80024A5C */

typedef struct S_80024A5C_1 {
    u32 unk_00;
} S_80024A5C_1;   /* packet in func_80024A5C */

typedef struct S_80024A5C_2 {
    u16 unk_00;
    s16 unk_02;
} S_80024A5C_2;   /* work in func_80024A5C */

typedef struct S_80024A5C_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80024A5C_3;   /* ctx2 in func_80024A5C */

typedef struct S_80024A5C_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    u32 unk_04;
    u16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
} S_80024A5C_4;   /* packet2 in func_80024A5C */

typedef struct S_80024A5C_5 {
    u16 unk_00;
    s16 unk_02;
    s32 unk_04;
} S_80024A5C_5;   /* arg1 in func_80024A5C */

typedef struct S_80024A5C_6 {
    u32 unk_00;
} S_80024A5C_6;   /* ot in func_80024A5C */

typedef struct S_80024A5C_7 {
    void * unk_00;
} S_80024A5C_7;   /* pbase in func_80024A5C */


typedef struct { void *p; } PagePtr;
extern PagePtr D_80083160;
extern u8 D_801C9E40[16];

extern void func_80024094(void *, s32, void *, s32);
extern void func_80067E2C(void *, void *);


void func_80024A5C(volatile s32 arg0, S_80024A5C_5 *arg1, void *arg2, u16 arg3, s32 arg4)
{
    u16 pos[2];
    u16 flag;
    s32 y;
    s32 y2;
    u8 *packet;
    register u8 *pbase ASM_REG("$18");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 arg4p ASM_REG("$23");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u32 hi_mask;
    u8 *work;
    u8 *ot;
    void *ctx;
    S_80024A5C_3 *ctx2;
    register s32 shifted ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *call_pos;
    s32 call_arg0;
    void *call_ot;
    s32 call_arg4;

    ctx = D_80083160.p;
    work = arg2;
    packet = ((S_80024A5C_0 *)ctx)->unk_8D0;
    shifted = ctx != (void *)D_801C9E40;
    ((S_80024A5C_0 *)ctx)->unk_8D0 = packet + 0xC;
    arg4p = arg4;
    flag = arg3;
    func_80067E2C(packet, D_80083160.p);
    hi_mask = 0xFF000000U;

    ((S_80024A5C_1 *)packet)->unk_00 = (((S_80024A5C_1 *)packet)->unk_00 & hi_mask) |
                            (((S_80024A5C_0 *)ctx)->unk_8B0 & 0x00FFFFFFU);
    ((S_80024A5C_0 *)ctx)->unk_8B0 = (((S_80024A5C_0 *)ctx)->unk_8B0 & hi_mask) |
                             ((u32)packet & 0x00FFFFFFU);

    pos[0] = ((S_80024A5C_2 *)work)->unk_00;
    pbase = (u8 *)&D_80083160;
    y = ((S_80024A5C_2 *)work)->unk_02;
    work = (u8 *)ctx + 0x8B0;
    ot = work;
    if (shifted != 0) {
        y -= 0xE0;
    }
    call_pos = pos;
    call_arg4 = (s32)((u32)arg4p << 16);
    call_ot = ot;
    ASM_KEEP_NV(call_pos);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_arg0 = arg0;
    call_arg4 >>= 16;
    pos[1] = y;
    func_80024094(call_pos, call_arg0, call_ot, call_arg4);

    if (flag != 0) {
        u8 *packet2;

        ctx2 = D_80083160.p;
        packet2 = ctx2->unk_8D0;
        ctx2->unk_8D0 = packet2 + 0x10;
        ((S_80024A5C_4 *)packet2)->unk_04 = 0x60000000;
        ((S_80024A5C_4 *)packet2)->unk_00.at03.v = 3;
        ((S_80024A5C_4 *)packet2)->unk_08 = arg1->unk_00;
        y2 = arg1->unk_02;
        if (shifted != 0) {
            y2 -= 0xE0;
        }
        ((S_80024A5C_4 *)packet2)->unk_0A = y2;
        ((S_80024A5C_4 *)packet2)->unk_0C = arg1->unk_04;
        ((S_80024A5C_4 *)packet2)->unk_00.at00.v = (((S_80024A5C_4 *)packet2)->unk_00.at00.v & hi_mask) |
                                 (((S_80024A5C_6 *)ot)->unk_00 & 0x00FFFFFFU);
        ((S_80024A5C_6 *)ot)->unk_00 = (((S_80024A5C_6 *)ot)->unk_00 & hi_mask) |
                            ((u32)packet2 & 0x00FFFFFFU);
    }

    ctx2 = ((S_80024A5C_7 *)pbase)->unk_00;
    packet = ctx2->unk_8D0;
    ctx2->unk_8D0 = packet + 0xC;
    func_80067E2C(packet, arg1);
    ((S_80024A5C_1 *)packet)->unk_00 = (((S_80024A5C_1 *)packet)->unk_00 & 0xFF000000U) |
                            (((S_80024A5C_6 *)ot)->unk_00 & 0x00FFFFFFU);
    ((S_80024A5C_6 *)ot)->unk_00 = (((S_80024A5C_6 *)ot)->unk_00 & 0xFF000000U) |
                        ((u32)packet & 0x00FFFFFFU);
}
