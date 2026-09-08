#include "common.h"

typedef struct S_80099FDC_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80099FDC_0;   /* arg0 in func_80099FDC */

typedef struct S_80099FDC_1 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80099FDC_1;   /* owner in func_80099FDC */

typedef struct S_80099FDC_2 {
    u8 pad_00[0x58];
    void * unk_58;
    void * unk_5C;
} S_80099FDC_2;   /* temp_a1 in func_80099FDC */

typedef struct S_80099FDC_3 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_80099FDC_3;   /* temp_v1 in func_80099FDC */



extern void *D_800814A8[3];

/* Clear the entry flag and link the entry into the current owner list. */
void func_80099FDC(void *entry)
{
    S_80099FDC_2 *entry_links;
    S_80099FDC_3 *neighbor_links;
    S_80099FDC_1 *owner;

    owner = D_800814A8[0];
    ((S_80099FDC_0 *)entry)->unk_10 = ((S_80099FDC_0 *)entry)->unk_10 & 0x7FFFFFFF;
    neighbor_links = (u8 *)owner->unk_58 + 0x20;
    entry_links = (u8 *)entry + 0x20;
    entry_links->unk_5C = neighbor_links->unk_5C;
    entry_links->unk_58 = owner->unk_58;
    owner->unk_58 = entry;
    neighbor_links->unk_5C = entry;
}
