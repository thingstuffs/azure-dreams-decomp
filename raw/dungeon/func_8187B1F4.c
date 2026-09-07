#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
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
    register u8 *scratch ASM_REG("$17");
    register u8 *scratch74 ASM_REG("$8");
    register u8 *scratch54 ASM_REG("$22");
    GlobalState **global;
    register GlobalState *state ASM_REG("$3");
    register u8 *state_base ASM_REG("$2");
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v1;
    register s32 var_s5 ASM_REG("$21");
    register volatile u16 *var_s3 ASM_REG("$19");
    u32 temp_v0;
    s32 loop_limit;
    register s32 result ASM_REG("$2");
    register s32 hard_zero ASM_REG("$0");
    register u32 combined ASM_REG("$2");
    u16 coord;
    void *call_a0;
    void *call_a2;
    void *call_a3;
    register u8 *tail ASM_REG("$6");
    register u8 *tail_a1 ASM_REG("$5");
    register u32 mask_high ASM_REG("$23");
    register u32 mask_low ASM_REG("$20");

    global = (GlobalState **)&D_80083160;
    ASM_KEEP_NV(global);
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);
    scratch74 = scratch;
    ASM_KEEP_NV(scratch74);
    scratch74 = (u8 *)((u32)scratch74 | 0x74);
    sp38 = scratch74;
    scratch54 = scratch;
    ASM_KEEP_NV(scratch54);
    scratch54 = (u8 *)((u32)scratch54 | 0x54);
    ASM_KEEP_NV(scratch54);
    mask_low = 0x00FFFFFF;
    ASM_KEEP_NV(mask_low);
    mask_high = 0xFF000000;
    ASM_KEEP(mask_high);
    VFIELD(scratch, s32, 0x88) = FIELD(arg1, s16, 2);
    VFIELD(scratch, s32, 0x8C) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0x90) = FIELD(arg1, s16, 0xA);
    func_800649A0();
    ASM_SCHED_BARRIER();
    VFIELD(scratch, s32, 0x3C) = 0x1000;
    VFIELD(scratch, s32, 0x38) = 0x1000;
    VFIELD(scratch, s32, 0x34) = 0x1000;
    VFIELD(scratch, u16, 0xA4) = FIELD(arg2, u16, 0x16);
    VFIELD(scratch, u16, 0xA8) = FIELD(arg2, u16, 0x1A);
    coord = FIELD(arg2, u16, 0x18);
    tail_a1 = (u8 *)sp38;
    FIELD(scratch, u16, 0xA6) = coord;
    func_80065820(scratch + 0xA4, tail_a1);
    func_80064AE0(&sp18);
    func_80064840(&sp18, sp38, scratch54);
    func_80064BC0(scratch54, scratch + 0x34);
    func_80064D80(scratch54);
    func_80064CF0(scratch54);
    state = global[0];
    state_base = (u8 *)state;
    ASM_KEEP_NV(state_base);
    state = (GlobalState *)state->next;
    state_base += 0xB0;
    VFIELD(scratch, void *, 0x24) = state_base;
    VFIELD(scratch, void *, 0x1C) = state;
    var_s5 = 0;
    if (FIELD(arg0, s16, 0x14) > 0) {
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
                FIELD(temp_s0, s32, 4) = FIELD(arg0, s32, 0);
                FIELD(temp_s0, s8, 4) = (s8)((FIELD(temp_s0, u8, 4) *
                    FIELD(arg0, s16, 0x10)) / FIELD(arg0, s16, 0x12));
                FIELD(temp_s0, u8, 5) = (u8)((FIELD(temp_s0, u8, 5) *
                    FIELD(arg0, s16, 0x10)) / FIELD(arg0, s16, 0x12));
                FIELD(temp_s0, u8, 6) = (u8)((FIELD(temp_s0, u8, 6) *
                    FIELD(arg0, s16, 0x10)) / FIELD(arg0, s16, 0x12));
                FIELD(temp_s0, s8, 3) = 2;
                FIELD(temp_s0, s8, 7) = 0x6A;
                FIELD(temp_s0, u32, 0) =
                    (FIELD(temp_s0, u32, 0) & mask_high) |
                    (FIELD((u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4, u32, 0) & mask_low);
                tail = (u8 *)(VFIELD(scratch, u32, 0x100) * 4);
                tail += (u32)VFIELD(scratch, void *, 0x24);
                combined =
                    (FIELD(tail, u32, 0) & mask_high) |
                    ((u32)temp_s0 & mask_low);
                FIELD(tail, u32, 0) = combined;
                temp_s0_2 = global[0]->next;
                global[0]->next = temp_s0_2 + 0xC;
                func_80067F20(temp_s0_2, 0, 0,
                              func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
                FIELD(temp_s0_2, u32, 0) =
                    (FIELD(temp_s0_2, u32, 0) & mask_high) |
                    (FIELD((u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4, u32, 0) & mask_low);
                state = (GlobalState *)(VFIELD(scratch, u32, 0x100) * 4);
                state = (GlobalState *)((u8 *)state +
                                        (u32)VFIELD(scratch, void *, 0x24));
                FIELD(state, u32, 0) =
                    (FIELD(state, u32, 0) & mask_high) |
                    ((u32)temp_s0_2 & mask_low);
            }
            loop_limit = FIELD(arg0, s16, 0x14);
            ASM_KEEP(loop_limit);
            var_s5 += 1;
            var_s3 += 1;
        } while (var_s5 < loop_limit);
    }
    ASM_USE(scratch54);
    func_80064A40();
    tail = FIELD(arg0, u8 *, -8);
    arg0 = tail + 0x20;
    if (tail != 0) {
        tail_a1 = FIELD(tail, u8 *, 8);
        temp_s0 = FIELD(tail, u8 *, 0xC);
        ASM_USE2(arg0, tail_a1);
        ASM_USE2(tail, temp_s0);
        func_80024A54();
    }
#ifndef __mips__
    hard_zero = 0;
#endif
    result = hard_zero;
    ASM_KEEP(result);
    return result;
}
