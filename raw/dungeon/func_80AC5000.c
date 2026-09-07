#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define SPAD_U16(off) (*(u16 *)(scratch + (off)))
#define SPAD_U32(off) (*(u32 *)(scratch + (off)))

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_801708FC(void) __attribute__((noreturn));
extern void *D_80083160;

typedef void (*Callback)(void);

extern void func_80171158(void);
extern void func_80171320(void);
extern void func_80171B54(void);
extern void func_80171B80(void);
extern void func_80171B00(void);
extern void func_80171AAC(void);
extern void func_80171AE4(void);
extern void func_80171B44(void);
extern void func_80173020(void);
extern void func_80173070(void);
extern void func_801730E4(void);
extern void func_80173158(void);
extern void func_801731D0(void);
extern void func_8017329C(void);
extern void func_801734CC(void);
extern void func_80173514(void);
extern void func_80173744(void);
extern void func_801737CC(void);
extern void func_8017334C(void);
extern void func_80173344(void);
extern void func_8017333C(void);
extern void func_80173354(void);
extern void func_801732F8(void);
extern void func_801732F0(void);
extern void func_801732E8(void);

struct CallbackBlock {
    Callback callbacks[33];
    u32 vectors[8];
};

const struct CallbackBlock func_80AC5000 __attribute__((section(".text.func_80AC5000"))) = {
    {
        func_80171158, func_80171320, func_80171B54, func_80171B54,
        func_80171B54, func_80171B80, func_80171B00, func_80171B00,
        func_80171B00, func_80171AAC, func_80171AE4, func_80171B80,
        func_80171B80, func_80171B44, func_80173020, func_80173070,
        func_801730E4, func_80173158, func_801731D0, 0,
        func_8017329C, func_801734CC, func_80173514, func_80173744,
        func_801737CC, 0, func_8017334C, func_80173344,
        func_8017333C, func_80173354, func_801732F8, func_801732F0,
        func_801732E8
    },
    {
        0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
        0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001
    }
};

#ifdef __mips__
__asm__(".size func_80AC5000, 644");
#endif

s32 func_80AC50A4(void *arg0, void *arg1)
{
    u32 *temp_a3;
    u32 *temp_v1;
    u32 temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *base;
    register void *call_a0 ASM_REG("$4");
    register void *call_a2 ASM_REG("$6");
    void *call_a3;
    u32 initial_cursor;
    register u32 slot_word ASM_REG("$3");
    u16 coord0;
    u16 coord1;
    u16 coord2;
    register void *state ASM_REG("$19") = arg0;
    register void *input ASM_REG("$8") = arg1;
    register void **global ASM_REG("$21");
    register u8 *scratch ASM_REG("$17");
    register u32 low_mask ASM_REG("$18");
    register u32 high_mask ASM_REG("$20");
    register void *next ASM_REG("$5");

    global = &D_80083160;
    low_mask = 0x00FF0000U;
    ASM_KEEP_NV(low_mask);
    base = D_80083160;
    ASM_KEEP_NV(base);
    low_mask |= 0xFFFFU;
    high_mask = 0xFF000000U;
    ASM_KEEP_NV(high_mask);
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(scratch);
    ASM_SET(scratch);
    initial_cursor = FIELD(base, u32, 0x8D0);
    SPAD_U32(0x24) = (u32)base + 0xB0;
    SPAD_U32(0x1C) = initial_cursor;
    ASM_SCHED_BARRIER();
    call_a0 = scratch + 4;
    ASM_KEEP_NV(call_a0);
    call_a2 = scratch + 0xD0;
    ASM_KEEP_NV(call_a2);
    coord0 = FIELD(input, u16, 2);
    temp_s0 = (void *)FIELD(scratch, volatile u32, 0x1C);
    call_a3 = scratch + 0xD4;
    SPAD_U16(4) = coord0;
    coord1 = FIELD(input, u16, 6);
    arg1 = (u8 *)temp_s0 + 8;
    SPAD_U16(6) = coord1;
    coord2 = FIELD(input, u16, 0xA);
    SPAD_U32(0x1C) = (u32)temp_s0 + 0xC;
    SPAD_U16(8) = coord2;
    ASM_KEEP_NV(input);

    temp_v0 = func_80065420(call_a0, arg1, call_a2, call_a3);
    SPAD_U32(0x100) = temp_v0;
    if (temp_v0 < 0x1E0U) {
        register s32 rand_zero ASM_REG("$4") = 0;
        register s32 rand_one ASM_REG("$5") = 1;
        register u32 state_word ASM_REG("$3");
        register u32 byte_value ASM_REG("$2");
        ASM_KEEP(rand_zero);
        ASM_KEEP(rand_one);
        state_word = FIELD(state, u32, 8);
        ASM_KEEP(state_word);
        byte_value = 2;
        ASM_KEEP_NV(byte_value);
        FIELD(temp_s0, u8, 3) = byte_value;
        byte_value = 0x6A;
        ASM_KEEP_NV(byte_value);
        FIELD(temp_s0, u32, 4) = state_word;
        {
            register u32 red ASM_REG("$3") = FIELD(temp_s0, volatile u8, 4);
            register u32 green ASM_REG("$6") = FIELD(temp_s0, volatile u8, 5);
            register u32 blue ASM_REG("$7") = FIELD(temp_s0, volatile u8, 6);
            ASM_KEEP(red);
            ASM_KEEP(green);
            ASM_KEEP(blue);
        }
        FIELD(temp_s0, u8, 7) = byte_value;
        FIELD(temp_s0, u32, 0) =
            (FIELD(temp_s0, u32, 0) & high_mask) |
            (*(u32 *)(SPAD_U32(0x24) + SPAD_U32(0x100) * 4) & low_mask);
        temp_a3 = (u32 *)(SPAD_U32(0x100) * 4 + SPAD_U32(0x24));
        slot_word = *temp_a3;
        *temp_a3 = (slot_word & high_mask) | ((u32)temp_s0 & low_mask);
        ASM_KEEP_NV(slot_word);

        temp_s0_2 = (void *)SPAD_U32(0x1C);
        SPAD_U32(0x1C) = (u32)temp_s0_2 + 0xC;
        func_80067F20(temp_s0_2, 0, 0,
                      func_80066460(rand_zero, rand_one,
                                    rand_zero, rand_zero) & 0xFFFF, 0);
        FIELD(temp_s0_2, u32, 0) =
            (FIELD(temp_s0_2, u32, 0) & high_mask) |
            (*(u32 *)(SPAD_U32(0x24) + SPAD_U32(0x100) * 4) & low_mask);
        temp_v1 = (u32 *)(SPAD_U32(0x100) * 4 + SPAD_U32(0x24));
        *temp_v1 = (*temp_v1 & high_mask) | ((u32)temp_s0_2 & low_mask);
        ASM_KEEP(low_mask);
        ASM_KEEP(high_mask);
    }

    next = FIELD(state, void *, -8);
    ASM_KEEP(next);
    if (next != 0) {
        register void *tail_arg ASM_REG("$4");
        state = (u8 *)next + 0x20;
        input = FIELD(next, void *, 8);
        ASM_KEEP(state);
        ASM_KEEP(input);
        ASM_KEEP(scratch);
        ASM_SCHED_BARRIER();
        tail_arg = scratch + 4;
        ASM_TAILSLOT_PIN(tail_arg);
        func_801708FC();
    }
    ASM_CLOBBER("$5");
    ASM_KEEP(global);
    FIELD(*global, u32, 0x8D0) = SPAD_U32(0x1C);
    return 0;
}
