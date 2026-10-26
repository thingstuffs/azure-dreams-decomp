/* CD-wait glyph animation, saved trail positions and video-field draw-buffer updates. */
#include "engine/scene/gp_shared_slots.h"
#include "engine/scene.h"



/* Swaps draw buffers on a new video field, advances the CD-wait path and draws four trail layers. */
void render_cd_wait_animation_on_new_field(void)
{
    void **draw_buffer = &g_game_work[0];

    if ((runtime_dispatch_state.field_0 & 3) == 1) {
        u8 field_id = (u8)((u32)VSync(1) >> 8);

        if (field_id != scene_sprite_last_field) {
            u8 *next_buffer;
            s32 layer;
            s32 trig_value;
            s32 wave_offset;
            s32 center_offset;

            scene_sprite_last_field = field_id;
            PutDispEnv((u8 *)g_game_work[0] + 0x5C);
            PutDrawEnv(*draw_buffer);

            next_buffer = upper_draw_context;
            if (*draw_buffer == upper_draw_context) {
                next_buffer += 0x108D4;
            }
            g_game_work[0] = next_buffer;
            *(u32 *)(next_buffer + 0x8D0) = (u32)next_buffer + 0x8D4;

            if (scene_sprite_cached_mode != scene_sprite_mode_word[0]) {
                scene_sprite_cached_mode = scene_sprite_mode_word[0];
                scene_sprite_fade_ticks = 8;
            }

            layer = 63;
            {
                s16 *y_history = scene_sprite_y_history;
                s16 *y_dst = y_history + 63;
                s16 *y_src = y_history + 62;
                s16 *x_history = scene_sprite_x_history;
                s16 *x_dst = x_history + 63;
                s16 *x_src = x_history + 62;

                do {
                    *x_dst = *x_src;
                    x_src--;
                    layer--;
                    *y_dst = *y_src;
                    y_src--;
                    x_dst--;
                    y_dst--;
                } while (layer > 0);
            }

            layer = 3;
            trig_value = rcos(scene_sprite_wave_tick * 80);
            {
                s16 *x_head = scene_sprite_x_history;
                wave_offset = trig_value >> 7;
                center_offset = shift10(trig_value) + 0x100;
                *x_head = (s16)(wave_offset + center_offset);
            }

            trig_value = rsin(scene_sprite_wave_tick * 80);
            {
                s16 *y_head = scene_sprite_y_history;
                s32 trail_center;
                wave_offset = trig_value >> 7;
                trail_center = shift10(trig_value) + 0xB0;
                *y_head = (s16)(wave_offset + trail_center);
            }

            draw_sprite_list();
            for (; layer >= 0; layer--) {
                draw_cd_wait_sprite_trail(layer);
            }

            if (scene_sprite_fade_ticks != 0) {
                scene_sprite_fade_ticks--;
            }
            DrawSync(0);
            scene_sprite_wave_tick++;
        }
    }
}

