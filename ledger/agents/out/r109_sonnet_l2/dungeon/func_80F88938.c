#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

void func_80047784();
void func_8009C93C();
s32 func_800A2B5C();
s32 func_800C7930();

/* Initialize action state and directional animation when the entity status permits. */
void func_80172138(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite,
    EntityRec *entity) {
    entity->unk_71 &= 0x7F;
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930((ObjectNodeHeader *)entity - 1, motion_param, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            func_80047784(sprite,
                          *((u8 *)sprite->frameTable + (((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7)),
                          0);
            entity->unk_6D--;
            func_8009C93C(entity, sprite, entity->facing, 1, 0);
            action_state->unk_98 |= 8;
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}
