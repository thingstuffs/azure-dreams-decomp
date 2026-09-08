#include "common.h"

typedef struct TownObject {
    void (*callback)(void);
    s8 pad_04[0x3C];
    u8 *field_40;
} TownObject;

extern s32 D_800814A0[];
extern u8 D_80083160[0xAB];

/* Flags inactive objects; otherwise copies shared bytes and invokes the callback. */
void func_800A2338(TownObject *object, s32 unused, u8 *output) {
    u8 *active_flag;

    active_flag = object->field_40;
    if (active_flag != 0) {
        if (*active_flag == 0) {
            ((u16 *)object)[-1] |= 0x8000;
            D_800814A0[0] |= 0x8000;
            return;
        }
    }

    output[0xC] = D_80083160[0xA8];
    output[0xD] = D_80083160[0xA9];
    output[0xE] = D_80083160[0xAA];
    object->callback();
}
