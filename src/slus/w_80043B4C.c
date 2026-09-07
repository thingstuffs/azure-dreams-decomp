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

void func_80043B4C(void)
{
    S_8008333C *p = &D_8008333C;
    u8 *base = p->field0;
    s32 i;

    for (i = 10; i < 12; i++) {
        ((S_80043B4C_entry *)(base + (i << p->field14) * 6 + 0x78))->flags |= 0x8000;
        ((S_80043B4C_entry *)(base + (i << p->field14) * 6 + 0x7E))->flags |= 0x8000;
        ((S_80043B4C_entry *)(base + (i << p->field14) * 6 + 0xFC))->flags |= 0x8000;
        ((S_80043B4C_entry *)(base + (i << p->field14) * 6 + 0x102))->flags |= 0x8000;
    }
}
