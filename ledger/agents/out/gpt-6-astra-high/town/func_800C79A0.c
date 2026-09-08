#include "common.h"
#include "records/Rec_D_800E3D7C.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800C4174(void *arg0, void *arg1, s32 arg2);

/* Updates and clamps record motion, delegating when the lower bound is reached. */
void func_800C5100(void *context, Rec_D_800E3D7C *record, s32 callback_arg) {
    if (record->unk_08.at00_s32.v == -0x08000000) {
        func_800C4174(context, record, callback_arg);
        return;
    }

    record->unk_10.at00_s32.v += 0xFFFE0000;
    record->unk_14.as_s32 -= 0x8000;
    record->unk_04.at00_s32.v += record->unk_10.at00_s32.v;
    record->unk_08.at00_s32.v += record->unk_14.as_s32;

    if (record->unk_10.at00_s32.v <= (s32)0xFF000000) {
        record->unk_10.at00_s32.v = -0x01000000;
    }
    if (record->unk_14.as_s32 <= (s32)0xFF000000) {
        record->unk_14.as_s32 = -0x01000000;
    }
    if (record->unk_04.at00_s32.v <= (s32)0xF8000000) {
        record->unk_04.at00_s32.v = -0x08000000;
    }
    if (record->unk_08.at00_s32.v <= (s32)0xF8000000) {
        record->unk_08.at00_s32.v = -0x08000000;
    }
}
