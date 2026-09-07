#include "common.h"

/* Sound driver "sequence slot" table; 8 entries, 12 bytes each. */
typedef struct S_80086C00 {
    s16 field_0;   /* 0x0: -1 == free slot */
    s16 field_2;   /* 0x2: type/status */
    s32 field_4;   /* 0x4: data pointer / word value */
    u16 field_8;   /* 0x8 */
    u16 field_A;   /* 0xA */
} S_80086C00;

extern S_80086C00 D_80086C00[8];

/* Registers a MIDI/SEQ header (a0) that matches one of three known magic
   signatures ("pQES"/SEQ, "MThd"/MIDI, "KDT ") into the first free slot of
   D_80086C00[] (field_0 == -1), storing a1 into field_0 and marking
   field_2 = 2. Returns the slot index, or -1 if the header wasn't
   recognised or no free slot was found. */
s16 func_8005AE08(void *a0, s32 a1)
{
    u32 magic = *(u32 *)a0;
    S_80086C00 *p;
    s32 i;
    s32 free_val;

    if (magic == 0x53455170 || magic == 0x6468544D || magic == 0x2054444B) {
        goto search;
    }
    return -1;

found:
    p->field_4 = (s32)a0;
    p->field_0 = a1;
    p->field_2 = 2;
    return i;

search:
    i = 0;
    free_val = -1;
    p = D_80086C00;
loop:
    if (p->field_0 == free_val) {
        goto found;
    }
    i++;
    p++;
    if (i < 8) {
        goto loop;
    }
    return -1;
}
