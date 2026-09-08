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

/* Adjust the object vector toward the selected angle and limit its magnitude. */
void func_80094C74(Func97514Object *object) {
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
        s32 magnitude_divisor;
        s32 component;
        register s32 x_quotient ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 y_quotient ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 scaled_component;

        delta_x = func_800644B8(angle) << 6;
        delta_y = func_80064584(angle) << 6;
        old_magnitude = func_8003BD84(object->x, object->y);
        if (old_magnitude <= 0x7FFFF) {
            old_magnitude = 0x80000;
        }
        object->x += delta_x;
        object->y += delta_y;
        new_magnitude = func_8003BD84(object->x, object->y);
        if (old_magnitude < new_magnitude) {
            rounded_new = new_magnitude + 0xFFF;
            adjusted_new = rounded_new;
            if (rounded_new < 0) {
                adjusted_new = new_magnitude + 0x1FFE;
            }
            magnitude_divisor = adjusted_new >> 0xC;
            component = object->x;
            x_quotient = component / magnitude_divisor;
            rounded_old = old_magnitude;
            if (old_magnitude < 0) {
                rounded_old = old_magnitude + 0xFFF;
            }
            rounded_old >>= 0xC;
            scaled_component = x_quotient * rounded_old;
            *(volatile s32 *)&object->x = scaled_component;
            component = *(volatile s32 *)&object->y;
            y_quotient = component / magnitude_divisor;
            scaled_component = y_quotient * rounded_old;
            object->y = scaled_component;
        }
    }
}
