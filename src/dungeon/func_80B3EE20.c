/* Relink of matched dungeon/func_80B1AE20; every changed retail word is a paired relocation. */
#define D_80170E54 D_8014CE54
#define D_801739F0 D_8014F9F0
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172620_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172620_0;   /* arg0 in func_8014E620 */


extern void func_80047784(void *, u8, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonSetRecordIntegerTileCenter(s32, u8, u8);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);

extern void *D_800E3DE8;
extern s32 D_8014CE54;
extern u8 D_8014F9F0[];

/* Advance the actor's animation state and clean up when it finishes. */
void func_8014E620(void *action, s32 actor_id, void *sprite, EntityRec *actor) {
    s32 state;

    state = ((S_80172620_0 *)action)->unk_9B;
    ((S_80172620_0 *)action)->unk_96--;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172620_0 *)action)->unk_9B = 0xFF;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->facing, 1);
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8014F9F0;
        func_80047784(sprite,
            D_8014F9F0[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172620_0 *)action)->unk_9B++;
        return;

    case 1:
        if (((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 6) &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            func_800A56E0(0x808);
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->facing, 1);
            ((S_80172620_0 *)action)->unk_9B = 0xFF;
        }
        return;

    case 0xFF:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            dungeonSetRecordIntegerTileCenter(actor_id, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            dungeonReduceActorFoodMeter(actor, 0x100);
            ((S_80172620_0 *)action)->unk_8C = &D_8014CE54;
            dungeonStatus.unk_0C = 0;
            dungeonAdvanceStatusTimers(actor);
            if (actor->unk_6D == 0) {
                actor->unk_46 &= 0x7FFF;
                return;
            }
            D_800E3DE8 = (u8 *)actor - 0x20;
        }
        return;
    }
}
