#include "common.h"

/* Sets the flags bit 0x8000 on four 6-byte table entries per party-slot index
 * i in [10, 12): entries at byte offsets (i << D_8008333C.field14) * 6 +
 * {0x78, 0x7E, 0xFC, 0x102} from D_8008333C.field0. Sibling func_80043A68
 * clears the same bit (&= 0x7FFF) on the identical index set. */
typedef struct S_80043B4C_entry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 flags;
} S_80043B4C_entry;

typedef struct S_8008333C {
    /* 0x00 */ u8 *field0;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ s16 field14;
} S_8008333C;

extern S_8008333C D_8008333C;

/* Sets flag 0x8000 on four table entries for each party slot from 10 through 11. */
void func_80043B4C(void)
{
    S_8008333C *table = &D_8008333C;
    u8 *entries = table->field0;
    s32 slot;

    for (slot = 10; slot < 12; slot++) {
        ((S_80043B4C_entry *)(entries + (slot << table->field14) * 6 + 0x78))->flags |= 0x8000;
        ((S_80043B4C_entry *)(entries + (slot << table->field14) * 6 + 0x7E))->flags |= 0x8000;
        ((S_80043B4C_entry *)(entries + (slot << table->field14) * 6 + 0xFC))->flags |= 0x8000;
        ((S_80043B4C_entry *)(entries + (slot << table->field14) * 6 + 0x102))->flags |= 0x8000;
    }
}
