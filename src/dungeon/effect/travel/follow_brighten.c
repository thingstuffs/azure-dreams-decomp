#include "modules/dungeon_ovl_18a0800/endpoint_creation.h"
#include "shared/audio_commands.h"
/* Staged effect travel and impact with timed fading and owner completion tracking. */
#include "modules/dungeon_ovl_18ac800.h"
#include "dungeon/effect/travel.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/system.h"

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_18ac800_entry)(FollowBrightenEffect *, ObjectPosition *, SpriteFrameState *) = follow_brighten;

/* Scales the coordinate by 64, adds the cell-center offset 32, and masks the result with 0xFFE0. */
static __inline__ s32 align_effect_coord(s32 coord)
{
    return ((coord << 6) + 32) & 0xFFE0;
}

/* Updates a moving effect through initialization, travel, impact, and fading. */
void follow_brighten(FollowBrightenEffect *self, ObjectPosition *motion, SpriteFrameState *part)
{
    ActorRecord *owner;
    ObjectNodeHeader *base;
    ObjectPosition *record;
    u8 *tail_page0;
    u8 *tail_page1;
    s32 velocity;
    register s32 state;
    s32 scratch[4];
    u32 color;
    u32 init_flags;
    u32 init_size;
    u8 *effect_params;

    owner = self->spell.caster;
    state = self->spell.phase;
    base = NODE_HEADER(owner);
    record = base->position;
    switch (state) {
    case 0:
        color = 0x00808080;
        init_flags = 0x01000340;
        init_size = 0x00200020;
        effect_params = D_80026484;
        part->color.unsigned_word = color;
        part->scale_y = 0x555;
        part->scale_x = 0x555;
        part->source = D_80026490;
        ((SignedWordView *)radial_effect_colors)->unk_00 = 0;
        ((SignedHalfView *)D_80026474)->unk_00 = 0;
        ((UnsignedWordView *)&D_80026476)->unk_00 = 0;
        ((UnsignedHalfView *)&row_quad_top_color)->unk_00 = 0;
        ((UnsignedByteView *)&row_quad_bottom_color)->unk_00 = 0;
        {
            u16 owner_flags = owner->facing;
            *(u16 *)D_80026484 = 0x1010;
            ((MovingParameter *)effect_params)->unk_08 = 0;
            self->direction = (owner_flags >> 9) & 7;
        }
        scratch[2] = init_flags;
        scratch[3] = init_size;
        draw_textured_ellipse(effect_params - 12, scratch + 2, 1, 0);
        self->spell.phase++;
    case 1:
        if (get_sprite_attachment_vector(base->sprite->source,
                          base->sprite, scratch, 0) == 0) {
            if (!(base->sprite->flags & 0x8000)) {
                break;
            }
        }
        motion->x.w.i = record->x.w.i;
        motion->y.w.i = record->y.w.i;
        if (base->sprite->flags & 0x8000) {
            u16 height = record->z.w.i - 64;
            motion->z.w.i = height;
            self->height.w.i = height;
        } else {
            u16 height = record->z.w.i + ((OriginOffsetView *)scratch)->unk_04;
            motion->z.w.i = height;
            self->height.w.i = height;
        }
        if (!(*self->spell.context & 0x80)) {
            break;
        }
        if (!(self->flags & 4)) {
            register_node(NODE_HEADER(self), project_sprite_chain);
            part->tpage_abr = 32;
            part->color.c.b = 128;
            part->color.c.g = 128;
            part->color.c.r = 128;
            part->flags |= 0xC;
            self->flags |= 4;
        }
        {
            void *target = owner->target;
            if (target != 0) {
                ObjectPosition *target_part = NODE_HEADER(target)->position;
                self->target_x = target_part->x.w.i;
                self->target_y = target_part->y.w.i;
                self->target_z = target_part->z.w.i -
                                          entity_height_offsets[0];
                {
                    SpriteFrameState *target_record = NODE_HEADER(owner)->sprite;
                    u8 x = target_record->tile_x +
                           ((u8 *)dir_step_x)[self->direction * 2];
                    self->current_tile.tile.x.u = x;
                    self->previous_tile.tile.x.u = x;
                    {
                        u8 y = target_record->tile_y +
                               ((u8 *)dir_step_y)[self->direction * 2];
                        self->current_tile.tile.y.u = y;
                        self->previous_tile.tile.y.u = y;
                    }
                    {
                        s32 owner_coord = owner->target_tile_x;
                        s32 record_coord =
                            target_record->tile_x;
                        s32 tile_distance;
                        if (owner_coord == record_coord) {
                            owner_coord = owner->target_tile_y;
                            record_coord = target_record->tile_y;
                        }
                        tile_distance = owner_coord - record_coord;
                        tile_distance = abs(tile_distance);
                        self->tiles_left = tile_distance + 1;
                    }
                }
            } else {
                self->tiles_left = 8;
                self->target_x = motion->x.w.i;
                self->target_y = motion->y.w.i;
                self->target_z = owner->ground_height - 80;
            }
        }
        *((s16 *)&motion->velocity_x + 1) =
            (dir_step_x[self->direction]) * 8;
        *((s16 *)&motion->velocity_y + 1) =
            (dir_step_y[self->direction]) * 8;
        self->spell.phase++;
        break;

    case 2:
    {
        s32 position;
        s32 adjusted;
        velocity = motion->velocity_x;
        position = motion->x.v;
        position += velocity;
        motion->x.v = position;
        adjusted = motion->velocity_x;
        position = adjusted >> 4;
        adjusted += position;
        velocity = abs(adjusted);
        motion->velocity_x = adjusted;
        if (velocity > 0x200000) {
            s32 limit = -0x200000;
            if (adjusted > 0) {
                limit = 0x200000;
            }
            motion->velocity_x = limit;
        }
    }
        {
            s32 position;
            s32 adjusted;
            velocity = motion->velocity_y;
            position = motion->y.v;
            position += velocity;
            motion->y.v = position;
            adjusted = motion->velocity_y;
            position = adjusted >> 4;
            adjusted += position;
            velocity = abs(adjusted);
            motion->velocity_y = adjusted;
            if (velocity > 0x200000) {
                s32 limit = -0x200000;
                if (adjusted > 0) {
                    limit = 0x200000;
                }
                motion->velocity_y = limit;
            }
        }
        {
            s32 height = self->height.v;
            s32 height_step = (((s32)self->target_z << 16) - height) >> 4;
            self->height.v = height + height_step;
        }
        {
            s32 height = motion->z.v;
            s32 height_step = (((s32)self->target_z << 16) - height) >> 4;
            motion->z.v = height + height_step;
        }
        motion->z.v += rsin((s32)self->frame_count
            << 7) << 6;
        create_effect_from_endpoints(motion, part);
        {
            s32 x = motion->x.w.i;
            if (x < 0) {
                x += 63;
            }
            self->current_tile.tile.x.u = x >> 6;
            {
                s32 y = motion->y.w.i;
                if (y < 0) {
                    y += 63;
                }
                self->current_tile.tile.y.u = y >> 6;
            }
        }
        if (self->previous_tile.packed == self->current_tile.packed) {
            break;
        }
        if (owner->target != 0) {
            /* BYTES: Comparing both coordinates keeps the word loads and high-half masks. */
            if (owner->target_tile_x == self->current_tile.tile.x.s &&
                owner->target_tile_y == self->current_tile.tile.y.s) {
                s32 snap_x = owner->target_tile_x;
                s32 snap_y;
                snap_x <<= 6;
                snap_x += 32;
                motion->x.w.i = snap_x;
                snap_y = owner->target_tile_y;
                snap_y <<= 6;
                snap_y += 32;
                motion->y.w.i = snap_y;
                motion->z.w.i = self->target_z;
                create_effect_from_endpoints(motion, part);
                {
                    ActorRecord *target = owner->target;
                    u16 next_state = self->spell.phase + 1;
                    u16 height = target->ground_height;
                    self->spell.phase = next_state;
                    ((MovingHeight *)particle_target_height)->unk_00 = height;
                }
                break;
            }
        }

        {
            u8 old_x = self->current_tile.tile.x.u;
            s16 steps_left = self->tiles_left - 1;
            u8 old_y = self->current_tile.tile.y.u;
            self->tiles_left = steps_left;
            self->previous_tile.tile.x.u = old_x;
            self->previous_tile.tile.y.u = old_y;
            if (steps_left != 0) {
                s32 x = align_effect_coord(self->current_tile.tile.x.s);
                s32 height = self->height.w.i;
                s32 y;
                y = align_effect_coord(self->current_tile.tile.y.s);
                if ((check_left_tile_and_center_height(x, y, height) << 16) == 0) {
                    break;
                }
            }
        }
        self->spell.phase = 16;
        break;

    case 3:
        ratan2(*((s16 *)&motion->velocity_x + 1),
            *((s16 *)&motion->velocity_y + 1));
        self->child =
            create_effect_object_groups(motion->x.w.i,
                motion->y.w.i,
                          motion->z.w.i);
        if (self->child == 0) {
            break;
        }
        if (owner->target != 0) {
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        }
        self->spell.phase++;
    case 4:
        part->color.c.r -= part->color.c.r >> 2;
        part->color.c.g -= part->color.c.g >> 2;
        part->color.c.b -= part->color.c.b >> 2;
        if (!(self->child->flags & 0x8000)) {
            break;
        }
        if (owner->target != 0) {
            apply_conditional_target_effect(owner->target, self->spell.variant,
                owner);
        }
        g_dungeon_status.active_actor = 0;
        NODE_HEADER(self)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;

    case 16:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        {
            s32 height_step = ((s32)self->target_z << 16) -
                        motion->z.v;
            height_step >>= 4;
            motion->z.v += height_step;
        }
        part->color.c.r -= part->color.c.r >> 1;
        part->color.c.g -= part->color.c.g >> 1;
        part->color.c.b -= part->color.c.b >> 1;
        create_effect_from_endpoints(motion, part);
        if (part->color.c.r < 2) {
            self->spell.phase++;
        }
        break;

    case 17:
        if (staged_fade_count != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        NODE_HEADER(self)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    {
        u16 frame = self->frame_count;
        staged_fade_count = 0;
        self->frame_count = frame + 1;
    }
}


/* Increment the object and global counters and flag the object after 256 counts. */
void advance_object_and_global_counters(u16 *object)
{
    u16 object_count;
    s32 counter;

    counter = (u16)staged_fade_count;
    object_count = object[13] + 1;
    counter++;
    object[13] = object_count;
    staged_fade_count = counter;
    if ((s16)object_count >= 0x101) {
        object[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
