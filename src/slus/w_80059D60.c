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
    u32 i;
    for (i = 0; i < D_800869B4[0]; i++) {
        if (D_80085FA8[i].field_2C == 0) {
            return 1;
        }
    }
    return 3;
}
