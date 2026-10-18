#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_transform_from_parent(BankActorState *, s32, SpriteFrameState *, EntityRec *);
extern s32 check_actor_floor_trap(SpriteFrameState *, EntityRec *);
extern u8 D_80174AD4[9];
extern u8 D_80174AFC[9];

/* Update actor and sprite state after checking the target entity. */
void update_bank_actor_sprite_state(BankActorState *actor, s32 action, SpriteFrameState *sprite, EntityRec *target)
{
    if (update_actor_transform_from_parent(actor, action, sprite, target) != 0) {
        if ((check_actor_floor_trap(sprite, target) << 16) > 0) {
            actor->callback = update_bank_actor_state;
            return;
        }
    } else if (sprite->frameTable == D_80174AFC &&
               !(target->flags1C & 0x208)) {
        sprite->frameTable = D_80174AD4;
        func_80047784(sprite,
                      D_80174AD4[((g_game_work.view.viewAngle + target->facing + 0x100) >> 9) & 7],
                      0);
    }
}

