/* Relink of matched dungeon/func_80A48C28; every changed retail word is a paired relocation. */
#define D_8017587C D_8016387C
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"


typedef struct S_80172428_1 {
    u8 pad_00[0x98];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_80172428_1;   /* arg0 in func_80160428 */


void func_80047784();         /* extern */
typedef struct Ent Ent;
Ent *dungeonPrepareDirectionalAttack(); /* extern */
s32 func_800A2B5C();                          /* extern */
s32 dungeonApplyCameraOffsetAndSelectTarget(); /* extern */
extern u8 D_8016387C;

/* Update the actor's action state and directional animation when both checks pass. */
void func_80160428(void *action_state, void *context, void *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((S_80172428_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((S_80172428_1 *)action_state)->unk_9B = 0;
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_8016387C;
            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &D_8016387C), 0);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            dungeonPrepareDirectionalAttack(actor, sprite, actor->facing, 1, 0);
            ((S_80172428_1 *)action_state)->unk_98 = (u16) (((S_80172428_1 *)action_state)->unk_98 | 8);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}
