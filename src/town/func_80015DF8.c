/* Relink of matched town/func_800B2670; every changed retail word is a paired relocation. */
#define D_800D15B8 D_800D1650
#include "common.h"

extern void func_80048E00(void *cursor, void *pattern_data);
extern s32 D_800D1650;

/* Initialize the record with global data and set its high flag bit. */
void func_800B3558(void *record) {
    func_80048E00(record, &D_800D1650);
    *(u8 *) ((u8 *) record + 0x3C) = *(u8 *) ((u8 *) record + 0x3C) | 0x80;
}
