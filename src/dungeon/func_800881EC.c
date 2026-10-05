#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#ifndef NULL
#define NULL 0
#endif

extern void func_80094E34(void);
extern void func_80048A44(void *a0, s16 a1, s16 a2, s32 a3);

extern u8 D_800DCFF0[8];

void func_8008D94C(u8 *state_ptr, s32 value, u8 *target_ptr, u8 *angle_ptr) {
    u16 flags;
    s32 index;
    u8 *table;

    flags = *(u16 *)(state_ptr + 0xA2);
    *(s8 *)(state_ptr + 0x9A) = 0x24;
    *(s8 *)(state_ptr + 0x9B) = 0;
    *(void **)(state_ptr + 0x8C) = NULL;
    *(u16 *)(state_ptr + 0xA2) = flags & 0xFEFF;
    func_80094E34();

    dungeonStatus.unk_04 = dungeonStatus.unk_04 * 2;
    table = &D_800DCFF0[0];
    *(u8 **)(target_ptr + 0x2C) = table;

    index = ((gameWork.view.viewAngle + *(s16 *)(angle_ptr + 0x2A) + 0x100) >> 9) & 7;
    func_80048A44(target_ptr, table[index], 0, 1);
}
