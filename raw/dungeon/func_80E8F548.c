#include "common.h"

typedef s32 M2C_UNK;
typedef struct {
    s32 value;
} __attribute__((packed)) unaligned_s32;

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *, s32);
extern s32 func_8004A658(s32, s32);
extern void func_800BC26C(void *, s32, s32, s32);
extern void func_80174E18(void) __attribute__((noreturn));

extern u8 D_80045340[9];
extern u8 D_8006E240[9];
extern u8 D_80174978[9];

void func_80174D48(void *arg0, void *arg1, void *arg2)
{
    s32 temp_a2;
    s32 temp_byte;
    s32 temp_copy;
    register void *first_call_a0 ASM_REG("$4");
    register u32 first_call_page ASM_REG("$5");
    register void *call_a0 ASM_REG("$4");
    register s32 call_zero ASM_REG("$5");
    s32 temp_half;
    void *temp_s1;
    register void *temp_s2 ASM_REG("$18");
    register void *temp_s3 ASM_REG("$19");
    register void *tail_value ASM_REG("$2");
    void *temp_v0;
    void *temp_v1;

    if ((FIELD(arg2, u8, 0x49) != 0) &&
        (temp_v0 = func_8003FC64(0x12), temp_v0 != NULL)) {
        first_call_a0 = temp_v0;
        ASM_KEEP(first_call_a0);
        ASM_SCHED_BARRIER();
        temp_v1 = FIELD(temp_v0, void *, 8);
        ASM_KEEP(temp_v1);
        temp_s2 = arg0;
        temp_copy = FIELD(temp_s2, s32, 0);
        temp_s1 = FIELD(temp_v0, void *, 0xC);
        ASM_SCHED_BARRIER();
        first_call_page = 0x80040000;
        ASM_KEEP(first_call_page);
        FIELD(temp_v1, s32, 0) = temp_copy;
        temp_copy = FIELD(temp_s2, s32, 4);
        ASM_SCHED_BARRIER();
        first_call_page += 0x5340;
        ASM_KEEP(first_call_page);
        FIELD(temp_v1, s32, 4) = temp_copy;
        temp_a2 = FIELD(temp_s2, s32, 8);
        FIELD(temp_v1, s32, 0x10) = 0;
        FIELD(temp_v1, s32, 0xC) = 0;
        FIELD(temp_v1, s32, 0x14) = 0xFFEE0000;
        FIELD(temp_v1, s32, 8) = temp_a2;
        func_8004491C(first_call_a0, (void *)first_call_page, temp_a2);
        FIELD(temp_s1, s32, 0xC) = 0x808080;
        ASM_SCHED_BARRIER();
        temp_half = 0xC90;
        ASM_KEEP(temp_half);
        temp_s3 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_s1, s16, 0x1E) = temp_half;
        FIELD(temp_s1, s16, 0x1C) = temp_half;
        temp_s2 = temp_s3;
        if (FIELD(arg2, u8, 0x49) == 0x12) {
            tail_value = D_8006E240;
            ASM_KEEP(tail_value);
            func_80174E18();
        }
        FIELD(temp_s1, s32, 8) =
            func_8004A658(FIELD(arg2, volatile u8, 0x49),
                          FIELD(arg2, u8, 0x48));
        ASM_KEEP(temp_s2);
        temp_byte = FIELD(arg1, u8, 0x24);
        ASM_KEEP(temp_byte);
        call_a0 = temp_v0;
        ASM_KEEP(call_a0);
        FIELD(temp_s2, s16, 0xA8) = temp_byte;
        temp_byte = FIELD(arg1, u8, 0x25);
        ASM_KEEP(temp_byte);
        call_zero = 0;
        ASM_KEEP(call_zero);
        FIELD(temp_s2, s16, 0xAA) = temp_byte;
        ASM_KEEP(temp_s3);
        FIELD(temp_s3, unaligned_s32, 0x48) = FIELD(arg2, unaligned_s32, 0x48);
        func_800BC26C(call_a0, call_zero, call_zero, call_zero);
        FIELD(temp_v0, void *, 0x10) = D_80174978;
    }
}

/* MECHANISM: Distinct pinned s2/s3 object bases force the retail 0x30 frame and saved-register roles.
   A packed four-byte assignment produces lwl/lwr/swl/swr; named call ABI values fill load-delay slots.
   Fenced split a1 materialization plus the noreturn tail carrier reproduce retail scheduling and tail j. */
