/* Relink of matched dungeon/func_80BC32AC; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct Ent Ent;
Ent *dungeonPrepareDirectionalAttack(); /* extern */
s32 func_800A2B5C();                          /* extern */
s32 dungeonApplyCameraOffsetAndSelectTarget(); /* extern */


typedef struct S_80172AAC_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172AAC_1;   /* arg0 in func_8016CAAC */

/* Clears an actor flag, applies a conditional effect, and updates its action state. */
void func_8016CAAC(S_80172AAC_1 *action_state, void *effect_context, void *action_context, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, effect_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A = 0x11;
            action_state->unk_9B = 0;
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            dungeonPrepareDirectionalAttack(actor, action_context, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 4;
        }
    }
}
