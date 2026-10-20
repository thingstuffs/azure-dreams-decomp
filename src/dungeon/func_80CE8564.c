#include "dungeon/monster/troll/troll_flash_effects.h"

/* Creates an object and initializes its position, flags, and directional frame table. */
void *create_actor_entity(s16 spawn_flags, s32 sprite_x, s32 sprite_y, s32 initial_height)
{
    s32 record_addr;
    EntityRec *result;
    s16 saved_y;
    s16 saved_x;
    SpriteFrameState *sprite;
    s16 init_flags;
    ObjectNodeHeader *object;
    void *position;
    s32 call_object;
    s32 call_position;
    s32 alternate_kind;
    s32 state_flags;
    void *new_frames;
    s32 kind;
    s32 mode;
    u32 global_kind;
    u32 branch_flags;
    void *current_frames;
    u8 *frame_table;
    s32 default_frames;
    s32 direction_index;
    s32 record_kind;

    result = 0;
    call_object = 0x112;
    saved_x = sprite_x;
    call_position = (s32)((u8 *)(&D_80083498));
    saved_y = sprite_y;
    object = allocate_list_node(call_object, (void *)call_position);
    init_flags = spawn_flags;
    if (object != 0) {
        result = (EntityRec *)((u8 *)object + 0x20);
        object->unk_10 = D_801720B4;
        *(s8 *)((u8 *)result + 0x13) = 0x16;
        register_node(object, project_sprite_chain);

        default_frames = (s32)D_80175E24;
        call_position = 0xE;
        position = object->unk_08;
        alternate_kind = 0xF;
        ((T_80171D64_S_80171D64_2 *)position)->unk_0A = initial_height;
        sprite = object->unk_0C;
        
        sprite->unk_24 = saved_x;
        sprite->frameTable = (void *)default_frames;
        record_kind = 0x20;
        sprite->unk_25 = saved_y;
        record_addr = (s32)result;
        result->unk_4B = record_kind;
        result->unk_48 = call_position;
        result->unk_49 = alternate_kind;
        mode = spawn_flags & 3;

        if (mode == 1) {
            (*(u32 *)((u8 *)result + 0x14)) |= 0x6000;
            branch_flags = result->flags1C;
            global_kind = (u8)D_800E2968;
            result->flags1C = branch_flags | 0x6000;
            if (global_kind >= 0xA) {
                if (global_kind < 0xD) {
                    result->unk_48 = alternate_kind;
                } else {
                    result->unk_48 = 0xD;
                }
            }
        } else {
            if (mode >= 2) {
                result->flags14 |= 0x2000;
                result->flags1C |= 0x2000;
            } else {
                global_kind = (u8)D_800E2968;
                if (global_kind < 0xA) {
                    result->unk_48 = call_position;
                } else if (global_kind < 0xD) {
                    result->unk_48 = alternate_kind;
                } else {
                    result->unk_48 = 0xD;
                }

                if (((init_flags & ~3) << 16) == 0) {
                    if (!(result->flags14 & 0x200)) {
                        state_flags = generate_random_value();
                        if (state_flags & 1) {
                            set_or_clear_actor_status_slot(result, 1,
                                (generate_random_value() & 0x3F) | 0x20);
                            kind = result->unk_48;
                            switch (kind) {
                            case 0xD:
                                current_frames = sprite->frameTable;
                                new_frames = D_80175E54;
                                if (current_frames != new_frames) {
                                    sprite->frameTable = new_frames;
                                }
                                break;
                            case 0xE:
                                current_frames = sprite->frameTable;
                                new_frames = D_80175E5C;
                                if (current_frames != new_frames) {
                                    sprite->frameTable = new_frames;
                                }
                                break;
                            case 0xF:
                                current_frames = sprite->frameTable;
                                new_frames = D_80175E64;
                                if (current_frames != new_frames) {
                                    sprite->frameTable = new_frames;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        call_object = (s32)object;
        call_position = (s32)position;
        initialize_actor_sprite_and_animation((void *)call_object, (void *)call_position, sprite,
            (s16)init_flags);
        ((T_80171D64_S_80171D64_4 *)((void *)record_addr))->unk_9A = 0xFF;
        ((T_80171D64_S_80171D64_4 *)((void *)record_addr))->unk_9C = -1;
        ((T_80171D64_S_80171D64_4 *)((void *)record_addr))->unk_8C = update_actor_behavior;
        try_move_actor_to_valid_position((void *)record_addr, position, sprite, result);

        kind = result->unk_48;
        switch (kind) {
        case 0xD:
            current_frames = sprite->frameTable;
            frame_table = D_80175E24;
            break;
        case 0xE:
            current_frames = sprite->frameTable;
            frame_table = D_80175E2C;
            break;
        case 0xF:
            current_frames = sprite->frameTable;
            frame_table = D_80175E34;
            break;
        default:
            return result;
        }
        if (current_frames != frame_table) {
            (sprite->frameTable) = frame_table;
            direction_index = ((g_game_work.view.viewAngle + result->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite,
                *(u8 *)((u32)direction_index + (u32)frame_table),
                0);
        }
    }
    return result;
}
