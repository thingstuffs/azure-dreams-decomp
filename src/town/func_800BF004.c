#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

extern M2C_UNK func_8003DB94();
extern M2C_UNK func_800478B8();
extern M2C_UNK D_800F15E4;


typedef struct S_800BC764_0 {
    u8 pad_00[0x68];
    s16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
} S_800BC764_0;   /* arg0 in func_800BC764 */


/* Waits 60 updates, then processes the record until a reset flag is set. */
void func_800BC764(S_800BC764_0 *context, void *unused, Rec_D_80082E80 *record) {
    s16 state;
    u16 ticks_left;

    state = context->unk_68;
    if (state == 1) {
        goto tick_delay;
    }
    if (state < 2) {
        if (state == 0) {
            goto start_delay;
        }
        return;
    }
    if (state == 2) {
        goto process_record;
    }
    return;

start_delay:
    context->unk_6C = 0x3CU;
    context->unk_68 = (s16) ((u16) context->unk_68 + 1);
tick_delay:
    ticks_left = context->unk_6C - 1;
    context->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        context->unk_68 = (s16) ((u16) context->unk_68 + 1);
        return;
    }
    return;

process_record:
    func_800478B8(record);
    if (record->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(record, &D_800F15E4, 0);
        context->unk_68 = 0;
    }
}
