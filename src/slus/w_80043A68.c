#include "common.h"

/* Clears the 0x8000 flag bit in 4 fixed sub-table entries (byte offsets 0x78/0x7E/0xFC/0x102
 * from D_8008333C's base pointer) for indices i=10,11 of a dynamically-scaled index
 * (i << D_8008333C.field14) * 6. Counterpart of func_80043B4C (sets the bit instead). */
typedef struct S_80043A68_entry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 flags;
} S_80043A68_entry;

typedef struct S_8008333C {
    /* 0x00 */ u8 *field0;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ s16 field14;
} S_8008333C;

extern S_8008333C D_8008333C;

void func_80043A68(void)
{
    S_8008333C *p = &D_8008333C;
    u8 *base = p->field0;
    s32 i;

    for (i = 10; i < 12; i++) {
        ((S_80043A68_entry *)(base + (i << p->field14) * 6 + 0x78))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (i << p->field14) * 6 + 0x7E))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (i << p->field14) * 6 + 0xFC))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (i << p->field14) * 6 + 0x102))->flags &= 0x7FFF;
    }
}
