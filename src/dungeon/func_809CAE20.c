#include "modules/dungeon_resource03_slot0.h"
#include "shared/sprite_frame_state.h"

void advance_actor_attack_and_resolve_damage(void *action, void *transform, void *sprite, EntityRec *actor)
{
    s32 state;
    void *allocated_effect;
    void *effect = 0;
    SpriteFrameState *effect_sprite;
    void *effect_transform;

    ((R03_80172620_S_80172620_0 *)action)->unk_96--;
    state = ((R03_80172620_S_80172620_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((R03_80172620_S_80172620_0 *)action)->unk_9B = 0xFF;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
            return;
        }

        if (rand() & 3) {
            ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80173CBC);
            (*(s32 *)((u8 *)action + 0xA4)) = 0;
            select_sprite_entry(sprite,
                (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable)
                    [((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((R03_80172620_S_80172620_0 *)action)->unk_9B = 3;
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80173CA4);
        select_sprite_entry(sprite,
            ((u8 *)D_80173CA4)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R03_80172620_S_80172620_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((((SpriteFrameState *)sprite)->unk_04 == 2) &&
            (((SpriteFrameState *)sprite)->flags & 0x1000)) {
            allocated_effect = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
            ((R03_80172620_S_80172620_0 *)action)->unk_A4.s = allocated_effect;
            effect = allocated_effect;
            if (effect != 0) {
                s32 sprite_link;
                s32 sprite_data;

                register_node(effect, project_sprite_chain);
                ((R03_80172620_S_80172620_3 *)effect)->unk_10 = ((u8 *)D_800D7960);
                effect_transform = ((R03_80172620_S_80172620_3 *)effect)->unk_08;
                *(R03_80172620_Copy24 *)effect_transform = *(R03_80172620_Copy24 *)transform;
                ((R03_80172620_S_80172620_3 *)effect)->unk_BB = 0;
                ((R03_80172620_S_80172620_3 *)effect)->unk_4A = ((u16)actor->facing);

                effect_sprite = ((R03_80172620_S_80172620_3 *)effect)->unk_0C;
                sprite_link = ((SpriteFrameState *)sprite)->unk_28;
                effect_sprite->scale_y = 0x1000;
                effect_sprite->scale_x = 0x1000;
                effect_sprite->unk_28 = sprite_link;
                effect_sprite->flags = ((SpriteFrameState *)sprite)->flags;
                effect_sprite->clut = ((SpriteFrameState *)sprite)->clut;
                sprite_data = ((SpriteFrameState *)sprite)->color.word;
                effect_sprite->frameTable = ((u8 *)D_80173CB4);
                effect_sprite->color.word = sprite_data;
                select_sprite_entry(effect_sprite,
                    ((u8 *)D_80173CB4)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }

        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80173CAC);
        select_sprite_entry(sprite,
            ((u8 *)D_80173CAC)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R03_80172620_S_80172620_0 *)action)->unk_9B++;
        return;

    case 2:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            void *active_effect;

            ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80173CBC);
            select_sprite_entry(sprite,
                ((u8 *)D_80173CBC)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            active_effect = ((R03_80172620_S_80172620_0 *)action)->unk_A4.s;
            if (active_effect != 0) {
                ((R03_80172620_S_80172620_5 *)active_effect)->unk_BB = 0xFF;
                ((R03_80172620_S_80172620_0 *)action)->unk_A4.u = 0;
            }
            ((R03_80172620_S_80172620_0 *)action)->unk_9B++;
        }

    case 3:
        if (((((SpriteFrameState *)sprite)->unk_04 == 2) &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            play_sound_if_enabled(0x808);
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
            ((R03_80172620_S_80172620_0 *)action)->unk_9B = 0xFF;
        }
        return;

    case 0xFF:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(transform,(u8)((SpriteFrameState *)sprite)->unk_24,(u8)((SpriteFrameState *)sprite)->unk_25);
        reduce_actor_food_meter(actor, 0x180);
        ((R03_80172620_S_80172620_0 *)action)->unk_8C = ((void *)func_80170E54);
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
