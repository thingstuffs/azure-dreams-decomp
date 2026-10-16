/* Relink of matched dungeon/func_80D90E98; every changed retail word is a paired relocation. */
#define D_80170E68 D_80158E68
#define D_80173894 D_8015B894
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_80047784(void *, s32, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonSetRecordIntegerTileCenter(void *, s32, s32);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);

extern void *D_800E3DE8;
extern u8 D_80158E68;
extern u8 D_8015B894[];

/* Advances an actor action through animation setup, a delay, and completion. */
void func_8015A698(void *action, void *motion, void *sprite, void *actor)
{
    s32 phase;
    s32 loaded_phase;
    u16 delay_ticks;

    phase = U8(action, 0x9B);
    switch (phase) {
    case 0:
        if (U16(sprite, 0x14) & 0x8000) {
            U8(action, 0x9B) = 2;
            U16(sprite, 0x14) |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, sprite, S16(actor, 0x2A), 1);
            return;
        }

        S32(motion, 0x14) = 0;
        S32(motion, 0x10) = 0;
        S32(motion, 0x0C) = 0;
        PTR(sprite, 0x2C) = D_8015B894;
        func_80047784(sprite,
            D_8015B894[((gameWork.view.viewAngle + S16(actor, 0x2A) + 0x100) >> 9) & 7],
            0);
        loaded_phase = U8(action, 0x9B);
        U16(action, 0x96) = 0;
        U8(action, 0x9B) = loaded_phase + 1;
        return;

    case 1:
        delay_ticks = U16(action, 0x96) + 1;
        U16(action, 0x96) = delay_ticks;
        if ((s16)delay_ticks != 10) {
            return;
        }
        func_800A56E0(0x808);
        dungeonResolveAttackDamageAndEffects(actor, sprite, S16(actor, 0x2A), 1);
        loaded_phase = U8(action, 0x9B);

        U8(action, 0x9B) = loaded_phase + 1;
        return;

    case 2:
        if (!(U16(sprite, 0x14) & 0xE000)) {
            return;
        }
        dungeonSetRecordIntegerTileCenter(motion, U8(sprite, 0x24), U8(sprite, 0x25));
        dungeonReduceActorFoodMeter(actor, 0x100);
        PTR(action, 0x8C) = &D_80158E68;
        dungeonStatus.unk_0C = 0;
        dungeonAdvanceStatusTimers(actor);
        if (S8(actor, 0x6D) == 0) {
            U16(actor, 0x46) &= 0x7FFF;
        } else {
            D_800E3DE8 = (u8 *)actor - 0x20;
        }

        return;
    }
}
