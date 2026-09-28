#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"

typedef struct ActionActor { u8 pad[0x8C]; s32 action; } ActionActor;

extern s32 D_800E4938[];

extern void func_800A56E0(u32);

/* Initialize the actor action state or signal that the action is blocked. */
void func_8008CF6C(void *actor, s32 unused_1, s32 unused_2, s32 action_value) {
    if (!(D_80013714 & 1)) {
        if (D_800E296C & 0x200000) {
            if (((s32)gameWork.unk_010) & 0x80) {
                func_800A56E0(0x506);
                return;
            }
        } else {
            *(u8 *)((u8 *)actor + 0x9A) = 0x19;
            func_800A56E0(0x514);
            D_800E4938[0] = action_value;
            *(u8 *)((u8 *)actor + 0x9B) = 0;
            ((ActionActor *)actor)->action = 0;
            D_80082E80.unk_038 = 0;
            D_800E296C |= 0x2000;
        }
    }
}
