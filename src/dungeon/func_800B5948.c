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

void func_800BB0A8(Func800B5948Object *arg0, s32 arg1, Func800B5948Object *arg2) {
    u16 temp_v0;

    if (D_80083462[0] & 0x10) {
        temp_v0 = arg0->unk1E - 1;
        arg0->unk1E = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            if (arg0->unk1C == 1) {
                func_8009A3D0(arg0->unk10, arg0->unk12, 2);
            } else {
                func_8009A3D0(arg0->unk10, arg0->unk12, 0x10);
            }
            func_800B5F80(arg0->unk20);
            return;
        }
    }
    arg2->unk1A = arg2->unk1A + 0x40;
}
