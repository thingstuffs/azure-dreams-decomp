#include "common.h"

extern void func_80048E00(void *arg0, void *arg1);
extern s32 D_800D15B8;

/* Initialize the record with global data and set its high flag bit. */
void func_800AFDD0(void *record) {
    func_80048E00(record, &D_800D15B8);
    *(u8 *) ((u8 *) record + 0x3C) = *(u8 *) ((u8 *) record + 0x3C) | 0x80;
}
