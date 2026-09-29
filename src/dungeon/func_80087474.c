#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern void func_80048A44(void *, u8, s32, s32);
extern void func_80094E34(void);
extern s32 func_800A2B04();
extern u8 D_800DD120[];

/* Set the facing animation, reset actor state, and update the map entry. */
void func_8008CBD4(void *actor_state, void *map_entry, void *sprite, void *entity) {
    *(u8 **)((s8 *)sprite + 0x2C) = D_800DD120;
    func_80048A44(sprite, D_800DD120[((gameWork.view.viewAngle + *(s16 *)((s8 *)entity + 0x2A) + 0x100) >> 9) & 7], 0,
        1);
    *(u8 *)((s8 *)actor_state + 0x9A) = 8;
    *(s8 *)((s8 *)actor_state + 0x9B) = 0;
    *(s32 *)((s8 *)actor_state + 0x8C) = 0;
    func_80094E34();
    *(s32 *)((s8 *)entity + 0x1C) &= ~0x1638;
    *(s32 *)((s8 *)map_entry + 0x10) = 0;
    *(s32 *)((s8 *)map_entry + 0xC) = 0;
    func_800A2B04(map_entry, *(u8 *)((s8 *)sprite + 0x24), *(u8 *)((s8 *)sprite + 0x25));
    dungeonStatus.unk_0A += 1;
}