/* Draws fourteen pulsing glyphs along the saved CD-wait path, interpolated for the requested trail layer. */
void draw_cd_wait_sprite_trail(s32 blend_step)
{
    u8 *scratch;
    SpriteQuad *packet;
    u8 *sprite_uv;
    u8 *quad;
    u8 *transform_flags;
    u8 *sprite_base;
    s32 sprite_index;
    u8 sprite_key[2];
    u8 **render_state;
    s32 uv_start;
    s32 uv_size;
    s32 width;
    s32 height;
    s32 path_offset;
    s32 shade;
    s32 colour;

    scratch = (u8 *)0x1F800000;
    render_state = (u8 **)g_game_work;

    if (scene_sprite_list_initialized == 0) {
        u8 *sprite_slot;
        s32 origin_offset;
        u8 *sprite_ids;
        sprite_index = 0;
        sprite_ids = scene_sprite_glyph_ids;
        origin_offset = -4;
        sprite_slot = scene_sprite_object_storage;
        scene_sprite_list_initialized = scene_sprite_list_initialized + 1;
        sprite_key[1] = 0;
        do {
            sprite_key[0] = *(u8 *)(sprite_index + (unsigned long)sprite_ids);
            colour = (s32)((u8 *)build_positioned_text_glyphs(sprite_slot, sprite_key, 0));
            S8_AT((u8 *)colour, 3) = origin_offset;
            S8_AT((u8 *)colour, 2) = origin_offset;
            if (sprite_index == 0) {
                scene_sprite_list_base = (u8 *)colour;
            }
            sprite_index++;
            sprite_slot += 0xC;
        } while (sprite_index < 0xE);
    }

    quad = *(u8 **)(render_state[0] + 0x8D0);
    sprite_index = 0;
    transform_flags = scratch + 0x94;
    U32_AT(scratch, 0x48) = 0;
    U16_AT(scratch, 0x8C) = 0;
    U16_AT(scratch, 0x84) = 0;
    U16_AT(scratch, 0x7C) = 0;
    U16_AT(scratch, 0x74) = 0;
    PushMatrix();
    {
        colour = (s32)((u8 *)scene_sprite_list_base);
        sprite_base = ((u8 *)colour) + 4;
    }
    U16_AT(scratch, 0x28) = 0;
    U16_AT(scratch, 0x2A) = 0;
    U16_AT(scratch, 0x2C) = 0;
    packet = (SpriteQuad *)quad;

    do {
        sprite_uv = sprite_base + sprite_index * 12;
        path_offset = sprite_index << 2;
        {
            s32 start_x = *(s16 *)((u8 *)scene_sprite_x_history + path_offset);
            s32 end_x = *(s16 *)((u8 *)scene_sprite_x_history + 4 + path_offset);
            U32_AT(scratch, 0x40) = start_x + ((end_x - start_x) * blend_step) / 8;
        }
        {
            s32 start_y = *(s16 *)((u8 *)scene_sprite_y_history + path_offset);
            s32 end_y = *(s16 *)((u8 *)scene_sprite_y_history + 4 + path_offset);
            U32_AT(scratch, 0x44) = start_y + ((end_y - start_y) * blend_step) / 8;
        }
        TransMatrix(scratch + 0x50, scratch + 0x40);
        RotMatrix(scratch + 0x28, scratch + 0x50);
        SetRotMatrix(scratch + 0x50);
        SetTransMatrix(scratch + 0x50);

        uv_start = U8_AT(sprite_uv, 4);
        U32_AT(scratch, 0x08) = uv_start;
        uv_size = U8_AT(sprite_uv, 6);
        U32_AT(scratch, 0x10) = uv_size;
        if (uv_start + uv_size >= 0x100) {
            U32_AT(scratch, 0x10) = uv_size - 1;
        }
        uv_start = U8_AT(sprite_uv, 5);
        U32_AT(scratch, 0x0C) = uv_start;
        uv_size = U8_AT(sprite_uv, 7);
        U32_AT(scratch, 0x14) = uv_size;
        if (uv_start + uv_size >= 0x100) {
            U32_AT(scratch, 0x14) = uv_size - 1;
        }

        {
            s16 edge_x = S8_AT(sprite_uv, -2);
            width = ((u16 *)scratch)[8];
            S16_AT(scratch, 0x80) = edge_x;
            S16_AT(scratch, 0x70) = edge_x;
            edge_x = edge_x + width;
            S16_AT(scratch, 0x88) = edge_x;
            S16_AT(scratch, 0x78) = edge_x;
        }
        {
            s16 edge_y = S8_AT(sprite_uv, -1);
            height = ((u16 *)scratch)[10];
            S16_AT(scratch, 0x7A) = edge_y;
            S16_AT(scratch, 0x72) = edge_y;
            edge_y = edge_y + height;
            S16_AT(scratch, 0x8A) = edge_y;
            S16_AT(scratch, 0x82) = edge_y;
        }

        RotTransSV(scratch + 0x70, quad + 0x08, transform_flags);
        RotTransSV(scratch + 0x78, quad + 0x10, transform_flags);
        RotTransSV(scratch + 0x80, quad + 0x18, transform_flags);
        RotTransSV(scratch + 0x88, quad + 0x20, transform_flags);

        {
            U32_AT(scratch, 0x10) += U32_AT(scratch, 0x08);
            U32_AT(scratch, 0x14) += U32_AT(scratch, 0x0C);
            U32_AT(scratch, 0x14) <<= 8;
            U32_AT(scratch, 0x0C) <<= 8;
        }

        packet->clut = U16_AT(sprite_uv, 2);
        packet->uv0.word = ((u16 *)scratch)[6] + ((u16 *)scratch)[4];
        packet->uv1.word = ((u16 *)scratch)[6] + ((u16 *)scratch)[8];
        packet->tpage = U16_AT(sprite_uv, 0);
        packet->uv2.word = ((u16 *)scratch)[10] + ((u16 *)scratch)[4];
        packet->uv3.word = ((u16 *)scratch)[10] + ((u16 *)scratch)[8];

        if (packet->x0 > packet->x3) {
            u8 right_u = packet->uv3.c.u;
            packet->uv3.c.u = right_u + 0xFF;
            packet->uv1.c.u = right_u;
        }
        if (packet->y0 > packet->y3) {
            u8 bottom_v = packet->uv3.c.v;
            packet->uv3.c.v = bottom_v + 0xFF;
            packet->uv2.c.v = bottom_v;
        }
        packet->tag.bytes[3] = 9;
        packet->code = 0x2C;

        {
            s32 pulse = (rsin((scene_sprite_wave_tick << 8) + (sprite_index << 6)) >> 6) + 0x80;
            s32 fade_shift = blend_step / 2;
            shade = pulse >> fade_shift;
        }
        packet->r = shade;
        colour = 0;
        if (scene_sprite_fade_ticks == 0) {
            colour = shade;
        }
        {
            u8 *draw_quad = quad;
            quad += 0x28;
            packet->b = colour;
            packet->g = colour;
            packet->code |= 2;
            DrawPrim(draw_quad);
        }
        packet++;
        sprite_index++;
    } while (sprite_index < 0xE);

    PopMatrix();
    {
        *(u8 **)(render_state[0] + 0x8D0) = quad;
    }
}
s16 scene_sprite_wave_tick = 0;
u16 scene_sprite_cached_mode = 0;
u16 scene_sprite_fade_ticks = 0;
u8 scene_sprite_last_field = 0;
s16 scene_sprite_list_initialized = 0;
void * scene_sprite_list_base = 0;
