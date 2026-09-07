#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef void (*Callback)(s32, void *, void *, void *);

typedef struct {
    u8 pad[0x3160];
    u8 *table[3];
} GlobalPage;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);

extern void func_800D0918(void) __attribute__((noreturn));
extern void func_800D09C4(void) __attribute__((noreturn));
extern void func_800D0A38(void) __attribute__((noreturn));
extern void func_800D0C14(void) __attribute__((noreturn));
extern void func_800D0C64(void) __attribute__((noreturn));
extern void func_800D0D78(void) __attribute__((noreturn));

extern u8 *D_80083160[3];
extern GlobalPage D_80080000;
__asm__(".set D_80080000, 0x80080000");

void func_800D07C8(s32 arg0, u8 *arg1, u8 *arg2, s16 arg3) {
    u8 matrix[32];
    register u8 *scratch ASM_REG("$17") = (u8 *)0x1F800000;
    u8 *temp_s0;
    register u8 *temp_s2 ASM_REG("$18");
    u8 *temp_s3;
    register u8 *temp_s4 ASM_REG("$20");
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_v0_7;
    register u16 temp_v1_3 ASM_REG("$3");
    register u8 temp_a0_2 ASM_REG("$4");
    register u8 var_v0 ASM_REG("$2");
    register GlobalPage *global_page ASM_REG("$4") = &D_80080000;
    Callback callback;

    FIELD(scratch, void *, 0x20) = global_page->table[0] + 0xB0;
    FIELD(scratch, s32, 0xE4) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0xE8) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0xEC) = FIELD(arg1, s16, 0xA);
    FIELD(scratch, s16, 0x8C) = 0;
    FIELD(scratch, s16, 0x84) = 0;
    FIELD(scratch, s16, 0x7C) = 0;
    FIELD(scratch, s16, 0x74) = 0;
    temp_s4 = FIELD(global_page->table[0], u8 *, 0x8D0);
    FIELD(arg2, u16, 0x14) |= 0x8000;
    func_800649A0();
    FIELD(scratch, u16, 0x108) = FIELD(arg2, u16, 0x20);
    FIELD(scratch, u16, 0x10A) = FIELD(arg2, u16, 0x22);
    FIELD(scratch, s32, 0x30) = FIELD(arg2, u16, 0x1C) * 2;
    FIELD(scratch, s32, 0x34) = FIELD(arg2, u16, 0x1E) * 2;
    FIELD(scratch, s32, 0x38) = 0;
    FIELD(scratch, u16, 0x100) = FIELD(arg2, u16, 0x16);
    FIELD(scratch, u16, 0x104) = FIELD(arg2, u16, 0x1A);
    FIELD(scratch, u16, 0x102) = FIELD(arg2, u16, 0x18);
    func_80065820(scratch + 0x100, scratch + 0xD0);
    temp_s0 = temp_s4 + 7;
    func_80064AE0(matrix);
    func_80064840(matrix, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    temp_s3 = FIELD(arg2, u8 *, 8);
    temp_s2 = temp_s3 + 8;
    ASM_KEEP_NV(temp_s2);
    FIELD(scratch, u16, 0x24) = FIELD(arg2, u16, 0x14);
    if (!(FIELD(temp_s3, u8, 0) & 0x20)) {
        FIELD(scratch, s32, 0x08) = FIELD(temp_s2, u8, 0);
        FIELD(scratch, s32, 0x0C) = FIELD(temp_s2, u8, 1);
        FIELD(scratch, s32, 0x10) = FIELD(temp_s2, u8, 2);
        FIELD(scratch, s32, 0x14) = FIELD(temp_s2, u8, 3);
        if ((FIELD(temp_s3, u8, 0) ^ FIELD(scratch, u16, 0x24)) & 1) {
            register s32 continuation_v0 ASM_REG("$2");
            continuation_v0 = (0 - (s8)FIELD(temp_s2, volatile u8, -6)) - FIELD(scratch, u16, 0x108);
            FIELD(scratch, s16, 0x80) = continuation_v0;
            FIELD(scratch, s16, 0x70) = continuation_v0;
            continuation_v0 -= FIELD(scratch, u16, 0x10);
            ASM_TAILSLOT_PIN(continuation_v0);
            func_800D09C4();
        }
        temp_v0_2 = (s8)FIELD(temp_s2, u8, -6) - FIELD(scratch, u16, 0x108);
        FIELD(scratch, s16, 0x80) = temp_v0_2;
        FIELD(scratch, s16, 0x70) = temp_v0_2;
        temp_v0_3 = temp_v0_2 + FIELD(scratch, u16, 0x10);
        FIELD(scratch, s16, 0x88) = temp_v0_3;
        FIELD(scratch, s16, 0x78) = temp_v0_3;
        if ((FIELD(temp_s3, u8, 0) ^ FIELD(scratch, u16, 0x24)) & 2) {
            register s32 continuation_v0 ASM_REG("$2");
            continuation_v0 = (0 - (s8)FIELD(temp_s2, volatile u8, -5)) - FIELD(scratch, u16, 0x10A);
            FIELD(scratch, s16, 0x7A) = continuation_v0;
            FIELD(scratch, s16, 0x72) = continuation_v0;
            continuation_v0 -= FIELD(scratch, u16, 0x14);
            ASM_TAILSLOT_PIN(continuation_v0);
            func_800D0A38();
        }
        temp_v0_5 = (s8)FIELD(temp_s2, u8, -5) - FIELD(scratch, u16, 0x10A);
        FIELD(scratch, s16, 0x7A) = temp_v0_5;
        FIELD(scratch, s16, 0x72) = temp_v0_5;
        temp_v0_6 = temp_v0_5 + FIELD(scratch, u16, 0x14);
        FIELD(scratch, s16, 0x8A) = temp_v0_6;
        FIELD(scratch, s16, 0x82) = temp_v0_6;

        ASM_KEEP(scratch);
        temp_v0_7 = (func_80065590(scratch + 0x70, scratch + 0x78,
                                   scratch + 0x80, scratch + 0x88,
                                   temp_s4 + 8, temp_s4 + 0x14,
                                   temp_s4 + 0x20, temp_s4 + 0x2C,
                                   scratch + 0x90, scratch + 0x94) - arg3) - 6;
        FIELD(scratch, s32, 0xC0) = temp_v0_7;
        if (temp_v0_7 < 0x1E0U) {
            var_a1 = 0;
            if ((u32)((FIELD(temp_s0, u16, 1) + 0x20) & 0xFFFF) < 0x181U) {
                register u32 masked ASM_REG("$2");
                masked = (u32)((FIELD(temp_s0, u16, 3) + 0x20) & 0xFFFF);
                var_a1 = masked < 0x121U;
            }
            var_v1 = 0;
            if ((u32)((FIELD(temp_s0, u16, 0xD) + 0x20) & 0xFFFF) < 0x181U) {
                register u32 masked ASM_REG("$2");
                masked = (u32)((FIELD(temp_s0, u16, 0xF) + 0x20) & 0xFFFF);
                var_v1 = masked < 0x121U;
            }
            var_a0 = 0;
            temp_a1 = var_a1 | var_v1;
            if ((u32)((FIELD(temp_s0, u16, 0x19) + 0x20) & 0xFFFF) < 0x181U) {
                register u32 masked ASM_REG("$2");
                masked = (u32)((FIELD(temp_s0, u16, 0x1B) + 0x20) & 0xFFFF);
                var_a0 = masked < 0x121U;
            }
            var_v1_2 = 0;
            temp_a0 = temp_a1 | var_a0;
            if ((u32)((FIELD(temp_s0, u16, 0x25) + 0x20) & 0xFFFF) < 0x181U) {
                register u32 masked ASM_REG("$2");
                masked = (u32)((FIELD(temp_s0, u16, 0x27) + 0x20) & 0xFFFF);
                var_v1_2 = masked < 0x121U;
            }
            if ((temp_a0 | var_v1_2) != 0) {
                FIELD(arg2, u16, 0x14) &= 0x7FFF;
                temp_v1 = FIELD(scratch, s32, 0x10) + FIELD(scratch, s32, 0x08);
                FIELD(scratch, s32, 0x10) = temp_v1;
                if (temp_v1 & 0x100) {
                    FIELD(scratch, s32, 0x10) = temp_v1 - 1;
                }
                temp_v1_2 = FIELD(scratch, s32, 0x14) + FIELD(scratch, s32, 0x0C);
                FIELD(scratch, s32, 0x14) = temp_v1_2;
                if (temp_v1_2 & 0x100) {
                    FIELD(scratch, s32, 0x14) = temp_v1_2 - 1;
                }
                FIELD(scratch, s32, 0x0C) <<= 8;
                FIELD(scratch, s32, 0x14) <<= 8;
                if (FIELD(scratch, u16, 0x24) & 0x100) {
                    FIELD(temp_s0, s16, 7) = FIELD(arg2, u16, 0x12);
                    func_800D0C14();
                }
                FIELD(temp_s0, s16, 7) = FIELD(arg2, u16, 0x12) + FIELD(temp_s2, u16, -2);
                FIELD(temp_s0, s16, 5) = FIELD(scratch, u16, 0x0C) + FIELD(scratch, u16, 0x08);
                FIELD(temp_s0, s16, 0x11) = FIELD(scratch, u16, 0x0C) + FIELD(scratch, u16, 0x10);
                {
                    s32 continuation_base = FIELD(arg2, u16, 0x10);
                    if (continuation_base != 0) {
                        register s32 continuation_v0 ASM_REG("$2");
                        continuation_v0 = continuation_base + (FIELD(temp_s2, u16, -4) & 0xFF9F);
                        ASM_TAILSLOT_PIN(continuation_v0);
                        func_800D0C64();
                    }
                }
                FIELD(temp_s0, u16, 0x13) = FIELD(temp_s2, u16, -4);
                FIELD(temp_s0, s16, 0x1D) = FIELD(scratch, u16, 0x14) + FIELD(scratch, u16, 0x08);
                FIELD(temp_s0, s16, 0x29) = FIELD(scratch, u16, 0x14) + FIELD(scratch, u16, 0x10);
                if (FIELD(temp_s0, s16, 1) > FIELD(temp_s0, s16, 0x25)) {
                    FIELD(temp_s0, u8, 0x11)--;
                    FIELD(temp_s0, u8, 0x29)--;
                }
                if (FIELD(temp_s0, s16, 3) > FIELD(temp_s0, s16, 0x27)) {
                    FIELD(temp_s0, u8, 0x1E)--;
                    FIELD(temp_s0, u8, 0x2A)--;
                }
                temp_v0_8 = FIELD(arg2, s32, 0xC);
                FIELD(temp_s0, s32, 0x21) = 0;
                FIELD(temp_s0, s32, 0x15) = 0;
                FIELD(temp_s0, s8, -4) = 0xC;
                FIELD(temp_s0, s32, 9) = temp_v0_8;
                FIELD(temp_s0, s32, -3) = temp_v0_8;
                temp_a0_2 = FIELD(temp_s2, u8, -7);
                FIELD(temp_s0, u8, 0) = temp_a0_2;
                temp_v1_3 = FIELD(scratch, u16, 0x24);
                if (temp_v1_3 & 8) {
                    var_v0 = temp_v1_3 & 4;
                    if (var_v0 == 0) {
                        var_v0 = temp_a0_2 & 0xFD;
                    } else {
                        var_v0 = temp_a0_2 | 2;
                    }
                    FIELD(temp_s0, u8, 0) = var_v0;
                }
                {
                    register u8 *call_s4 ASM_REG("$5") = temp_s4;
                    ASM_KEEP_NV(call_s4);
                    temp_s0 += 0x34;
                    temp_s4 += 0x34;
                    func_8006658C(FIELD(scratch, u8 *, 0x20) + (FIELD(scratch, s32, 0xC0) * 4), call_s4);
                }
                ASM_KEEP(temp_s0);
                ASM_KEEP(temp_s4);
                func_800D0D78();
            }
        }
    } else {
        callback = FIELD(temp_s2, Callback, 0);
        if (callback != 0) {
            callback(arg0, arg1, arg2, temp_s3);
        }
    }

    temp_s2 += 0xC;
    if (FIELD(temp_s3, s8, 0) >= 0) {
        temp_s3 += 0xC;
        ASM_KEEP(temp_s2);
        ASM_TAILSLOT_PIN(temp_s3);
        func_800D0918();
    }
    ASM_KEEP(temp_s2);
    func_80064A40();
    {
        register u8 **table ASM_REG("$8") = D_80083160;
        ASM_KEEP(table);
        FIELD(table[0], u8 *, 0x8D0) = temp_s4;
    }
}
