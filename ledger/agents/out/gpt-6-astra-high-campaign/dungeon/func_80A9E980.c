#include "common.h"

typedef struct {
    u8 pad[0x1A];
    u16 field_1A;
    u16 field_1C;
    u16 field_1E;
} Object;

extern s32 D_800814A0[3];

/* Advance the object angle and height and set completion flags at height 0x2000. */
void func_80174180(u16 *record_data, s32 unused, Object *object) {
    u16 angle;
    u16 height;

    angle = object->field_1A + 0x320;
    height = object->field_1E + 0x200;
    do { object->field_1E = height; } while (0);
    object->field_1C = height;
    object->field_1A = angle;
    if (height >= 0x2000) {
        record_data[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
