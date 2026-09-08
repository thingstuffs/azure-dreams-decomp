#include "common.h"

typedef struct {
    s8 pad00[4];
    s32 unk04;
    s8 pad08[0x10];
    s32 unk18;
    s8 pad1C[4];
    u8 *unk20;
} UnkStruct800B023C;

extern s32 func_800AD968(void);
extern s32 func_800AD914(u8 *arg0);

/* Checks whether the entry bypasses the limit or its combined value is below 20. */
s32 func_800AD99C(UnkStruct800B023C *entry) {
    s32 total;

    if (entry->unk18 == 0) {
        if ((u32) (entry->unk20[(entry->unk04 * 4) + 1] - 0x17) < 2U) {
            return 1;
        }
        total = func_800AD968();
        total += func_800AD914(entry->unk20);
        return total < 20;
    }
    return 1;
}
