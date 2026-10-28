#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
/* Entity sprite initialization (G00339). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800ACB90. */
#include "dungeon/effect/entity_sprite_initialization_g00339.h"
#include "dungeon/effect.h"
#include "shared/sprite_frame_state.h"

/* Initialize the entity sprite position, scale, color, and active state. */
void initialize_entity_sprite_effect(void *entity, EntityRec *position, SpriteFrameState *sprite, s16 unused)
{
    S_800B22F0_1 *state = (S_800B22F0_1 *)((u8 *)entity + 0x20);

    sprite->room_index =
        find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);

    state->unk_88 =
        sample_terrain_surface_height(((u16)position->x.w.i), ((u16)position->y.w.i),
                      (s16)(((u16)position->z.w.i) - 0x20));

    sprite->scale_y = 0x1000;
    sprite->scale_x = 0x1000;
    sprite->color.word = 0x2C808080;
    sprite->flags |= 0x8000;
    clear_entry_flag_and_link_owner(entity);

    cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
                  (state->unk_1C & 0x2000) ? 0x300 : 0x3000);

    state->unk_AD = 1;
    state->unk_71 = 0;
    state->unk_1C |= 0x40000000;
    create_tracked_effect(entity, 0, (u8 *)sprite + 0x2C, (u8 *)entity + 0x4A);
}

/* Create an object and initialize its components and flags from the mode and supplied values. */
void *create_mode_configured_object(s16 mode, s32 part_b_byte_24, s32 part_b_byte_25, s32 part_a_value,
                    s32 part_b_value)
{
    s16 saved_byte_24;
    long value_or_part_b;
    s16 part_a_s16;
    long byte_or_work;
    s16 byte_25;
    s32 kind;
    s16 kind_test;
    s32 flags_14;
    s32 flags_1c;
    void *part_a;
    S_800B23F8_0 *obj;
    S_800B23F8_1 *work;
    s16 init_mode;

    work = 0;
    saved_byte_24 = part_b_byte_24;
    part_a_s16 = part_a_value;
    byte_25 = part_b_byte_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    init_mode = mode;
    if (obj != 0) {
        work = (S_800B23F8_1 *)((u8 *)obj + 0x20);
        obj->unk_10 = &D_800B274C;
        work->unk_13 = 0x1E;
        register_node(obj, project_sprite_chain);

        part_a = obj->unk_08;
        ((S_800B23F8_2 *)part_a)->unk_0A = part_a_s16;
        value_or_part_b = (long)obj->unk_0C;
        kind_test = 1;
        ((SpriteFrameState *)value_or_part_b)->tile_y = byte_25;
        byte_or_work = (long)work;
        ((SpriteFrameState *)value_or_part_b)->tile_x = saved_byte_24;

        kind = mode & 3;
        if (kind == kind_test) {
            flags_14 = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags_1c = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else {
            kind_test = kind < 2;
            if (kind_test) {
                goto post_kind;
            }
            flags_14 = work->unk_14 | ACTOR_CLASS_ENABLED;
            flags_1c = work->unk_1C | ACTOR_PLAYER_SIDE;
        }
        work->unk_14 = flags_14;
        work->unk_1C = flags_1c;

post_kind:
        initialize_entity_sprite_effect(obj, part_a, (void *)value_or_part_b, init_mode);
        ((S_800B23F8_4 *)((void *)byte_or_work))->unk_9A = 0xFF;
        ((S_800B23F8_4 *)((void *)byte_or_work))->unk_9C = -1;
        (*(s32 * *)((u8 *)((void *)byte_or_work) + 0x8C)) = &slow_target_action_callback;
        ((SpriteFrameState *)value_or_part_b)->source = part_b_value;
    }
    return work;
}
