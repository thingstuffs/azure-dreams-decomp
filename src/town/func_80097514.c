#include "common.h"
#include "m2c_compat.h"

s32 func_8003BD84();                        /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s16 func_80094BC8();                        /* extern */
extern u8 D_80083160[];

typedef struct {
    u8 pad[0xC];
    s32 x;
    s32 y;
} Func97514Object;

typedef struct S_80094C74_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xBC];
    s16 unk_C8;
} S_80094C74_0;   /* global_base in func_80094C74 */

void func_80094C74(Func97514Object *arg0) {
    u8 *global_base;
    s16 angle;
    s32 delta_x;
    s32 delta_y;
    s32 old_magnitude;
    s32 new_magnitude;

    global_base = D_80083160;
    angle = func_80094BC8(((S_80094C74_0 *)global_base)->unk_08, ((S_80094C74_0 *)global_base)->unk_C8);
    if (angle != -1) {
        register s32 rounded_new ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 adjusted_new ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 rounded_old ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 divisor;
        s32 dividend;
        register s32 quotient ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 second_quotient ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 scaled_value;

        delta_x = func_800644B8(angle) << 6;
        delta_y = func_80064584(angle) << 6;
        old_magnitude = func_8003BD84(arg0->x, arg0->y);
        if (old_magnitude <= 0x7FFFF) {
            old_magnitude = 0x80000;
        }
        arg0->x += delta_x;
        arg0->y += delta_y;
        new_magnitude = func_8003BD84(arg0->x, arg0->y);
        if (old_magnitude < new_magnitude) {
            rounded_new = new_magnitude + 0xFFF;
            adjusted_new = rounded_new;
            if (rounded_new < 0) {
                adjusted_new = new_magnitude + 0x1FFE;
            }
            divisor = adjusted_new >> 0xC;
            dividend = arg0->x;
            quotient = dividend / divisor;
            rounded_old = old_magnitude;
            if (old_magnitude < 0) {
                rounded_old = old_magnitude + 0xFFF;
            }
            rounded_old >>= 0xC;
            scaled_value = quotient * rounded_old;
            *(volatile s32 *)&arg0->x = scaled_value;
            dividend = *(volatile s32 *)&arg0->y;
            second_quotient = dividend / divisor;
            scaled_value = second_quotient * rounded_old;
            arg0->y = scaled_value;
        }
    }
}

/* MECHANISM: A held D_80083160 base, void ABI, and typed x/y compound updates establish the exact frame and saved-register roles.
   Post-call guarded a0/a1/v1/a2/a3 lifetimes reproduce the two signed-rounding divisions and product/store order.
   Paired volatile x-store/y-load preserves the divide-hazard nops; the rebuilt shape selects exact 2.7.2-cdk-G0 codegen. */
