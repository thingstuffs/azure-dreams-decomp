#include "common.h"
#include "records/Rec_D_800E3D7C.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800C4174(void *arg0, void *arg1, s32 arg2);
extern void func_800C51CC(void);



void func_800C5100(void *arg0, Rec_D_800E3D7C *arg1, s32 arg2) {
    if (arg1->unk_08.at00_s32.v == -0x08000000) {
        func_800C4174(arg0, arg1, arg2);
        func_800C51CC();
        return;
    }

    arg1->unk_10.at00_s32.v += 0xFFFE0000;
    arg1->unk_14.as_s32 -= 0x8000;
    arg1->unk_04.at00_s32.v += arg1->unk_10.at00_s32.v;
    arg1->unk_08.at00_s32.v += arg1->unk_14.as_s32;

    if (arg1->unk_10.at00_s32.v <= (s32)0xFF000000) {
        arg1->unk_10.at00_s32.v = -0x01000000;
    }
    if (arg1->unk_14.as_s32 <= (s32)0xFF000000) {
        arg1->unk_14.as_s32 = -0x01000000;
    }
    if (arg1->unk_04.at00_s32.v <= (s32)0xF8000000) {
        arg1->unk_04.at00_s32.v = -0x08000000;
    }
    if (arg1->unk_08.at00_s32.v <= (s32)0xF8000000) {
        arg1->unk_08.at00_s32.v = -0x08000000;
    }
}
