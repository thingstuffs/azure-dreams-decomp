#include "common.h"

/* Two-level item table lookup: itemCategoryTable[categoryIndex].kind selects whether the
 * itemCategoryTable[categoryIndex].records array (pointed to by the struct's offset0xC field)
 * is laid out as 12-byte or 20-byte records; records[recordIndex]'s signed halfword field
 * at offset 2 is then used as an index into the word table D_8007361C. */
typedef struct S_8004A658_CategoryEntry {
    u8 kind;         /* 0x0: selects 12-byte (nonzero) vs 20-byte (zero) record layout */
    u8 pad1[11];     /* 0x1-0xB: unmodeled fields (a sibling func reads 0x2 as a count, 0x8 as a fn ptr, 0x3 as a byte index) */
    void *records;   /* 0xC: pointer to an array of fixed-size item records */
    u8 pad2[4];      /* 0x10-0x13: unmodeled tail (pads entry to 0x14 = 20 bytes) */
} S_8004A658_CategoryEntry;

typedef struct S_8004A658_RecA { s16 f0; s16 f1; s16 pad[4]; } S_8004A658_RecA;   /* 12-byte record, kind != 0 */
typedef struct S_8004A658_RecB { s16 f0; s16 f1; s16 pad[8]; } S_8004A658_RecB;   /* 20-byte record, kind == 0 */

extern S_8004A658_CategoryEntry itemCategoryTable[];
extern s32 D_8007361C[256];

/* Returns the word-table value selected by an item record in the given category. */
s32 func_8004A658(s32 category_index, s32 record_index)
{
    return D_8007361C[(&itemCategoryTable[category_index])->kind == 0
        ? ((S_8004A658_RecB *)(&itemCategoryTable[category_index])->records)[record_index].f1
        : ((S_8004A658_RecA *)(&itemCategoryTable[category_index])->records)[record_index].f1];
}
