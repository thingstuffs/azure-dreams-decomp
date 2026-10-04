/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"

#define M2C_BREAK() 0
#define M2C_SYNC() 0

void func_80047784();
typedef struct Ent Ent;
Ent *func_8009C93C();
s32 func_800A2B5C();
s32 func_800C7930();


/* Initialize action state and directional animation when the entity status permits. */
void func_80172434(Rec_func_800A9E70_arg0 *action_state, void *context, Rec_D_80082E80 *animation,
    EntityRec *entity) {
    entity->unk_71 = (s8) (entity->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930((u8 *)entity - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            func_80047784(animation, *(animation->unk_2C.as_pu8 + (((s32) (gameWork.view.viewAngle + entity->facing
                + 0x100) >> 9) & 7)), 0);
            entity->unk_6D = (u8) (((u8)entity->unk_6D) - 1);
            func_8009C93C(entity, animation, entity->facing, 1, 0);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}
