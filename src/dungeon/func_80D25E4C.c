#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8017364C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017364C_0;   /* arg0 in func_8016164C */

typedef struct S_8017364C_2 {
    u8 * unk_00;
} S_8017364C_2;   /* (u8 *)var_v0 - 0x14 in func_8016164C */


/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8003F270(void);                 /* extern */
void func_80047784();         /* extern */
s32 func_80069EF8();                                /* extern */
void *func_800A05A4();      /* extern */
void func_800A2B04();              /* extern */
s32 func_800A4ACC();                      /* extern */
s32 func_800A56E0();                     /* extern */
s32 func_800A94A0();       /* extern */
void func_8015F020(); /* extern */
extern M2C_UNK D_8015F760;
extern u8 D_80162E88[9];

/* Updates an actor's ability action, effects, and completion state. */
void func_8016164C(void *action, EntityRec *motion, void *sprite, EntityRec *actor) {
    s16 next_effect;
    s16 effect_count;
    s32 ability_id;
    s32 normal_ability;
    s16 use_player;
    u16 effect_ticks;
    u16 finish_ticks;
    u8 *ability;
    s32 phase;
    void *target;
    u8 *target_sprite;

    phase = ((S_8017364C_0 *)action)->unk_9B;
    use_player = 0;
    switch (phase) {
    case 0:
        if (actor->flags1C & 0x2000) {
            ability_id = actor->unk_46 & 0x3FFF;
            switch (ability_id) {
            case 7:
                use_player = 1;
            case 3:
                ability = (u8 *)actor + 0xE;
                break;
            case 6:
                use_player = 1;
            case 2:
                ability = (u8 *)actor + 0xB;
                break;
            case 5:
                use_player = 1;
            case 1:
                ability = (u8 *)actor + 8;
                break;
            default:
                ability = NULL;
                break;
            }
        } else {
            normal_ability = actor->unk_46 & 0x3FFF;
            switch (normal_ability) {
            case 3:
                ability = (u8 *)actor + 0xE;
                break;
            case 2:
                ability = (u8 *)actor + 0xB;
                break;
            case 1:
                ability = (u8 *)actor + 8;
                break;
            default:
                ability = NULL;
                break;
            }
        }
        if (*ability != 0) {
            ((S_8017364C_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 player_target = use_player;
                if (player_target) {
                    target = D_800814A8;
                    actor->target = target;
                    {
                        target_sprite =
                            ((S_8017364C_2 *)((u8 *)target - 0x14))->unk_00;
                        actor->unk_72 = target_sprite[0x24];
                        actor->unk_73 = target_sprite[0x25];
                    }
                } else {
                    u8 *ability_table;
                    u8 ability_kind;
                    u32 ability_entry;

                    ability_kind = *ability;
                    ability_table = (u8 *)D_8006DE24;
                    ability_entry = ability_kind * 20;
                    ability_entry += (u32)ability_table;
                    if (((u8 *)ability_entry)[0x12] == 2) {
                        target = actor->target;
                        if (target != NULL) {
                            {
                                target_sprite =
                                    ((S_8017364C_2 *)((u8 *)target - 0x14))->unk_00;
                                actor->unk_72 = target_sprite[0x24];
                                actor->unk_73 = target_sprite[0x25];
                            }
                        }
                    } else {
                        {
                            s32 x = (s32)func_800A05A4(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
                                          ((Rec_D_80082E80 *)sprite)->unk_25,
                                          actor->facing, 0x10);
                            s32 y;

                            *(void * volatile *)((u8 *)actor + 0x60) = (void *)x;
                            x = actor->unk_72;
                            y = actor->unk_73;
                            if (x < 0) {
                                x = -x;
                            }
                            if (y < 0) {
                                y = -y;
                            }
                            actor->unk_72 = x;
                            actor->unk_73 = y;
                        }
                    }
                }
            }
            if (func_800A94A0(actor, ability, use_player, action + 0x98) == 0) {
                return;
            }
            ((S_8017364C_0 *)action)->unk_96 = 0x13U;
            ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
            return;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
            func_800A4ACC(actor);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            ((S_8017364C_0 *)action)->unk_8C = &D_8015F760;
            actor->unk_73 = 0;
            actor->unk_72 = 0;
            actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
            return;
        }
    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v
                | 0x800);
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
        ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
        func_800A56E0(0x703);
    case 2:
        effect_ticks = ((S_8017364C_0 *)action)->unk_96 - 1;
        ((S_8017364C_0 *)action)->unk_96 = effect_ticks;
        if ((effect_ticks << 0x10) <= 0 || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((S_8017364C_0 *)action)->unk_98 = (u16) (((S_8017364C_0 *)action)->unk_98 | 0x80);
            ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v
                | 0x800);
            ((S_8017364C_0 *)action)->unk_96 = 0xFU;
        }
        if ((u32) (((S_8017364C_0 *)action)->unk_96 - 9) >= 6U) {
            return;
        }
        effect_count = 0;
        do {
            func_8015F020(action - 0x20, 0, 0xC0C0, (func_80069EF8() & 0xFF) | 0x80, 0, 0, 0);
            next_effect = effect_count + 1;
            effect_count = next_effect;
        } while (next_effect < 0xA);
        return;
    case 3:
        if (((s32)dungeonStatus.unk_0C) == 0) {
            ((S_8017364C_0 *)action)->unk_96 = 0U;
        }
        finish_ticks = ((S_8017364C_0 *)action)->unk_96 - 1;
        ((S_8017364C_0 *)action)->unk_96 = finish_ticks;
        if ((finish_ticks << 0x10) <= 0) {
            ((S_8017364C_0 *)action)->unk_96 = 0U;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v =
                (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pm != D_80162E88) {
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = D_80162E88;
            func_80047784(sprite, D_80162E88[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v =
                (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
        }
        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
        ((S_8017364C_0 *)action)->unk_8C = &D_8015F760;
        func_800A4ACC(actor);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        func_800A56E0(0xB4);
        return;
    }
}
