#include "common.h"

typedef struct S_800A4ACC_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
    s8 unk_2D;
} S_800A4ACC_0;   /* var_s0 in func_800A4ACC */

typedef struct S_800A4ACC_1 {
    s32 unk_00;
} S_800A4ACC_1;   /* arg0 in func_800A4ACC; pointer addresses record offset 0x18 */


extern void func_80042BDC();
extern void func_800A5DFC();

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Advance four status timers toward zero and clear expired statuses. */
s32 func_800A4ACC(void *record) {
    s32 slot_index;
    s8 status;
    s8 duration;
    u8 expired_status;
    void *status_slot;

    slot_index = 3;
    status_slot = record + 6;
next_status:
    status = ((S_800A4ACC_0 *)status_slot)->unk_2C;
    if (status != 0) {
        if (status == 5) {
            func_800A5DFC(record, ((S_800A4ACC_1 *)((u8 *)record - 0x18))->unk_00);
        }
        duration = ((S_800A4ACC_0 *)status_slot)->unk_2D;
        if (duration != 0) {
            if (duration > 0) {
                ((S_800A4ACC_0 *)status_slot)->unk_2D =
                    (s8)((u8)((S_800A4ACC_0 *)status_slot)->unk_2D - 1);
            } else if (duration < 0) {
                ((S_800A4ACC_0 *)status_slot)->unk_2D =
                    (s8)((u8)((S_800A4ACC_0 *)status_slot)->unk_2D + 1);
            }
            if (((S_800A4ACC_0 *)status_slot)->unk_2D == 0) {
                expired_status = (u8)((S_800A4ACC_0 *)status_slot)->unk_2C;
                ((S_800A4ACC_0 *)status_slot)->unk_2C = 0;
                func_80042BDC(record, (s8)expired_status);
            }
        }
    }
    slot_index -= 1;
    status_slot -= 2;
    if (slot_index >= 0) {
        goto next_status;
    }
}
