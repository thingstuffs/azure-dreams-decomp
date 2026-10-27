/* Moves the spell to its target, creates the replacement actor and retires its visual. */
#include "dungeon/effect/transform.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#include "engine/scene.h"
extern u16 D_8006CCD8[8],D_8006CCE8[8];
extern u32 D_800814A0;
extern SpriteFrameState D_80082E80;
extern s32 D_8008346C;
extern s32 D_800DEF08;
s32 abs(s32);
s32 get_surface_height_at_record(ObjectPosition *);
s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
s32 check_left_tile_and_center_height(u16,u16,s16);
s32 increment_bounded_counter(void);
void play_sound_if_enabled(s32);
s32 generate_random_value(void);
void *create_actor_graphics_at_tile();
void init_monster_from_stats(void *,s32);

void update_transform_spell(TransformSpellState *spell, ObjectPosition *motion, SpriteFrameState *sprite) {
    union { struct { ObjectPosition target; TransformHalf distances[3]; } fields; TransformHalf halves[15]; } travel;
    TransformHalf *axis;
    ObjectPosition *target;
    union { s32 word; u16 halves[2]; } result_flags;
    ActorRecord *source_actor;
    ObjectNodeHeader *visual;
    SpriteFrameState *attachment_sprite;
    s16 terrain_height;
    s16 height_result;
    s16 duration_steps;
    s32 x_distance;
    s32 duration_fixed;
    s32 direction_byte_offset;
    s32 axis_count;
    s32 y_distance;
    s32 z_distance;
    s32 hit_points;
    s32 random_value;
    s32 tile_center_x;
    s32 tile_center_y;
    u8 stored_hp;
    u16 source_height;
    u8 power;
    ObjectNodeHeader *source_node;
    SpriteFrameState *source_sprite;
    ActorRecord *created_actor;
    ObjectPosition *source_position;

    source_actor = spell->source;
    spell->ticks.u++;
    switch (spell->phase) {
    case 0:
        source_sprite = ((ObjectNodeHeader *)source_actor - 1)->sprite;
        direction_byte_offset = ((u16)primary_actor_record->facing >> 8) & 0xE;
        source_actor->facing = get_rounded_facing_and_rounding_flag(source_sprite->tile_x, source_sprite->tile_y, D_80082E80.tile_x + D_8006CCD8[direction_byte_offset / 2], D_80082E80.tile_y + D_8006CCE8[direction_byte_offset / 2], &result_flags.word);
        spell->ticks.s = 0;
        spell->phase++;
        spell->direction.s = (source_actor->facing >> 9) & 7;
        spell->kind = 0;
        spell->visual = 0;
        sprite->color.word = 0x808080;
        /* fallthrough */
    case 1:
        source_node = (ObjectNodeHeader *)source_actor - 1;
        attachment_sprite = source_node->sprite;
        if ((resolve_record_orientation_or_fallback(attachment_sprite->source, attachment_sprite, &travel.fields.distances[0].u, 0) != 0) || (source_node->sprite->flags & 0x8000)) {
            source_position = source_node->position;
            motion->x.w.i = source_position->x.w.i;
            motion->y.w.i = source_position->y.w.i;
            source_height = source_position->z.w.i;
            motion->z.w.i = source_height;
            if (!(source_node->sprite->flags & 0x8000)) {
                motion->x.w.i = motion->x.w.i + travel.fields.distances[0].u;
                motion->y.w.i = motion->y.w.i + travel.fields.distances[1].u;
                motion->z.w.i = (u16)motion->z.w.i + travel.fields.distances[2].u;
            } else {
                motion->z.w.i = source_height - 0x40;
            }
            if (*spell->request_flags & 0x80) {
                target = &travel.fields.target;
                if ((source_node->flags | 0x2000) != 0) {
                    spell->tile_x = D_80082E80.tile_x + D_8006CCD8[((u16)primary_actor_record->facing >> 9) & 7];
                    spell->tile_y = D_80082E80.tile_y + D_8006CCE8[((u16)primary_actor_record->facing >> 9) & 7];
                } else {
                    spell->tile_x = D_80082E80.tile_x + D_8006CCD8[spell->direction.s];
                    spell->tile_y = D_80082E80.tile_y + D_8006CCE8[spell->direction.s];
                }
                tile_center_x = spell->tile_x;
                tile_center_x = (tile_center_x << 6) + 0x20;
                target->x.w.i = tile_center_x;
                tile_center_y = spell->tile_y;
                tile_center_y = (tile_center_y << 6) + 0x20;
                target->y.w.i = tile_center_y;
                target->z.w.i = primary_actor_record->ground_height - 0x20;
                height_result = get_surface_height_at_record(target);
                target->z.w.i = height_result;
                spell->height = height_result;
                get_offset_map_cell_value_and_flags(spell->tile_x - 1, spell->tile_y, 0, &result_flags.halves[1]);
                if (result_flags.halves[1] & 0x3300) {
                    target->z.v = primary_actor_record->ground_height << 0x10;
                    spell->phase = 5;
                } else {
                    terrain_height = target->z.w.i;
                    if (terrain_height >= 0x201) {
                        target->z.v = primary_actor_record->ground_height << 0x10;
                        spell->phase = 5;
                    } else if ((check_left_tile_and_center_height((u16)target->x.w.i, (u16)target->y.w.i, terrain_height) << 0x10) != 0) {
                        target->z.v = primary_actor_record->ground_height << 0x10;
                        spell->phase = 5;
                    } else if ((increment_bounded_counter() << 0x10) == 0) {
                        target->z.v = primary_actor_record->ground_height << 0x10;
                        spell->phase = 5;
                    } else {
                        if ((source_node->flags | 0x2000) != 0) {
                            spell->kind = 1;
                        } else {
                            spell->kind = 2;
                        }
                        spell->phase++;
                    }
                }
                axis_count = 1;
                axis = &travel.halves[1];
                x_distance = abs((s16)(u16)target->x.w.i - motion->x.w.i);
                travel.fields.distances[0].u = x_distance;
                y_distance = (s16)(u16)target->y.w.i - motion->y.w.i;
                y_distance = abs(y_distance);
                travel.fields.distances[1].u = y_distance;
                z_distance = target->z.w.i - motion->z.w.i;
                z_distance = abs(z_distance);
                travel.fields.distances[2].u = z_distance;
                spell->duration.s = x_distance;
                do {
                    if (axis[12].s > spell->duration.s) {
                        spell->duration.u = axis[12].u;
                    }
                    axis_count++;
                    axis++;
                } while (axis_count < 3);
                duration_fixed = spell->duration.u << 0x10;
                duration_steps = (duration_fixed >> 0x14) + (duration_fixed >> 0x15);
                spell->duration.s = duration_steps;
                if (duration_steps == 0) {
                    spell->duration.s = 1;
                }
                motion->velocity_x = (target->x.v - motion->x.v) / spell->duration.s;
                motion->velocity_y = (target->y.v - motion->y.v) / spell->duration.s;
                motion->velocity_z = (target->z.v - motion->z.v) / spell->duration.s;
                allocate_display_object_and_copy_state(spell, motion, spell->duration.s);
                allocate_display_object_and_copy_state(spell, motion, spell->duration.s);
                allocate_display_object_and_copy_state(spell, motion, spell->duration.s);
                spell->ticks.s = 0;
            }
        }
        break;
    case 2:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        if (spell->ticks.s >= spell->duration.s) {
            play_sound_if_enabled(0x300);
            spell->visual = create_randomized_transform_effect(spell, motion);
            spell->ticks.s = 0;
            spell->phase++;
        }
        break;
    case 3:
        if (spell->ticks.s >= 0x31) {
            if (spell->kind != 0) {
                init_monster_from_stats(created_actor = create_actor_graphics_at_tile(spell->kind, spell->tile_x, spell->tile_y, spell->height), 0x35);
                random_value = generate_random_value();
                power = spell->power;
                hit_points = (power >> 1) + (power * 2) + (random_value & 3) + 0x10;
                stored_hp = hit_points;
                if (hit_points >= 0x100) {
                    stored_hp = 255;
                }
                created_actor->hp = stored_hp;
                created_actor->max_hp = stored_hp;
                select_record_entry_and_value(((ObjectNodeHeader *)created_actor - 1)->sprite, &D_800DEF08, spell->visual->sprite->unk_04);
            }
            visual = spell->visual;
            if (visual != 0) {
                visual->flags |= 0x8000;
                D_800814A0 |= 0x8000;
            }
            spell->ticks.s = 0;
            spell->phase++;
        }
        break;
    case 4:
        if (spell->active == 0) {
            D_8008346C = 0;
            *((u16 *)spell - 1) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;
    case 5:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        if (spell->ticks.s >= spell->duration.s) {
            spell->phase = 4;
            spell->ticks.s = 0;
        }
        break;
    }
    spell->active = 0;
}
