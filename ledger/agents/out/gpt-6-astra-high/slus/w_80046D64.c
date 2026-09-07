#include "common.h"

/* D_8006E7F0: array of pointers to per-type info records; each record has a
 * u16 count at +0x6 and four u16 word-offsets at +0x8/+0xA/+0xC/+0xE. */
typedef struct S_80046D64_Info {
    u8 pad0[6];
    u16 count; /* 0x6 */
    u16 off8;  /* 0x8 */
    u16 offA;  /* 0xA */
    u16 offC;  /* 0xC */
    u16 offE;  /* 0xE */
} S_80046D64_Info;

extern S_80046D64_Info *D_8006E7F0[];

/* D_80083160: shared state table (own view here); this function only touches
 * a small sub-record living at +0x1DC (five s32 fields; f0 is untouched by
 * this function, f4/f8/fC/f10 are written). */
typedef struct S_80046D64_Dst {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} S_80046D64_Dst;

typedef struct S_80083160_View {
    u8 pad0[0x1DC];
    S_80046D64_Dst sub;
} S_80083160_View;

extern S_80083160_View D_80083160;

/* Sets four list pointers from type offsets and relocates the first list entries. */
void func_80046D64(s32 data_base, s16 type_index)
{
    S_80083160_View *state = &D_80083160;
    S_80046D64_Dst *lists = &state->sub;
    s32 *first_list;
    s32 *entry;
    s32 remaining;

    first_list = (s32 *) (data_base + D_8006E7F0[type_index]->off8 * 4);
    lists->f4 = (s32) first_list;

    entry = first_list;
    remaining = D_8006E7F0[type_index]->count;
    if (remaining > 0) {
        do {
            remaining--;
            *entry += data_base;
            entry++;
        } while (remaining > 0);
    }

    lists->f8 = data_base + D_8006E7F0[type_index]->offA * 4;
    lists->fC = data_base + D_8006E7F0[type_index]->offC * 4;
    lists->f10 = data_base + D_8006E7F0[type_index]->offE * 4;
}
