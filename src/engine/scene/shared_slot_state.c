/* CD-wait glyph animation, saved trail positions and video-field draw-buffer updates. */
#include "engine/scene/gp_shared_slots.h"
#include "engine/scene.h"
#include "engine/text.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libetc.h"
#include "shared/gpu_packets.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"



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
    SpriteQuadScratch *scratch;
    POLY_FT4 *packet;
    u8 *sprite_uv;
    POLY_FT4 *quad;
    s32 *transform_flags;
    u8 *sprite_base;
    s32 sprite_index;
    u8 sprite_key[2];
    GpuContext **render_state;
    s32 uv_start;
    s32 uv_size;
    s32 width;
    s32 height;
    s32 path_offset;
    s32 shade;
    s32 colour;

    scratch = (SpriteQuadScratch *)0x1F800000;
    render_state = (GpuContext **)g_game_work;

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

    quad = render_state[0]->packetCursor;
    sprite_index = 0;
    transform_flags = &scratch->gte_flag;
    scratch->translation.vz = 0;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    PushMatrix();
    {
        colour = (s32)((u8 *)scene_sprite_list_base);
        sprite_base = ((u8 *)colour) + 4;
    }
    scratch->rotation.vx = 0;
    scratch->rotation.vy = 0;
    scratch->rotation.vz = 0;
    packet = quad;

    do {
        sprite_uv = sprite_base + sprite_index * 12;
        path_offset = sprite_index << 2;
        {
            s32 start_x = *(s16 *)((u8 *)scene_sprite_x_history + path_offset);
            s32 end_x = *(s16 *)((u8 *)scene_sprite_x_history + 4 + path_offset);
            scratch->translation.vx = start_x + ((end_x - start_x) * blend_step) / 8;
        }
        {
            s32 start_y = *(s16 *)((u8 *)scene_sprite_y_history + path_offset);
            s32 end_y = *(s16 *)((u8 *)scene_sprite_y_history + 4 + path_offset);
            scratch->translation.vy = start_y + ((end_y - start_y) * blend_step) / 8;
        }
        TransMatrix(&scratch->matrix, &scratch->translation);
        RotMatrix(&scratch->rotation, &scratch->matrix);
        SetRotMatrix(&scratch->matrix);
        SetTransMatrix(&scratch->matrix);

        uv_start = U8_AT(sprite_uv, 4);
        scratch->uv_u_start = uv_start;
        uv_size = U8_AT(sprite_uv, 6);
        scratch->uv_u_extent = uv_size;
        if (uv_start + uv_size >= 0x100) {
            scratch->uv_u_extent = uv_size - 1;
        }
        uv_start = U8_AT(sprite_uv, 5);
        scratch->uv_v_start = uv_start;
        uv_size = U8_AT(sprite_uv, 7);
        scratch->uv_v_extent = uv_size;
        if (uv_start + uv_size >= 0x100) {
            scratch->uv_v_extent = uv_size - 1;
        }

        {
            s16 edge_x = S8_AT(sprite_uv, -2);
            width = (u16)scratch->uv_u_extent;
            scratch->vertices[2].vx = edge_x;
            scratch->vertices[0].vx = edge_x;
            edge_x = edge_x + width;
            scratch->vertices[3].vx = edge_x;
            scratch->vertices[1].vx = edge_x;
        }
        {
            s16 edge_y = S8_AT(sprite_uv, -1);
            height = (u16)scratch->uv_v_extent;
            scratch->vertices[1].vy = edge_y;
            scratch->vertices[0].vy = edge_y;
            edge_y = edge_y + height;
            scratch->vertices[3].vy = edge_y;
            scratch->vertices[2].vy = edge_y;
        }

        RotTransSV(&scratch->vertices[0], (SVECTOR *)&quad->x0, transform_flags);
        RotTransSV(&scratch->vertices[1], (SVECTOR *)&quad->x1, transform_flags);
        RotTransSV(&scratch->vertices[2], (SVECTOR *)&quad->x2, transform_flags);
        RotTransSV(&scratch->vertices[3], (SVECTOR *)&quad->x3, transform_flags);

        {
            scratch->uv_u_extent += scratch->uv_u_start;
            scratch->uv_v_extent += scratch->uv_v_start;
            scratch->uv_v_extent <<= 8;
            scratch->uv_v_start <<= 8;
        }

        packet->clut = U16_AT(sprite_uv, 2);
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(u16 *)&packet->u0 = (u16)scratch->uv_v_start + (u16)scratch->uv_u_start;
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(u16 *)&packet->u1 = (u16)scratch->uv_v_start + (u16)scratch->uv_u_extent;
        packet->tpage = U16_AT(sprite_uv, 0);
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(u16 *)&packet->u2 = (u16)scratch->uv_v_extent + (u16)scratch->uv_u_start;
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(u16 *)&packet->u3 = (u16)scratch->uv_v_extent + (u16)scratch->uv_u_extent;

        if (packet->x0 > packet->x3) {
            u8 right_u = packet->u3;
            packet->u3 = right_u + 0xFF;
            packet->u1 = right_u;
        }
        if (packet->y0 > packet->y3) {
            u8 bottom_v = packet->v3;
            packet->v3 = bottom_v + 0xFF;
            packet->v2 = bottom_v;
        }
        ((GpuLinkTag *)&packet->tag)->len = 9;
        packet->code = 0x2C;

        {
            s32 pulse = (rsin((scene_sprite_wave_tick << 8) + (sprite_index << 6)) >> 6) + 0x80;
            s32 fade_shift = blend_step / 2;
            shade = pulse >> fade_shift;
        }
        packet->r0 = shade;
        colour = 0;
        if (scene_sprite_fade_ticks == 0) {
            colour = shade;
        }
        {
            POLY_FT4 *draw_quad = quad;
            quad++;
            packet->b0 = colour;
            packet->g0 = colour;
            packet->code |= 2;
            DrawPrim(draw_quad);
        }
        packet++;
        sprite_index++;
    } while (sprite_index < 0xE);

    PopMatrix();
    {
        render_state[0]->packetCursor = quad;
    }
}
s16 scene_sprite_wave_tick = 0;
u16 scene_sprite_cached_mode = 0;
u16 scene_sprite_fade_ticks = 0;
u8 scene_sprite_last_field = 0;
s16 scene_sprite_list_initialized = 0;
void * scene_sprite_list_base = 0;
