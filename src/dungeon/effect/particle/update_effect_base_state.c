#include "shared/audio_commands.h"
/* Staged target motion, layered sprite-chain drawing, and delayed sprite fading. */
#include "shared/object_node.h"
#include "dungeon/effect/particle/update_effect_base_state.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
/* Normal selector 9: ordinary typed entry pointer; gcc emits the state table. */
void (*const dungeon_1864800_entry)(void *, void *, void *) = run_fading_target_projectile;
#include "dungeon/effect/particle/update_effect_base_state.h"

/*
 * Returns the signed 16-bit difference between the target grid coordinate scaled by 64 and the
 * start adjusted by 32.
 */
static __inline__ s16 delta_axis(s8 target, u16 start) {
    s32 t = target;
    t <<= 6;
    start -= 32;
    return t - start;
}

/* Updates a staged effect, moves it toward its target, and emits particles. */
void run_fading_target_projectile(void *effect, void *motion, void *source_render) {
    void *owner;
    Vec3 delta;
    s32 target_timer;
    void *owner_start;
    void *owner_sprite;
    ObjectNodeHeader *spawned;
    void *particle_data;
    SpriteFrameState *sprite;
    s32 particles_left;
    S_81844800_5 *sprite_page;
    s16 state;
    s16 state_2;

    owner = ((S_81844800_0 *)effect)->unk_00;
    {
        owner_start = (u8 *)owner - 0x20;
    }
    state = ((S_81844800_0 *)effect)->unk_0A.s;
    owner_sprite = ((S_81844800_1_pre *)owner)[-1].unk_00;
    if (state != 0) {
        if (state < 5) {
            particles_left = 12;
            sprite_page = secondary_sprite;
            do {
                spawned = allocate_list_node(0x312, &scene_object_list_anchor.next);
                if (spawned != 0) {
                    particle_data = (u8 *)spawned + 0x20;
                    sprite = spawned->sprite;
                    spawned->update_callback = fade_effect_sprite_to_black;
                    ((S_81844800_14 *)(spawned->position))->unk_00.s =
                        ((S_81844800_3 *)motion)->unk_00.at00.v + (((rand() & 0x1FF) - 255) << 13);
                    ((S_81844800_14 *)(spawned->position))->unk_04.s =
                        ((S_81844800_3 *)motion)->unk_04.at00.v + (((rand() & 0x1FF) - 255) << 13);
                    ((S_81844800_14 *)(spawned->position))->unk_08.at00.v =
                        ((S_81844800_3 *)motion)->unk_08.at00.v + (((rand() & 0x1FF) - 255) << 10);

                    {
                        u16 flags = sprite->flags;
                        sprite->scale_y = 0x1000;
                        sprite->scale_x = 0x1000;
                        sprite->tpage_abr = 0x40;
                        sprite->unk_00 = sprite_page;
                        sprite->flags = flags | 0xC;
                        {
                            u32 texture_page = sprite_page->unk_04;
                            sprite->unk_04 = 0;
                            sprite->frame_ticks = 0;
                            sprite->color.word = 0x00404040;
                            sprite->source = texture_page;
                        }
                    }
                    ((S_81844800_2 *)spawned)->unk_20 = effect;
                    ((S_81844800_6 *)particle_data)->unk_48 = rand() & 3;
                    ((S_81844800_6 *)particle_data)->unk_4A = 8;
                    ((S_81844800_6 *)particle_data)->unk_4C = 0;
                }
                particles_left--;
            } while (particles_left >= 0);
        }
    }
    switch (((S_81844800_0 *)effect)->unk_0A.s) {
    case 0:
    {
        void *target;
        if ((((S_81844800_15 *)(((S_81844800_0 *)effect)->unk_04))->unk_00 & 0x80) == 0) {
            return;
        }
        target = scan_actor_along_heading(
            owner,
            ((S_81844800_7 *)owner_sprite)->unk_24,
            ((S_81844800_7 *)owner_sprite)->unk_25,
            ((S_81844800_1 *)owner)->unk_2A,
            (s16)get_definition_entry_byte_13(9));
        ((S_81844800_1 *)owner)->unk_60 = target;
        if (target == 0) {
            ((S_81844800_1 *)owner)->unk_72.s = ((S_81844800_7 *)owner_sprite)->unk_24;
            ((S_81844800_1 *)owner)->unk_73.s = ((S_81844800_7 *)owner_sprite)->unk_25;
        } else {
            sprite = ((S_81844800_8_pre *)target)[-1].unk_00;
            if ((sprite->flags & 0x8000) != 0) {
                if ((((S_81844800_9 *)source_render)->unk_14 & 0x8000) != 0) {
                    apply_attack_power_and_element_effects(
                        ((S_81844800_1 *)owner)->unk_60,
                        10,
                        ((S_81844800_0 *)effect)->unk_09,
                        4,
                        ((S_81844800_1 *)owner)->unk_2A,
                        owner,
                        2);
                    ((S_81844800_0 *)effect)->unk_0A.u = 5;
                    return;
                }
            }
            ((S_81844800_1 *)owner)->unk_72.s = sprite->tile_x;
            ((S_81844800_1 *)owner)->unk_73.s = sprite->tile_y;
        }
        {
            if (resolve_record_orientation_or_fallback(
                ((S_81844800_16 *)(((S_81844800_10 *)owner_start)->unk_0C))->unk_08,
                ((S_81844800_10 *)owner_start)->unk_0C, &delta, 0) == 0) {
                delta.z = 0;
                delta.y = 0;
                delta.x = 0;
            }
            {
                s32 target_x;
                ((S_81844800_3 *)motion)->unk_00.at02.v =
                    ((S_81844800_17 *)(((S_81844800_11 *)owner_start)->unk_08))->unk_02 + delta.x;
                ((S_81844800_3 *)motion)->unk_04.at02.v =
                    ((S_81844800_17 *)(((S_81844800_11 *)owner_start)->unk_08))->unk_06 + delta.y;
                ((S_81844800_3 *)motion)->unk_08.at02.v =
                    ((S_81844800_17 *)(((S_81844800_11 *)owner_start)->unk_08))->unk_0A + delta.z;
                ((S_81844800_0 *)effect)->unk_50.s = 8;
                {
                    target_x = ((S_81844800_1 *)owner)->unk_72.u;
                    {
                        ((S_81844800_3 *)motion)->unk_0C.at02.v =
                            delta_axis(target_x, ((S_81844800_3 *)motion)->unk_00.at02.v);
                    }
                }
                ((S_81844800_3 *)motion)->unk_0C.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
                {
                    target_x = ((S_81844800_1 *)owner)->unk_73.u;
                    {
                        ((S_81844800_3 *)motion)->unk_10.at02.v =
                            delta_axis(target_x, ((S_81844800_3 *)motion)->unk_04.at02.v);
                    }
                }
                ((S_81844800_3 *)motion)->unk_10.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
                ((S_81844800_3 *)motion)->unk_14.at02.v = (s16)sample_terrain_surface_height(
                    ((S_81844800_3 *)motion)->unk_00.at02.v,
                    ((S_81844800_3 *)motion)->unk_04.at02.v,
                    (s16)(((S_81844800_17 *)(((S_81844800_11 *)owner_start)->unk_08))->unk_0A - 48)) -
                    (((S_81844800_3 *)motion)->unk_08.at02.v + 176);
            }
            ((S_81844800_3 *)motion)->unk_14.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            ((S_81844800_0 *)effect)->unk_0A.u++;
            return;
        }
    }

    case 1:
        ((S_81844800_3 *)motion)->unk_00.at00.v += ((S_81844800_3 *)motion)->unk_0C.at00.v;
        ((S_81844800_3 *)motion)->unk_04.at00.v += ((S_81844800_3 *)motion)->unk_10.at00.v;
        ((S_81844800_3 *)motion)->unk_08.at00.v += ((S_81844800_3 *)motion)->unk_14.at00.v;
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            return;
        }
        {
            target_timer = 12;
            state = ((S_81844800_0 *)effect)->unk_0A.u;
            ((S_81844800_0 *)effect)->unk_50.s = target_timer;
            ((S_81844800_0 *)effect)->unk_0A.u = state + 1;
            return;
        }

    case 2:
    {
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            return;
        }
        if (((S_81844800_1 *)owner)->unk_60 == 0) {
            ((S_81844800_0 *)effect)->unk_50.s = 8;
            ((S_81844800_0 *)effect)->unk_0A.u = 5;
            return;
        }
        target_timer = 10;
        state = ((S_81844800_0 *)effect)->unk_0A.u;
        ((S_81844800_0 *)effect)->unk_50.s = target_timer;
        ((S_81844800_0 *)effect)->unk_0A.u = state + 1;
        return;
    }

    case 3:
        if ((((S_81844800_0 *)effect)->unk_52.s & 0x7FFF) == 0) {
            spawned = allocate_list_node(0x201, &scene_object_list_anchor.next);
            if (spawned != 0) {
                S_81844800_12 *burst_data = (u8 *)spawned + 0x20;
                spawned->update_callback = update_effect_base_state;
                register_node(spawned, draw_layered_vertical_sprite_chain);
                burst_data->unk_2A = 8;
                ((S_81844800_2 *)spawned)->unk_20 = effect;
                burst_data->unk_04 = ((S_81844800_3 *)motion)->unk_00.at02.v;
                burst_data->unk_06 = ((S_81844800_3 *)motion)->unk_04.at02.v;
                burst_data->unk_08 = ((S_81844800_3 *)motion)->unk_08.at02.v;
                ((S_81844800_0 *)effect)->unk_52.s++;
                burst_data->unk_2C = 0;
            }
        }
        if (((S_81844800_0 *)effect)->unk_50.u == 7 &&
            ((S_81844800_1 *)owner)->unk_60 != 0) {
            apply_attack_power_and_element_effects(
                ((S_81844800_1 *)owner)->unk_60,
                10,
                ((S_81844800_0 *)effect)->unk_09,
                4,
                ((S_81844800_1 *)owner)->unk_2A,
                owner,
                2);
        }
        particles_left = 20;
        do {
            spawned = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (spawned != 0) {
                particle_data = (u8 *)spawned + 0x20;
                sprite = spawned->sprite;
                spawned->update_callback = fade_effect_sprite_to_black;
                ((S_81844800_14 *)(spawned->position))->unk_00.u =
                    ((S_81844800_3 *)motion)->unk_00.at00.v;
                ((S_81844800_14 *)(spawned->position))->unk_04.u =
                    ((S_81844800_3 *)motion)->unk_04.at00.v;
                state = (rand() & 0x3F) - 176;
                ((S_81844800_14 *)(spawned->position))->unk_08.at02.v =
                    ((S_81844800_3 *)motion)->unk_08.at02.v - state;
                ((S_81844800_14 *)(spawned->position))->unk_0E = (rand() & 0xF) - 8;
                ((S_81844800_14 *)(spawned->position))->unk_12 = (rand() & 0xF) - 8;
                ((S_81844800_14 *)(spawned->position))->unk_16 = -(rand() & 7);
                {
                    u16 flags = sprite->flags;
                    sprite->scale_y = 0x1000;
                    sprite->scale_x = 0x1000;
                    sprite->tpage_abr = 0x60;
                    sprite->unk_00 = fading_sprite_entries;
                    sprite->flags = flags | 0xC;
                    {
                        u32 texture_page = ((u32)((SpriteSourceEntry *)fading_sprite_entries)->source);
                        sprite->unk_04 = 0;
                        sprite->frame_ticks = 0;
                        sprite->color.word = 0x00404040;
                        sprite->source = texture_page;
                    }
                }
                ((S_81844800_2 *)spawned)->unk_20 = effect;
                ((S_81844800_6 *)particle_data)->unk_48 = rand() & 3;
                ((S_81844800_6 *)particle_data)->unk_4A = 16;
                ((S_81844800_6 *)particle_data)->unk_4C = 0;
            }
            particles_left--;
        } while (particles_left >= 0);
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            return;
        }
        {
            u16 timer_reset = 8;
            state_2 = ((S_81844800_0 *)effect)->unk_0A.u;
            ((S_81844800_0 *)effect)->unk_50.s = timer_reset;
            ((S_81844800_0 *)effect)->unk_0A.u = state_2 + 1;
            return;
        }

    case 4:
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            return;
        }
        ((S_81844800_0 *)effect)->unk_0A.u++;
        return;

    case 5:
    {
        u16 effect_count;
        if ((((S_81844800_0 *)effect)->unk_52.u & 0x8000) != 0) {
            effect_count = ((S_81844800_0 *)effect)->unk_52.s & 0x7FFF;
            ((S_81844800_0 *)effect)->unk_52.s = effect_count;
            return;
        }
        g_dungeon_status.active_actor = 0;
        ((S_81844800_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

        return;
    }
}
#include "dungeon/effect/particle/update_effect_base_state.h"

/*
 * Advances the two position halfwords, sets successive color words to 0x00808080, then subtracts
 * 0x00202020 from all five. After the color countdown and a three-count delay, marks the effect
 * and global object flags for removal.
 */
void update_effect_base_state(s32 effect_or_count) {
    union { S_81844F2C_0 *v; } effect = {0};
    u32 *cursor;
    s32 i;
    u16 saved;
    u32 position;
    u32 step;
    s32 state;
    u8 *page;

    effect.v = (S_81844F2C_0 *)effect_or_count;
    page = effect.v->unk_00;
    ((S_81844F2C_1 *)page)->unk_52 |= 0x8000;
    position = effect.v->unk_04;
    step = effect.v->unk_0C;
    effect_or_count = effect.v->unk_2A.s;
    position += step;
    effect.v->unk_04 = position;
    position = effect.v->unk_06.s;
    step = effect.v->unk_0E;
    saved = effect.v->unk_2C.s;
    position += step;
    state = effect.v->unk_2C.u;
    effect_or_count -= 1;
    effect.v->unk_2A.u = effect_or_count;
    effect.v->unk_06.u = position;
    switch (state) {
    case 0:
        effect_or_count = 7 - (s16)effect_or_count;
        if (effect_or_count < 5) {
            ((u32 *)((u8 *)effect.v + 0x14))[effect_or_count] = 0x00808080;
        } else {
            for (i = 4; i >= 0; i--) {
                ((u32 *)((u8 *)effect.v + 0x14))[i] += 0xFFDFDFE0;
            }
        }
        if (effect.v->unk_2A.p > 0) {
            return;
        }
        effect.v->unk_2A.s = 3;
        effect.v->unk_2C.p += 1;
        return;
    case 1:
        if ((effect_or_count << 16) > 0) {
            return;
        }
        effect.v->unk_2C.p = saved + 1;
        return;
    case 2:
        ((S_81844F2C_0_pre *)effect.v)[-1].unk_00 |= 0x8000;
        page = (u8 *)0x80080000;
        ((S_81844F2C_4 *)page)->unk_14A0 |= 0x8000;
    }
}
#include "dungeon/effect/particle/update_effect_base_state.h"

#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u32)(_addr))
#define getaddr(p) (u32)(((P_TAG *)(p))->addr)
#define OTP(d) ((u32 *)((u8 *)render_state->draw_buffer + 0xB0) + (d))

#define LOAD_PTR(p) (*(u8 **)(p))
#define LOAD_U32(p) (*(u32 *)(p))
#define STORE_U32(p, v) (*(u32 *)(p) = (v))
#define STORE_U16(p, v) (*(u16 *)(p) = (v))
#define STORE_U8(p, v) (*(u8 *)(p) = (v))

/* Draw textured quads with randomized texture and horizontal jitter for each linked effect node. */
s32 draw_layered_vertical_sprite_chain(u8 *first_node)
{
    u32 uv_choices[4];
    Packed8 world_pos;
    Coord screen_coords[3];
    u8 *node;
    u8 *effect_node;
    u8 *next_link;
    GameWork *render_state;
    u8 *alloc_ctx;
    u8 *alloc_ctx_2;
    u8 *ot_entry;
    u8 *prim;
    Coord *screen_base;
    Coord *screen_pos;
    register Coord *scratch_or_height;
    s32 index_or_jitter;
    s32 depth_bucket;
    u16 half_width;
    u16 jitter_half_width;
    s32 tex_value;
    s32 tex_u_start;
    s32 tex_u_end;
    s32 random_value;
    u16 ot_or_coord;
    u16 vertex_x;
    u16 base_y;
    u16 tip_y;

    u32 tag_mask;
    node = first_node;
    render_state = &g_game_work;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_81845068). */
    do {
        uv_choices[0] = 0xA0;
        uv_choices[1] = 0x80;
    } while (0);
    screen_base = &screen_coords[0];
    uv_choices[2] = 0;
    uv_choices[3] = 0x20;

    do {
        effect_node = node;
        world_pos = *(Packed8 *)(node + 4);
        index_or_jitter = 0;
        scratch_or_height = &screen_coords[2];
        screen_pos = screen_base;
        do {
            depth_bucket = RotTransPers(&world_pos, screen_pos, scratch_or_height, scratch_or_height) - 8;
            screen_pos++;
            index_or_jitter++;
            *(u16 *)((u8 *)&world_pos + 4) =
                *(u16 *)((u8 *)&world_pos + 4) + 0xB0;
        } while (index_or_jitter < 2);

        scratch_or_height = (Coord *)(screen_coords[0].y - screen_coords[1].y);

        if ((u32)depth_bucket < 0x1E0) {
            alloc_ctx = render_state->draw_buffer;
            prim = LOAD_PTR(alloc_ctx + 0x8D0);
            LOAD_PTR(alloc_ctx + 0x8D0) = prim + 0x34;
            STORE_U32(prim + 4, 0x00808080);
            SetPolyFT4(prim);
            SetSemiTrans(prim, 1);
            STORE_U16(prim + 0x16, GetTPage(0, 0, 0x2C0, 0x100));
            STORE_U16(prim + 0x0E, GetClut(0xA0, 0x1F7));

            ((Scratch *)&screen_coords[2])->word = (s32)scratch_or_height / 6;
            vertex_x = screen_coords[0].x;
            half_width = ((Scratch *)&screen_coords[2])->half;
            vertex_x += half_width;
            STORE_U16(prim + 0x10, vertex_x);
            STORE_U16(prim + 8, vertex_x);
            vertex_x = screen_coords[0].x - half_width;
            STORE_U16(prim + 0x20, vertex_x);
            STORE_U16(prim + 0x18, vertex_x);
            base_y = screen_coords[0].y;
            STORE_U16(prim + 0x1A, base_y);
            STORE_U16(prim + 0x0A, base_y);
            tip_y = screen_coords[1].y;
            STORE_U16(prim + 0x22, tip_y);
            STORE_U16(prim + 0x12, tip_y);

            tex_value = 7 - *(s16 *)(effect_node + 0x2A);
            ((Scratch *)&screen_coords[2])->word = tex_value;
            ot_entry = (u8 *)(depth_bucket * 4);
            tex_u_end = (((Scratch *)&screen_coords[2])->byte & 3) << 5;
            tex_u_start = tex_u_end - 0x80;
            tex_u_end -= 0x61;
            STORE_U8(prim + 0x1C, tex_u_start);
            STORE_U8(prim + 0x0C, tex_u_start);
            STORE_U8(prim + 0x24, tex_u_end);
            STORE_U8(prim + 0x14, tex_u_end);
            tex_value = ((Scratch *)&screen_coords[2])->word >> 2;
            tex_value <<= 5;
            STORE_U8(prim + 0x25, tex_value);
            STORE_U8(prim + 0x1D, tex_value);
            STORE_U8(prim + 0x15, tex_value + 0x1F);
            STORE_U8(prim + 0x0D, tex_value + 0x1F);
            {
                u32 ot_tag;
                tag_mask = 0xFF000000;
                setaddr(prim, getaddr(OTP(depth_bucket)));
                ot_entry += (u32)render_state->draw_buffer;
                ot_tag = LOAD_U32(ot_entry + 0xB0);
                ot_tag &= tag_mask;
                STORE_U32(ot_entry + 0xB0, ot_tag | ((u32)prim & 0xFFFFFF));
            }
        }

        alloc_ctx_2 = render_state->draw_buffer;
        prim = LOAD_PTR(alloc_ctx_2 + 0x8D0);
        LOAD_PTR(alloc_ctx_2 + 0x8D0) = prim + 0x34;
        STORE_U32(prim + 4, 0x00161616);
        SetPolyFT4(prim);
        SetSemiTrans(prim, 1);
        STORE_U16(prim + 0x16, GetTPage(0, 3, 0x2C0, 0x100));
        STORE_U16(prim + 0x0E, GetClut((rand() & 0xF) << 4, 0x1F8));

        index_or_jitter = rand() & 1;
        tex_value = *(u8 *)&uv_choices[index_or_jitter];
        STORE_U8(prim + 0x1C, tex_value);
        STORE_U8(prim + 0x0C, tex_value);
        tex_value = *(u8 *)&uv_choices[index_or_jitter] + 0x5F;
        STORE_U8(prim + 0x24, tex_value);
        STORE_U8(prim + 0x14, tex_value);
        tex_value = *((u8 *)&uv_choices[index_or_jitter] + 8) + 0x20;
        STORE_U8(prim + 0x15, tex_value);
        STORE_U8(prim + 0x0D, tex_value);
        tex_value = *((u8 *)&uv_choices[index_or_jitter] + 8);
        STORE_U8(prim + 0x25, tex_value);
        STORE_U8(prim + 0x1D, tex_value);

        random_value = rand();
        index_or_jitter = (random_value % 64) - 0x20;
        ((Scratch *)&screen_coords[2])->word = (s32)scratch_or_height / 6;
        index_or_jitter = (index_or_jitter >> 1) + (index_or_jitter >> 2);
        ot_or_coord = screen_coords[0].x;
        jitter_half_width = ((Scratch *)&screen_coords[2])->half;
        vertex_x = ot_or_coord + jitter_half_width + index_or_jitter;
        STORE_U16(prim + 0x10, vertex_x);
        STORE_U16(prim + 8, vertex_x);
        vertex_x = screen_coords[0].x - jitter_half_width + index_or_jitter * 2;
        STORE_U16(prim + 0x20, vertex_x);
        STORE_U16(prim + 0x18, vertex_x);
        base_y = screen_coords[0].y;
        ot_entry = (u8 *)(depth_bucket * 4);
        STORE_U16(prim + 0x1A, base_y);
        STORE_U16(prim + 0x0A, base_y);
        tip_y = screen_coords[1].y;
        STORE_U16(prim + 0x22, tip_y);
        STORE_U16(prim + 0x12, tip_y);

        {
            u32 ot_tag;
            tag_mask = 0xFF000000;
            setaddr(prim, getaddr(OTP(depth_bucket)));
            ot_entry += (u32)render_state->draw_buffer;
            ot_tag = LOAD_U32(ot_entry + 0xB0);
            ot_tag &= tag_mask;
            STORE_U32(ot_entry + 0xB0, ot_tag | ((u32)prim & 0xFFFFFF));
        }

    } while (((next_link = LOAD_PTR(node - 8)) != 0) && ((node = next_link + 0x20), 1));

    return 0;
}
#include "dungeon/effect/particle/update_effect_base_state.h"
#include "shared/game_work.h"

