#include "common.h"

typedef struct S_8187B1F4_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8187B1F4_0;   /* arg1 in func_8187B1F4 */

typedef struct S_8187B1F4_1 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x12];
    u16 unk_A6;
} S_8187B1F4_1;   /* scratch in func_8187B1F4 */

typedef struct S_8187B1F4_2 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_8187B1F4_2;   /* arg2 in func_8187B1F4 */

typedef struct S_8187B1F4_3_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8187B1F4_3_pre;   /* the 0x8 bytes before arg0 in func_8187B1F4, addressed as arg0[-1] */

typedef struct S_8187B1F4_3 {
    s32 unk_00;
    u8 pad_04[0xC];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
} S_8187B1F4_3;   /* arg0 in func_8187B1F4 */

typedef struct S_8187B1F4_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 v; } at00p; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
} S_8187B1F4_4;   /* temp_s0 in func_8187B1F4 */

typedef struct S_8187B1F4_5 {
    u32 unk_00;
} S_8187B1F4_5;   /* (u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4 in func_8187B1F4 */

typedef struct S_8187B1F4_6 {
    u32 unk_00;
    u8 pad_04[0x4];
    u8 * unk_08;
    u8 * unk_0C;
} S_8187B1F4_6;   /* tail in func_8187B1F4 */

typedef struct S_8187B1F4_7 {
    u32 unk_00;
} S_8187B1F4_7;   /* temp_s0_2 in func_8187B1F4 */

typedef struct S_8187B1F4_8 {
    u32 unk_00;
} S_8187B1F4_8;   /* state in func_8187B1F4 */


#define VFIELD(base, type, offset) (*(volatile type *)((u8 *)(base) + (offset)))

typedef struct GlobalState {
    u8 pad[0x8D0];
    u8 *next;
} GlobalState;

extern void func_80024A54() __attribute__((noreturn));
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065420(void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u32, s32);
extern GlobalState *D_80083160[];

