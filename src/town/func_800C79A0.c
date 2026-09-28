#include "common.h"
#include "shared/entity.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800C4174(void *arg0, void *arg1, s32 arg2);

/* Updates and clamps record motion, delegating when the lower bound is reached. */
void func_800C5100(void *context, EntityRec *record, s32 callback_arg) {
    if (record->z.v == -0x08000000) {
        func_800C4174(context, record, callback_arg);
        return;
    }

    record->unk_10 += 0xFFFE0000;
    record->flags14 -= 0x8000;
    record->y.v += record->unk_10;
    record->z.v += record->flags14;

    if (record->unk_10 <= (s32)0xFF000000) {
        record->unk_10 = -0x01000000;
    }
    if (record->flags14 <= (s32)0xFF000000) {
        record->flags14 = -0x01000000;
    }
    if (record->y.v <= (s32)0xF8000000) {
        record->y.v = -0x08000000;
    }
    if (record->z.v <= (s32)0xF8000000) {
        record->z.v = -0x08000000;
    }
}
