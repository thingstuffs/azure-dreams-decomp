/* Timed visual effects, linked sprite copies, and tile fade animation. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/effect/sprite/advance_timed_visual_effect.h"
#include "shared/object_flags.h"


/* Keeps both sprite scales at normal size and removes the effect when its countdown ends. */
void expire_effect_at_unit_scale(void *state_data, s32 unused, void *scale_data)
{
    u8 *state = state_data;
    s32 remaining_ticks;
    u8 *scale = scale_data;

    *(u16 *)(state + 2) = *(u16 *)(state + 2) - 1;
    *(s16 *)(scale + 0x1C) = 0x1000;
    *(s16 *)(scale + 0x1E) = 0x1000;
    remaining_ticks = *(s16 *)(state + 2);
    ((s16 *)D_80025E80)[0] = 1;
    if (remaining_ticks <= 0) {
        *(u16 *)(state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* MECHANISM: Frameless leaf; pin the persistent arg0 pointer in $a1.
   Hold the signed halfword reload in a pinned s32 $a0 local: this selects
   retail's direct lh/bgtz and avoids the s16 pin's extra lhu/sll pair. */

void finish_timed_visual_effect(void *object) {
    u16 *flags = (u16 *)object - 1;

    (*(s16 *)D_80025E80) = 1;
    *flags |= 0x8000;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}

/* Bobs and pulses a substitute sprite while hiding the linked sprite, restoring the linked sprite when
   time expires. */
void advance_timed_visual_effect(void *state, void *position, void *visual) {
    void *object;
    void *linked_visual;
    s16 ticks_left;

    object = ((Row_818FEF80_S_818FEF80_0 *)state)->unk_30;
    (*(s16 *)D_80025E80) = 1;
    if ((u32)(((Row_818FEF80_S_818FEF80_1 *)object)->unk_13 - 0x33) < 4U) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    ((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.s--;
    if (((Row_818FEF80_S_818FEF80_0 *)state)->unk_0A.s == 0) {
        ((Row_818FEF80_S_818FEF80_0 *)state)->unk_0A.u = 1;
        ((Row_818FEF80_S_818FEF80_2 *)position)->unk_08.u += -0x20000;
    } else {
        ((Row_818FEF80_S_818FEF80_0 *)state)->unk_0A.s = 0;
        ((Row_818FEF80_S_818FEF80_2 *)position)->unk_08.u += 0x20000;
    }
    object = ((Row_818FEF80_S_818FEF80_0 *)state)->unk_30;
    linked_visual = ((Row_818FEF80_S_818FEF80_1_pre *)object)[-1].unk_00;
    ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_14 &= 0xFF7F;
    ((Row_818FEF80_S_818FEF80_4 *)linked_visual)->unk_14 |= 0x80;

    ticks_left = ((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u;
    if (ticks_left < 0x3C) {
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0E = (((0x3C - ticks_left) << 6) / 60) + 0x40;
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0D = (((0x3C - ((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u) << 6) / 60) + 0x40;
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0C = (((0x3C - ((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u) << 6) / 60) + 0x40;
    } else {
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0E = (((ticks_left - 0x3C) << 6) / 60) + 0x40;
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0D = (((((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u - 0x3C) << 6) / 60) + 0x40;
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0C = (((((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u - 0x3C) << 6) / 60) + 0x40;
    }

    if (((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u <= 0) {
        u16 linked_flags;

        ((Row_818FEF80_S_818FEF80_0_pre *)state)[-1].unk_00 |= 0x8000;
        linked_flags = ((Row_818FEF80_S_818FEF80_4 *)linked_visual)->unk_14;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        ((Row_818FEF80_S_818FEF80_4 *)linked_visual)->unk_14 = linked_flags & 0xFF7F;
    }
}

/* Inverts a tiled texture mask, draws clipped moving sprites, and fades them in and out before completion. */
void update_tiled_fade_effect(void *effect, void *offset_state, void *render_state) {
    Row_818FF19C_Rect8 moving_rect;
    Row_818FF19C_Rect8 tile_rect;
    s16 draw_pos[2];
    s32 tile_col;
    s32 tile_row;
    s32 pixel_index;
    s32 rounded_frame;
    s32 y_offset;
    s32 stage;
    s32 offset_applied;
    s16 column_x;
    s16 tile_x;
    s16 tile_y;
    u16 fill_pixel;
    u8 *buffer_base;
    s32 frame;
    s16 next_frame;
    u16 *pixel;

    moving_rect = D_80024028;
    tile_rect = D_80024030;
    offset_applied = ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_0A;
    (*(s16 *)D_80025E80) = 1;
    if (offset_applied == 0) {
        ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_0A = 1;
        ((Row_818FF19C_S_818FF19C_1 *)offset_state)->unk_08 += -0x20000;
    } else {
        ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_0A = 0;
        ((Row_818FF19C_S_818FF19C_1 *)offset_state)->unk_08 += 0x20000;
    }
    stage = ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_00.s;
    switch (stage) {
    case 0:
        tile_col = 0;
        buffer_base = (u8 *)0x80020000;
        fill_pixel = 0xFFFF;
        column_x = 0x340;
        do {
            tile_row = 0;
            tile_x = column_x;
            tile_y = 0x154;
            do {
                tile_rect.x = tile_x;
                tile_rect.y = tile_y;
                tile_rect.w = 0x18;
                tile_rect.h = 0x15;
                func_8006733C(&tile_rect, (u16 *)(buffer_base + 0x5EE8));
                do {
                } while (func_80067014(1) != 0);

                pixel = (u16 *)(buffer_base + 0x5EE8);
                pixel_index = 0;
                do {
                    if (*pixel == 0) {
                        *pixel = fill_pixel;
                    } else {
                        *pixel = 0;
                    }
                    pixel_index++;
                    pixel++;
                } while (pixel_index < 0x1F8);

                func_800672D8(&tile_rect, (u16 *)(buffer_base + 0x5EE8));
                tile_row++;
                tile_y += 0x15;
            } while (tile_row < 4);

            tile_col++;
            column_x += 0x18;
        } while (tile_col < 4);

        ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_00.u++;
        ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_14 &= 0xFF7F;

    case 1:
        tile_rect.x = 0x340;
        tile_rect.y = 0x100;
        tile_rect.w = 0x60;
        tile_rect.h = 0x54;
        draw_pos[0] = 0x370;
        draw_pos[1] = 0x148;
        draw_transformed_sprite_with_clip_rect(((Row_818FF19C_S_818FF19C_0 *)effect)->unk_38, &tile_rect, draw_pos, 0, 1);

        draw_pos[0] = moving_rect.x + (moving_rect.w >> 1) - 6;
        rounded_frame = ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02;
        y_offset = (rounded_frame / 4) - 0x4E;
        draw_pos[1] = moving_rect.y - y_offset;
        draw_transformed_sprite_with_clip_rect(((Row_818FF19C_S_818FF19C_0 *)effect)->unk_3C, &moving_rect, draw_pos, 1, 1);

        frame = ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02;
        if (frame < 0x15) {
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0E = (frame << 7) / 20;
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0D = (((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 << 7) / 20;
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0C = (((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 << 7) / 20;
        }
        if (((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 >= 0x51) {
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0E = ((0x64 - ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0D = ((0x64 - ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0C = ((0x64 - ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
        }

        next_frame = (u16)((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 + 1;
        ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 = next_frame;
        if (next_frame >= 0x65) {
            ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 = 0;
            ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_00.u++;
            ((Row_818FF19C_S_818FF19C_3 *)(((Row_818FF19C_S_818FF19C_0 *)effect)->unk_34))->unk_90 = 1;
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

    if ((u32)(((Row_818FF19C_S_818FF19C_4 *)(((Row_818FF19C_S_818FF19C_0 *)effect)->unk_30))->unk_13 - 0x33) < 4U) {
        ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_14 |= 0x80;
    }
}

/* Creates a half-scale sprite linked to the owner and target, copying its color and mirroring its
   rotation. */
void create_owner_linked_mirrored_sprite(void **owner_ref, Row_818FF5B8_S_818FF5B8_4 *spawn_pos, Row_818FF5B8_S_818FF5B8_5 *appearance) {
    Row_818FF5B8_S_818FF5B8_2 *sprite;
    ObjectNodeHeader *object;
    Row_818FF5B8_S_818FF5B8_0 *state;
    ObjectPosition *position;

    object = allocate_flagged_object_node(0x212);
    state = ((void *)object) + 0x20;
    if (object != 0) {
        state->unk_2C = (void *) *owner_ref;
        state->unk_30 = (s32) ((Row_818FF5B8_S_818FF5B8_1 *)(*owner_ref))->unk_60;
        state->unk_34 = owner_ref;
        (object->unk_10) = &D_80024750;
        register_node(object, project_sprite_chain);
        sprite = (object->sprite);
        sprite->unk_10 = 0x20;
        sprite->unk_06 = 0;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        position = (object->position);
        position->x.v = (s32) spawn_pos->unk_00;
        position->y.v = (s32) spawn_pos->unk_04;
        position->z.v = (s32) spawn_pos->unk_08;
        sprite = (object->sprite);
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_0C = (u8) appearance->unk_0C;
        sprite->unk_0D = (u8) appearance->unk_0D;
        sprite->unk_0E = (u8) appearance->unk_0E;
        sprite->unk_1A = (s16) (0x1000 - appearance->unk_1A);
        *(Row_818FF5B8_Copy12 *)((u8 *)object + 0x40) = D_80025E64;
        sprite->unk_08 = (void *) (((void *)object) + 0x40);
    }
}

