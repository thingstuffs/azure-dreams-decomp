/* Relink of matched dungeon/func_80CBEDB8; every changed retail word is a paired relocation. */
#define D_80170F20 D_80158F20
#define D_801762E8 D_8015E2E8
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801725B8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801725B8_0;   /* arg0 in func_8015A5B8 */


typedef struct S_801725B8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801725B8_3;   /* arg1 in func_8015A5B8 */


extern void func_80047784(void *, s32, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);

extern u8 D_80158F20;
extern u8 D_8015E2E8[];

/* Advances the actor's directional animation and resets its action state on completion. */
void func_8015A5B8(void *action, void *motion, void *anim, EntityRec *actor)
{
    switch (((S_801725B8_0 *)action)->unk_9B) {
    case 0:
        if (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x8000) {
            ((S_801725B8_0 *)action)->unk_9B = 2;
            ((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, anim, actor->facing, 1);
            return;
        }
        {
            u8 *direction_table;

            ((S_801725B8_3 *)motion)->unk_14 = 0;
            ((S_801725B8_3 *)motion)->unk_10 = 0;
            ((S_801725B8_3 *)motion)->unk_0C = 0;
            direction_table = D_8015E2E8;
            (*(u8 * *)((u8 *)anim + 0x2C)) = direction_table;
            func_80047784(anim,
                direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801725B8_0 *)action)->unk_9B++;
        }
        return;

    case 1:
        if (((Rec_D_80082E80 *)anim)->unk_04.as_s8 == 3 && (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (!((((Rec_D_80082E80 *)anim)->unk_04.as_s8 == 6 && (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x1000)) ||
              (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0xE000))) {
            return;
        }
        dungeonResolveAttackDamageAndEffects(actor, anim, actor->facing, 1);
        ((S_801725B8_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 2:
        if (!(((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        dungeonReduceActorFoodMeter(actor, 0x100);
        ((S_801725B8_0 *)action)->unk_8C = &D_80158F20;
        dungeonStatus.unk_0C = 0;
        (actor->unk_46) &= 0x7FFF;
        dungeonAdvanceStatusTimers(actor);
        return;
    }
}
