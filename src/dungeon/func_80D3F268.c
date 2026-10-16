#include "common.h"
#include "shared/game_work.h"

extern s32 func_800AC82C(void *, s32, void *, void *);
extern s32 dungeonCheckActorFloorTrap(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void createOwnerLinkedDirectionalObject(void *, s32, void *);

extern u8 D_800E23E0[];
extern u8 D_800E2428[];
extern u8 D_80171A80[];

/* Selects a response state or updates the sprite's directional animation. */
void dungeonUpdateActorActionTransition(void *state, s32 update_mode, void *sprite, void *entity)
{
    if (func_800AC82C(state, update_mode, sprite, entity) != 0) {
        if ((dungeonCheckActorFloorTrap(sprite, entity) << 16) > 0) {
            *(void **)((u8 *)state + 0x8C) = D_80171A80;
            return;
        }
    } else if (*(void **)((u8 *)sprite + 0x2C) == D_800E2428 &&
               !(*(s32 *)((u8 *)entity + 0x1C) & 0x208)) {
        u8 *direction_frames;

        direction_frames = D_800E23E0;
        *(void **)((u8 *)sprite + 0x2C) = direction_frames;
        func_80047784(
            sprite,
            direction_frames[((gameWork.view.viewAngle + *(s16 *)((u8 *)entity + 0x2A) + 0x100) >> 9) & 7],
            0);
        if (*(u8 *)((u8 *)state + 0xB0) == 0) {
            createOwnerLinkedDirectionalObject(state, update_mode, sprite);
        }
    }
}
