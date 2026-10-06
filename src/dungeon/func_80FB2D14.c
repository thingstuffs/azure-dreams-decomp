#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
typedef struct Ent Ent;



typedef struct S_80172514_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80172514_1;   /* arg0 in func_80172514 */


extern void func_80047784();
extern Ent *func_8009C93C();
extern s32 func_800A2B5C();
extern s32 func_800C7930();
extern u8 D_80175258[];

/* Reset actor action state and select a facing-dependent animation when status checks pass. */
void func_80172514(void *action_state, s32 action_context, void *sprite, EntityRec *actor) {
    actor->unk_71 &= 0x7F;

    if (!(dungeonStatus.flags & 0x2000) &&
        ((func_800A2B5C(actor) << 16) == 0) &&
        (func_800C7930((u8 *)actor - 0x20, action_context, 8, 0x300),
         ((func_800A2B5C(actor) << 16) == 0))) {
        ((S_80172514_1 *)action_state)->unk_8C = 0;
        ((S_80172514_1 *)action_state)->unk_9B = 0;

        if (((S_80172514_1 *)action_state)->unk_98 & 0x8000) {
            ((S_80172514_1 *)action_state)->unk_9A = 0x17;
            actor->unk_84 = 0x28;
            actor->unk_85 = 0x10;
        } else {
            ((S_80172514_1 *)action_state)->unk_9A = 0x11;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80175258;
        func_80047784(
            sprite,
            D_80175258[((s32)(gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor->unk_6D--;
        func_8009C93C(actor, sprite, actor->facing, 1, 0);
    }
}
