#include "shared/audio_commands.h"
#include "dungeon/actor/motion.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* Flame actor spawning, child displays, action updates, and textured effects. */
#include "dungeon/monster/flame.h"
#include "shared/actor_action_flags.h"
#include "shared/monster_ids.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/effect/sprite.h"
#include "engine/cd.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/actor_status.h"
#include "dungeon/level/room_flags.h"
#include "dungeon/item.h"
#include "engine/texture.h"
#include "dungeon/actor/state.h"
#include "dungeon/effect.h"
#include "dungeon/effect/screen.h"

void * (*const resource06_slot0_entry0)(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id) = spawn_animated_monster;
void (*const resource06_slot0_entry1)(u8 *actor, u8 *motion, u8 *entity) = create_anchored_directional_object;

/* Creates a Flame actor with three child display objects and initializes its status and tile placement. */
void *spawn_animated_monster(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    R06_8017087C_S_8017087C_5 *slot_base;
    R06_8017087C_S_8017087C_8 *child_slot;
    s32 entry_id_fixed;
    SpriteFrameState *part_b;
    void *work;
    s8 saved_x;
    s16 saved_part_id;
    s8 saved_y;
    s32 setup_value;
    register s32 work_flags;
    void *alloc_or_entry;
    s32 entry_id;
    s32 entry_mode;
    s32 child_index;
    u8 *slot;
    s32 entry_index;

    work = 0;
    alloc_or_entry = (void *)274;
    saved_x = tile_x;
    saved_part_id = part_id;
    saved_y = tile_y;
    obj = allocate_list_node((s32)alloc_or_entry, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = create_anchored_directional_object;
        ((R06_8017087C_S_8017087C_1 *)work)->unk_13 = MONSTER_FLAME;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_part_id;
        part_b = obj->sprite;
        slot_base = work;
        kind = kind_flags & 3;
        part_b->frameTable = ((u8 *)flame_direction_frames);
        part_b->tile_x = saved_x;
        part_b->tile_y = saved_y;

        if (kind == 1) {
            setup_value = ((R06_8017087C_S_8017087C_1 *)work)->unk_14 | 0x6000;
            work_flags = ((R06_8017087C_S_8017087C_1 *)work)->unk_1C | 0x6000;
            ((R06_8017087C_S_8017087C_1 *)work)->unk_14 = setup_value;
            ((R06_8017087C_S_8017087C_1 *)work)->unk_1C = work_flags;
        } else if (kind >= 2) {
            setup_value = ((R06_8017087C_S_8017087C_1 *)work)->unk_14 | 0x2000;
            work_flags = ((R06_8017087C_S_8017087C_1 *)work)->unk_1C | 0x2000;
            ((R06_8017087C_S_8017087C_1 *)work)->unk_14 = setup_value;
            ((R06_8017087C_S_8017087C_1 *)work)->unk_1C = work_flags;
        } else {
            if (((kind_flags & ~3) << 16) == 0) {
                if (!(((R06_8017087C_S_8017087C_1 *)work)->unk_14 & 0x200)) {
                    setup_value = generate_random_value();
                    if (setup_value & 1) {
                        ((R06_8017087C_S_8017087C_1 *)work)->unk_1C |= 0x200;
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = ((u8 *)flame_alt_direction_frames);
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b,(s16)(kind_flags));

        child_index = 0;
        entry_id_fixed = 0x00190000;
        slot = (u8 *)slot_base;
        ((R06_8017087C_S_8017087C_4 *)slot)->unk_9A = 0xFF;
        slot_base->unk_9C = -1;
        slot_base->unk_8C = initialize_destination_state;
        ((R06_8017087C_S_8017087C_1 *)work)->unk_1C |= 0x40000;
        slot_base->unk_92 = -24;
        slot_base->unk_9E = 3;
        do {
            void *child_obj;

            child_obj = allocate_list_node(274, &scene_object_list_anchor.next);
            ((R06_8017087C_S_8017087C_4 *)slot)->unk_A4 = child_obj;
            if (child_obj != 0) {
                void *child_work = (u8 *)child_obj + 0x20;

                if (child_index != 0) {
                    ((R06_8017087C_S_8017087C_6 *)child_work)->unk_02 = 1;
                } else {
                    ((R06_8017087C_S_8017087C_6 *)child_work)->unk_02 = 2;
                }
                entry_index = 0;
                if (entry_index < ((R06_8017087C_S_8017087C_6 *)child_work)->unk_02) {
                    s32 entry_offset;
                    s32 child_id_fixed;

                    child_slot = slot;
                    child_id_fixed = entry_id_fixed;
                    entry_offset = 8;
                    do {
                        SpriteFrameState *entry= (u8 *)child_work + entry_offset;
                        R06_8017087C_S_8017087C_9 *callback_obj;
                        s32 field_value;

                        field_value = part_b->animation_resource;
                        entry->color.word = 0x00C0C0C0;
                        alloc_or_entry = entry;
                        entry_id = child_id_fixed >> 16;
                        entry->animation_resource = field_value;
                        entry_mode = 0;
                        callback_obj = child_slot->unk_A4;
                        callback_obj->unk_10 = process_effect_block_entries;
                        setup_value = entry->flags;
                        setup_value |= 0xC;
                        entry->flags = setup_value;
                        select_sprite_entry(alloc_or_entry, entry_id, entry_mode);
                        entry_offset += 48;
                        entry->tpage_abr = 96;
                        entry->clut = part_b->clut - 128;
                        ((R06_8017087C_S_8017087C_6 *)child_work)->unk_06 = child_index + 1;
                        texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(part_b, ((u8 *)child_texture_entries), ((R06_8017087C_S_8017087C_6 *)child_work)->unk_06);
                        ((R06_8017087C_S_8017087C_6 *)child_work)->unk_98 = (u8 *)obj + 30;
                    } while (++entry_index < ((R06_8017087C_S_8017087C_6 *)child_work)->unk_02);
                }
            }
            entry_id_fixed += 0x10000;
            slot += 4;
        } while (++child_index < slot_base->unk_9E);
        slot_base->unk_98 = slot_base->unk_98 | 0x2000;
        try_move_actor_to_valid_position(slot_base, part_a, part_b, work);
    }
    return work;
}

/* Runs actor callbacks and updates child sprite colors, facing, animation, motion, and ground contact. */
void create_anchored_directional_object(u8 *actor, u8 *motion, u8 *entity)
{
    u8 *subject = actor;
    s16 state_index;
    s32 sprite_index;
    u32 global_flags;
    u16 *global_flags_ptr = (u16 *)((u8 *)resident_globals_page);
    u8 *part_base;
    R06_80170BB8_Callback callback;
    u16 entity_flags;
    s32 subject_flags;
    s16 ground_height;
    s32 bob_offset;
    s16 floor_offset;
    s32 height_limit;
    u16 height_raw;
    u16 height_raw2;
    s32 height_offset;
    s32 ground_offset;
    u8 * model_state;
    u8 * sprite_data;
    s32 view_dir;
    u32 new_height;

    part_base = (*(u8 **)((u8 *)actor + 0xA4));
    global_flags = global_flags_ptr[0x1A31];
    model_state = (part_base + 0x20);

    sprite_data = (part_base + 0x28);
    if (global_flags & 0x2000) {
        callback = (*(R06_80170BB8_Callback *)((u8 *)actor + 0x8C));
        if (callback == (R06_80170BB8_Callback)((u8 *)initialize_destination_state)) {
            callback(actor, motion, entity, actor);
        } else {
            (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        }
    } else {
        u32 raw_state;

        raw_state = (*(u8 *)((u8 *)actor + 0x6D));
        state_index = (s8)raw_state;
        if (refresh_actor_facing_and_lifecycle(actor, motion, entity, actor) == 0) {
            {
                R06_80170BB8_Callback actor_callback;

                actor_callback = (*(R06_80170BB8_Callback *)((u8 *)actor + 0x8C));
                if (actor_callback != 0) {
                    actor_callback(actor, motion, entity, actor);
                }
            }
            ((R06_80170BB8_Callback *)D_8017589C)[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, entity, actor);

            if ((s16)state_index != (*(s8 *)((u8 *)actor + 0x6D))) {
                try_move_actor_to_valid_position(actor, motion, entity, actor);
            }

            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at00.v += ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_0C;
            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at00.v += ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_10;

            if (!((*(u32 *)((u8 *)actor + 0x1C)) & 0x00040000) &&
                !((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_14 += (*(s8 *)((u8 *)actor + 0x9D)) * 0x14000;
                (*(u8 *)((u8 *)actor + 0x9D))++;
            } else {
                (*(u8 *)((u8 *)actor + 0x9D)) = 0;
            }
            (*(s32 *)((u8 *)actor + 0x90)) += ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_14;

            if (((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u & 0x200) {
                if ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000) {
                    ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_3C = 0x00808080;
                    ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_0C.u32 = 0x00808080;
                } else if (((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_0C.u8 >= 8) {
                    ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_3C += 0xFFF7F7F8;
                    ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_0C.u32 = ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_3C;
                }

                if (((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_14 & 0x6000) {
                    if (((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_0C.u8 < 8 ||
                        ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000)) {
                        u16 actor_flags = (*(u16 *)((u8 *)actor + 0x98));

                        if (!(actor_flags & 0x8000)) {
                            (*(u16 *)((u8 *)actor + 0x98)) = actor_flags | 0xC000;
                            ((R06_80170BB8_S_80170BB8_3 *)(model_state))->unk_04 |= 0x8000;
                            (*(u16 *)((u8 *)actor + 0xA0)) =
                                (rand() & 7) + 0x10;
                        }
                    }
                }

                sprite_index = 0;
                if (--(*(s16 *)((u8 *)actor + 0xA0)) == 0) {
                    (*(u16 *)((u8 *)actor + 0x98)) &= 0x7FFF;
                    ((R06_80170BB8_S_80170BB8_3 *)(model_state))->unk_04 &= 0x7FFF;
                    if (((R06_80170BB8_S_80170BB8_3 *)(model_state))->unk_02 > 0) {
                        do {
                            select_sprite_entry(sprite_data + sprite_index * 0x30, 0x1C, 0);
                            sprite_index++;
                        } while (sprite_index < ((R06_80170BB8_S_80170BB8_3 *)(model_state))->unk_02);
                    }
                }
            } else {
                if (((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_0C.u8 >= 0x80) {
                    ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_3C = 0x00808080;
                    ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_0C.u32 = 0x00808080;
                } else {
                    ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_3C += 0x00080808;
                    ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_0C.u32 = ((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_3C;
                }

                if ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000) {
                    (*(u16 *)((u8 *)actor + 0x98)) &= 0x3FFF;
                    ((R06_80170BB8_S_80170BB8_3 *)(model_state))->unk_04 &= 0x7FFF;
                }

                if ((*(u16 *)((u8 *)actor + 0x98)) & 0x1000) {
                    select_sprite_entry(sprite_data, 0x1D, 0);
                    select_sprite_entry(sprite_data + 0x30, 0x1D, 0);
                    (*(u16 *)((u8 *)actor + 0x98)) &= 0xEFFF;
                } else if (((*(u16 *)((u8 *)actor + 0x98)) & 0x2000) &&
                           (((R06_80170BB8_S_80170BB8_2 *)sprite_data)->unk_14 & 0x6000)) {

                    if ((*(u8 *)((u8 *)actor + 0x9A)) == 7) {
                        select_sprite_entry(sprite_data, 0x19, 0);
                        select_sprite_entry(sprite_data + 0x30, 0x24, 0);
                    } else {
                        s32 random_value;

                        select_sprite_entry(sprite_data, 0x19, 0);
                        random_value = rand();
                        ground_offset = 0x24;
                        if (random_value & 3) {
                            ground_offset = 0x19;
                        }
                        select_sprite_entry(sprite_data + 0x30, ground_offset, 0);
                    }
                }
            }

            entity_flags = ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14;
            if (!(entity_flags & 0x8000)) {
                {
                    s32 view_angle;

                    view_angle =
                        g_game_work.view.camera_rotation.parts.viewAngle + ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_2A + 0x100;
                    state_index = (view_angle >> 9) & 7;
                }
                {

                    if ((*(s16 *)((u8 *)actor + 0x94)) != (view_dir = (s16)state_index)) {
                        select_indirect_table_entry(entity,
                                      (*(u8 *)((u8 *)(((R06_80170BB8_S_80170BB8_4 *)entity)->unk_2C) + view_dir)),
                                      ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_04);
                        (*(s16 *)((u8 *)actor + 0x94)) = state_index;
                    }

                    if (((u8 *)D_8006CCF8)[view_dir] != 0) {
                        ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 |= 1;
                    } else {
                        ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 &= 0xFFFE;
                    }
                }

                if ((*(u8 *)((u8 *)actor + 0x9A)) != 8) {
                    apply_monster_koyaw_data(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.s, entity + 0xC);
                }

                if (!(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.s & 0x20)) {
                    if (!(((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 & 0x40)) {
                        advance_sprite_animation_and_textures(entity);
                    }
                } else {
                    ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 |= 0x7000;
                    ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u &= 0xFFFBFFFF;
                }

                ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u &= 0xF7FFFFFF;
                subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;

                if (subject_flags & 0x00040000) {
                    if (!(((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 & 0x40) &&
                        ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_2C == ((u8 *)flame_direction_frames)) {
                        u16 bob_frame = (*(u16 *)((u8 *)actor + 0xB8));

                        (*(u16 *)((u8 *)actor + 0xB8)) = bob_frame + 1;
                        (*(s32 *)((u8 *)actor + 0xB4)) +=
                            rsin((s16)bob_frame * 0xAA) << 5;
                    }

                    if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                        ground_offset = (s16)(sample_terrain_surface_height(
                            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v, ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                            (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20)) -
                                              ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88);
                        height_offset = (*(s16 *)((u8 *)actor + 0x92));
                        height_raw = (*(u16 *)((u8 *)actor + 0x92));
                        height_limit = ground_offset - 0x18;
                        if (height_limit < height_offset) {

                            new_height = height_raw - 8;
                            (*(u16 *)((u8 *)actor + 0x92)) = new_height;
                            subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                        } else {
                            height_limit = ground_offset;
                            height_limit -= 0x20;
                            height_limit = height_offset < height_limit;
                            if (height_limit) {
                                new_height = height_raw + 8;
                                (*(u16 *)((u8 *)actor + 0x92)) = new_height;
                            }
                            subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                        }
                    } else {
                        subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                    }
                } else {
                    {
                        s32 reset_bob_offset;
                        s16 reset_ground_height;
                        s16 reset_floor_offset;

                        reset_bob_offset = (*(s32 *)((u8 *)actor + 0xB4));
                        (*(u16 *)((u8 *)actor + 0xB8)) = 0;
                        (*(s32 *)((u8 *)actor + 0xB4)) = 0;
                        (*(s32 *)((u8 *)actor + 0x90)) -= reset_bob_offset;
                        if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                            reset_ground_height = sample_terrain_surface_height(
                                ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v, ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                                (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20));
                            reset_floor_offset = (s16)(reset_ground_height - ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88);
                            if (reset_floor_offset < (*(s16 *)((u8 *)actor + 0x92))) {
                                (*(s16 *)((u8 *)actor + 0x92)) = reset_floor_offset;
                                (*(u8 *)((u8 *)actor + 0x9D)) = 0;
                                ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                                ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u |= 0x08000000;
                            }
                        }
                        subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;

                    }
                }
            } else {
                if (entity_flags & 0x800) {
                    ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 = entity_flags & 0x8FFF;
                } else {
                    ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 = entity_flags | 0x7000;
                }

                ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u &= 0xF7FFFFFF;
                subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;

                if (!(subject_flags & 0x00040000)) {

                    bob_offset = (*(s32 *)((u8 *)actor + 0xB4));
                    (*(u16 *)((u8 *)actor + 0xB8)) = 0;
                    (*(s32 *)((u8 *)actor + 0xB4)) = 0;
                    (*(s32 *)((u8 *)actor + 0x90)) -= bob_offset;
                    if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                        ground_height = sample_terrain_surface_height(
                            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v, ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                            (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20));
                        floor_offset = (s16)(ground_height - ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88);
                        if (floor_offset < (*(s16 *)((u8 *)actor + 0x92))) {
                            (*(s16 *)((u8 *)actor + 0x92)) = floor_offset;
                            (*(u8 *)((u8 *)actor + 0x9D)) = 0;
                            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                            ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u |= 0x08000000;
                        }
                    }
                    subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                } else {
                    if (!(((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 & 0x40) &&
                        ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_2C == ((u8 *)flame_direction_frames)) {
                        u16 bob_frame = (*(u16 *)((u8 *)actor + 0xB8));

                        (*(u16 *)((u8 *)actor + 0xB8)) = bob_frame + 1;
                        (*(s32 *)((u8 *)actor + 0xB4)) +=
                            rsin((s16)bob_frame * 0xAA) << 5;
                    }

                    if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                        ground_offset = (s16)(sample_terrain_surface_height(
                            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v, ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                            (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20)) -
                                              ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88);
                        height_offset = (*(s16 *)((u8 *)actor + 0x92));
                        height_raw2 = (*(u16 *)((u8 *)actor + 0x92));
                        height_limit = ground_offset - 0x18;
                        if (height_limit < height_offset) {
                            new_height = height_raw2 - 8;
                            (*(u16 *)((u8 *)actor + 0x92)) = new_height;
                        } else {
                            height_limit = ground_offset;
                            height_limit -= 0x20;
                            height_limit = height_offset < height_limit;
                            if (height_limit) {
                                new_height = height_raw2 + 8;
                                (*(u16 *)((u8 *)actor + 0x92)) = new_height;
                            }
                        }
                    }
                    subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                }
            }
            if (subject_flags & 0x40000000) {
                ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u = subject_flags & 0xBFFFFFFF;
                ground_height = sample_terrain_surface_height((((R06_80170BB8_S_80170BB8_4 *)entity)->unk_24 << 6) | 0x20,
                                       (((R06_80170BB8_S_80170BB8_4 *)entity)->unk_25 << 6) | 0x20,
                                       (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20));
                if ((s16)ground_height < 0x200) {
                    (*(u16 *)((u8 *)actor + 0x92)) +=
                        ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - ground_height;
                    ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 = ground_height;
                }
            }

            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_0A = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 +
                                      (*(u16 *)((u8 *)actor + 0x92)) -
                                      (*(u16 *)((u8 *)actor + 0xB6));
            ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 |= 0x40;
        }
    }

}

/* Selects movement, attacks, and spells from actor status, MP, and its position relative to the player. */
void initialize_destination_state(ActorRecord *actor, ObjectPosition *actor_context, SpriteFrameState *sprite, ActorRecord *creature) {
    u16 distance;
    s8 room_id;
    u16 behavior_flags;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id.u = 0xE;
        update_actor_object_motion(actor, actor_context, sprite, creature);
        return;
    }

    if (creature->mp_value.parts.whole == 0) {
        u8 *animation_table;

        advance_actor_pending_action(actor, actor_context, sprite, creature);
        if (sprite->frameTable == ((u8 *)flame_alt_direction_frames)) {
            return;
        }
        animation_table = ((u8 *)flame_frame_set_1);
        sprite->frameTable = animation_table;
        select_sprite_entry(sprite,
            animation_table[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x200) {
        if (sprite->frameTable == ((u8 *)flame_alt_direction_frames)) {
            actor->action_id.u = 0xD;
            actor->action_phase.u = 1;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_8C = 0;
            ((R06_8017140C_S_8017140C_1 *)creature)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, actor_context, sprite, ((u8 *)flame_frame_set_1)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        void *current_animation;
        u8 *animation_table;

        if (((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor, actor_context, sprite, creature);
            return;
        }

        if (actor->action_id.u != 0xE) {
            actor->action_id.u = 0xE;
        }

        current_animation = sprite->frameTable;
        animation_table = ((u8 *)flame_direction_frames);
        if (current_animation != animation_table) {
            sprite->frameTable = animation_table;
            select_sprite_entry(sprite,
                animation_table[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
                0);
            sprite->frame_ticks = 1;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_B6.s = 0;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_B8 = 0;
        }

        ((R06_8017140C_S_8017140C_1 *)creature)->unk_1C |= 0x40000;
        actor->action_state_flags &= 0xFFF7;

        if (creature->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, actor_context, sprite, ((u8 *)D_80175874)) != 0) {
                return;
            }
        }

        if (((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x80000) {
            s16 adjusted_offset;

            begin_actor_move_to_target_facing(actor, actor_context, sprite, creature);
            adjusted_offset = ((R06_8017140C_S_8017140C_0 *)actor)->unk_92.u - ((R06_8017140C_S_8017140C_0 *)actor)->unk_B6.u;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_B6.s = 0;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_B8 = 0;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_92.s = adjusted_offset;
            update_flame_parent_motion(actor, actor_context, sprite, creature);
            return;
        }

        if ((can_entity_gain_level(creature) << 16) != 0) {
            if ((process_selected_actor_record(actor, actor_context, sprite, creature) << 16) != 0) {
                wait_for_flame_action_slot(actor, actor_context, sprite, creature);
            }
        }
    }

    room_id = ((s8)find_active_rect_containing_point(sprite->tile_x, sprite->tile_y));
    sprite->room_index = room_id;

    if (creature->pending_turn_updates > 0) {
        if (((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x20) {
            update_actor_status_and_mp(creature);
            return;
        }
        if (*(u16 *)&sprite->tile_x != reference_tile_object.tile_position.word) {
            if (!(creature->action_flags & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(creature,
                            (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((relink_flame_path(actor, actor_context, sprite, 0) << 16) == 0) {
                    return;
                }
                behavior_flags = creature->action_flags | 0x4000;
                creature->action_flags = behavior_flags;
                if (!(behavior_flags & 0x8000)) {
                    choose_flame_move(actor, actor_context, sprite, creature);
                    return;
                }
            }

            {
                u32 behavior_index = (u32)((creature->action_flags & 0x3FFF) - 1);

                switch (behavior_index) {
                case 7:
                case 8:
                    if ((try_flame_attack(actor, actor_context, sprite, creature) << 16) != 0) {
                        return;
                    }
                    update_actor_action_and_direction(actor, actor_context, sprite, creature);
                    return;

                case 4:
                case 5:
                case 6:
                {
                    ActorRecord *player;
                    s16 facing_angle;

                    facing_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)sprite->tile_x,(s16)sprite->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                        &distance));
                    player = primary_actor_record;
                    creature->facing = facing_angle;
                    if (player->action_id.u == 0x11) {
                        begin_actor_spell_action(actor, actor_context, sprite, ((u8 *)D_80175884), initialize_destination_state);
                        return;
                    }
                }

                case 11:
                    update_actor_status_and_mp(creature);
                    return;

                case 0:
                case 1:
                case 2:
                    begin_actor_spell_action(actor, actor_context, sprite, ((u8 *)D_80175884), initialize_destination_state);
                    return;

                default:
                    break;
                }
            }
        }
        choose_flame_move(actor, actor_context, sprite, creature);
        return;
    }

    if (!(((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x430)) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)sprite->tile_x,(s16)sprite->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                        &distance));
                }
            }
        }
    }
}

/* Advances one stored path step, updates occupied tiles and facing, and sets the movement delay. */
void update_actor_object_motion(void *motion, ObjectPosition *unused, SpriteFrameState *actor, void *path_state)
{
    u8 *direction_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 tile_mask;

    if (((R06_80171964_S_8017169C_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (((R06_80171964_S_8017169C_0 *)path_state)->unk_71.u <= ((R06_80171964_S_8017169C_0 *)path_state)->unk_8A.s) {
        return;
    }

    direction_table = actor->frameTable;
    if (direction_table != ((u8 *)flame_direction_frames)) {
        (actor->frameTable) = ((u8 *)flame_direction_frames);
        select_sprite_entry(
            actor,
            ((u8 *)flame_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R06_80171964_S_8017169C_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    old_x = actor->tile_x;
    old_y = actor->tile_y;
    tile_mask = 0x3000;
    if (((R06_80171964_S_8017169C_0 *)path_state)->unk_1C.s & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

    actor->tile_x =
        ((R06_80171964_S_8017169C_3 *)((u8 *)path_state + ((R06_80171964_S_8017169C_0 *)path_state)->unk_8A.s))->unk_74;
    actor->tile_y =
        ((R06_80171964_S_8017169C_3 *)((u8 *)path_state + ((R06_80171964_S_8017169C_0 *)path_state)->unk_8A.s))->unk_7C;
    ((R06_80171964_S_8017169C_0 *)path_state)->unk_8A.u++;

    new_x = actor->tile_x;
    new_y = actor->tile_y;
    tile_mask = 0x3000;
    if (((R06_80171964_S_8017169C_0 *)path_state)->unk_1C.s & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, tile_mask);

    ((R06_80171964_S_8017169C_0 *)path_state)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag(
        old_x, old_y, actor->tile_x, actor->tile_y,
        (u8 *)motion + 0x98));
    ((R06_80171964_S_8017169C_0 *)path_state)->unk_1C.u |= 0x40000000;
    ((R06_80171964_S_8017169C_2 *)motion)->unk_9A = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((R06_80171964_S_8017169C_2 *)motion)->unk_96 = 0;
        return;
    }

    ((R06_80171964_S_8017169C_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((R06_80171964_S_8017169C_0 *)path_state)->unk_71.u;
        if (step_count > 0) {
            ((R06_80171964_S_8017169C_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
}

/* Chooses a clear step or attack, records the actor's path, and updates occupied tiles and movement
 * counts. */
void choose_flame_move(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data) {
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;
    ActorRecord *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_data->movement_queue_state >= 0) {
        if (actor_data->unk_12 >= 2 ||
            (s16)try_flame_attack(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            actor_data->action_flags = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, &move_data->unk_9C);
    actor_flags = actor_data->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_data,position_data->tile_x,position_data->tile_y);
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0) {
                SpriteFrameState *blocker_sprite = ((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)position_data->tile_x,(s16)position_data->tile_y,(s16)(blocker_sprite->tile_x),(s16)(blocker_sprite->tile_y),
                    &move_data->action_state_flags));
                actor_data->facing = target_angle;
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_data->flags14 & 0x80000000)) {
                actor_data->flags14 |= 0x80000000;
                actor_data->facing +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data,position_data->tile_x,position_data->tile_y,(s16)(actor_data->facing)) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u16 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((u8 *)&actor_data->unk_44)[1] + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (position_data->tile_x == (u16)target_x &&
                    position_data->tile_y == (u16)target_y) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }

                turn_data = &move_data->action_state_flags;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)position_data->tile_x,(s16)position_data->tile_y,(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                actor_data->facing = target_angle;
                if (((s16)check_directional_move_and_terrain((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    actor_data->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)position_data->tile_x,(s16)position_data->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)test_neighbor_position_relation(
                        position_data->tile_x, position_data->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                              &move_data->action_state_flags);
            }
        }
    } else if ((s8)position_data->room_index >= 0 &&
               dungeon_rooms[(s8)position_data->room_index].flags & ROOM_HOLY_BEAM) {
        select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                      &move_data->action_state_flags);
    } else if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
        current_angle = (s32)probe_directional_neighbor(actor_data,position_data->tile_x,position_data->tile_y,(s16)(actor_data->facing));
        blocker = (ActorRecord *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & ACTOR_PLAYER_SIDE) &&
            (s16)((s16)get_actor_height_difference(blocker, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    (actor_data->facing >> 9) & 0xFFFF,(s16)position_data->tile_x,(s16)position_data->tile_y,(s16)((s16)(actor_data->ground_height - 0x20)))) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }

        if (actor_data->flags1C & ACTOR_PLAYER_AWARE) {
            TileObject *target_position = &reference_tile_object;
            actor_data->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)position_data->tile_x,(s16)position_data->tile_y,(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), &move_data->action_state_flags));
            if (((s16)test_neighbor_position_relation(
                    position_data->tile_x, position_data->tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(primary_actor_record, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            (actor_data->facing >> 9) & 0xFFFF,(s16)position_data->tile_x,(s16)position_data->tile_y,(s16)((s16)(actor_data->ground_height - 0x20)))) != 0) {
                        actor_data->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                          &move_data->action_state_flags);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)actor_turn_angle_offsets);

    do {
        turn_flags = move_data->action_state_flags;
        current_angle = actor_data->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_directional_move_and_terrain((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_data->facing = trial_angle;
            ((ActorStatusBytesView *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))->path_x =
                position_data->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))->path_y =
                position_data->tile_y;
            actor_data->movement_queue_state++;

            update_map_cell_flags_with_item_limit(
                position_data->tile_x, position_data->tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = ((u16)actor_data->facing >> 8) & 0xE;
                x_step += step_offset;
                position_data->tile_x += *x_step;
                position_data->tile_y += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)position_data->tile_x,(s16)position_data->tile_y,(u16)((actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            reference_tile_object.tile_position.word != *(u16 *)&position_data->tile_x) {
            if (((s16)check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20)) != 0) {
                do {
                    return;
                } while (0);
            }
        }

        turn_index++;
        if (turn_index >= 8) {
            break;
        }
    } while (1);

    if (turn_index >= 8) {
        actor_data->movement_queue_state &= 0x7F;
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_data->unk_9C = position_data->room_index;
        actor_data->pending_turn_updates--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (actor_data->pending_turn_updates == 0) {
        actor_data->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (position_data->tile_x << 6) | 0x20,
        (position_data->tile_y << 6) | 0x20,(s16)((s16)(actor_data->ground_height - 0x20))));
    if (turn_index < 0x200) {
        actor_data->ground_height = turn_index;
    }
}

/* Checks target compatibility, height, and action availability; starts an adjacent attack when allowed. */
s32 try_flame_attack(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite, ActorRecord *actor) {
    ActorRecord *neighbor;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->movement_queue_state;
    actor_flags &= 0x7F;
    actor->movement_queue_state = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    neighbor = probe_directional_neighbor(actor, sprite->tile_x, sprite->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, neighbor) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(neighbor, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((ObjectNodeHeader *)actor - 1, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->action_id.u = 0x11;
        action_state->action_phase.u = 0;
        action_state->unk_8C.handler = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        sprite->frameTable = ((u8 *)flame_direction_frames);
        select_sprite_entry(sprite, (((u8 *)flame_direction_frames))[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}


/* Claims an action slot, starts the directional attack animation, and prepares its target and damage
 * state. */
void update_actor_action_and_direction(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((R06_80172428_S_80172428_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((R06_80172428_S_80172428_1 *)action_state)->unk_9B = 0;
            sprite->frameTable = ((u8 *)flame_frame_set);
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + ((u8 *)flame_frame_set)), 0);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            action_state->action_state_flags = (u16) (action_state->action_state_flags | 8);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

/* Relinks actor state, updates status or movement as needed, and reports whether a new action may start. */
s32 relink_flame_path(void *entity_arg, ObjectPosition *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        choose_flame_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R06_80172550_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        choose_flame_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R06_80172550_S_80172628_0 *)entity)->unk_71 = (u8) (((R06_80172550_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R06_80172550_S_80172628_0 *)entity)->unk_71 = (u8) (((R06_80172550_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R06_80172550_S_80172628_0 *)entity)->unk_46 = (u16) (((R06_80172550_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}

/*
 * Spends MP and advances status timers when movement completes, resuming the actor handler only
 * after a positive signed floor-trap check. Sets the secondary timer to -0x20 under dungeon flag
 * 0x80 during movement or after an accepted trap check. /
 */
void finish_actor_tile_move_then_initialize_destination(void *state, void *motion, void *source, void *target) {
    if (update_actor_movement_to_tile(state, motion, source, target) != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = ((s32 *)initialize_destination_state);
            if (g_dungeon_status.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (g_dungeon_status.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}

/*
 * Runs update_linked_actor_motion and installs initialize_destination_state only when it succeeds
 * and the signed floor-trap check returns positive.
 */
void finish_linked_actor_motion_and_floor_trap_then_initialize_destination(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic) {
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->unk_8C.handler = initialize_destination_state;
        }
    }
}

/* Times an attack animation and sound, applies damage, spends MP, and restores actor movement. */
void advance_action_through_animation(R06_8017278C_S_8017278C_0 *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor) {
    u16 ticks_left;
    s32 initial_state;
    s32 state;
    u8 *direction_frames;

    initial_state = 1;
    state = action->unk_9B;
    switch (state) {
    case 0:
        action->unk_9B = initial_state;
    case 1:
        if (sprite->flags & 0x8000) {
            action->unk_9B = 3U;
            sprite->flags = (u16) (sprite->flags | 0x6000);
            resolve_attack_damage_and_effects(actor, sprite,(s16)(((ActorRecord *)actor)->facing),(s16)(1));
            return;
        }
        direction_frames = ((u8 *)flame_frame_set);
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sprite->frameTable = direction_frames;
        select_sprite_entry(sprite,(u8)(direction_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100)
            >> 9) & 7]), 0);
        action->unk_96 = 9;
        action->unk_9B++;
        return;
    case 2:
        ticks_left = action->unk_96 - 1;
        action->unk_96 = ticks_left;
        if ((ticks_left << 0x10) > 0) {
            return;
        }
        play_sound_if_enabled(0x804);
        resolve_attack_damage_and_effects(actor, sprite,(s16)(((ActorRecord *)actor)->facing),(s16)(1));
        action->unk_9B++;
        return;
    case 3:
        if (sprite->flags & 0xE000) {
            set_record_integer_tile_center(motion,(u8)sprite->tile_x,(u8)sprite->tile_y);
            spend_actor_mp(actor, 0x100);
            action->unk_8C = ((u8 *)initialize_destination_state);
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            if (((ActorRecord *)actor)->pending_turn_updates == 0) {
                ((ActorRecord *)actor)->action_flags = (u16) (((ActorRecord *)actor)->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
            } else {
                *((void **)actor_update_node_cursor) = actor - 0x20;
            }
        }
        return;
    default:
        return;
    }
}

/* Starts a targeted spell, waits for loading and animation, then restores actor movement and status. */
void start_selected_move_and_reset_action(ActorRecord *action, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 phase;
    s16 is_special;
    s32 move_kind;
    u8 *move_data;
    void *target;
    s8 target_x;
    s8 target_y;
    u16 recovery_ticks;

    phase = action->action_phase.u;
    is_special = 0;
    switch (phase) {
    case 0:
        if (((u32)actor->flags1C) & ACTOR_PLAYER_SIDE) {
            move_kind = (actor->action_flags & ACTOR_ACTION_CODE_MASK) - 1;
            switch (move_kind) {
            case 6:
                is_special = 1;
                /* fall through */
            case 2:
                move_data = (u8 *)actor + 0xE;
                break;
            case 5:
                is_special = 1;
                /* fall through */
            case 1:
                move_data = (u8 *)actor + 0xB;
                break;
            case 4:
                is_special = 1;
                /* fall through */
            case 0:
                move_data = (u8 *)actor + 8;
                break;
            default:
                move_data = 0;
                break;
            }
        } else {
            move_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (move_kind) {
            case 3:
                move_data = (u8 *)actor + 0xE;
                break;
            case 2:
                move_data = (u8 *)actor + 0xB;
                break;
            case 1:
                move_data = (u8 *)actor + 8;
                break;
            default:
                move_data = 0;
                break;
            }
        }
        if (*move_data != 0) {
            action->action_state_flags &= 0xFF7F;
            if (is_special != 0) {
                target = primary_actor_record;
                actor->target = target;
                phase = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                actor->target_tile_x = ((R06_80172970_S_80172970_3 *)phase)->unk_24;
                actor->target_tile_y = ((R06_80172970_S_80172970_3 *)phase)->unk_25;
            } else if (item_action_definitions[*move_data].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    phase = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    actor->target_tile_x = ((R06_80172970_S_80172970_3 *)phase)->unk_24;
                    actor->target_tile_y = ((R06_80172970_S_80172970_3 *)phase)->unk_25;
                }
            } else {
                actor->target =
                    scan_actor_along_heading(actor,
                    sprite->tile_x,
                    sprite->tile_y,
                    actor->facing, 0x10);
                target_x = actor->target_tile_x;
                target_y = actor->target_tile_y;
                target_x = abs(target_x);
                target_y = abs(target_y);
                actor->target_tile_x = target_x;
                actor->target_tile_y = target_y;

            }

            action->action_state_flags |= 0x1000;
            if (create_actor_spell_effect(actor, move_data,(s16)(is_special),
                (u16 *)((u8 *)action + 0x98)) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            ((R06_80172970_S_80172970_0 *)action)->unk_96 = 0xE;
            action->action_phase.u++;
            return;
        }

        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        ((R06_80172970_S_80172970_0 *)action)->unk_8C = ((u8 *)initialize_destination_state);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->action_phase.u++;

    case 2:
        recovery_ticks = ((R06_80172970_S_80172970_0 *)action)->unk_96 - 1;
        ((R06_80172970_S_80172970_0 *)action)->unk_96 = recovery_ticks;
        if ((s32)(recovery_ticks << 16) > 0) {
            if (!(sprite->flags & 0xE000)) {
                return;
            }
        }
        action->action_state_flags |= 0x80;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        if (*(u8 **)&sprite->frameTable != ((u8 *)flame_direction_frames)) {
            (sprite->frameTable) = ((u8 *)flame_direction_frames);
            select_sprite_entry(
                sprite,
                ((u8 *)flame_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        sprite->flags &= 0xF7FF;
        ((R06_80172970_S_80172970_0 *)action)->unk_8C = ((u8 *)initialize_destination_state);
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            (*(u8 *)&actor->pending_turn_updates)--;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

        return;
    default:
        return;
    }
}

/* MECHANISM: The 0x38 frame naturally holds args in s3/s4/s2/s1, with s5 state and s0 choice. Carrying
   the loaded object through the copy join removes a redundant lw+nop pair. A kept special-test copy
   restores move v0,s5; holding the copied record in v1 closes the final four register-field
   substitutions. */

/* Applies a value change and knockback, decelerates the actor, then recenters it and restores movement. */
void update_directional_motion_and_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *tile_state, ActorRecord *entity) {
    s16 timer;
    s32 direction;
    s32 tracked_entity;

    direction = (entity->movement_facing >> 9) & 7;
    switch (action->action_phase.u) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 18;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 18;
        action->action_phase.u++;

        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, tile_state, ((u8 *)flame_direction_frames));
            return;
        }
        if (tile_state->flags & 0x8000) {
            action->action_timer.s = 0;
            action->action_phase.s = 2;
            return;
        }
        if (entity->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->action_timer.s = timer;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 14;
        motion->velocity_y -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 14;
        if (action->action_timer.s > 0) {
            action->action_timer.s = action->action_timer.u - 1;
        } else if (tile_state->flags & 0x6000) {
            action->action_timer.s = 0;
        }
        if (action->action_timer.s != 0) {
            return;
        }
        if (entity->hp == 0) {
            action->action_phase.s = 0;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, tile_state, ((u8 *)flame_frame_set_1));
            return;
        }
        action->action_timer.s = 8;
        action->action_phase.u++;
        return;

    case 2:
        if (action->action_timer.s != 0) {
            {
                s32 target_coord = tile_state->tile_x << 6;
                s32 current_coord = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_coord - current_coord) << 15) >> 1;
            }
            {
                s32 target_coord = tile_state->tile_y << 6;
                s32 current_coord = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_coord - current_coord) << 15) >> 1;
            }
            motion->velocity_x += motion->velocity_x >> 1;
            motion->velocity_y += motion->velocity_y >> 1;
        }
        timer = action->action_timer.u - 1;
        action->action_timer.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile_state->tile_x, tile_state->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C.address = ((u8 *)initialize_destination_state);
        return;

    default:
        return;
    }
}

/* Fades the actor and its child sprites after defeat, awards experience, clears tile occupancy, and
 * unlinks it. */
void fade_sprites_and_remove_entity(void *actor, ObjectPosition *unused, SpriteFrameState *sprite, void *entity)
{
    u8 state;
    u8 *sprite_group;
    s32 sprite_index;
    s32 group_index;

    state = U8(actor, 0x9B);
    sprite_group = 0;
    switch (state) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            break;
        }
        U8(actor, 0x9B) = 1;
                        /* fallthrough */
    case 1:
    {
        s32 entity_flags;
        s32 sprite_offset;
        u8 *group_cursor;
        u32 white_rgb;
        SpriteFrameState *group_sprite;

        entity_flags = S32(entity, 0x14);
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        play_sound_if_enabled(0x805);

        group_index = 0;
        sprite->tpage_abr = 0x60;
        sprite->flags |= 0xC;
        U16(actor, 0x98) &= 0xDFFF;
        if (S16(actor, 0x9E) > 0) {
            white_rgb = 0xFFFFFF;
            group_cursor = actor;
            do {
                sprite_group = (u8 *)PTR(group_cursor, 0xA4) + 0x20;
                sprite_index = 0;
                if (S16(sprite_group, 2) > 0) {
                    sprite_offset = 8;
                    do {
                        group_sprite = sprite_group + sprite_offset;
                        group_sprite->color.word = white_rgb;
                        select_sprite_entry(group_sprite,(u8)(0x23), 0);
                        sprite_offset += 0x30;
                        sprite_index++;
                    } while (sprite_index < S16(sprite_group, 2));
                }
                group_cursor += 4;
                group_index++;
            } while (group_index < S16(actor, 0x9E));
        }
        U8(actor, 0x9B) = U8(actor, 0x9B) + 1;
        break;
    }

    case 2:
    {
        u8 *group_cursor;
        s32 fade_delta;

        group_index = 0;
        if ((s32)sprite_group < S16(actor, 0x9E)) {
            fade_delta = 0xFFEFEFF0;
            group_cursor = actor;
            do {
                sprite_group = (u8 *)PTR(group_cursor, 0xA4) + 0x20;
                sprite_index = 0;
                if (S16(sprite_group, 2) > 0) {
                    do {
                        (*(u32 *)((u8 *)sprite_group + sprite_index * 0x30 + 0x14)) += fade_delta;
                        sprite_index++;
                    } while (sprite_index < S16(sprite_group, 2));
                }
                group_cursor += 4;
                group_index++;
            } while (group_index < S16(actor, 0x9E));
        }
        if (U16(sprite_group, 0x1C) & 0x6000) {
            sprite->frameTable = ((u8 *)flame_frame_set_1);
            select_sprite_entry(sprite,(u8)(((u8 *)flame_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + S16(entity, 0x2A) + 0x100) >> 9) & 7]),
                0);
            U16(actor, 0x96) = 0x80;
            U8(actor, 0x9B) = U8(actor, 0x9B) + 1;
        }
        break;
    }

    case 3:
    {
        u8 brightness;
        u8 tile_x;
        u8 tile_y;
        s32 effect_id;
        DungeonGlobalStatus *dungeon_state;

        U32(entity, 0x1C) |= 0x10000000;
        brightness = U8(actor, 0x96);
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        sprite->color.c.r = brightness;
        U16(actor, 0x96) -= 0x10;
        if (sprite->color.c.r != 0) {
            break;
        }
        dungeon_state = &g_dungeon_status;
        if (dungeon_state->pending_display_owner == (u8 *)entity - 0x20) {
            *(u32 *)&dungeon_state->pending_display_owner &= 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);
        tile_x = sprite->tile_x;
        tile_y = sprite->tile_y;
        effect_id = 0x3000;
        if (U32(entity, 0x1C) & 0x2000) {
            effect_id = 0x300;
        }
        update_map_cell_flags_with_item_limit((u8)(tile_x),(u8)(tile_y), effect_id);
        unlink_entity_node(entity);
        U16(entity, -2) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
    }
}

/* Runs the shared hop and shrink update, then clears the record halfword at offset 0xB6. */
void reset_record_motion_field_b(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    update_actor_hop_and_shrink(body, motion, sprite, actor);
    body->unk_B4.halves.high.s = 0;
}

/* Runs the shared actor removal sequence with the supplied callback arguments. */
void advance_flame_removal(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}

/* Runs update_actor_hop_and_grow and installs initialize_destination_state when it returns nonzero. */
void grow_hopping_flame(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->unk_8C.handler = initialize_destination_state;
    }
}

/* Waits for a status effect to clear, updates actor status and activity counts, then restores movement. */
void update_actor_state_by_flags(ActorRecord *in_actor, ObjectPosition *in_context, SpriteFrameState *in_sprite, ActorRecord *in_entity) {
    void *context = in_context;
    s32 entity_flags;
    u16 stat_value;
    u16 stat_delta;
    u8 *page_base;
    s32 state;

    state = in_actor->action_phase.u;
    switch (state) {
    case 0:
        if (!(in_sprite->flags & 0xE000)) {
            return;
        }
        (in_sprite->frameTable) = ((u8 *)flame_alt_direction_frames);
        select_sprite_entry(in_sprite,(u8)(((u8 *)flame_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + in_entity->facing + 0x100) >> 9) & 7]),
            0);
        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_96 = 0;
        {
            u16 counter_value;

            counter_value = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
            counter_value--;
            g_dungeon_status.activity_counts.parts.pending_action_count = counter_value;
        }
        in_actor->action_phase.u++;
        return;

    case 1:
        if ((get_entity_effect_value(in_entity, STATUS_SLEEP) << 16) == 0) {
            (in_sprite->frameTable) = ((u8 *)flame_alt_direction_frames);
            select_sprite_entry(in_sprite,(u8)(((u8 *)flame_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + in_entity->facing + 0x100) >> 9) & 7]),
                0);
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s |= 0x40000;
            if (!(in_sprite->flags & 0x8000)) {

                state = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
                state++;
                g_dungeon_status.activity_counts.parts.pending_action_count = state;
                in_actor->action_phase.u++;
                return;
            }
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s &= ~0x200;
            ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)initialize_destination_state);
            return;
        }
        page_base = (u8 *)0x80080000;

        {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (in_entity->hp_delta != 0) {
                if (begin_ready_actor_directional_action(in_actor, context, in_sprite, 0) != 0) {
                    return;
                }
            }
            if (in_entity->mp_value.parts.whole == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_actor, context, in_sprite, in_entity);
                return;
            }
            if ((has_pending_actor_or_turn_action(in_entity) << 16) != 0) {
                return;
            }
            entity_flags = ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u;
            if (entity_flags & 0x100) {
                begin_pushed_actor_move(in_actor, context, in_sprite, in_entity);
                return;
            }
            if (entity_flags & 0x80000) {

                begin_actor_move_to_target_facing(in_actor, context, in_sprite, in_entity);
                stat_value = ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_92;
                stat_delta = ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B6;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B6 = 0;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B8 = 0;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_92 = stat_value - stat_delta;
                update_flame_parent_motion(in_actor, context, in_sprite, in_entity);
                return;
            }
            if (in_entity->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(in_entity) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                if ((check_entity_relation(in_entity,
                        (u8 *)owner->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(in_entity);
            on_actor_status_updated(in_entity);
            if ((get_entity_effect_value(in_entity, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&in_sprite->room_index;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, in_sprite) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(in_entity, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(in_entity, STATUS_SLEEP) << 16) != 0) {
                return;
            }
        }
        (in_sprite->frameTable) = ((u8 *)flame_alt_direction_frames);
        select_sprite_entry(in_sprite,(u8)(((u8 *)flame_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + in_entity->facing + 0x100) >> 9) & 7]),
            0);
        {
            u32 updated_flags;

            updated_flags = ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s;
            updated_flags |= 0x40000;
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s = updated_flags;
        }
        if (in_sprite->flags & 0x8000) {
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;
            ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)initialize_destination_state);
            return;
        }

        {

            state = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
            state++;
            g_dungeon_status.activity_counts.parts.pending_action_count = state;
        }

        in_actor->action_phase.u++;
        return;

    case 2:
        if (!(in_sprite->flags & 0xE000)) {
            return;
        }
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }

        ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;

        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)initialize_destination_state);

        return;
    }
}

/* Waits for MP recovery while processing actor status, then restores the normal animation and movement. */
void wait_for_flame_mp(ActorRecord *entity, ObjectPosition *context, SpriteFrameState *anim, ActorRecord *actor) {
    s32 state;

    state = entity->action_phase.u;
    switch (state) {
    case 0:
    {
        s32 *scene_state;
        u8 *direction_anims;

        if (!(anim->flags & 0xE000)) {
            return;
        }

        scene_state = &g_dungeon_status.turn_scale;
        ((R06_801738E0_S_801738E0_2 *)scene_state)->unk_0A--;
        direction_anims = ((u8 *)flame_alt_direction_frames);
        (anim->frameTable) = direction_anims;
        select_sprite_entry(anim,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        entity->action_phase.u++;
        return;
    }
    case 1:
    {
        u8 *scene_state;
        u32 actor_flags;

        if (actor->mp_value.parts.whole != 0) {
            s32 *status_page;

            (anim->frameTable) = ((u8 *)flame_frame_set_1);
            select_sprite_entry(anim,
                ((u8 *)flame_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((R06_801738E0_S_801738E0_3 *)actor)->unk_1C |= 0x40000;
            status_page = &g_dungeon_status.turn_scale;
            ((R06_801738E0_S_801738E0_2 *)status_page)->unk_0A++;
            entity->action_phase.u++;
            return;
        }

        scene_state = (u8 *)&g_dungeon_status.turn_scale;
        if (((R06_801738E0_S_801738E0_4 *)scene_state)->unk_02 & 0x1000) {
            return;
        }

        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(entity, context, anim, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            return;
        }

        actor_flags = ((R06_801738E0_S_801738E0_3 *)actor)->unk_1C;
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(entity, context, anim, actor);
            return;
        }

        if (actor_flags & 0x80000) {
            u16 entity_value;
            u16 pending_delta;

            begin_actor_move_to_target_facing(entity, context, anim, actor);
            entity_value = ((R06_801738E0_S_801738E0_0 *)entity)->unk_92;
            pending_delta = ((R06_801738E0_S_801738E0_0 *)entity)->unk_B6;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_B6 = 0;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_B8 = 0;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_92 = entity_value - pending_delta;
            update_flame_parent_motion(entity, context, anim, actor);
            return;
        }

        if (actor->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            if ((check_entity_relation(actor,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);
        if (actor->mp_value.parts.whole == 0) {
            return;
        }

        (anim->frameTable) = ((u8 *)flame_frame_set_1);
        select_sprite_entry(anim,
            ((u8 *)flame_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R06_801738E0_S_801738E0_3 *)actor)->unk_1C |= 0x40000;
        ((R06_801738E0_S_801738E0_4 *)scene_state)->unk_0A++;
    }
        entity->action_phase.u++;
        return;
    case 2:
        if (anim->flags & 0xE000) {
            s32 *scene_state;

            scene_state = &g_dungeon_status.turn_scale;
            ((R06_801738E0_S_801738E0_2 *)scene_state)->unk_0A--;
            ((R06_801738E0_S_801738E0_3 *)actor)->unk_1C &= ~0x208;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_8C = ((void *)initialize_destination_state);
        }

        return;
    default:
        return;
    }
}

/*
 * Resumes the main actor handler after parent motion completes and the signed floor-trap check is
 * positive; during motion, restores movement frames when the alternate table is active and flags
 * 0x208 are clear.
 */
void update_flame_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object) {
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C.handler = ((u8 *)initialize_destination_state);
            return;
        }
    } else if (*(u8 **)&entity->frameTable == ((u8 *)flame_alt_direction_frames) &&
               !(map_object->flags1C & 0x208)) {
        entity->frameTable = ((u8 *)flame_direction_frames);
        select_sprite_entry(entity,(s16)(((u8 *)flame_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->facing + 0x100) >> 9) & 7]),(s16)(0));
    }
}

/*
 * Runs update_thrown_actor_travel and installs initialize_destination_state only when it succeeds
 * and the signed floor-trap check returns positive.
 */
void create_randomized_rotated_effect(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic) {
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->unk_8C.handler = initialize_destination_state;
        }
    }
}

/*
 * Runs interpolate_actor_to_terrain_tile and installs initialize_destination_state when it returns
 * nonzero.
 */
void finish_actor_terrain_interpolation_then_initialize_destination(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->unk_8C.handler = initialize_destination_state;
    }
}

/* Runs update_spinning_actor_fall and installs initialize_destination_state when it returns nonzero. */
void finish_spinning_actor_fall_then_initialize_destination(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->unk_8C.handler = initialize_destination_state;
    }
}

/* Runs update_actor_fade_in and installs initialize_destination_state when it returns nonzero. */
void finish_actor_fade_in_then_initialize_destination(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->unk_8C.handler = initialize_destination_state;
    }
}

/* Projects visible sprites in the linked effect chain using the shared depth adjustment. */
s32 project_flame_sprite_chain(void *initial_payload, s32 entry_data, R06_80173E08_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R06_80173E08_Scratchpad *scratch = (R06_80173E08_Scratchpad *)0x1F800000;
    R06_80173E08_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_8017591C)[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R06_80173E08_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/*
 * Projects linked effect positions and queues brightness-scaled pixel and drawing-mode packets by
 * depth.
 *
 * MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets.
 */
s32 append_linked_shaded_point_packets(u8 *node, void *vertex_arg)
{
    u8 **state_ptr;
    R06_80173E94_S_80173E94_1 *scratch;
    register u8 *state;
    register u8 *final_state;
    register u8 *packet_end;
    register R06_80173E94_S_80173E94_3 *packet;
    u8 *mode_packet;
    u8 *vertex;
    void *previous;
    u32 depth_index;
    u16 vertex_x;

    vertex = vertex_arg;
    state_ptr = (u8 **)((u8 *)(&g_game_work));
    state = g_game_work.draw_buffer;
    scratch = (R06_80173E94_S_80173E94_1 *)0x1F800000;

    scratch->unk_18 = ((GpuContext *)state)->packetCursor;
    scratch->unk_20.p = state + 0xB0;

    do {
        vertex_x = ((R06_80173E94_S_80173E94_2 *)vertex)->unk_02;
        packet = scratch->unk_18;
        scratch->unk_00 = vertex_x;
        scratch->unk_02 = ((R06_80173E94_S_80173E94_2 *)vertex)->unk_06;
        scratch->unk_04 = ((R06_80173E94_S_80173E94_2 *)vertex)->unk_0A;
        scratch->unk_18 = packet + 1;

        depth_index = RotTransPers(scratch, &packet->screen, &scratch->transform_p,
                             &scratch->transform_flags);
        scratch->unk_C0 = depth_index;

        if (depth_index < 0x1E0) {
            s32 shade_or_page;
            s32 pixel_mode;
            s32 blend_mode;
            s32 page_x;
            s32 tile_code;

            packet->unk_04.at00.v = ((R06_80173E94_S_80173E94_4 *)node)->unk_08;
            shade_or_page = packet->unk_04.at00u.v * ((R06_80173E94_S_80173E94_4 *)node)->unk_32;
            if (shade_or_page < 0) {
                shade_or_page += 0xFF;
            }
            packet->unk_04.at00u.v = shade_or_page >> 8;

            shade_or_page = packet->unk_04.at01.v * ((R06_80173E94_S_80173E94_4 *)node)->unk_32;
            if (shade_or_page < 0) {
                shade_or_page += 0xFF;
            }
            packet->unk_04.at01.v = shade_or_page >> 8;

            shade_or_page = packet->unk_04.at02.v * ((R06_80173E94_S_80173E94_4 *)node)->unk_32;
            if (shade_or_page < 0) {
                shade_or_page += 0xFF;
                pixel_mode = 0;
            } else {
                pixel_mode = 0;
            }
            blend_mode = 1;
            packet->unk_04.at02.v = shade_or_page >> 8;
            packet->unk_00.at03.v = 2;
            tile_code = 0x6A;
            page_x = pixel_mode;
            packet->unk_04.at03.v = tile_code;

            ((R06_80173E94_OrderingTag *)packet)->addr =
                ((R06_80173E94_OrderingTag *)(scratch->unk_20.p2
                    + scratch->unk_C0))->addr;
            {
                u32 *ot_entry;
                u32 ot_tag;
                u32 packet_addr;

                ot_entry = (u32 *)(scratch->unk_C0 << 2);
                ot_entry = (u32 *)((u32)ot_entry +
                                   (u32)scratch->unk_20.p2);
                ot_tag = *ot_entry;
                *ot_entry = ((u32)((ot_tag & 0xFF000000) | ((u32)((u32)packet & 0x00FFFFFF))));
            }

            mode_packet = scratch->unk_18;
            scratch->unk_18 = mode_packet + 0xC;
            shade_or_page = GetTPage(pixel_mode, blend_mode, page_x, pixel_mode);
            SetDrawMode(mode_packet, 0, 0, (u16)shade_or_page, 0);

            ((R06_80173E94_OrderingTag *)mode_packet)->addr =
                ((R06_80173E94_OrderingTag *)(scratch->unk_20.p2
                    + scratch->unk_C0))->addr;
            mode_packet = (u8 *)((u32)mode_packet & 0x00FFFFFF);
            (*(u32 *)((u8 *)(scratch->unk_20.p2) + scratch->unk_C0 * 4)) =
                ((*(u32 *)((u8 *)(scratch->unk_20.p2)
                    + scratch->unk_C0 * 4)) & 0xFF000000) |
                (u32)mode_packet;
        }

        previous = ((R06_80173E94_S_80173E94_4_pre *)node)[-1].unk_00;
        node = (u8 *)previous + 0x20;
        if (previous == 0) {
            break;
        }
        vertex = ((R06_80173E94_S_80173E94_5 *)previous)->unk_08;
    } while (1);

    final_state = *state_ptr;
    packet_end = scratch->unk_18;
    ((GpuContext *)final_state)->packetCursor = packet_end;
    return 0;
}

/* Moves the effect with directional jitter and a vertical offset, reduces its speed, and removes it on
 * timeout. */
void advance_randomized_motion_and_complete(PointRecord *object_data, R06_801740E4_S_801740E4_0 *position, R06_801740E4_S_801740E4_2 *state) {
    s16 next_speed;
    s32 random_value;
    s32 lowered_z;

    position->unk_00 += ((dir_step_x[object_data->unk_14] * object_data->brightness) << 7) + (rand() & 0x7FFF);
    position->unk_04 += ((dir_step_y[object_data->unk_14] * object_data->brightness) << 7) + (rand() & 0x7FFF);
    random_value = rand();
    lowered_z = position->unk_08 + (s32) 0xFFFE0000;
    position->unk_08 = lowered_z - (random_value & 0xFFF);
    next_speed = (u16) object_data->brightness - 8;
    object_data->brightness = next_speed;
    if (((next_speed << 0x10) <= 0) || (state->unk_14 & 0x8000)) {
        ((R06_801740E4_S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_00 = (u16) (((R06_801740E4_S_801740E4_1 *)((u8 *)object_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}

/* Creates a shaded point effect at a randomized offset from its owner with the supplied color and
 * brightness. */
void advance_actor_action_and_update_status(
    void *source,
    s16 value_34,
    s32 value_28,
    s16 value_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    ObjectNodeHeader *source_obj = source;
    s16 saved_value_34 = value_34;
    u32 saved_value_28 = value_28;
    s16 saved_value_52 = value_52;
    ObjectNodeHeader *object_fields;
    R06_80174214_S_80174214_0 *fields;
    s32 x_jitter;
    s32 y_jitter;
    s32 z_jitter;
    s16 x_bias;
    s16 y_bias;
    s16 z_bias;
    s16 x_pos;
    s16 y_pos;
    s16 z_pos;
    void *init_data;
    ObjectPosition *x_dest;
    ObjectPosition *y_dest;
    ObjectPosition *z_dest;

    object_fields = allocate_list_node(0x211, &source_obj->next);
    if (object_fields != NULL) {
        object_fields->update_callback = (u8 *)advance_randomized_motion_and_complete;
        x_jitter = rand() & 0x1F;
        x_pos = ((R06_80174214_S_80174214_6 *)(source_obj->position))->unk_02;
        x_dest = object_fields->position;
        x_pos += x_jitter;
        x_bias = x_offset - 0x10;
        x_pos += x_bias;
        x_dest->x.w.i = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = ((R06_80174214_S_80174214_6 *)(source_obj->position))->unk_06;
        y_dest = object_fields->position;
        y_pos += y_jitter;
        y_bias = y_offset - 0x10;
        y_pos += y_bias;
        y_dest->y.w.i = (s16)y_pos;

        z_jitter = rand();
        init_data = ((void *)append_linked_shaded_point_packets);
        z_pos = ((R06_80174214_S_80174214_6 *)(source_obj->position))->unk_0A;
        z_jitter &= 0x1F;
        fields = (R06_80174214_S_80174214_0 *)((u8 *)object_fields + 0x20);
        z_dest = object_fields->position;
        z_pos += z_jitter;
        z_bias = z_offset - 0x10;
        z_pos += z_bias;
        z_dest->z.w.i = (s16)z_pos;
        fields->unk_14 = saved_value_34;
        fields->unk_32 = saved_value_52;
        register_node(object_fields, init_data);
        fields->unk_08.u = saved_value_28;
    }
}

/*
 * Projects an effect quad, clips it by depth and screen bounds, then queues a colored textured
 * polygon.
 *
 * MECHANISM: a splitting cell (2.8.0-G0) emits ((u8 *)advance_randomized_motion_and_complete) /
 * ((u8 *)append_linked_shaded_point_packets) as HIGH/LO pairs itself (the lui in the beqz delay
 * slot). The s16 stack offsets stay in s2-s4 from the prologue, and fields is the 0x20-advanced
 * record.
 */
void project_and_queue_textured_quad(void *quad, void *position, void *draw_state, s16 depth_bias)
{
    R06_80174334_S_80174334_0 *scratch = (R06_80174334_S_80174334_0 *)0x1F800000;
    R06_80174334_S_80174334_5 *packet;
    void *packet_data;
    u8 *texture;
    s32 ot_index;
    u16 draw_flags;
    u8 tex_flags;
    R06_80174334_MATRIX matrix;

    scratch->unk_24.p = *(u8 **)&g_game_work.draw_buffer + 0xB0;
    scratch->matrices.position.x = ((R06_80174334_S_80174334_1 *)position)->unk_02;
    scratch->matrices.position.y = ((R06_80174334_S_80174334_1 *)position)->unk_06;
    scratch->matrices.position.z = ((R06_80174334_S_80174334_1 *)position)->unk_0A;
    ((R06_80174334_S_80174334_2 *)draw_state)->unk_14 |= 0x8000;

    PushMatrix();

    scratch->unk_3C = 0x2000;
    scratch->unk_38 = 0x2000;
    scratch->unk_34 = 0x2000;
    scratch->unk_A4 = ((R06_80174334_S_80174334_2 *)draw_state)->unk_16;
    scratch->unk_A8 = ((R06_80174334_S_80174334_2 *)draw_state)->unk_1A;
    scratch->unk_A6 = ((R06_80174334_S_80174334_2 *)draw_state)->unk_18;
    RotMatrix(&scratch->unk_A4, &scratch->matrices.transform[1]);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, &scratch->matrices.transform[1], &scratch->matrices.transform[0]);
    ScaleMatrix(&scratch->matrices.transform[0], &scratch->unk_34);
    SetTransMatrix(&scratch->matrices.transform[0]);
    SetRotMatrix(&scratch->matrices.transform[0]);

    texture = ((R06_80174334_S_80174334_2 *)draw_state)->unk_08;
    scratch->unk_28 = ((R06_80174334_S_80174334_2 *)draw_state)->unk_14;
    scratch->unk_0C.s32 = texture[8];
    scratch->unk_10.s32 = texture[9];
    /* BYTES: this raw word store keeps the following draw-buffer load in order. */
    (*(s32 *)((u8 *)scratch + 0x14)) = texture[0xA];
    scratch->unk_18.s32 = texture[0xB];
    packet_data = ((GpuContext *)(*(u8 **)&g_game_work.draw_buffer))->packetCursor;
    packet = packet_data;
    ((GpuContext *)(*(u8 **)&g_game_work.draw_buffer))->packetCursor = packet_data + 0x34;

    scratch->unk_B0 = ((R06_80174334_S_80174334_4 *)quad)->unk_64;
    scratch->unk_B8 = ((R06_80174334_S_80174334_4 *)quad)->unk_6A;
    scratch->unk_C0 = ((R06_80174334_S_80174334_4 *)quad)->unk_70;
    scratch->unk_C8 = ((R06_80174334_S_80174334_4 *)quad)->unk_76;
    scratch->unk_B2 = ((R06_80174334_S_80174334_4 *)quad)->unk_66;
    scratch->unk_BA = ((R06_80174334_S_80174334_4 *)quad)->unk_6C;
    scratch->unk_C2 = ((R06_80174334_S_80174334_4 *)quad)->unk_72;
    scratch->unk_CA = ((R06_80174334_S_80174334_4 *)quad)->unk_78;
    scratch->unk_B4 = ((R06_80174334_S_80174334_4 *)quad)->unk_68;
    scratch->unk_BC = ((R06_80174334_S_80174334_4 *)quad)->unk_6E;
    scratch->unk_C4 = ((R06_80174334_S_80174334_4 *)quad)->unk_74;
    scratch->unk_CC = ((R06_80174334_S_80174334_4 *)quad)->unk_7A;

    ot_index = RotAverage4(&scratch->unk_B0, &scratch->unk_B8,
                             &scratch->unk_C0, &scratch->unk_C8,
                             &packet->xy0.word, &packet->xy1.word,
                             &packet->xy2.word, &packet->xy3.word,
                             &scratch->transform_p, &scratch->transform_flags) - depth_bias - 6;
    scratch->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(packet->xy0.parts.x.u + 0x20) < 0x181) &&
             ((u16)(packet->xy0.parts.y.u + 0x20) < 0x121)) |
            (((u16)(packet->xy1.parts.x + 0x20) < 0x181) &&
             ((u16)(packet->xy1.parts.y + 0x20) < 0x121)) |
            (((u16)(packet->xy2.parts.x + 0x20) < 0x181) &&
             ((u16)(packet->xy2.parts.y + 0x20) < 0x121)) |
            (((u16)(packet->xy3.parts.x.u + 0x20) < 0x181) &&
             ((u16)(packet->xy3.parts.y.u + 0x20) < 0x121))) {
            ((R06_80174334_S_80174334_2 *)draw_state)->unk_14 &= 0x7FFF;

            scratch->unk_14.s32 += scratch->unk_0C.s32;
            if (scratch->unk_14.s32 & 0x100) {
                scratch->unk_14.s32--;
            }
            scratch->unk_18.s32 += scratch->unk_10.s32;
            if (scratch->unk_18.s32 & 0x100) {
                scratch->unk_18.s32--;
            }
            scratch->unk_10.s32 <<= 8;
            scratch->unk_18.s32 <<= 8;

            if (((R06_80174334_S_80174334_2 *)draw_state)->unk_12) {
                if (scratch->unk_28 & 0x100) {
                    packet->unk_0E = ((R06_80174334_S_80174334_2 *)draw_state)->unk_12;
                } else {
                    packet->unk_0E = ((R06_80174334_S_80174334_2 *)draw_state)->unk_12 +
                                              ((R06_80174334_S_80174334_6 *)texture)->unk_06;
                }
            } else {
                packet->unk_0E = ((R06_80174334_S_80174334_6 *)texture)->unk_06;
            }

            packet->unk_0C = scratch->unk_10.u16 +
                                      scratch->unk_0C.u16;
            packet->unk_18.u16 = scratch->unk_10.u16 +
                                       scratch->unk_14.u16;

            if (((R06_80174334_S_80174334_2 *)draw_state)->unk_10) {
                packet->unk_1A = ((R06_80174334_S_80174334_2 *)draw_state)->unk_10 +
                                           (((R06_80174334_S_80174334_6 *)texture)->unk_04 & 0xFF9F);
            } else {
                packet->unk_1A = ((R06_80174334_S_80174334_6 *)texture)->unk_04;
            }

            packet->unk_24.at00.v = scratch->unk_18.u16 +
                                       scratch->unk_0C.u16;
            packet->unk_30.at00.v = scratch->unk_18.u16 +
                                       scratch->unk_14.u16;

            if (packet->xy0.parts.x.s > packet->xy3.parts.x.s) {
                packet->unk_18.u8--;
                packet->unk_30.at00u.v--;
            }
            if (packet->xy0.parts.y.s > packet->xy3.parts.y.s) {
                packet->unk_24.at01.v--;
                packet->unk_30.at01.v--;
            }

            packet->unk_04.at00.v = ((R06_80174334_S_80174334_4 *)quad)->unk_04;
            packet->unk_10 = ((R06_80174334_S_80174334_4 *)quad)->unk_08;
            packet->unk_1C = ((R06_80174334_S_80174334_4 *)quad)->unk_0C;
            packet->unk_28 = ((R06_80174334_S_80174334_4 *)quad)->unk_10;

            SetPolyGT4(packet);

            tex_flags = texture[1];
            ((R06_80174334_S_80174334_2 *)draw_state)->unk_0F = tex_flags;
            draw_flags = scratch->unk_28;
            if (draw_flags & 8) {
                ((R06_80174334_S_80174334_2 *)draw_state)->unk_0F = (draw_flags & 4) ?
                    (tex_flags | 2) : (tex_flags & 0xFD);
            }

            packet->unk_04.at03.v |= ((R06_80174334_S_80174334_2 *)draw_state)->unk_0F;
            packet->unk_00 = (packet->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(scratch->unk_24.p2)
                    + scratch->unk_100 * 4)) & 0x00FFFFFF);

            (*(u32 *)((u8 *)(scratch->unk_24.p2) + scratch->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(scratch->unk_24.p2)
                    + scratch->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    PopMatrix();
}


/* Traverses linked effect nodes and projects each node's textured quad into render packets. */
s32 project_textured_quad_chain(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        project_and_queue_textured_quad(state, context, data,(s16)(0));
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((R06_8017489C_Func800C138CData *)next_node)->context;
        data = ((R06_8017489C_Func800C138CData *)next_node)->data;
    }
}

/*
 * Decrements the 16-bit lifetime and sets local and global removal flags when the signed result is
 * zero or negative.
 */
void advance_record_countdown(void *record_data) {
    u16 remaining_count;

    remaining_count = ((R06_801748F0_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((R06_801748F0_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((R06_801748F0_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((R06_801748F0_S_801748F0_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* Fades a four-strip textured effect, emits randomized particles, and flags it for removal on timeout. */
void update_fading_four_strip_effect(u8 *effect, R06_80174934_Vec3w *origin, u8 *render_data)
{
    s16 phase;
    u16 phase_bits;
    s16 strip_index;
    s16 vertex_index;
    s16 next_vertex;
    s16 row_index;
    s16 next_row;
    s16 axis_index;
    s16 next_axis;
    s16 frames_left;
    s16 top;
    s16 bottom;
    s32 fade_level;
    s32 random_offset;
    s32 particle_variant;
    s32 particle_strength;
    ObjectNodeHeader *strip_obj;
    ObjectNodeHeader *init_obj;
    u8 *strip_data;
    u8 *render_ctl;
    ObjectPosition *position;
    u8 *frame_data;
    void *callback;
    u32 *vertex_color;

    phase_bits = ((R06_80174934_S_80174934_0 *)effect)->unk_16.u;
    phase = ((R06_80174934_S_80174934_0 *)effect)->unk_16.s;
    switch (phase) {
    case 0:
        render_data[0xC] = (u8)((effect[4] *
            (0x32 - ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s)) / 10);
        render_data[0xD] = (u8)((effect[5] *
            (0x32 - ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s)) / 10);
        fade_level = 0x32 - ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s;
        render_data[0xE] = (u8)((effect[6] * fade_level) / 10);
        if (((R06_80174934_S_80174934_0 *)effect)->unk_1A.s < 0x29) {
            ((R06_80174934_S_80174934_0 *)effect)->unk_16.p =
                ((R06_80174934_S_80174934_0 *)effect)->unk_16.u + 1;
        }
        break;
    case 1:
        if (((R06_80174934_S_80174934_0 *)effect)->unk_1A.s < 0xC) {
            ((R06_80174934_S_80174934_0 *)effect)->unk_16.s = phase_bits + 1;
        }

        if (rand() & 1) {
            particle_variant = rand() & 7;
            particle_strength = rand() & 0xFF;
            particle_strength = particle_strength | 0x80;
            random_offset = rand();
            advance_actor_action_and_update_status(effect - 0x20, particle_variant, 0xF0, particle_strength,
                ((R06_80174934_S_80174934_0 *)effect)->unk_64, ((R06_80174934_S_80174934_0 *)effect)->unk_66,
                (s16)(-0x70 - (random_offset & 0x1F)));
        } else {
            particle_variant = rand() & 7;
            particle_strength = rand() & 0xFF;
            particle_strength = particle_strength | 0x80;
            random_offset = rand();
            advance_actor_action_and_update_status(effect - 0x20, particle_variant, 0xF0, particle_strength,
                ((R06_80174934_S_80174934_0 *)effect)->unk_64, ((R06_80174934_S_80174934_0 *)effect)->unk_66,
                (s16)(-0x40 - (random_offset & 0x1F)));
        }
        break;
    case 2:
        render_data[0xC] = (u8)((effect[4] * ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s) / 10);
        render_data[0xD] = (u8)((effect[5] * ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s) / 10);
        render_data[0xE] = (u8)((effect[6] * ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s) / 10);
        break;
    }

    ((R06_80174934_S_80174934_0 *)effect)->unk_20 = ((R06_80174934_S_80174934_0 *)effect)->unk_20 + 1;
    for (strip_index = 0; strip_index < 4; strip_index++) {
        strip_obj = allocate_flagged_object_node(0x12);
        if (strip_obj != 0) {
            init_obj = strip_obj;
            callback = ((u8 *)project_textured_quad_chain);
            strip_data = ((u8 *)strip_obj) + 0x20;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_1A = 1;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_1C = 1;
            strip_obj->update_callback = ((u8 *)advance_record_countdown);
            register_node(init_obj, callback);

            render_ctl = *(u8 * *)&strip_obj->sprite;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_10 = 0x20;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_14 |= 0xC;

            position = strip_obj->position;
            position->x.v = origin->x;
            position->y.v = origin->y;
            position->z.v = origin->z;

            render_ctl = *(u8 * *)&strip_obj->sprite;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_1E = 0x1000;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_1C = 0x1000;
            render_ctl[0xE] = 0x80;
            render_ctl[0xD] = 0x80;
            render_ctl[0xC] = 0x80;

            vertex_index = 0;
            do {
                vertex_color = (u32 *)strip_data + vertex_index;
                ((u8 *)vertex_color)[4] = render_data[0xC];
                ((u8 *)vertex_color)[5] = render_data[0xD];
                next_vertex = vertex_index + 1;
                vertex_index = next_vertex;
                ((u8 *)vertex_color)[6] = render_data[0xE];
            } while (next_vertex < 4);

            if (strip_index == 3) {
                strip_data[0xA] = 0;
                strip_data[9] = 0;
                strip_data[8] = 0;
                strip_data[6] = 0;
                strip_data[5] = 0;
                strip_data[4] = 0;
            }

            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_06 = 0;
            memcpy(strip_data + 0x28, ((u8 *)D_80175910), 12);
            frame_data = strip_data + 0x28;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_08 = frame_data;
            frame_data[8] = (u8)(frame_data[8] + ((R06_80174934_S_80174934_0 *)effect)->unk_1E * 4);
            frame_data = ((R06_80174934_S_80174934_3 *)render_ctl)->unk_08;
            frame_data[9] = (u8)(frame_data[9] + ((((R06_80174934_S_80174934_0 *)effect)->unk_20 & 3) * 8));

            row_index = 0;
            do {
                axis_index = 0;
                do {
                    ((R06_80174934_Rows *)strip_data)->row[row_index][axis_index] =
                        ((R06_80174934_Rows *)effect)->row[row_index][axis_index];
                    next_axis = axis_index + 1;
                    axis_index = next_axis;
                } while (next_axis < 3);
                next_row = row_index + 1;
                row_index = next_row;
            } while (next_row < 4);

            top = 0 - ((strip_index + 1) * 0x10);
            bottom = 0 - (strip_index * 0x10);
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_6E = top;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_68 = top;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_7A = bottom;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_74 = bottom;
        }
    }

    frames_left = ((R06_80174934_S_80174934_0 *)effect)->unk_1A.u - 1;
    ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s = frames_left;
    if (frames_left <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return;
}

/* Creates sixteen colored ring segments around the supplied position, each with a fading strip callback. */
void create_sixteen_segment_ring(R06_80174E78_Source *source, R06_80174E78_Vec3i *center, void *unused_context)
{
    s16 segment_index;
    void (*update_callback)(void);
    s32 base_level;

    segment_index = 0;
    update_callback = update_fading_four_strip_effect;
    base_level = 32;
    for (; segment_index < 16; segment_index++) {
        ObjectNodeHeader *entity;
        void *body_storage;
        R06_80174E78_Sub *sub;
        ObjectPosition *position;
        SpriteFrameState *prim;
        s32 angle;
        s32 next_angle;
        s16 radial_offset;
        u16 prim_flags;
        u16 *prim_flags_ptr;
        ObjectNodeHeader *setup_entity;
        s32 initial_count;
        s32 unit_scale;
        s32 trig_angle;
        s32 trig_value;

        entity = allocate_flagged_object_node(18);
        if (entity == 0) {
            continue;
        }

        body_storage = entity + 1;
        sub = body_storage;
        initial_count = 50;
        setup_entity = entity;
        sub->field_1A = initial_count;
        sub->field_1C = source->field_96;
        entity->update_callback = update_callback;
        register_node(setup_entity, project_sprite_chain);

        prim = entity->sprite;
        prim_flags_ptr = &prim->flags;
        prim_flags = *(u16 *)prim_flags_ptr;
        prim_flags |= 0xC;
        *prim_flags_ptr = prim_flags;
        prim->tpage_abr = base_level;
        prim_flags |= 0x80;
        *prim_flags_ptr = prim_flags;

        position = entity->position;
        position->x.v = center->x;
        next_angle = (segment_index + 1) << 8;
        position->y.v = center->y;
        position->z.v = center->z;

        sub->field_6E = -64;
        sub->field_68 = -64;
        sub->field_7A = 0;
        sub->field_74 = 0;

        trig_value = rcos(next_angle);
        angle = segment_index << 8;
        trig_angle = angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->field_70 = radial_offset;
        sub->field_64 = radial_offset;

        trig_value = rcos(trig_angle);
        trig_angle = next_angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->field_76 = radial_offset;
        sub->field_6A = radial_offset;

        trig_value = rsin(trig_angle);
        trig_angle = angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->field_72 = radial_offset;
        sub->field_66 = radial_offset;

        trig_value = rsin(trig_angle);
        radial_offset = (trig_value * 24) >> 12;
        sub->field_78 = radial_offset;
        sub->field_6C = radial_offset;

        prim = entity->sprite;
        prim->color.c.r = 128;
        unit_scale = 4096;
        prim->scale_y = unit_scale;
        prim->scale_x = unit_scale;
        prim->color.c.g = base_level;
        prim->color.c.b = base_level;
        sub->field_04 = prim->color.c.r;
        sub->field_05 = prim->color.c.g;
        sub->field_06 = prim->color.c.b;
    }
}

/* Stops movement and waits for dungeon activity to finish, then clears the callback and counts the new
 * action. */
void wait_for_flame_action_slot(void *entity_data, ObjectPosition *unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other = other_data;
    s32 kind = 0x17;

    other[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = ((void *)wait_for_flame_action_slot);
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other[0x6D] = 0;
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(other) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        (*(s16 *)actor_action_reset_value) = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}

/* Advances the transition sprite, then restores the view tint to neutral and removes the effect. */
void fade_effect_to_neutral_and_finish(void *entity_data, void *unused, void *source_data)
{
    u8 *entity = entity_data;
    SpriteFrameState *source= source_data;
    GameWork *colors = &g_game_work;
    u16 frame_count;
    u16 fade_left;

    if (entity[0x9A] == 0) {
        ((s32 *)D_80175928)[0] = *(s32 *)&source->source;
        advance_sprite_animation_and_textures(source);

        if (source->flags & 0xE000) {
            unlink_node(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        frame_count = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = frame_count + 1;
        if ((frame_count & 3) == 1) {
            ((u16 *)D_8017591C)[0]++;
            return;
        }
    } else {
        colors->view.tint.parts.tint_r += (0x80 - colors->view.tint.parts.tint_r) / *(s16 *)(entity + 0x96);
        colors->view.tint.parts.tint_g += (0x80 - colors->view.tint.parts.tint_g) / *(s16 *)(entity + 0x96);
        colors->view.tint.parts.tint_b += (0x80 - colors->view.tint.parts.tint_b) / *(s16 *)(entity + 0x96);

        fade_left = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = fade_left;
        if ((fade_left << 16) <= 0) {
            *(u16 *)(entity - 2) |= 0x8000;
            *(s32 *)((u8 *)(&object_flag_block)) |= 0x8000;
        }
    }
}

/* Loads transition effects, fades the view tint, replaces the actor, and restores the new actor's facing. */
void advance_actor_transition_and_restore_child_angle(ActorRecord *action, ObjectPosition *position, SpriteFrameState *entity, ActorRecord *actor) {
    ObjectNodeHeader *effect_node;
    SpriteFrameState *effect_sprite;
    R06_80175270_S_80175270_2 *work = ((u8 *)(&g_game_work));
    u8 state;
    s32 effect_id;
    s32 direction;
    s32 raw_direction;
    u16 angle;

    state = ((R06_80175270_S_80175270_0 *)action)->phase;
    if (state >= 9) {
        return;
    }
    switch (state) {
    case 0:
        ((R06_80175270_S_80175270_0 *)action)->phase++;
        return;

    case 1:
        run_cd_image_commands(((u8 *)D_801758FC), ((u8 *)D_80175920), 0);
        ((R06_80175270_S_80175270_0 *)action)->unk_BA = 0;
        ((R06_80175270_S_80175270_0 *)action)->phase++;
        ((R06_80175270_S_80175270_1 *)actor)->unk_8A = ((R06_80175270_S_80175270_1 *)actor)->unk_2A.u;
        ((R06_80175270_S_80175270_1 *)actor)->unk_1C &= 0xFFFBFFFF;
        /* fallthrough */

    case 2:
        angle = ((R06_80175270_S_80175270_1 *)actor)->unk_2A.u;
        raw_direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((R06_80175270_S_80175270_1 *)actor)->unk_2A.s + 0x100) >> 9;
        direction = raw_direction & 7;
        if ((((u8 *)((void **)flame_transition_object))[-4] == 0) || (direction != 2)) {
            if (direction == 2) {
                return;
            }
            ((R06_80175270_S_80175270_1 *)actor)->unk_2A.u = angle + 0x200;
            return;
        }
        run_cd_image_commands((u8 *)((s32 *)D_80175904) - 8, (u8 *)((void **)flame_transition_object) - 4, 1);
        sound_set_cd_cue_parameters(0, ((s32 *)cd_cue_base)[0], 0x04000AD4, 0x05000CC4);
        effect_id = read_stream_cue_start_offset();
        Control_CD(0x15, effect_id, 0);
        ((u8 *)flame_effect_load_done)[0] = 0;
        Control_CD(0xFF, ((s32 *)resource_completion_callback_address), ((u8 *)flame_effect_load_done));
        select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, position, 8, 0x300);
        ((R06_80175270_S_80175270_0 *)action)->timer.s = 0x10;
        ((R06_80175270_S_80175270_0 *)action)->phase++;
        /* fallthrough */

    case 3:
        {
            s32 frames_left;
            u8 *target_color;
            u8 effect_done;

            frames_left = ((R06_80175270_S_80175270_0 *)action)->timer.u;
            ((R06_80175270_S_80175270_0 *)action)->timer.u = frames_left - 1;
            if ((s16)(frames_left - 1) <= 0) {
                effect_done = ((u8 *)flame_effect_load_done)[0];
                ((R06_80175270_S_80175270_0 *)action)->timer.u = frames_left;
                if (effect_done != 0) {
                    ((R06_80175270_S_80175270_0 *)action)->phase++;
                    play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                    return;
                }
                return;
            }
            target_color = ((u8 **)actor_effect_color_targets)[lookup_masked_byte_table(actor)];
            work->unk_A8 += (((R06_80175270_S_80175270_3 *)target_color)->unk_00 - work->unk_A8) / ((R06_80175270_S_80175270_0 *)action)->timer.s;
            work->unk_A9 += (((R06_80175270_S_80175270_3 *)target_color)->unk_01 - work->unk_A9) / ((R06_80175270_S_80175270_0 *)action)->timer.s;
            work->unk_AA += (((R06_80175270_S_80175270_3 *)target_color)->unk_02 - work->unk_AA) / ((R06_80175270_S_80175270_0 *)action)->timer.s;
            return;
        }

    case 4:
        {
            s16 asset_index;
            s32 *position_y_dst;
            s32 *position_z_dst;
            s32 position_y;
            s32 position_z;
            s32 color;

            effect_node = allocate_flagged_object_node(0x12);
            if (effect_node == 0) {
                return;
            }
            effect_node->update_callback = ((u8 *)fade_effect_to_neutral_and_finish);
            register_node(effect_node, ((u8 *)project_flame_sprite_chain));
            color = 0x00808080;
            effect_node->position->x.v = position->x.v;
            position_y_dst = &effect_node->position->x.v;
            position_y = position->y.v;
            ((void **)flame_transition_object)[0] = effect_node;
            position_y_dst[1] = position_y;
            position_z_dst = &effect_node->position->x.v;
            position_z = position->z.v;
            ((s16 *)D_8017591C)[0] = -12;
            position_z_dst[2] = position_z;
            effect_sprite = effect_node->sprite;
            effect_sprite->scale_y = 0x1000;
            effect_sprite->scale_x = 0x1000;
            effect_sprite->color.word = color;
            asset_index = lookup_masked_byte_table(actor) - 1;
            if (asset_index < 0) {
                asset_index = rand() % 3;
            }
            select_record_entry_and_value(effect_sprite, ((u8 *)dungeon_resource_buffer) + ((s32 *)D_80175904)[asset_index], 0);
            entity->flags |= 0x80;
            ((R06_80175270_S_80175270_0 *)action)->timer.s = 0;
            ((R06_80175270_S_80175270_0 *)action)->phase++;
            create_sixteen_segment_ring(action, position, entity);
            return;
        }

    case 5:
        {
            work = ((void **)flame_transition_object)[0];
            work = work->unk_0C.p;
            if (work->unk_14 & 0xE000) {
                ((R06_80175270_S_80175270_0 *)action)->timer.s = 0x10;
                ((R06_80175270_S_80175270_0 *)action)->phase++;
                decrement_monster_entry_count(actor->species, 3);
                update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y, 0x300);
                unlink_entity_node(actor);
                work = (u8 *)actor - 0x20;
                work->unk_10.i |= 0x80000000;
            }
        }

    case 6:
        {
            if (((R06_80175270_S_80175270_0 *)action)->phase != 6) {
                return;
            }
            if (create_status_linked_render_effect(position, ((s32 *)D_80175928)[0], (s16)((s16 *)D_8017591C)[0], ((u8 *)staged_spawn_count)) == 0) {
                return;
            }
            ((R06_80175270_S_80175270_0 *)action)->timer.s = 0x10;
            ((R06_80175270_S_80175270_0 *)action)->phase++;
            decrement_monster_entry_count(actor->species, 3);
            update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y, 0x300);
            unlink_entity_node(actor);
            work = (u8 *)actor - 0x20;
            work->unk_10.i |= 0x80000000;
            return;
        }

    case 7:
        {
            void *child;
            SpriteFrameState *child_obj;
            s16 heading;

            if ((((R06_80175270_S_80175270_1 *)actor)->unk_60 = advance_staged_entity_load(entity, actor)) == 0) {
                return;
            }
            ((R06_80175270_S_80175270_0 *)action)->timer.s = 0x10;
            ((R06_80175270_S_80175270_0 *)action)->phase++;
            ((R06_80175270_S_80175270_9 *)(((R06_80175270_S_80175270_1 *)actor)->unk_60))->unk_2A = ((R06_80175270_S_80175270_1 *)actor)->unk_2A.u;
            child = ((R06_80175270_S_80175270_1 *)actor)->unk_60;
            child_obj = ((R06_80175270_S_80175270_6_pre *)child)[-1].unk_00;
            heading = (g_game_work.view.camera_rotation.parts.viewAngle + ((R06_80175270_S_80175270_6 *)child)->unk_2A + 0x100) >> 9;
            heading &= 7;
            select_indirect_table_entry(child_obj, ((R06_80175270_S_80175270_10 *)(*(u8 **)&child_obj->frameTable + heading))->unk_00, child_obj->unk_04);
            child_obj->flags &= 0xFFFE;
        }

    case 8:
        {

            ((R06_80175270_S_80175270_0 *)action)->timer.u--;
            if (((R06_80175270_S_80175270_0 *)action)->timer.s > 0) {
                return;
            }
            ((R06_80175270_S_80175270_9 *)(((R06_80175270_S_80175270_1 *)actor)->unk_60))->unk_2A = ((R06_80175270_S_80175270_1 *)actor)->unk_8A;
            ((R06_80175270_S_80175270_0_pre *)action)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((R06_80175270_S_80175270_1 *)actor)->unk_6D = 0;
        }
        }
}

/*
 * Runs resolve_actor_floor_trap_once and installs initialize_destination_state when it returns
 * positive.
 */
void finish_actor_floor_trap_then_initialize_destination(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->unk_8C.handler = initialize_destination_state;
    }
}

/*
 * Runs propagate_actor_action_flag and installs initialize_destination_state when it returns
 * positive.
 */
void finish_actor_action_flag_propagation_then_initialize_destination(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->unk_8C.handler = initialize_destination_state;
    }
}
