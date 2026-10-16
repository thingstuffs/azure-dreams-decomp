#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_800D9884_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_800D9884_0;   /* arg0 in dungeonUpdateActorTargetAfterCheck */


s32 dungeonAdvanceStatusTimers();                     /* extern */
s32 dungeonUpdateActorMovementToTile();                                /* extern */
void dungeonReduceActorFoodMeter();            /* extern */
s32 dungeonCheckActorFloorTrap();                /* extern */
extern M2C_UNK D_800D8C64;

/* Updates the target and resets state after a successful check or a reset flag. */
void dungeonUpdateActorTargetAfterCheck(S_800D9884_0 *state, void *unused, void *source, void *target) {
    if (dungeonUpdateActorMovementToTile() != 0) {
        dungeonReduceActorFoodMeter(target, 4);
        dungeonAdvanceStatusTimers(target);
        if ((dungeonCheckActorFloorTrap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = &D_800D8C64;
        state->unk_90.at00.v = 0;
    }
    if (dungeonStatus.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
