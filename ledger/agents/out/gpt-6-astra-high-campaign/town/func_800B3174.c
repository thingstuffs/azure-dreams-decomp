#include "common.h"

extern s32 func_80048E00(s32, s32*);
extern s32 func_800B0870(s32, s32*);
extern s32 D_800D15C4;

/* Process the record and its subrecord at offset 0x48 using the shared data. */
void func_800B08D4(s32 record_address) {
    func_80048E00(record_address, &D_800D15C4);
    func_800B0870(record_address + 0x48, &D_800D15C4);
}
