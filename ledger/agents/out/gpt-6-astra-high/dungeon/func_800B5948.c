#include "common.h"

typedef struct {
    u8 pad00[0x10];
    s16 unk10;
    s16 unk12;
    u8 pad14[6];
    u16 unk1A;
    s16 unk1C;
    u16 unk1E;
    s16 unk20;
} Func800B5948Object;

extern u16 D_80083462[5];
extern void func_8009A3D0(s16, s16, s32);
extern void func_800B5F80(s16);

/* Updates the object's countdown and triggers an effect when it expires. */
void func_800BB0A8(Func800B5948Object *object, s32 unused, Func800B5948Object *related_object) {
    u16 ticks_left;

    if (D_80083462[0] & 0x10) {
        ticks_left = object->unk1E - 1;
        object->unk1E = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            if (object->unk1C == 1) {
                func_8009A3D0(object->unk10, object->unk12, 2);
            } else {
                func_8009A3D0(object->unk10, object->unk12, 0x10);
            }
            func_800B5F80(object->unk20);
            return;
        }
    }
    related_object->unk1A = related_object->unk1A + 0x40;
}
