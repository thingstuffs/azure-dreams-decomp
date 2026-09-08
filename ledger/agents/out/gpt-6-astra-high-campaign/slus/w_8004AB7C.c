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

/* Shuffles item pointers in enabled categories and restores item-effect links. */
void func_8004AB7C(void)
{
    s32 category_id;
    S_8004AB7C_CategoryEntry *category;

    func_8003E1FC();
    func_8003F320();
    func_800A6D60(1);
    func_800A6D98(D_80013628.v);

    category = itemCategoryTable;
    for (category_id = 0; category_id < 20; category_id++, category++) {
        if (((s32)category->pad1[0] >> D_80012090.v) & 1) {
            func_8004AA78(category_id);
        }
    }

    func_8004A940();
    func_800A6D60(0);
}
