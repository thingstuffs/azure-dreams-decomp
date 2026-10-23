#include "shared/audio_commands.h"
/* Moving target effects, tint changes, radial sprite emission, and shaded point rendering. */
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "shared/entity.h"
#include "shared/object_node.h"
void (*const dungeon_18a0800_entry)(TrackingEffect *, ObjectPosition *, SpriteFrameState *) = follow_brighten;
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

extern int abs(int);

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern u8 D_800257D0[];
extern u8 D_800257E8[];

extern void draw_textured_ellipse(void *, s32 *, s32, s32);
extern s16 set_item_w0(u8, u8, u8, u8);
extern s32 check_left_tile_and_center_height(s32, s32, s16);

/* Updates a moving effect through initialization, target tracking, fading, and cleanup. */
void follow_brighten(TrackingEffect *self, ObjectPosition *motion, SpriteFrameState *part)
{
    ActorRecord *owner;
    ObjectNodeHeader *owner_base;
    ObjectPosition *owner_motion;
    void *target;
    s32 state;
    s16 spawn_height;
    s32 direction_step;
    long state_step;
    s32 height_result;
    u32 height_offset;
    u32 target_height;
    s32 velocity;
    s32 position;
    s32 over_limit;
    s32 z_pos;
    s32 z_delta;
    s32 coord;
    ActorRecord *spawn_target;
    s32 cell_center_x;
    u32 red;
    u32 green;
    u32 blue;
    u32 color;
    u32 texture_flags;
    u32 texture_size;
    s16 attach_offset[3];
    s32 texture_init[2];

    owner = self->owner;
    state = self->state.s;
    owner_base = (ObjectNodeHeader *)((u8 *)owner - 0x20);
    owner_motion = owner_base->position;
    switch (state) {
    case 0:
        color = 0x00808080;
        texture_flags = 0x01000340;
        texture_size = 0x00200020;
        part->color.word = color;
        part->scale_y = 0x800;
        part->scale_x = 0x800;
        part->source = D_800257E8;
        self->direction.u = ((u16)owner->facing >> 9) & 7;
        texture_init[0] = texture_flags;
        texture_init[1] = texture_size;
        draw_textured_ellipse(D_800257D0, texture_init, 1, 0);
        self->state.u++;

    case 1:
        if (get_sprite_attachment_vector(owner_base->sprite->source,
                          owner_base->sprite, attach_offset, 0) == 0) {
            if ((owner_base->sprite->flags & 0x8000) == 0) {
                break;
            }
        }

        motion->x.w.i = (u16)owner_motion->x.w.i;
        motion->y.w.i = (u16)owner_motion->y.w.i;
        if (owner_base->sprite->flags & 0x8000) {
            motion->z.w.i = (u16)owner_motion->z.w.i - 0x40;
        } else {
            motion->z.w.i = (u16)owner_motion->z.w.i + attach_offset[2];
        }

        if ((self->animation->flags & 0x80) == 0) {
            break;
        }
        if ((self->flags & 4) == 0) {
            register_node((u8 *)self - 0x20, (s32)project_sprite_chain);
            part->tpage_abr = 0x20;
            part->color.c.b = 0x80;
            part->color.c.g = 0x80;
            part->color.c.r = 0x80;
            part->flags |= 0xC;
            self->flags |= 4;
        }

        if (owner->target != 0) {
            void *source_data;
            u8 target_type;
            u8 *height_table;
            u8 tile_coord;
            source_data = F(owner->target, void *, -0x18);
            self->target_x = F(source_data, u16, 2);
            self->target_y = F(source_data, u16, 6);
            height_table = entity_height_offsets;
            target_type = F(owner->target, u8, 0x13);
            height_offset = height_table[target_type];
            height_offset += 0x20;
            target_height = F(source_data, u16, 0xA);
            self->target_z.u = target_height - height_offset;

            {
                s16 direction;
                direction = self->direction.s;
                source_data = F(owner, void *, -0x14);
                tile_coord = F(source_data, u8, 0x24) + dir_step_x[direction];
                self->current_tile.tile.x.u = tile_coord;
                self->previous_tile.tile.x.u = tile_coord;
            }
            {
                s16 direction;
                direction = self->direction.s;
                tile_coord = F(source_data, u8, 0x25) + dir_step_y[direction];
                self->current_tile.tile.y.u = tile_coord;
                self->previous_tile.tile.y.u = tile_coord;
            }
            {
                s32 owner_coord;
                s32 tile_distance;
                owner_coord = owner->target_tile_x;
                z_pos = F(source_data, u8, 0x24);
                if (owner_coord == z_pos) {
                    owner_coord = owner->target_tile_y;
                    z_pos = F(source_data, u8, 0x25);
                    tile_distance = owner_coord - z_pos;
                } else {
                    tile_distance = owner_coord - z_pos;
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                self->tiles_left = tile_distance + 1;
            }
        } else {
            self->tiles_left = 8;
            self->target_x = (u16)motion->x.w.i;
            self->target_y = (u16)motion->y.w.i;
            self->target_z.u = (u16)owner->ground_height - 0x50;
        }
        direction_step = dir_step_x[self->direction.s];
        F(motion, s16, 0x0E) = direction_step << 3;
        direction_step = dir_step_y[self->direction.s];
        F(motion, s16, 0x12) = direction_step << 3;
        state_step = self->state.u;
        self->unk_1C = 0;
        self->state.u = state_step + 1;
        break;

    case 2:
    {
        s32 next_velocity;
        velocity = motion->velocity_x;
        position = motion->x.v;
        position += velocity;
        motion->x.v = position;
        next_velocity = motion->velocity_x;
        position = next_velocity >> 4;
        next_velocity += position;
        velocity = abs(next_velocity);
        position = 0x200000;
        over_limit = velocity > position;
        motion->velocity_x = next_velocity;
        if (over_limit) {
            position = -0x200000;
            if (next_velocity > 0) {
                position = 0x200000;
            }
            motion->velocity_x = position;
        }
    }
        {
            s32 next_velocity;
            velocity = motion->velocity_y;
            position = motion->y.v;
            position += velocity;
            motion->y.v = position;
            next_velocity = motion->velocity_y;
            position = next_velocity >> 4;
            next_velocity += position;
            velocity = abs(next_velocity);
            position = 0x200000;
            over_limit = velocity > position;
            motion->velocity_y = next_velocity;
            if (over_limit) {
                position = -0x200000;
                if (next_velocity > 0) {
                    position = 0x200000;
                }
                motion->velocity_y = position;
            }
        }

        z_delta = self->target_z.s << 16;
        z_pos = motion->z.v;
        z_delta -= z_pos;
        z_delta >>= 3;
        z_pos += z_delta;
        motion->z.v = z_pos;
        create_effect_from_endpoints(motion, part);

        coord = motion->x.w.i;
        if (coord < 0) {
            coord += 0x3F;
        }
        self->current_tile.tile.x.s = coord >> 6;
        coord = motion->y.w.i;
        if (coord < 0) {
            coord += 0x3F;
        }
        self->current_tile.tile.y.s = coord >> 6;
        if (self->previous_tile.packed == self->current_tile.packed) {
            break;
        }

        if (owner->target != 0) {
            if (self->sound_played == 0) {
                if ((s16)set_item_w0(self->current_tile.tile.x.u, self->current_tile.tile.y.u,
                                     (u8)owner->target_tile_x, (u8)owner->target_tile_y) < 5) {
                    self->sound_played = 1;
                    play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                }
            }
        }
        if (owner->target != 0 &&
            F(owner, s16, 0x72) == self->current_tile.packed) {
            motion->x.w.i = self->target_x;
            motion->y.w.i = self->target_y;
            motion->z.w.i = self->target_z.u;
            self->state.u++;
            break;
        }

        coord = self->current_tile.tile.x.u;
        z_pos = self->tiles_left;
        z_pos -= 1;
        target = self->current_tile.tile.y.u;
        self->tiles_left = z_pos;
        z_pos <<= 16;
        self->previous_tile.tile.x.u = coord;
        self->previous_tile.tile.y.u = target;
        if (z_pos != 0) {
            cell_center_x = (((s32)self->current_tile.tile.x.s << 6) + 0x20) & 0xFFE0;
            height_result = check_left_tile_and_center_height(
                cell_center_x,
                (((s32)self->current_tile.tile.y.s << 6) + 0x20) & 0xFFE0,
                motion->z.w.i);
            if ((height_result << 16) == 0) {
                break;
            }
        }
        self->state.u = 0x10;
        break;

    case 3:
        spawn_target = owner->target;
        spawn_height = spawn_target->ground_height;
        self->child = create_initialized_effect_object((s32)self, motion, spawn_height, (s32)spawn_target);
        if (self->child == 0) {
            break;
        }
        part->flags |= 0x80;
        state_step = self->state.u;
        state_step++;
        self->state.u = state_step;

    case 4:
        state_step = (long)self->child;
        if ((F((void *)state_step, u16, 0x1E) & 0x8000) == 0) {
            break;
        }
        target = owner->target;
        if (target != 0) {
            apply_indexed_effect_condition(target, self->variant, owner);
        }
        self->state.u = 0x11;
        break;

    case 16:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        z_delta = self->target_z.s << 16;
        z_pos = motion->z.v;
        z_delta -= z_pos;
        z_delta >>= 3;
        z_pos += z_delta;
        motion->z.v = z_pos;
        red = part->color.c.r;
        green = part->color.c.g;
        blue = part->color.c.b;
        part->color.c.r = red - (red >> 1);
        part->color.c.g = green - (green >> 1);
        part->color.c.b = blue - (blue >> 1);
        create_effect_from_endpoints(motion, part);
        if (part->color.c.r >= 2) {
            break;
        }
        self->state.u++;
        break;

    case 17:
        if (*(s16 *)tint_effect_update_count == 0) {
            g_dungeon_status.active_actor = 0;
            F(self, u16, -2) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    tint_effect_update_count[0] = 0;
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_81880F28_0 {
    void * unk_00;
    u8 pad_04[0x6];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x10];
    u16 unk_1C;
} S_81880F28_0;   /* arg0 in tint_effect_and_advance_motion */

typedef struct S_81880F28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81880F28_1;   /* object in tint_effect_and_advance_motion */


typedef struct S_81880F28_3_pre {
    EffectColor * unk_00;
    u8 pad_04[0x10];
} S_81880F28_3_pre;   /* the 0x14 bytes before ((S_81880F28_0 *)arg0)->unk_00 in tint_effect_and_advance_motion, addressed as ((S_81880F28_0 *)arg0)->unk_00[-1] */

/* Tint the object red, restore its color, and advance its motion. */
void tint_effect_and_advance_motion(void *effect, void *motion_data) {
    ObjectPosition *motion = motion_data;
    void *object;
    EffectColor *color;
    s16 state;
    s32 channel_value;

    tint_effect_update_count[0]++;
    state = ((S_81880F28_0 *)effect)->unk_0A.s;

    switch (state) {
    case 0:
        object = ((S_81880F28_0 *)effect)->unk_00;
        ((S_81880F28_1 *)object)->unk_1C |= 0x10000000;
        ((S_81880F28_0 *)effect)->unk_0A.u++;

    case 1:
        color = ((S_81880F28_3_pre *)(((S_81880F28_0 *)effect)->unk_00))[-1].unk_00;

        channel_value = color->red + 1;
        color->red = channel_value;
        if ((u32)(channel_value & 0xFF) >= 0xC1U) {
            color->red = 0xC0;
        }

        channel_value = color->green - 1;
        color->green = channel_value;
        if ((u32)(channel_value & 0xFF) < 0x40U) {
            color->green = 0x40;
        }

        channel_value = color->blue - 1;
        color->blue = channel_value;
        if ((u32)(channel_value & 0xFF) < 0x40U) {
            color->blue = 0x40;
        }

        if (tint_effect_phase_counts[0] < 14) {
            ((S_81880F28_0 *)effect)->unk_0A.u++;
        }
        break;
    case 2:
        color = ((S_81880F28_3_pre *)(((S_81880F28_0 *)effect)->unk_00))[-1].unk_00;

        channel_value = color->red - 4;
        color->red = channel_value;
        if ((u32)(channel_value & 0xFF) < 0x80U) {
            color->red = 0x80;
        }

        channel_value = color->green + 4;
        color->green = channel_value;
        if ((u32)(channel_value & 0xFF) >= 0x81U) {
            color->green = 0x80;
        }

        channel_value = color->blue + 4;
        color->blue = channel_value;
        if ((u32)(channel_value & 0xFF) >= 0x81U) {
            color->blue = 0x80;
        }

        if (tint_effect_phase_counts[0] == 0) {
            ((S_81880F28_1 *)((S_81880F28_0 *)effect)->unk_00)->unk_1C &= ~0x10000000;
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

    motion->z.v += motion->velocity_z;
    motion->velocity_z += -0x80000;
    create_radial_effect_node(motion);
    ((S_81880F28_0 *)effect)->unk_1C++;
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80024968_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void (*unk_10)(void *, void *);
    u8 pad_14[0xC];
    s32 unk_20;
} S_80024968_0;

   /* arg1 in create_initialized_effect_object */

/* Creates an object, copies three values into its data, and initializes it. */
void *create_initialized_effect_object(s32 resource_id, MovingPosition *source_values, s16 setup_value, s32 object_value) {
    MovingPosition *target_values;
    S_80024968_0 *object;

    object = allocate_list_node(2, (ObjectNodeHeader **)(resource_id - 0x20));
    if (object != NULL) {
        target_values = object->unk_08;
        object->unk_10 = tint_effect_and_advance_motion;
        target_values->x = (u16) source_values->x;
        target_values->y = (u16) source_values->y;
        target_values->z = (u16) source_values->z;
        object->unk_20 = object_value;
        spawn_ring_effects(target_values, setup_value);
    }
    return object;
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u16 value;
    u8 pad[10];
} Global16;

/* Advances counters and conditionally processes the target, propagating its status flag. */
void advance_sprite_on_alternate_ticks_until_complete(void *record, s32 unused, void *target)
{
    u16 flags = *(u16 *)((u8 *)record + 0x1C);

    tint_effect_update_count[0] = tint_effect_update_count[0] + 1;
    if (flags & 1) {
        advance_sprite_animation_and_textures(target);
        if (*(u16 *)((u8 *)target + 0x14) & 0x4000) {
            *(u16 *)((u8 *)record - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    *(u16 *)((u8 *)record + 0x1C) += 1;
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

   /* coords in create_radial_effect_node */

   /* arg0 in create_radial_effect_node */

extern u8 spark_sprite_entries[];

/* Creates a visual node at the supplied coordinates with 16 evenly spaced radial effects. */
void *create_radial_effect_node(MovingPosition *source_coords)
{
    s16 angle;
    s32 effect_index;
    SpriteFrameState *part;
    MovingPosition *coords;
    ObjectNodeHeader *node;

    node = allocate_flagged_object_node(0x202);
    if (node != 0) {
        node->update_callback = advance_sprite_on_alternate_ticks_until_complete;
        register_node(node, (s32)project_sprite_chain);
        coords = node->position;
        coords->x = source_coords->x;
        coords->y = source_coords->y;
        coords->z = source_coords->z;
        part = node->sprite;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->color.word = 0x808080;
        select_record_entry_and_value(part, spark_sprite_entries, 0);
        part->tpage_abr = 0x20;
        part->flags |= 0xC;
        effect_index = 0;
        angle = (s16)rand();
        do {
            allocate_jittered_effect_node(coords, angle, 0x10, 1);
            effect_index++;
            angle += 0x100;
        } while (effect_index < 0x10);
    }
    return node;
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80024B98_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024B98_0;   /* arg0 in func_80024B98 */


/* Advance an effect through its delay, motion, brightness changes, and periodic emissions. */
void advance_rising_fading_emitter(void *effect, ObjectPosition *motion, SpriteFrameState *primitive) {
    s16 state;
    s32 wave_value;
    u16 frame_count;

    tint_effect_update_count[0]++;
    state = ((S_80024B98_0 *)effect)->unk_0A.s;
    if (state != 2) {
        if (state == 0) {
            frame_count = ((S_80024B98_0 *)effect)->unk_1E - 1;
            ((S_80024B98_0 *)effect)->unk_1E = frame_count;
            if ((s16)frame_count > 0) {
                return;
            }
            ((S_80024B98_0 *)effect)->unk_0A.u++;
        }
        frame_count = ((S_80024B98_0 *)effect)->unk_1C + 1;
        ((S_80024B98_0 *)effect)->unk_1C = frame_count;
        if ((s16)frame_count >= 0x41) {
            ((S_80024B98_0 *)effect)->unk_0A.u = 2;
        }
    } else {
        primitive->color.word += 0xFFFBFBFC;
        if (primitive->color.c.r < 4) {
            tint_effect_phase_counts[0]--;
            (*(u16 *)((u8 *)effect + (-2))) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
    }
    motion->z.v += motion->velocity_z;
    motion->velocity_z += 0x10000;
    if (motion->z.w.i > ((S_80024B98_0 *)effect)->unk_14)
        motion->z.w.i = ((S_80024B98_0 *)effect)->unk_14;
    wave_value = rsin((s16)((S_80024B98_0 *)effect)->unk_1C << 6);
    primitive->color.word += 0x20202;
    primitive->scale_y -= wave_value >> 5;
    if (primitive->color.c.r >= 0x41)
        primitive->color.word = 0x404040;
    advance_sprite_animation_and_textures(primitive);
    if (!(((S_80024B98_0 *)effect)->unk_1C & 0x1F))
        create_effect_render_object(motion, ((S_80024B98_0 *)effect)->unk_14, ((S_80024B98_0 *)effect)->unk_24);
    if (!(((S_80024B98_0 *)effect)->unk_1C & 3))
        allocate_jittered_effect_node(motion, (((S_80024B98_0 *)effect)->unk_24 << 24) >> 16, 0x10, 0);
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

   /* saved_arg0 in spawn_ring_effects */

typedef struct S_80024D90_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    s16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024D90_4;

/* Spawns sixteen effects in a ring around the source position. */
void *spawn_ring_effects(void *source_pos, s16 effect_param) {
    register MovingPosition *origin = source_pos;
    register s16 state_param = effect_param;
    register s32 effect_index = 0;
    register s32 *callback = advance_rising_fading_emitter;
    register u16 *counter_page = (u16 *)0x80020000;
    register s32 component_offset = -0x400;
    register ObjectNodeHeader *effect;
    ObjectPosition *position;
    register s32 angle;
    s32 value;
    register SpriteFrameState *component;

    do {
        effect = allocate_flagged_object_node(0x202);
        if (effect != NULL) {
            effect->update_callback = callback;
            register_node(effect, (s32)draw_linked_sprites_clipped);
            angle = effect_index << 8;
            position = effect->position;
            value = origin->x + (rcos(angle) >> 7);
            position->x.w.i = value;
            value = origin->y + (rsin(angle) >> 7);
            position->y.w.i = value;
            position->z.w.i =
                (s16)(origin->z - 0x100);
            component = effect->sprite;
            component->scale_x = 0x800;
            component->scale_y = 0x1CCC;
            component->color.word = 0;
            select_record_entry_and_value(component, D_80025854, 0);
            value = counter_page[0x57CC / 2];
            source_pos = (u8 *)effect + 0x20;
            component->angle_x = 0x400;
            component->angle_y = component_offset;
            ((S_80024D90_4 *)source_pos)->unk_24 = effect_index;
            ((S_80024D90_4 *)source_pos)->unk_14 = state_param;
            ((S_80024D90_4 *)source_pos)->unk_1E = (s16)(effect_index * 2);
            value += 1;
            counter_page[0x57CC / 2] = value;
        }
        effect_index += 1;
        component_offset += 0x100;
    } while (effect_index < 0x10);
    return effect;
}

#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad[0x24];
    s16 field24;
} Func818816E0Arg0;

typedef struct {
    s32 field0;
    s32 field4;
} Func818816E0Arg1;

typedef struct {
    u8 pad0[0x0C];
    u8 field0C;
    u8 field0D;
    u8 field0E;
    u8 pad1[0x0D];
    u16 field1C;
    u16 field1E;
} Func818816E0Arg2;

/* Moves and fades an effect, marking it inactive when its brightness falls below the cutoff. */
void move_and_fade_effect(void *effect_data, void *position_data, void *visual_data) {
    Func818816E0Arg0 *effect;
    Func818816E0Arg1 *position;
    register Func818816E0Arg2 *visual;
    u16 decay_value;
    u8 brightness;
    s32 angle;

    visual = (Func818816E0Arg2 *)visual_data;
    effect = (Func818816E0Arg0 *)effect_data;
    position = (Func818816E0Arg1 *)position_data;
    angle = effect->field24 << 8;
    tint_effect_update_count[0] = tint_effect_update_count[0] + 1;
    position->field0 = position->field0 + (rcos(angle) * 8);
    position->field4 = position->field4 + (rsin(effect->field24 << 8) * 8);
    brightness = visual->field0E - 2;
    visual->field0E = brightness;
    visual->field0D = brightness;
    visual->field0C = brightness;
    if ((u32)(brightness & 0xFF) < 0x20U) {
        tint_effect_phase_counts[0] = (s16)((u16)tint_effect_phase_counts[0] - 1);
        ((u16 *)effect_data)[-1] = (u16)(((u16 *)effect_data)[-1] | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
    decay_value = visual->field1E;
    visual->field1E = (u16)(decay_value - (decay_value >> 7));
    visual->field1C = (u16)(visual->field1C + 8);
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

   /* arg0 in create_effect_render_object */

typedef struct S_80024FD8_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    s16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024FD8_4;

/* Creates a render object at the supplied position and initializes its effect state. */
void *create_effect_render_object(MovingPosition *source_pos, s16 effect_param, s16 size)
{
    s32 signed_size;
    s32 render_code;
    u16 object_count;
    SpriteFrameState *render_state;
    ObjectNodeHeader *object;
    MovingPosition *position;
    S_80024FD8_4 *effect_state;

    object = allocate_flagged_object_node(0x202);
    if (object != 0) {
        object->update_callback = move_and_fade_effect;
        register_node(object, (s32)draw_linked_sprites_clipped);
        position = object->position;
        position->x = source_pos->x;
        position->y = source_pos->y;
        position->z = source_pos->z;
        render_state = object->sprite;
        render_state->color.word = 0x808080;
        render_state->scale_x = 0x400;
        render_state->scale_y = 0x1CCC;
        select_record_entry_and_value(render_state, D_80025854, 0);
        signed_size = (s16)size;
        render_state->angle_y = (signed_size << 8) - 0x400;
        render_code = 0x60;
        effect_state = (u8 *)object + 0x20;
        render_state->tpage_abr = render_code;
        object_count = (*(u16 *)tint_effect_phase_counts);
        render_state->angle_x = 0x400;
        effect_state->unk_24 = size;
        effect_state->unk_14 = effect_param;
        effect_state->unk_1E = signed_size * 2;
        (*(u16 *)tint_effect_phase_counts) = object_count + 1;
    }
    return object;
}

#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800250E8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800250E8_0;   /* arg1 in update_spark_effect */

typedef struct S_800250E8_1_pre {
    u16 unk_00;
} S_800250E8_1_pre;   /* the 0x2 bytes before arg0 in update_spark_effect, addressed as arg0[-1] */

typedef struct S_800250E8_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x8];
    s16 unk_26;
} S_800250E8_1;   /* arg0 in update_spark_effect */

typedef struct S_800250E8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800250E8_2;   /* tail_arg in update_spark_effect */

extern s32 rand(void);

/* Updates effect motion and marks it inactive when its lifetime or owner expires. */
void update_spark_effect(void *effect, S_800250E8_0 *motion, void *owner)
{
    void *owner_state;
    s32 life_left;
    s32 y_step;
    s32 z_velocity;
    s32 z_position;
    s32 z_velocity_copy;
    s32 y_motion;
    s32 x_direction;
    s32 y_direction;
    s32 x;
    s32 y;
    s16 probe_z;
    u16 counter;
    u16 *counter_ptr;

    owner_state = owner;
    counter_ptr = tint_effect_update_count;
    x = motion->unk_00.at02.v;
    counter = counter_ptr[0];
    probe_z = motion->unk_08.at02.v;
    y = motion->unk_04.at02.v;
    counter++;
    probe_z -= 2;
    counter_ptr[0] = counter;
    if (motion->unk_08.at02u.v <
        (s16)sample_terrain_surface_height(x, y, probe_z)) {
        if (((S_800250E8_1 *)effect)->unk_26 == 0) {
            x_direction = rcos(((S_800250E8_1 *)effect)->unk_1A);
            motion->unk_00.at00.v = (s32)(motion->unk_00.at00.v +
                (((s32)(x_direction * ((S_800250E8_1 *)effect)->unk_1C.s) >> 4) +
                 (rand() & 0xFFFF)));

            y_direction = rsin(((S_800250E8_1 *)effect)->unk_1A);
            y_step = ((y_direction * ((S_800250E8_1 *)effect)->unk_1C.s) >> 4) +
                       (rand() & 0xFFFF);
            motion->unk_04.at00.v = (s32)(motion->unk_04.at00.v + y_step);

            z_velocity_copy = rand();
            motion->unk_08.at00.v = (s32)(motion->unk_08.at00.v +
                (0xFFFE0000 - (z_velocity_copy & 0xFFF)));
        } else {
            motion->unk_00.at00.v = (s32)(motion->unk_00.at00.v +
                rcos(((S_800250E8_1 *)effect)->unk_1A) *
                ((S_800250E8_1 *)effect)->unk_1C.s * 8);
            y_motion = rsin(((S_800250E8_1 *)effect)->unk_1A) *
                      ((S_800250E8_1 *)effect)->unk_1C.s;
            z_velocity = motion->unk_14;
            z_position = motion->unk_08.at00.v;
            motion->unk_08.at00.v = z_position + z_velocity;
            motion->unk_14 += 0x6000;
            motion->unk_04.at00.v = (s32)(motion->unk_04.at00.v + y_motion * 8);
        }
    }

    life_left = ((S_800250E8_1 *)effect)->unk_1C.u - 1;
    ((S_800250E8_1 *)effect)->unk_1C.s = life_left;
    if ((life_left << 16) <= 0 ||
        (((S_800250E8_2 *)owner_state)->unk_14 & 0x8000)) {
        ((S_800250E8_1_pre *)effect)[-1].unk_00 = (u16)(((S_800250E8_1_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800252E0_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800252E0_0;   /* global in queue_projected_point_primitives */

typedef struct S_800252E0_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    void * unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_800252E0_1;   /* scratch in queue_projected_point_primitives */

   /* input in queue_projected_point_primitives */

typedef struct S_800252E0_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800252E0_3;   /* arg2use in queue_projected_point_primitives */

typedef struct S_800252E0_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
} S_800252E0_4;   /* p in queue_projected_point_primitives */

typedef struct S_800252E0_5_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800252E0_5_pre;   /* the 0x8 bytes before arg0 in queue_projected_point_primitives, addressed as arg0[-1] */

typedef struct S_800252E0_6 {
    void * unk_00;
} S_800252E0_6;   /* global_slot in queue_projected_point_primitives */

typedef struct S_800252E0_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800252E0_7;   /* next in queue_projected_point_primitives */

typedef struct S_800252E0_8 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800252E0_8;   /* ((S_800252E0_6 *)global_slot)->unk_00 in queue_projected_point_primitives */

extern s32 build_and_enqueue_interpolated_depth_sorted_shaded_lines_linked_list();
extern u32 RotTransPers();
extern s32 GetTPage();
extern void SetDrawMode();
extern u8 resident_globals_page[];

/* Queue projected point primitives from a linked list into the ordering table. */
s32 queue_projected_point_primitives(void *node_data, void *position_data, void *appearance_data) {
    MovingPosition *position = position_data;
    void *appearance = appearance_data;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *render_slot = resident_globals_page + 0x3160;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;
    void *packet;
    union { s32 * pointer; u32 value; } ot_entry;

    {
        void *render_state = (*(void **)((u8 *)resident_globals_page + 0x3160));
        void *packet_cursor = ((S_800252E0_0 *)render_state)->unk_8D0;
        ((S_800252E0_1 *)scratch)->unk_20 = (u8 *)render_state + 0xB0;
        ((S_800252E0_1 *)scratch)->unk_18 = packet_cursor;
    }
    for (;;) {
        u16 coord = position->x;
        ((S_800252E0_1 *)scratch)->unk_00 = coord;
        coord = position->y;
        ((S_800252E0_1 *)scratch)->unk_02 = coord;
        ((S_800252E0_1 *)scratch)->unk_04 = position->z;
        packet = ((S_800252E0_1 *)scratch)->unk_18;
        ((S_800252E0_1 *)scratch)->unk_18 = (u8 *)packet + 0xC;
        ((S_800252E0_1 *)scratch)->unk_C0 = RotTransPers(
            scratch, (u8 *)packet + 8, scratch + 0x90, scratch + 0x94);
        if (((S_800252E0_1 *)scratch)->unk_C0 < 0x1E0) {
            s32 color = ((S_800252E0_3 *)appearance)->unk_0C;
            ((S_800252E0_4 *)packet)->unk_00.at03.v = 2;
            ((S_800252E0_4 *)packet)->unk_04.at00.v = color;
            ((S_800252E0_4 *)packet)->unk_04.at03.v = 0x6A;
            ((S_800252E0_4 *)packet)->unk_00.at00.v = (((S_800252E0_4 *)packet)->unk_00.at00.v & length_mask) |
                (*(s32 *)((((S_800252E0_1 *)scratch)->unk_C0 << 2) +
                          (u32)((S_800252E0_1 *)scratch)->unk_20) & addr_mask);
            {
                u32 depth_index;
                depth_index = *(u32 *)(scratch + 0xC0);
                ot_entry.pointer = (s32 *)((depth_index << 2) +
                              (u32)*(void **)(scratch + 0x20));
            }
            *ot_entry.pointer = (*ot_entry.pointer & length_mask) | ((u32)packet & addr_mask);
            packet = ((S_800252E0_1 *)scratch)->unk_18;
            ((S_800252E0_1 *)scratch)->unk_18 = (u8 *)packet + 0xC;
            SetDrawMode(packet, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);
            ((S_800252E0_4 *)packet)->unk_00.at00.v = (((S_800252E0_4 *)packet)->unk_00.at00.v & length_mask) |
                (*(s32 *)((((S_800252E0_1 *)scratch)->unk_C0 << 2) +
                          (u32)((S_800252E0_1 *)scratch)->unk_20) & addr_mask);
            {
                ot_entry.value = *(u32 *)(scratch + 0xC0);
                ot_entry.value = (ot_entry.value << 2) +
                           (u32)*(void **)(scratch + 0x20);
                packet = (void *)((u32)packet & addr_mask);
                *(s32 *)ot_entry.value = (*(s32 *)ot_entry.value & length_mask) |
                                   (u32)packet;
            }
        }
        {
            void *next_node = ((S_800252E0_5_pre *)node_data)[-1].unk_00;
            if (next_node == NULL) {
                ((S_800252E0_8 *)(((S_800252E0_6 *)render_slot)->unk_00))->unk_8D0 =
                    ((S_800252E0_1 *)scratch)->unk_18;
                return 0;
            }
            node_data = (u8 *)next_node + 0x20;
            position = ((S_800252E0_7 *)next_node)->unk_08;
            appearance = ((S_800252E0_7 *)next_node)->unk_0C;
        }
    }
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

   /* payload in allocate_jittered_effect_node */

   /* source in allocate_jittered_effect_node */

typedef struct S_800254C4_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x8];
    s16 unk_26;
} S_800254C4_3;   /* fields in allocate_jittered_effect_node */

/* Allocates a node, copies or jitters its source values, and initializes its fields. */
s32 allocate_jittered_effect_node(void *source_data, s16 initial_1a, s16 initial_1c, s16 spawn_mode) {
    register MovingPosition *source = source_data;
    register s16 field_1a = initial_1a;
    register s16 field_1c = initial_1c;
    register s16 mode = spawn_mode;
    register ObjectNodeHeader *node;

    node = allocate_flagged_object_node(0x202);
    if (node != 0) {
        s32 mode_test;

        node->update_callback = update_spark_effect;
        register_node(node, (s32)queue_projected_point_primitives);
        mode_test = mode << 0x10;
        {
            MovingPosition *payload = node->position;

            s32 value_0a;

            if (mode_test == 0) {
                payload->x =
                    (u16)((source->x + (rand() & 0x1F)) - 0x10);
                payload->y =
                    (u16)((source->y + (rand() & 0x1F)) - 0x10);
                value_0a = source->z - 0x50;
            } else {
                payload->x = source->x;
                payload->y = source->y;
                value_0a = source->z;
            }
            payload->z = value_0a;
        }
        node->sprite->color.c.r = 0xF0;
        {
            S_800254C4_3 *fields = ((void *)node) + 0x20;

            fields->unk_1A = field_1a;
            fields->unk_1C = field_1c;
            fields->unk_26 = mode;
        }
    }
}

#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"
#include "shared/object_flags.h"

/* Fade the effect color and set completion flags when red falls below eight. */
void fade_effect_color_below_eight(u16 *effect_data, s32 unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    tint_effect_update_count[0]++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 3);
    blue = color->blue;
    color->green = green - (green >> 3);
    color->blue = blue - (blue >> 3);

    if (color->red < 8) {
        effect_data[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "shared/sprite_frame_state.h"
#include "common.h"


typedef struct S_80025654_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80025654_2;   /* arg0 in create_effect_from_endpoints */

typedef struct S_80025654_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80025654_4;   /* arg1 in create_effect_from_endpoints */

/* Creates an object with initial values, endpoint differences, and copied settings. */
void *create_effect_from_endpoints(S_80025654_2 *endpoints, S_80025654_4 *settings) {
    ObjectPosition *transition;
    ObjectNodeHeader *object;
    SpriteFrameState *object_settings;

    object = allocate_flagged_object_node(0x202);
    if (object != 0) {
        object->update_callback = fade_effect_color_below_eight;
        register_node(object, (s32)process_linked_mesh_states_mode_0);
        transition = object->position;
        transition->x.w.i = (u16) endpoints->unk_02;
        transition->y.w.i = (u16) endpoints->unk_06;
        transition->z.w.i = (u16) endpoints->unk_0A;
        *((s16 *)&transition->velocity_x + 1) = (s16) (endpoints->unk_02 - endpoints->unk_0E);
        *((s16 *)&transition->velocity_y + 1) = (s16) (endpoints->unk_06 - endpoints->unk_12);
        *((s16 *)&transition->velocity_z + 1) = (s16) (endpoints->unk_0A - endpoints->unk_16);
        object_settings = object->sprite;
        object_settings->scale_x = (u16) settings->unk_1C;
        object_settings->scale_y = (u16) settings->unk_1E;
        object_settings->color.word = (s32) settings->unk_0C;
        object_settings->source = (s32) settings->unk_08;
        object_settings->flags = (u16) settings->unk_14;
    }
    return object;
}
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "common.h"

extern s32 try_trigger_target_record_effect(s32, s32);
extern s32 set_or_clear_actor_status_slot(s32, s32, s32);
extern void adjust_source_value_and_finalize(s32, void *);
extern u8 D_800E1CD5[9];

/* Conditionally applies D_800E1CD5 using a check indexed by the supplied value's low byte. */
void apply_indexed_effect_condition(s32 target, u8 packedValue, void *owner_context) {
    if (try_trigger_target_record_effect(target, 1) == 0) {
        s32 valueGroupIndex = packedValue >> 2;
        valueGroupIndex += 2;
        /*
         * Original bug: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 on
         * failure. Testing it as nonzero misreports slot 0 as failure and -1 as success.
         * Slot-0 success loses its message; rejected insertion prints success.
         * try_apply_confusion_status uses the nonnegative success test.
         */
        if ((set_or_clear_actor_status_slot(target, 0x15, valueGroupIndex) << 16) != 0) {
            adjust_source_value_and_finalize(target, D_800E1CD5);
        }
    }
}
