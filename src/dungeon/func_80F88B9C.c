#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonUpdateActorMovementToTile();
extern s32 dungeonCheckActorFloorTrap();

/* Select the bank actor callback when the resident checks succeed. */
void dungeonSelectBankResidentCallback(BankActorState *state, s32 unused, SpriteFrameState *source, EntityRec *target) {
    if (dungeonUpdateActorMovementToTile() != 0) {
        dungeonReduceActorFoodMeter(target, 4);
        dungeonAdvanceStatusTimers(target);
        if ((dungeonCheckActorFloorTrap(source, target) << 16) > 0) {
            state->callback = dungeonUpdateBankActorState;
            if (dungeonStatus.flags & 0x80) {
                state->unk_92 = -0x20;
            }
        }
    } else if (dungeonStatus.flags & 0x80) {
        state->unk_92 = -0x20;
    }
}

