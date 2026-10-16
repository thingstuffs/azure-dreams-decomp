/* Relink of matched dungeon/func_8105AFCC; every changed retail word is a paired relocation. */
#define D_80170F68 D_80158F68
#define D_80173FE8 D_8015BFE8
#define D_80174010 D_8015C010
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

extern s32 D_80158F68;
extern void *D_800E3DE8[];
extern u8 D_8015BFE8[];
extern u8 D_8015C010[];

typedef struct {
    u8 pad0[0x8C];
    s32 *field8C;
    u8 pad90[6];
    u16 field96;
    u16 field98;
    u8 pad9A;
    u8 field9B;
} Obj0;

typedef struct {
    u8 pad0[0x14];
    u16 field14;
    u8 pad16[0x0E];
    u8 field24;
    u8 field25;
    u8 pad26[6];
    u8 *field2C;
} Obj2;

typedef struct {
    u8 pad0[0x2A];
    s16 field2A;
    u8 pad2C[0x1A];
    u16 field46;
    u8 pad48[0x25];
    s8 field6D;
} Obj3;

extern void func_80047784(Obj2 *, u8, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonSetRecordIntegerTileCenter(void *, u8, u8);
extern void dungeonAdvanceStatusTimers(Obj3 *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(Obj3 *, s32);

/* Advances a timed actor animation and applies its completion effects. */
void func_8015A7CC(Obj0 *action, M2C_UNK context, Obj2 *sprite, Obj3 *actor) {
    s16 ticks_left;
    s32 state;
    s32 volume;

    state = action->field9B;
    ticks_left = action->field96 - 1;
    action->field96 = ticks_left;
    switch (state) {
    case 0:
        if (sprite->field14 & 0x8000) {
            action->field9B = 0xFF;
            sprite->field14 |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->field2A, 1);
            return;
        }
        if (action->field98 & 0x8000) {
            sprite->field2C = D_8015C010;
            ticks_left = 10;
        } else {
            sprite->field2C = D_8015BFE8;
            ticks_left = 4;
        }
        action->field96 = ticks_left;
        func_80047784(sprite, sprite->field2C[(((s32) (gameWork.view.viewAngle + actor->field2A + 0x100) >> 9) & 7)],
            0);
        action->field9B++;
        return;
    case 1:
        if ((ticks_left << 16) > 0)
            return;
        func_800A56E0(0x809);
        dungeonResolveAttackDamageAndEffects(actor, sprite, actor->field2A, 1);
        action->field9B = 0xFF;
        return;
    case 0xFF:
        if ((sprite->field14 & 0xE000) == 0)
            return;
        dungeonSetRecordIntegerTileCenter(context, sprite->field24, sprite->field25);
        volume = 0x100;
        if (action->field98 & 0x8000)
            volume = 0x800;
        dungeonReduceActorFoodMeter(actor, volume);
        action->field8C = &D_80158F68;
        dungeonStatus.unk_0C = 0;
        dungeonAdvanceStatusTimers(actor);
        if (actor->field6D == 0) {
            actor->field46 &= 0x7FFF;
            return;
        }
        *D_800E3DE8 = (void *)((s8 *)actor - 0x20);

        return;
    default:
        return;
    }
}
