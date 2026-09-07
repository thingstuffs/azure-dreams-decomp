#include "common.h"

/* Item-category table entry: kind at 0x0 selects 12-byte vs 20-byte record
 * layout; records pointer at 0xC. Only the byte at offset 0x1 is read here as a
 * per-category bit-flag byte. Established layout from src/w_8004A658.c. */
typedef struct S_8004AB7C_CategoryEntry {
    u8 kind;
    u8 pad1[11];
    void *records;
    u8 pad2[4];
} S_8004AB7C_CategoryEntry;

extern S_8004AB7C_CategoryEntry itemCategoryTable[];

/* Force hi/lo access rather than a small-data scalar load. */
extern struct {
    s32 v;
    s32 pad[2];
} D_80012090;

extern struct {
    s32 v;
    s32 pad[2];
} D_80013628;

extern void func_8003E1FC(void);
extern void func_8003F320(void);
extern void func_800A6D60(s32 a0);
extern void func_800A6D98(s32 a0);
extern void func_8004AA78(s32 a0);
extern void func_8004A940(void);

void func_8004AB7C(void)
{
    s32 i;
    S_8004AB7C_CategoryEntry *entry;

    func_8003E1FC();
    func_8003F320();
    func_800A6D60(1);
    func_800A6D98(D_80013628.v);

    entry = itemCategoryTable;
    for (i = 0; i < 20; i++, entry++) {
        if (((s32)entry->pad1[0] >> D_80012090.v) & 1) {
            func_8004AA78(i);
        }
    }

    func_8004A940();
    func_800A6D60(0);
}
