#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void func_800C78A0(void *, s32, s32, s32, s32, s32);

/* Invokes the placement helper at the tile center using the current entity value. */
void func_80170BC4(void) {
    func_800C78A0(
        ((u8 *)(&dungeonStatus.unk_18)),
        (D_80082E80.tileX << 6) | 0x20,
        (D_80082E80.tileY << 6) | 0x20,
        *(s16 *)((u8 *)D_800E3D7C + 0x88),
        1,
        0x400
        );
}
