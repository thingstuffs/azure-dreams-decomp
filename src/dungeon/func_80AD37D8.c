/* Relink of matched dungeon/func_80AC77D8; every changed retail word is a paired relocation. */
#define D_80171728 D_80165728
#define D_80174E1C D_80168E1C
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);

extern s32 D_80165728;
extern u8 D_80168E1C[];


typedef struct S_80172FD8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172FD8_0;   /* arg0 in func_80166FD8 */


typedef struct S_80172FD8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FD8_3;   /* arg1 in func_80166FD8 */

/* Advances an actor's timed animation sequence and performs its final cleanup. */
void func_80166FD8(void *sequence, void *motion, void *sprite, EntityRec *actor)
{
    u8 state;

    state = ((S_80172FD8_0 *)sequence)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172FD8_0 *)sequence)->unk_9B = 4;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->facing, 1);
            return;
        }
        ((S_80172FD8_3 *)motion)->unk_14 = 0;
        ((S_80172FD8_3 *)motion)->unk_10 = 0;
        ((S_80172FD8_3 *)motion)->unk_0C = 0;
        ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
        ((S_80172FD8_0 *)sequence)->unk_9B++;
        return;

    case 1:
        if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 4 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            (*(u8 **)((u8 *)sprite + 0x2C)) = D_80168E1C;
            func_80047784(sprite,
                D_80168E1C[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
            ((S_80172FD8_0 *)sequence)->unk_9B++;
            return;
        }
        return;

    case 2:
        if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 9 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->facing, 1);
            ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
            ((S_80172FD8_0 *)sequence)->unk_9B++;
        }
        if (((S_80172FD8_0 *)sequence)->unk_96.s == 6) {
            func_800A56E0(0x808);
            return;
        }
        return;

    case 3:
        if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 6) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
        }
        if (((S_80172FD8_0 *)sequence)->unk_96.s == 15 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
            ((S_80172FD8_0 *)sequence)->unk_9B++;
            return;
        }
        return;

    case 4:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            dungeonReduceActorFoodMeter(actor, 0x100);
            ((S_80172FD8_0 *)sequence)->unk_8C = &D_80165728;
            dungeonStatus.unk_0C = 0;
            dungeonAdvanceStatusTimers(actor);
            actor->unk_46 &= 0x7FFF;
        }
    default:
        return;
    }
}
