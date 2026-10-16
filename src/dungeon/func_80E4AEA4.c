/* Relink of matched dungeon/func_80E38EA4; every changed retail word is a paired relocation. */
#define D_80170EE4 D_8015EEE4
#define D_80176600 D_80164600
#define D_80176668 D_80164668
#define dungeonCreateActionSpriteEffect func_80162690
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801726A4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801726A4_0;   /* arg0 in func_801606A4 */


typedef struct S_801726A4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801726A4_3;   /* arg1 in func_801606A4 */


extern void func_80047784(void *, s32, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern void func_80162690(void *);

extern u8 D_8015EEE4[];
extern u8 D_80164600[];
extern u8 D_80164668[];

/* Advances an actor's animation sequence and handles its completion. */
void func_801606A4(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u16 sprite_flags;
    u16 frame_count;
    s32 state;

    state = ((S_801726A4_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((S_801726A4_0 *)action)->unk_98 |= 1;
        ((S_801726A4_0 *)action)->unk_9B++;
                        /* fall through */
    case 1:
        sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
        if (sprite_flags & 0x8000) {
            ((S_801726A4_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->facing, 1);
            return;
        }

        if (sprite_flags & 0x6000) {
            ((S_801726A4_3 *)motion)->unk_0C =
                ((S_801726A4_3 *)motion)->unk_10 =
                ((S_801726A4_3 *)motion)->unk_14 = 0;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80164600;
            func_80047784(sprite,
                D_80164600[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            func_80162690((u8 *)action - 0x20);
            ((S_801726A4_0 *)action)->unk_96 = 0;
            ((S_801726A4_0 *)action)->unk_9B++;
            func_800A56E0(0x804);
            return;
        }
        break;
    case 2:
        frame_count = ((S_801726A4_0 *)action)->unk_96 + 1;
        ((S_801726A4_0 *)action)->unk_96 = frame_count;

        if ((s16)frame_count == state ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->facing, 1);
        }

        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80164668;
            func_80047784(sprite,
                D_80164668[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801726A4_0 *)action)->unk_9B++;
            ((S_801726A4_0 *)action)->unk_98 &= 0xFFFE;
            return;
        }
        break;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            dungeonReduceActorFoodMeter(actor, 0x100);
            ((S_801726A4_0 *)action)->unk_8C = D_8015EEE4;
            dungeonStatus.unk_0C = 0;
            (actor->unk_46) &= 0x7FFF;
            dungeonAdvanceStatusTimers(actor);
        }
    }
}
