#include "modules/dungeon_ovl_18a0800/endpoint_creation.h"
#include "shared/audio_commands.h"
/* Staged effect travel and impact with timed fading and owner completion tracking. */
#include "modules/dungeon_ovl_18ac800.h"
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
void (*const dungeon_18ac800_entry)(MovingEffectState *, MovingMotion *, MovingSprite *) = follow_brighten;

/* Scales the coordinate by 64, adds the cell-center offset 32, and masks the result with 0xFFE0. */
static __inline__ s32 align_effect_coord(s32 coord)
{
    return ((coord << 6) + 32) & 0xFFE0;
}

/* Updates a moving effect through initialization, travel, impact, and fading. */
void follow_brighten(MovingEffectState *self, MovingMotion *motion, MovingSprite *part)
{
    MovingActor *owner;
    MovingObject *base;
    MovingPosition *record;
    u8 *tail_page0;
    u8 *tail_page1;
    s32 velocity;
    register s32 state;
    s32 scratch[4];
    u32 color;
    u32 init_flags;
    u32 init_size;
    u8 *effect_params;

    owner = (MovingActor *)self->unk_00;
    state = self->unk_0A.s;
    base = (MovingObject *)((u8 *)owner - 32);
    record = (MovingPosition *)base->unk_08;
    switch (state) {
    case 0:
        color = 0x00808080;
        init_flags = 0x01000340;
        init_size = 0x00200020;
        effect_params = D_80026484;
        part->color.at00.v = color;
        part->scale_y = 0x555;
        part->scale_x = 0x555;
        part->source = D_80026490;
        ((SignedWordView *)radial_effect_colors)->unk_00 = 0;
        ((SignedHalfView *)D_80026474)->unk_00 = 0;
        ((UnsignedWordView *)D_80026476)->unk_00 = 0;
        ((UnsignedHalfView *)&row_quad_top_color)->unk_00 = 0;
        ((UnsignedByteView *)&row_quad_bottom_color)->unk_00 = 0;
        {
            u16 owner_flags = owner->unk_2A;
            *(u16 *)D_80026484 = 0x1010;
            ((MovingParameter *)effect_params)->unk_08 = 0;
            self->unk_16.u = (owner_flags >> 9) & 7;
        }
        scratch[2] = init_flags;
        scratch[3] = init_size;
        draw_textured_ellipse(effect_params - 12, scratch + 2, 1, 0);
        self->unk_0A.u++;
    case 1:
        if (get_sprite_attachment_vector(((MovingSpriteFlags *)(base->unk_0C))->unk_08,
                          base->unk_0C, scratch, 0) == 0) {
            if (!(((MovingSpriteFlags *)(base->unk_0C))->unk_14 & 0x8000)) {
                break;
            }
        }
        motion->unk_00.at02.v = record->x;
        motion->unk_04.at02.v = record->y;
        if (((MovingSpriteFlags *)(base->unk_0C))->unk_14 & 0x8000) {
            u16 height = record->z - 64;
            motion->unk_08.at02.v = height;
            self->unk_30.at02.v = height;
        } else {
            u16 height = record->z + ((OriginOffsetView *)scratch)->unk_04;
            motion->unk_08.at02.v = height;
            self->unk_30.at02.v = height;
        }
        if (!(((MovingAnimationFlags *)(self->unk_04))->unk_00 & 0x80)) {
            break;
        }
        if (!(self->unk_12 & 4)) {
            register_node(NODE_HEADER(self), project_sprite_chain);
            part->tpage_abr = 32;
            part->color.at02.v = 128;
            part->color.at01.v = 128;
            part->color.at00u.v = 128;
            part->flags |= 0xC;
            self->unk_12 |= 4;
        }
        {
            u8 *target = owner->unk_60.p;
            if (target != 0) {
                MovingTargetPosition *target_part = (MovingTargetPosition *)((MovingTarget_pre *)target)[-1].unk_00;
                self->unk_0C = target_part->unk_02;
                self->unk_0E = target_part->unk_06;
                self->unk_10.u = target_part->unk_0A -
                                          entity_height_offsets[0];
                {
                    MovingTile *target_record = (MovingTile *)((MovingActor_pre *)owner)[-1].unk_00;
                    u8 x = target_record->tile_x +
                           ((u8 *)dir_step_x)[self->unk_16.s * 2];
                    self->unk_1C.at02.v = x;
                    self->unk_20.at00.v = x;
                    {
                        u8 y = target_record->tile_y +
                               ((u8 *)dir_step_y)[self->unk_16.s * 2];
                        self->unk_1C.at03.v = y;
                        self->unk_20.at01.v = y;
                    }
                    {
                        s32 owner_coord = owner->unk_70.at02.v;
                        s32 record_coord =
                            target_record->tile_x;
                        s32 tile_distance;
                        if (owner_coord == record_coord) {
                            owner_coord = owner->unk_70.at03.v;
                            record_coord = target_record->tile_y;
                        }
                        tile_distance = owner_coord - record_coord;
                        tile_distance = abs(tile_distance);
                        self->unk_14 = tile_distance + 1;
                    }
                }
            } else {
                self->unk_14 = 8;
                self->unk_0C = motion->unk_00.at02.v;
                self->unk_0E = motion->unk_04.at02.v;
                self->unk_10.u = owner->unk_88 - 80;
            }
        }
        motion->unk_0C.at02.v =
            (dir_step_x[self->unk_16.s]) * 8;
        motion->unk_10.at02.v =
            (dir_step_y[self->unk_16.s]) * 8;
        self->unk_0A.u++;
        break;

    case 2:
    {
        s32 position;
        s32 adjusted;
        velocity = motion->unk_0C.at00.v;
        position = motion->unk_00.at00.v;
        position += velocity;
        motion->unk_00.at00.v = position;
        adjusted = motion->unk_0C.at00.v;
        position = adjusted >> 4;
        adjusted += position;
        velocity = abs(adjusted);
        motion->unk_0C.at00.v = adjusted;
        if (velocity > 0x200000) {
            s32 limit = -0x200000;
            if (adjusted > 0) {
                limit = 0x200000;
            }
            motion->unk_0C.at00.v = limit;
        }
    }
        {
            s32 position;
            s32 adjusted;
            velocity = motion->unk_10.at00.v;
            position = motion->unk_04.at00.v;
            position += velocity;
            motion->unk_04.at00.v = position;
            adjusted = motion->unk_10.at00.v;
            position = adjusted >> 4;
            adjusted += position;
            velocity = abs(adjusted);
            motion->unk_10.at00.v = adjusted;
            if (velocity > 0x200000) {
                s32 limit = -0x200000;
                if (adjusted > 0) {
                    limit = 0x200000;
                }
                motion->unk_10.at00.v = limit;
            }
        }
        {
            s32 height = self->unk_30.at00.v;
            s32 height_step = (((s32)self->unk_10.s << 16) - height) >> 4;
            self->unk_30.at00.v = height + height_step;
        }
        {
            s32 height = motion->unk_08.at00.v;
            s32 height_step = (((s32)self->unk_10.s << 16) - height) >> 4;
            motion->unk_08.at00.v = height + height_step;
        }
        motion->unk_08.at00.v += rsin((s32)self->unk_18.s
            << 7) << 6;
        create_effect_from_endpoints(motion, part);
        {
            s32 x = motion->unk_00.at02u.v;
            if (x < 0) {
                x += 63;
            }
            self->unk_1C.at02.v = x >> 6;
            {
                s32 y = motion->unk_04.at02u.v;
                if (y < 0) {
                    y += 63;
                }
                self->unk_1C.at03.v = y >> 6;
            }
        }
        if (self->unk_20.at00u.v == self->unk_1C.at02u.v) {
            break;
        }
        if (owner->unk_60.p2 != 0) {
            if ((owner->unk_70.at00.v & 0xFFFF0000) ==
                (self->unk_1C.at00.v & 0xFFFF0000)) {
                s32 snap_x = owner->unk_70.at02.v;
                s32 snap_y;
                snap_x <<= 6;
                snap_x += 32;
                motion->unk_00.at02.v = snap_x;
                snap_y = owner->unk_70.at03.v;
                snap_y <<= 6;
                snap_y += 32;
                motion->unk_04.at02.v = snap_y;
                motion->unk_08.at02.v = self->unk_10.u;
                create_effect_from_endpoints(motion, part);
                {
                    u8 *target = owner->unk_60.p;
                    u16 next_state = self->unk_0A.u + 1;
                    u16 height = ((MovingTarget *)target)->unk_88;
                    self->unk_0A.u = next_state;
                    ((MovingHeight *)particle_target_height)->unk_00 = height;
                }
                break;
            }
        }

        {
            u8 old_x = self->unk_1C.at02.v;
            s16 steps_left = self->unk_14 - 1;
            u8 old_y = self->unk_1C.at03.v;
            self->unk_14 = steps_left;
            self->unk_20.at00.v = old_x;
            self->unk_20.at01.v = old_y;
            if (steps_left != 0) {
                s32 x = align_effect_coord(self->unk_1C.at02p.v);
                s32 height = self->unk_30.at02u.v;
                s32 y;
                y = align_effect_coord(self->unk_1C.at03u.v);
                if ((check_left_tile_and_center_height(x, y, height) << 16) == 0) {
                    break;
                }
            }
        }
        self->unk_0A.u = 16;
        break;

    case 3:
        ratan2(motion->unk_0C.at02.v,
            motion->unk_10.at02.v);
        self->unk_2C.i =
            create_effect_object_groups(motion->unk_00.at02u.v,
                motion->unk_04.at02u.v,
                          motion->unk_08.at02u.v);
        if (self->unk_2C.i == 0) {
            break;
        }
        if (owner->unk_60.p2 != 0) {
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        }
        self->unk_0A.u++;
    case 4:
        part->color.at00u.v -= part->color.at00u.v >> 2;
        part->color.at01.v -= part->color.at01.v >> 2;
        part->color.at02.v -= part->color.at02.v >> 2;
        if (!(((MovingSpawnFlags *)(self->unk_2C.p))->unk_1E & 0x8000)) {
            break;
        }
        if (owner->unk_60.p2 != 0) {
            apply_conditional_target_effect(owner->unk_60.p2, self->unk_09,
                owner);
        }
        g_dungeon_status.active_actor = 0;
        NODE_HEADER(self)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;

    case 16:
        motion->unk_00.at00.v += motion->unk_0C.at00.v;
        motion->unk_04.at00.v += motion->unk_10.at00.v;
        {
            s32 height_step = ((s32)self->unk_10.s << 16) -
                        motion->unk_08.at00.v;
            height_step >>= 4;
            motion->unk_08.at00.v += height_step;
        }
        part->color.at00u.v -= part->color.at00u.v >> 1;
        part->color.at01.v -= part->color.at01.v >> 1;
        part->color.at02.v -= part->color.at02.v >> 1;
        create_effect_from_endpoints(motion, part);
        if (part->color.at00u.v < 2) {
            self->unk_0A.u++;
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
        u16 frame = self->unk_18.u;
        staged_fade_count = 0;
        self->unk_18.u = frame + 1;
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