/* Updates effect motion, waits for its timer, then fades its sprite to black. */
void fade_effect_sprite_to_black(void *effect, VecState *motion, SpriteFrameState *sprite) {
    void *owner = *(void **)effect;
    s32 z_velocity;
    s16 state;
    u16 timer;

    *(u16 *)((s8 *)owner + 0x52) |= 0x8000;

    z_velocity = motion->vz;
    if (z_velocity != 0) {
        z_velocity -= 0x20000;
    }
    motion->vz = z_velocity;
    motion->x += motion->vx;
    motion->y += motion->vy;
    motion->z += motion->vz;

    state = *(s16 *)((s8 *)effect + 0x4C);
    switch (state) {
    case 0:
        timer = *(u16 *)((s8 *)effect + 0x48) - 1;
        *(u16 *)((s8 *)effect + 0x48) = timer;
        if ((s16)timer <= 0) {
            register_node((s8 *)effect - 0x20, project_sprite_chain);
            *(u16 *)((s8 *)effect + 0x4C) += 1;
        }
        break;

    case 1:
        advance_sprite_animation_and_textures(sprite);
        if (sprite->flags & 0x6000) {
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
        }
        if (sprite->color.c.r <= *(s16 *)((s8 *)effect + 0x4A)) {
            sprite->color.word = 0;
            *(u16 *)((s8 *)effect - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        {
            u8 brightness = sprite->color.c.b - *(u8 *)((s8 *)effect + 0x4A);
            sprite->color.c.b = brightness;
            sprite->color.c.g = brightness;
            sprite->color.c.r = brightness;
        }
        break;
    }
}
