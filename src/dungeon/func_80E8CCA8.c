#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_801724A8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801724A8_0;   /* arg0 in dungeonUpdateTheTargetConditionallyResetsCallerState */


s32 dungeonAdvanceStatusTimers();                     /* extern */
s32 dungeonUpdateActorMovementToTile(move_state, motion, target_tile, actor);                                /* extern */
void dungeonReduceActorFoodMeter();            /* extern */
s32 dungeonCheckActorFloorTrap();                /* extern */
extern M2C_UNK D_801710F4;

/* Updates the target and conditionally resets the caller state. */
void dungeonUpdateTheTargetConditionallyResetsCallerState(S_801724A8_0 *state, s32 context, s32 source, s32 target) {
    if (dungeonUpdateActorMovementToTile(state, context, source, target) != 0) {
        dungeonReduceActorFoodMeter(target, 3);
        dungeonAdvanceStatusTimers(target);
        if ((dungeonCheckActorFloorTrap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = &D_801710F4;
        state->unk_90.at00.v = 0;
    }
    if (dungeonStatus.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
