#include "common.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 field_2C;
    u8 pad_30[0x50 - 0x30];
} Slot;

extern s32 D_800869B4[3];
extern Slot D_80085FA8[];

/* Return 1 if any slot is active, or 3 if all slots are finished. */
s32 func_80059D60(void) {
    u32 slot_count;
    u32 i;
    Slot *slot;

    i = 0;
    if (D_800869B4[0] != 0) {
        slot_count = D_800869B4[0];
        slot = D_80085FA8;
        do {
            if (slot->field_2C == 0) {
                return 1;
            }
            do {
                i++;
            } while (0);
            slot++;
        } while (i < slot_count);
    }
    return 3;
}
