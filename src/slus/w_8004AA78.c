#include "common.h"

#include "common.h"

/* 20-byte item record; offset 0xC is the pointer this function shuffles. */
typedef struct S_8004AA78_Rec {
    u8 pad0[0xC];
    s32 ptr;
    u8 pad1[4];
} S_8004AA78_Rec;

/* 20-byte category-table entry: count @0x2, records pointer @0xC. */
typedef struct S_8004AA78_CategoryEntry {
    u8 pad0[2];
    u8 count;
    u8 pad1[9];
    S_8004AA78_Rec *records;
    u8 pad2[4];
} S_8004AA78_CategoryEntry;

/* Stack workspace: indices[0x40] then ptrs[] at +0x40 (matches retail lw offset). */
typedef struct S_8004AA78_Buf {
    u8 indices[0x40];
    s32 ptrs[0x40];
} S_8004AA78_Buf;

extern S_8004AA78_CategoryEntry itemCategoryTable[];
extern void func_8004A9B0(u8 *arg0, s32 arg1);

void func_8004AA78(s32 arg0) {
    S_8004AA78_Buf sp10;
    s32 var_a1;
    s32 var_a2;
    s32 temp_s0;
    S_8004AA78_Rec *temp_s1;
    S_8004AA78_Rec *var_a0;
    u8 *var_v1;
    s32 temp_v0;

    var_a1 = 0;
    temp_s0 = itemCategoryTable[arg0].count;
    temp_s1 = itemCategoryTable[arg0].records;
    var_a2 = 0;
    if (temp_s0 != 0) {
        var_a0 = temp_s1;
        var_v1 = sp10.indices;
        do {
            temp_v0 = var_a0->ptr;
            if (temp_v0 != 0) {
                *(s32 *)(var_v1 + 0x40) = temp_v0;
                var_v1 += 4;
                var_a1 += 1;
            }
            var_a2 += 1;
            var_a0 += 1;
        } while (var_a2 < temp_s0);
    }

    var_a2 = 0;
    if (var_a1 > 0) {
        do {
            sp10.indices[var_a2] = (u8)var_a2;
            var_a2 += 1;
        } while (var_a2 < var_a1);
    }

    func_8004A9B0(sp10.indices, var_a1);

    var_a1 = 0;
    var_a2 = 0;
    if (temp_s0 != 0) {
        /* Indexed form keeps base+0xC (avoids IV strength-reduce to &field). */
        S_8004AA78_Buf *buf = &sp10;
        do {
            temp_v0 = temp_s1[var_a2].ptr;
            if (temp_v0 != 0) {
                temp_v0 = buf->ptrs[buf->indices[var_a1]];
                var_a1 += 1;
                temp_s1[var_a2].ptr = temp_v0;
            }
            var_a2 += 1;
        } while (var_a2 < temp_s0);
    }
}
