#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 D_8002694C;
extern s32 D_800814A0;
extern void *D_80024038[];

extern void func_80025560(void) __attribute__((noreturn));
extern void func_800255AC(void) __attribute__((noreturn));

void func_8187BB80(void *arg0, s32 arg1, void *arg2) {
    register u8 *obj ASM_REG("$5") = arg0;
    register u8 *aux ASM_REG("$6") = arg2;
    register s32 one;
    register s32 current ASM_REG("$2");

    ASM_KEEP(obj);
    ASM_KEEP(aux);
    D_8002694C = 1;
    FIELD(obj, u16, 2)--;

    if (FIELD(obj, s32, 0x40) == 0) {
        register s32 y ASM_REG("$3");
        register u32 x ASM_REG("$2");

        FIELD(obj, s16, 0x20) =
            (FIELD(obj, s16, 0x1E) + FIELD(obj, s16, 0x58)) / 2;
        y = (FIELD(obj, s16, 0x2A) + FIELD(obj, s16, 0x60)) / 2;
        FIELD(obj, s16, 0x2C) = y;
        x = *(volatile u16 *)(obj + 0x20);
        ASM_KEEP(y);
        ASM_KEEP(x);
        FIELD(obj, u16, 0x66) = y;
        FIELD(obj, u16, 0x62) = y;
        FIELD(obj, u16, 0x5E) = x;
        FIELD(obj, u16, 0x5A) = x;
    }

    current = FIELD(obj, s32, 0x40);
    one = 1;
    ASM_KEEP(one);
    if (current == one) {
        FIELD(obj, s16, 0x20) =
            (FIELD(obj, s16, 0x1E) + FIELD(obj, s16, 0x58)) / 2;
        FIELD(obj, s16, 0x20) =
            (FIELD(obj, s16, 0x1E) + FIELD(obj, s16, 0x20)) / 2;
        FIELD(obj, s16, 0x2C) =
            (FIELD(obj, s16, 0x2A) + FIELD(obj, s16, 0x60)) / 2;
        FIELD(obj, s16, 0x2C) =
            (FIELD(obj, s16, 0x2A) + FIELD(obj, s16, 0x2C)) / 2;
        FIELD(obj, u16, 0x5A) = FIELD(obj, u16, 0x5E) =
            FIELD(obj, u16, 0x20);
        FIELD(obj, u16, 0x62) = FIELD(obj, u16, 0x66) =
            FIELD(obj, u16, 0x2C);
    }

    if (*(volatile s32 *)(obj + 0x40) == 0x10000) {
        register u32 x ASM_REG("$2") = FIELD(obj, u16, 0x1E);
        register u32 y ASM_REG("$3") = FIELD(obj, u16, 0x2A);

        ASM_KEEP(x);
        ASM_KEEP(y);
        FIELD(obj, u16, 0x5E) = x;
        FIELD(obj, u16, 0x5A) = x;
        FIELD(obj, u16, 0x66) = y;
        FIELD(obj, u16, 0x62) = y;
    }

    if (FIELD(obj, s16, 0x40) == one) {
        s32 dispatch;
        static void *const jt_keep[] = {
            &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
            &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8
        };

        (void)jt_keep;
        FIELD(obj, s16, 0x40) = 0;
        dispatch = FIELD(obj, s16, 0x42);
        if ((u32)dispatch >= 9) {
            goto jt_c8;
        }
        goto *D_80024038[(u32)dispatch];

jt_c0:
        FIELD(obj, s16, 0x42) = 1;
        return func_800255AC();

jt_c1: {
            register u32 value ASM_REG("$2") = FIELD(obj, u8, 0x4C);
            register s32 next ASM_REG("$3") = 2;
            ASM_KEEP(value);
            ASM_TAILSLOT_PIN(next);
            return func_80025560();
        }

jt_c2: {
            register u32 value ASM_REG("$2") = FIELD(obj, u8, 0x4C);
            register s32 next ASM_REG("$3") = 3;
            ASM_KEEP(value);
            ASM_TAILSLOT_PIN(next);
            return func_80025560();
        }

jt_c3: {
            register u32 value ASM_REG("$2") = FIELD(obj, u8, 0x4C);
            register s32 next ASM_REG("$3") = 4;
            ASM_KEEP(value);
            ASM_TAILSLOT_PIN(next);
            return func_80025560();
        }

jt_c4:
        FIELD(obj, s16, 0x42) = 5;
        FIELD(obj, u8, 0x4C) = 0x80;
        FIELD(obj, u8, 0x4D) += 0x20;
        return func_800255AC();

jt_c5: {
            register u32 value ASM_REG("$2") = FIELD(obj, u8, 0x4C);
            register s32 next ASM_REG("$3") = 6;
            ASM_KEEP(value);
            ASM_TAILSLOT_PIN(next);
            return func_80025560();
        }

jt_c6:
        FIELD(obj, s16, 0x42) = 7;
        FIELD(obj, u8, 0x4C) += 0x20;
        return func_800255AC();

jt_c7:
        FIELD(obj, u8, 0x4E) = 0;
        FIELD(obj, u8, 0x4F) = 0;
        FIELD(aux, u8, 0x0D) = 0xFF;
        FIELD(aux, u8, 0x0C) = 0xFF;
        FIELD(aux, u8, 0x0E) = 0;
        FIELD(obj, u8, 0x37) = 0xFF;
        FIELD(obj, u8, 0x36) = 0xFF;
        FIELD(obj, u8, 0x38) = 0;
        FIELD(aux, u16, 0x14) |= 0xC;
        return func_800255AC();
    } else {
        FIELD(obj, u16, 0x40)++;
    }

jt_c8:
    if (FIELD(obj, s16, 2) < 30) {
        FIELD(aux, u8, 0x0C) =
            (FIELD(obj, u8, 0x36) * FIELD(obj, s16, 2)) / 30;
        FIELD(aux, u8, 0x0D) =
            (FIELD(obj, u8, 0x37) * FIELD(obj, s16, 2)) / 30;
        FIELD(aux, u8, 0x0E) =
            (FIELD(obj, u8, 0x38) * FIELD(obj, s16, 2)) / 30;
    }
    ASM_USE_NV(one);

    if (FIELD(obj, s16, 2) <= 0) {
        FIELD(obj, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
