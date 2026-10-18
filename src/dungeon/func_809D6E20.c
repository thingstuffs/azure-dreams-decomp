/* Relink of matched dungeon/func_809CAE20; every changed retail word is a paired relocation. */
#define D_80173CA4 D_80167CA4
#define D_80173CAC D_80167CAC
#define D_80173CB4 D_80167CB4
#define D_80173CBC D_80167CBC
#include "modules/dungeon_resource03_slot0.h"
extern void func_80164E54(void *, void *, void *, void *);
extern s32 rand(void);

void func_80166620(void *action, void *transform, void *sprite, EntityRec *actor)
{
    s32 state;
    void *allocated_effect;
    void *effect = 0;
    void *effect_sprite;
    void *effect_transform;

    ((R03_80172620_S_80172620_0 *)action)->unk_96--;
    state = ((R03_80172620_S_80172620_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((R03_80172620_S_80172620_0 *)action)->unk_9B = 0xFF;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
            return;
        }

        if (rand() & 3) {
            ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 = ((u8 *)D_80167CBC);
            (*(s32 *)((u8 *)action + 0xA4)) = 0;
            func_80047784(sprite,
                ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8
                    [((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((R03_80172620_S_80172620_0 *)action)->unk_9B = 3;
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80167CA4);
        func_80047784(sprite,
            ((u8 *)D_80167CA4)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R03_80172620_S_80172620_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2) &&
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) {
            allocated_effect = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
            ((R03_80172620_S_80172620_0 *)action)->unk_A4.s = allocated_effect;
            effect = allocated_effect;
            if (effect != 0) {
                s32 sprite_link;
                s32 sprite_data;

                func_8004491C(effect, func_80045340);
                ((R03_80172620_S_80172620_3 *)effect)->unk_10 = ((u8 *)D_800D7960);
                effect_transform = ((R03_80172620_S_80172620_3 *)effect)->unk_08;
                *(R03_80172620_Copy24 *)effect_transform = *(R03_80172620_Copy24 *)transform;
                ((R03_80172620_S_80172620_3 *)effect)->unk_BB = 0;
                ((R03_80172620_S_80172620_3 *)effect)->unk_4A = ((u16)actor->facing);

                effect_sprite = ((R03_80172620_S_80172620_3 *)effect)->unk_0C;
                sprite_link = ((Rec_D_80082E80 *)sprite)->unk_28.at00_s32.v;
                ((R03_80172620_S_80172620_4 *)effect_sprite)->unk_1E = 0x1000;
                ((R03_80172620_S_80172620_4 *)effect_sprite)->unk_1C = 0x1000;
                ((R03_80172620_S_80172620_4 *)effect_sprite)->unk_28 = sprite_link;
                ((R03_80172620_S_80172620_4 *)effect_sprite)->unk_14 = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
                ((R03_80172620_S_80172620_4 *)effect_sprite)->unk_12 = ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v;
                sprite_data = ((Rec_D_80082E80 *)sprite)->unk_0C.at00_s32.v;
                ((R03_80172620_S_80172620_4 *)effect_sprite)->unk_2C = ((u8 *)D_80167CB4);
                ((R03_80172620_S_80172620_4 *)effect_sprite)->unk_0C = sprite_data;
                func_80047784(effect_sprite,
                    ((u8 *)D_80167CB4)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }

        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80167CAC);
        func_80047784(sprite,
            ((u8 *)D_80167CAC)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R03_80172620_S_80172620_0 *)action)->unk_9B++;
        return;

    case 2:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            void *active_effect;

            (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80167CBC);
            func_80047784(sprite,
                ((u8 *)D_80167CBC)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            active_effect = ((R03_80172620_S_80172620_0 *)action)->unk_A4.s;
            if (active_effect != 0) {
                ((R03_80172620_S_80172620_5 *)active_effect)->unk_BB = 0xFF;
                ((R03_80172620_S_80172620_0 *)action)->unk_A4.u = 0;
            }
            ((R03_80172620_S_80172620_0 *)action)->unk_9B++;
        }

    case 3:
        if (((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2) &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            play_sound_if_enabled(0x808);
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
            ((R03_80172620_S_80172620_0 *)action)->unk_9B = 0xFF;
        }
        return;

    case 0xFF:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(transform,(u8)(((Rec_D_80082E80 *)sprite)->unk_24),(u8)(((Rec_D_80082E80 *)sprite)->unk_25));
        reduce_actor_food_meter(actor, 0x180);
        ((R03_80172620_S_80172620_0 *)action)->unk_8C = ((void *)func_80164E54);
        g_dungeon_status.unk_0C = 0;
        advance_status_timers(actor);
        if (actor->unk_6D == 0) {
            actor->unk_46 &= 0x7FFF;
        } else {
            (*(void * *)D_800E3DE8) = (u8 *)actor - 0x20;
        }

        return;
    }
}
