#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern s32 func_80042900(void *, s32);
extern s32 func_800A6508(void);
extern s32 func_800A6D30(void);

extern u8 D_800E3D40;

s32 func_800CDC18(void *ptr, s32 unused1, s32 unused2, s32 unused3)
{
    s32 source_value;
    register s16 divisor;
    s32 remainder_value;
    s16 value;

    if (*(u8 *)((u8 *)ptr + 0x13) == 0) {
        value = 0;
        if (D_800E3D40 == 0) {
            source_value = func_800A6D30() & 0xFFFF;
            if (((u8)(*(u8 *)((u8 *)ptr + 3))) != 0) {
                remainder_value = source_value % ((s16)((s32)((u8)(*(u8 *)((u8 *)ptr + 3)))));
                value = remainder_value;
            }
        }

        if (func_80042900(ptr, 10) << 16) {
            value = 0xFF;
        }

        if (value < 0x30) {
            *(u16 *)(((u8 *)D_800E3D7C) + 0xA2) |= 0x100;
            dungeonStatus.unk_0A += 1;
        } else if (*(u8 *)((u8 *)ptr + 0x13) == 0) {
                        /* garbage-passthru: a3 is 10 left by func_80042900, not a caller-held C value. */
            func_800A6508();
        }
    }
    return 1;
}