s32 func_8187B1F4(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 sp18[8];
    void * volatile sp38;
    u8 *scratch;
    register u8 *scratch74 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *scratch54;
    GlobalState **global;
    register GlobalState *state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *state_base;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v1;
    register s32 var_s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    volatile u16 *var_s3;
    u32 temp_v0;
    s32 loop_limit;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 combined ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 coord;
    void *call_a0;
    void *call_a2;
    void *call_a3;
    register u8 *tail ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *tail_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u32 mask_high;
    register u32 mask_low ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    global = (GlobalState **)&D_80083160;
    ASM_KEEP_NV(global);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    scratch74 = scratch;
    ASM_KEEP_NV(scratch74);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    scratch74 = (u8 *)((u32)scratch74 | 0x74);
    sp38 = scratch74;
    scratch54 = scratch;
    ASM_KEEP_NV(scratch54);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    scratch54 = (u8 *)((u32)scratch54 | 0x54);
    ASM_KEEP_NV(scratch54);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    mask_low = 0x00FFFFFF;
    mask_high = 0xFF000000;
    ASM_KEEP(mask_high);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    VFIELD(scratch, s32, 0x88) = ((S_8187B1F4_0 *)arg1)->unk_02;
    VFIELD(scratch, s32, 0x8C) = ((S_8187B1F4_0 *)arg1)->unk_06;
    ((S_8187B1F4_1 *)scratch)->unk_90 = ((S_8187B1F4_0 *)arg1)->unk_0A;
    func_800649A0();
    VFIELD(scratch, s32, 0x3C) = 0x1000;
    VFIELD(scratch, s32, 0x38) = 0x1000;
    VFIELD(scratch, s32, 0x34) = 0x1000;
    VFIELD(scratch, u16, 0xA4) = ((S_8187B1F4_2 *)arg2)->unk_16;
    VFIELD(scratch, u16, 0xA8) = ((S_8187B1F4_2 *)arg2)->unk_1A;
    coord = ((S_8187B1F4_2 *)arg2)->unk_18;
    tail_a1 = (u8 *)sp38;
    ((S_8187B1F4_1 *)scratch)->unk_A6 = coord;
    func_80065820(scratch + 0xA4, tail_a1);
    func_80064AE0(&sp18);
    func_80064840(&sp18, sp38, scratch54);
    func_80064BC0(scratch54, scratch + 0x34);
    func_80064D80(scratch54);
    func_80064CF0(scratch54);
    state = global[0];
    state_base = (u8 *)state;
    state = (GlobalState *)state->next;
    state_base += 0xB0;
    VFIELD(scratch, void *, 0x24) = state_base;
    VFIELD(scratch, void *, 0x1C) = state;
    var_s5 = 0;
    if (((S_8187B1F4_3 *)arg0)->unk_14 > 0) {
        var_s3 = (u16 *)arg0;
        do {
            VFIELD(scratch, u16, 4) = var_s3[0xB];
            VFIELD(scratch, u16, 6) = var_s3[0x22];
            call_a0 = scratch + 4;
            coord = var_s3[0x39];
            state = global[0];
            call_a2 = scratch + 0xD0;
            VFIELD(scratch, u16, 8) = coord;
            temp_s0 = state->next;
            call_a3 = scratch + 0xD4;
            state->next = temp_s0 + 0xC;
            temp_v0 = func_80065420(call_a0, temp_s0 + 8,
                                    call_a2, call_a3);
            VFIELD(scratch, u32, 0x100) = temp_v0;
            if (temp_v0 < 0x1E0U) {
                ((S_8187B1F4_4 *)temp_s0)->unk_04.at00.v = ((S_8187B1F4_3 *)arg0)->unk_00;
                ((S_8187B1F4_4 *)temp_s0)->unk_04.at00u.v = (s8)((((S_8187B1F4_4 *)temp_s0)->unk_04.at00p.v *
                    ((S_8187B1F4_3 *)arg0)->unk_10) / ((S_8187B1F4_3 *)arg0)->unk_12);
                ((S_8187B1F4_4 *)temp_s0)->unk_04.at01.v = (u8)((((S_8187B1F4_4 *)temp_s0)->unk_04.at01.v *
                    ((S_8187B1F4_3 *)arg0)->unk_10) / ((S_8187B1F4_3 *)arg0)->unk_12);
                ((S_8187B1F4_4 *)temp_s0)->unk_04.at02.v = (u8)((((S_8187B1F4_4 *)temp_s0)->unk_04.at02.v *
                    ((S_8187B1F4_3 *)arg0)->unk_10) / ((S_8187B1F4_3 *)arg0)->unk_12);
                ((S_8187B1F4_4 *)temp_s0)->unk_00.at03.v = 2;
                ((S_8187B1F4_4 *)temp_s0)->unk_04.at03.v = 0x6A;
                ((S_8187B1F4_4 *)temp_s0)->unk_00.at00.v =
                    (((S_8187B1F4_4 *)temp_s0)->unk_00.at00.v & mask_high) |
                    (((S_8187B1F4_5 *)((u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4))->unk_00 & mask_low);
                tail = (u8 *)(VFIELD(scratch, u32, 0x100) * 4);
                tail += (u32)VFIELD(scratch, void *, 0x24);
                combined =
                    (((S_8187B1F4_6 *)tail)->unk_00 & mask_high) |
                    ((u32)temp_s0 & mask_low);
                ((S_8187B1F4_6 *)tail)->unk_00 = combined;
                temp_s0_2 = global[0]->next;
                global[0]->next = temp_s0_2 + 0xC;
                func_80067F20(temp_s0_2, 0, 0,
                              func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
                ((S_8187B1F4_7 *)temp_s0_2)->unk_00 =
                    (((S_8187B1F4_7 *)temp_s0_2)->unk_00 & mask_high) |
                    (((S_8187B1F4_5 *)((u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4))->unk_00 & mask_low);
                state = (GlobalState *)(VFIELD(scratch, u32, 0x100) * 4);
                state = (GlobalState *)((u8 *)state +
                                        (u32)VFIELD(scratch, void *, 0x24));
                ((S_8187B1F4_8 *)state)->unk_00 =
                    (((S_8187B1F4_8 *)state)->unk_00 & mask_high) |
                    ((u32)temp_s0_2 & mask_low);
            }
            loop_limit = ((S_8187B1F4_3 *)arg0)->unk_14;
            ASM_KEEP(loop_limit);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            var_s5 += 1;
            var_s3 += 1;
        } while (var_s5 < loop_limit);
    }
    ASM_USE(scratch54);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    func_80064A40();
    tail = ((S_8187B1F4_3_pre *)arg0)[-1].unk_00;
    arg0 = tail + 0x20;
    if (tail != 0) {
        tail_a1 = ((S_8187B1F4_6 *)tail)->unk_08;
        temp_s0 = ((S_8187B1F4_6 *)tail)->unk_0C;
        ASM_USE2(arg0, tail_a1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2(tail, temp_s0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_80024A54();
    }
#ifndef __mips__
    hard_zero = 0;
#endif
    result = hard_zero;
    return result;
}
