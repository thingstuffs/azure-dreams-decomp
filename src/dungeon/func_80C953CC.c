#include "modules/dungeon_ovl_cb3000.h"

void advance_actor_item_action_effect(CB_80172BCC_S_func_80C953CC_1 *work, CB_80172BCC_S_func_80C953CC_2 *position, CB_80172BCC_S_func_80C953CC_3 *entity,
    CB_80172BCC_S_func_80C953CC_4 *actor)
{
    CB_80172BCC_S_func_80C953CC_9 *part;
    s32 alternate = 0;

    switch (work->unk_9B) {
    case 0:
        if (actor->unk_1C & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                alternate = 1;
                /* fallthrough */
            case 3:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 0xE);
                break;
            case 6:
                alternate = 1;
                /* fallthrough */
            case 2:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 0xB);
                break;
            case 5:
                alternate = 1;
                /* fallthrough */
            case 1:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 8);
                break;
            default:
                part = 0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 0xE);
                break;
            case 2:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 0xB);
                break;
            case 1:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 8);
                break;
            default:
                part = 0;
                break;
            }
        }

        if (part->unk_00 != 0) {
            void *target_actor;
            CB_80172BCC_S_func_80C953CC_3 *target_entity;

            (*(u16 *)((u8 *)work + 0x98)) &= 0xFF7F;
            if ((s8)alternate) {
                actor->unk_60 = target_actor = D_800814A8;
                target_entity = *(CB_80172BCC_S_func_80C953CC_3 **)((u8 *)target_actor - 0x14);
                actor->unk_72.u8 = target_entity->unk_24;
                actor->unk_73.u8 = target_entity->unk_25;
            } else if (D_8006DE24[part->unk_00].kind == 2) {
                if ((target_actor = actor->unk_60) != 0) {
                    target_entity = *(CB_80172BCC_S_func_80C953CC_3 **)((u8 *)target_actor - 0x14);
                    actor->unk_72.u8 = target_entity->unk_24;
                    actor->unk_73.u8 = target_entity->unk_25;
                }
            } else {
                s32 target_x;
                s32 target_y;

                actor->unk_60 =
                    scan_monster_along_heading(actor, entity->unk_24,
                                  entity->unk_25,
                                  actor->unk_2A, 0x10);
                target_x = abs(actor->unk_72.s8);
                target_y = abs(actor->unk_73.s8);
                actor->unk_72.u8 = target_x;
                actor->unk_73.u8 = target_y;
            }

            if (create_actor_spell_effect(actor, part, alternate, (u8 *)work + 0x98) != 0) {
                work->unk_9B++;
            }
        } else {
            CB_80172BCC_S_func_80C953CC_5 *active_actor;

            position->unk_14 = 0;
            position->unk_10 = 0;
            position->unk_0C = 0;
            set_record_integer_tile_center(position, entity->unk_24,
                          entity->unk_25);
            active_actor = D_800814A8;
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)active_actor + 0xA6))--;
            advance_status_timers(actor);
            actor->unk_6D--;
            work->unk_8C = func_8017102C;
            actor->unk_73.u8 = 0;
            actor->unk_72.u8 = 0;
            actor->unk_46 &= 0x7FFF;
        }
        break;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            entity->unk_14 |= 0x800;
            break;
        }

        entity->unk_14 &= 0xF7FF;
        work->unk_9B++;
        actor = func_8003FC64(0x212);
        if (actor != 0) {
            CB_80172BCC_S_func_80C953CC_6 *transform;
            CB_80172BCC_S_func_80C953CC_7 *node;
            CB_80172BCC_S_func_80C953CC_8 *model;

            func_8017087C(actor, work, position);
            transform = (CB_80172BCC_S_func_80C953CC_6 *)((u8 *)actor + 0x20);
            transform->unk_24 = 10;
            transform->unk_26 = 10;
            node = actor->unk_08;
            actor->unk_10 = expand_then_shrink_effect;
            node->unk_0A -= 0x1E;
            model = actor->unk_0C;
            model->unk_10 = 0x60;
            model->unk_06 = 6;
            model->unk_1E = 0;
            model->unk_1C = 0;
            model->unk_0E = 0;
            model->unk_0D = 0;
            model->unk_0C = 0;
            *(CB_80172BCC_Copy12 *)((u8 *)actor + 0x9A) = D_8017539C;
            model->unk_08 = (u8 *)actor + 0x9A;
        }
        play_sound_if_enabled(0x703);
        break;

    case 2:
        if ((entity->unk_04 == 5 &&
             (entity->unk_14 & 0x1000)) ||
            (entity->unk_14 & 0xE000)) {
            work->unk_96 = 0x20;
            work->unk_98 |= 0x80;
            work->unk_9B++;
        }
        break;

    case 3:
        part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)((s32 *)&g_dungeon_status.active_actor) - 0x0C);
        if (part->unk_0C == 0) {
            work->unk_96 = 0;
        }
        if (!(entity->unk_14 & 0xE000)) {
            break;
        }

        position->unk_14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        set_record_integer_tile_center(position, entity->unk_24,
                      entity->unk_25);
        if (entity->unk_2C != D_801752B4) {
            s32 direction;

            (*(void **)((u8 *)entity + 0x2C)) = D_801752B4;
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9;
            select_sprite_entry(entity, D_801752B4[direction & 7], 0);
        }
        if (part->unk_0C != 0) {
            break;
        }

        part->unk_0A--;
        work->unk_8C = func_8017102C;
        advance_status_timers(actor);
        actor->unk_73.u8 = 0;
        actor->unk_72.u8 = 0;
        actor->unk_6D--;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    }
}