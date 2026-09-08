#include "common.h"

/* Adjusts three 16-bit fields in the record by fixed offsets. */
void func_800A970C(s32 unused, void *record) {
    *(u16 *)((u8 *)record + 0xE) += 0x20;
    *(u16 *)((u8 *)record + 0x12) += 0x4E;
    *(u16 *)((u8 *)record + 0x16) -= 0x1E;
}
