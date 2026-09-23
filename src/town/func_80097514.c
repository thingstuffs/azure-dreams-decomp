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
            object->x = object->x / ((new_magnitude + 0xFFF) / 0x1000) * (old_magnitude / 0x1000);
            object->y = object->y / ((new_magnitude + 0xFFF) / 0x1000) * (old_magnitude / 0x1000);
        }
    }
}
