#include "shared/audio_commands.h"
/* Particle rendering, timed display slots, and an actor tint and particle sequence. */
#include "dungeon/effect/particle/advance_object_spawning_displays_high.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"

void (*const dungeon_1960800_entry)(void *, void *, void *) = (void (*)(void *, void *, void *))advance_actor_tint_particle_sequence;
const RectTable high_particle_texture_rects = {{{832,320,64,64},{832,384,64,64},{832,448,64,64},{896,256,64,64},{896,320,64,64},{896,384,64,64},{896,448,64,64},{832,256,64,64}}};

void fade_tinted_display_sprite(void *effect, void *unused, void *primitive)
;
/* Advance the effect fade and mark it finished when its countdown expires. */
extern s32 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, s32, s32);
extern s32 rand(void);
extern u8 D_80025704[16];
extern u8 D_80025710[16];
extern u8 D_800256EC[16];
extern u8 timed_projectile_sprite_entries[];
extern u8 high_particle_sprite_entries[];
extern u8 effect_sprite_sources[];
extern s32 get_sprite_attachment_vector(void *, void *, void *, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern s32 rand(void);
extern s32 read_sound_mode_blocking_status(s32);

/* Fades a red-tinted sprite, adjusts its offset, and clears the owner's indexed slot when the
   countdown ends. */
void fade_tinted_display_sprite(void *effect, void *unused, void *primitive) {
    s32 shade;
    u16 frames_left;

    frames_left = ((u16)((EntityRec *)effect)->facing) - 1;
    shade = (s32)((s32)(frames_left << 0x10) >> 9) / (s16)((EntityRec *)effect)->unk_2C;
    tint_particle_effect_updated = 1;
    ((EntityRec *)effect)->facing = frames_left;
    ((S_81940800_1 *)primitive)->unk_0E = (s8)shade;
    ((S_81940800_1 *)primitive)->unk_0D = (s8)shade;
    ((S_81940800_1 *)primitive)->unk_0C = (s8)(shade + 0x10);
    if (((S_81940800_1 *)primitive)->unk_06 >= -6) {
        ((S_81940800_1 *)primitive)->unk_06 = (s16)((u16)((S_81940800_1 *)primitive)->unk_06 - 2);
    }
    if ((s16)((u16)((EntityRec *)effect)->facing) <= 0) {
        ((S_81940800_2 *)(((((EntityRec *)effect)->unk_32 * 2) + ((s32)((EntityRec *)effect)->target))))->unk_46 = 0;
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_81940800_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}

/* Creates a display effect in a free slot and expires the owner when its timer ends. */
void spawn_free_slot_display_effect(void *owner) {
    s16 center[2];
    RectTable rect_table;
    u8 *copy_src;
    u8 *copy_dst;
    u8 *copy_end;
    s16 slot;
    s32 rect_offset;
    Rect16 *rect;
    ObjectNodeHeader *effect;
    u8 *effect_work;
    SpriteFrameState *display;
    ObjectPosition *vector_src;
    ObjectPosition *vector_dst;
    u16 timer;

    copy_dst = (u8 *)&rect_table;
    copy_src = (u8 *)&high_particle_texture_rects;
    if ((u32)copy_src & 3) {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(PackedBlock *)copy_dst = *(PackedBlock *)copy_src;
            copy_src += sizeof(PackedBlock);
            copy_dst += sizeof(PackedBlock);
        } while (copy_src != copy_end);
    } else {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(AlignedBlock *)copy_dst = *(AlignedBlock *)copy_src;
            copy_src += sizeof(AlignedBlock);
            copy_dst += sizeof(AlignedBlock);
        } while (copy_src != copy_end);
    }

    for (slot = 0; slot < 8; slot++) {
        if ((*(s16 *)((u8 *)owner + 0x46 + (((s32)slot << 16) >> 15))) == 0) {
            break;
        }
    }

    if (slot != 8) {
        (*(s16 *)((u8 *)owner + 0x46 + slot * 2)) = 1;
        rect_offset = (s32)slot << 3;
        rect = (Rect16 *)((u8 *)&rect_table + rect_offset);
        center[0] = rect->x + ((s16)rect->w >> 1);
        center[1] = rect->y + 0x30;
        draw_transformed_sprite_with_clip_rect(primary_actor_record, rect, center, 1, 1);

        effect = allocate_flagged_object_node(0x212);
        if (effect != 0) {
            effect_work = (u8 *)effect + 0x20;
            ((S_80024104_0 *)effect_work)->unk_2A = 7;
            ((S_80024104_0 *)effect_work)->unk_2C = 7;
            ((S_80024104_0 *)effect_work)->unk_32 = slot;
            ((S_80024104_0 *)effect_work)->unk_60 = owner;
            effect->update_callback = fade_tinted_display_sprite;
            register_node(effect, project_sprite_chain);

            display = effect->sprite;
            display->depth_bias = 4;
            display->flags &= 0xFFF3;

            vector_src = ((ObjectNodeHeader *)((u8 *)primary_actor_record - 0x20))->position;
            vector_dst = effect->position;
            vector_dst->x.v = ((s32 *)vector_src)[0];
            vector_dst->y.v = ((s32 *)vector_src)[1];
            vector_dst->z.v = ((s32 *)vector_src)[2];

            display = effect->sprite;
            display->scale_y = 0x1000;
            display->scale_x = 0x1000;
            display->color.c.b = 0x80;
            display->color.c.g = 0x80;
            display->color.c.r = 0x80;

            *(PackedVec3 *)((u8 *)effect + 0x92) = tint_particle_sprite_data;
            display->source = (u8 *)effect + 0x92;
            ((S_80024104_0 *)effect_work)->unk_7A = (u8)rect->x - 0x40;
            ((S_80024104_0 *)effect_work)->unk_7B = (u8)rect->y;
        }
    }

    timer = (*(u16 *)((u8 *)owner + 0x2A)) - 1;
    (*(u16 *)((u8 *)owner + 0x2A)) = timer;
    if ((s16)timer <= 0) {
        (*(u16 *)((u8 *)owner + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* cfail-repair: tf7-phase1-cache-v3 */

/* Creates an object linked to the source with its position and default part data. */
void advance_object_spawning_displays_high(void *source, void *unused_position, void *unused_sprite) {
    ObjectPosition *position;
    SpriteFrameState *part;
    ObjectNodeHeader *object;
    S_800243D8_0 *state;
    S_800243D8_3 *source_position;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        state->unk_2A = 0xB;
        state->unk_60 = source;
        (object->update_callback) = &spawn_free_slot_display_effect;
        register_node(object, project_sprite_chain);
        part = object->sprite;
        part->tpage_abr = 0x20;
        part->depth_bias = 0;
        part->flags = (u16) (part->flags | 0xC);
        source_position = ((S_800243D8_1_pre *)source)[-1].unk_00;
        position = object->position;
        position->x.v = (s32) source_position->unk_00;
        position->y.v = (s32) source_position->unk_04;
        position->z.v = (s32) source_position->unk_08;
        part = object->sprite;
        part->scale_y = 0;
        part->scale_x = 0;
        part->color.c.b = 0;
        part->color.c.g = 0;
        part->color.c.r = 0;
        (*(Copy12 *)((u8 *)object + 0x92)) = *(Copy12 *)&tint_particle_sprite_data;
        part->source = (void *) (((void *)object) + 0x92);
    }
}

/*
 * Projects linked points and queues shaded tiles with draw-mode packets.
 *
 * Shaded tile primitive (code 0x6A, 3 words).
 */
s32 draw_brightness_scaled_point_chain(PointRecord *first_point, ObjectPosition *first_position)
{
    PointRecord *point = first_point;
    ObjectPosition *position = first_position;
    GameWork *render_state = &g_game_work;
    GpuContext *render_ctx = (GpuContext *)render_state->draw_buffer;
    u8 *packet_start;
    Scratch800244E4 *scratch =
        (Scratch800244E4 *)0x1F800000;
    PointPacket *tile;
    PointPacket *draw_mode;
    s32 color_value;
    s32 draw_page;
    ObjectNodeHeader *next_node;

    packet_start = render_ctx->packetCursor;
    scratch->ot = (u32 *)&render_ctx->orderTag;
    scratch->cursor = packet_start;

    for (;;) {
        tile = (PointPacket *)scratch->cursor;
        scratch->x = position->x.w.i;
        scratch->y = position->y.w.i;
        scratch->z = position->z.w.i;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = RotTransPers(scratch, &tile->data,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            *(u32 *)&tile->r = point->color;

            color_value = (s32)tile->r * point->brightness;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->r = color_value >> 7;

            color_value = (s32)tile->g * point->brightness;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->g = color_value >> 7;

            color_value = (s32)tile->b * point->brightness;
            tile->b = (color_value / 128);

            ((u8 *)tile)[3] = 2;
            tile->code = 0x6A;
            ((GpuLinkTag *)&tile->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = GetTPage(0, 1, 0, 0);
            SetDrawMode(draw_mode, 0, 0, (u16)draw_page, 0);

            ((GpuLinkTag *)&draw_mode->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)draw_mode;
        }

        /* the preceding header's +0x18 holds the next node */
        next_node = ((ObjectNodeHeader *)point - 1)->chain_next;
        if (next_node != 0) {
            point = (PointRecord *)(next_node + 1);
            position = next_node->position;
            continue;
        }

        break;
    }

    ((GpuContext *)render_state->draw_buffer)->packetCursor = scratch->cursor;
    return 0;
}

// Decrease position and timer, setting entity and global flags when the timer expires.
void lower_timed_effect_position(Entity *entity, State *state)
{
    s16 remainingTimer;

    state->position -= 0x18000;
    tint_particle_effect_updated = 1;
    remainingTimer = entity->timer - 8;
    entity->timer = remainingTimer;
    if (remainingTimer <= 0) {
        ((u16 *)entity)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Spawn and initialize an object at a randomized offset from its parent. */
void handle_spawn_initialize_randomized_offset_parent(Object *source, s32 state_14_value, s32 state_08_value, s32 state_32_value,
                   s16 x_offset, s16 y_offset, s16 z_offset) {
    Object *parent = source;
    s16 held_x_offset = x_offset;
    s16 held_y_offset = y_offset;
    s16 held_z_offset = z_offset;
    s32 state_14 = state_14_value;
    ObjectNodeHeader *spawned;
    Data *position;
    u8 *state;
    s32 jitter;

    spawned = allocate_list_node(0x211, (ObjectNodeHeader **)parent);
    if (spawned != 0) {
        spawned->update_callback = lower_timed_effect_position;
        jitter = rand();
        (*(Data * *)&spawned->position)->x =
            *(u16 *)&((ObjectPosition *)parent->data)->x.w.i +
            (jitter & 0xF) + (held_x_offset - 8);
        jitter = rand();
        (*(Data * *)&spawned->position)->y =
            *(u16 *)&((ObjectPosition *)parent->data)->y.w.i +
            (jitter & 0xF) + (held_y_offset - 8);
        state = (u8 *)spawned + 0x20;
        jitter = rand();
        position = *(Data * *)&spawned->position;
        position->z =
            *(u16 *)&((ObjectPosition *)parent->data)->z.w.i +
            (jitter & 0x1F) + (held_z_offset - 0x10);
        *(s16 *)(state + 0x14) = state_14;
        *(s16 *)(state + 0x32) = state_32_value;
        register_node(spawned, draw_brightness_scaled_point_chain);
        *(s32 *)(state + 8) = state_08_value;
    }
}

/* Advance animation values and set completion flags when the countdown expires. */
void expand_rotating_countdown_sprite(void *countdownState, s32 unused, void *animationState)
{
    s32 remainingTicks;

    *(u16 *)((u8 *)countdownState + 0x2A) =
        (u16)(*(u16 *)((u8 *)countdownState + 0x2A) - 1);
    *(u16 *)((u8 *)animationState + 0x1C) =
        (u16)(*(u16 *)((u8 *)animationState + 0x1C) + 0x320);
    *(u16 *)((u8 *)animationState + 0x1E) =
        (u16)(*(u16 *)((u8 *)animationState + 0x1E) + 0x320);
    *(u16 *)((u8 *)animationState + 0x1A) =
        (u16)(*(u16 *)((u8 *)animationState + 0x1A) + 0x190);
    remainingTicks = *(s16 *)((u8 *)countdownState + 0x2A);
    tint_particle_effect_updated = 1;
    if (remainingTicks <= 0) {
        *(u16 *)((u8 *)countdownState - 2) =
            (u16)(*(u16 *)((u8 *)countdownState - 2) | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}

// Decrement the object's timer, call its handler, and set expiry flags when the timer runs out.
void advance_timed_effect_animation(DungeonObject *object, s32 unused, void *handlerContext)
{
    tint_particle_effect_updated = 1;
    object->timer--;
    advance_sprite_animation_and_textures(handlerContext);
    if (object->timer <= 0) {
        ((u16 *)object)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Decrements the object counter and sets flags when it reaches zero. */
void decrement_object_counter(void *object)
{
    u8 *object_bytes = object;
    u16 counter;

    counter = *(u16 *)(object_bytes + 42);
    tint_particle_effect_updated = 1;
    counter--;
    *(u16 *)(object_bytes + 42) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(object_bytes - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* MECHANISM: A long-lived u8 base preserves the retail may-alias load-delay nops.
   Loading the counter before the global store lets that store cover load latency
   and naturally yields the a1 pointer, a0 constant, and v1 counter roles. */

/* Create an object with copied position and packed data, and initialize its rendering state. */
void *create_packed_sprite_effect(void *source, void *unused_1, void *unused_2, void *packed_data, s32 render_param, s32 render_x,
    s32 render_y, s32 render_mode) {
    s16 render_param_copy;
    ObjectPosition *position;
    SpriteFrameState *render_state;
    S_800249F0_0 *state;
    ObjectNodeHeader *object;
    S_800249F0_4 *source_position;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        state->unk_2A = 0x3C;
        (object->update_callback) = &decrement_object_counter;
        register_node(object, project_sprite_chain);
        render_state = object->sprite;
        ((S_800249F0_1 *)render_state)->unk_14 |= 0xC;
        render_param_copy = render_param;
        ((S_800249F0_1 *)render_state)->unk_10 = (s16) (render_param_copy << 5);
        ((S_800249F0_1 *)render_state)->unk_14 |= 0x80;
        source_position = ((S_800249F0_2_pre *)source)[-1].unk_00;
        position = object->position;
        position->x.v = (s32) source_position->unk_00;
        position->y.v = (s32) source_position->unk_04;
        position->z.v = (s32) source_position->unk_08;
        render_state = object->sprite;
        ((S_800249F0_5 *)render_state)->unk_1C = (s16) render_x;
        ((S_800249F0_5 *)render_state)->unk_1E = (s16) render_y;
        ((S_800249F0_5 *)render_state)->unk_0E = 0x80;
        ((S_800249F0_5 *)render_state)->unk_0D = 0x80;
        ((S_800249F0_5 *)render_state)->unk_0C = (s8) render_mode;
        (*(Packed12 *)((u8 *)object + 0x92)) = *(Packed12 *)packed_data;
        ((S_800249F0_5 *)render_state)->unk_08 = (void *) (((void *)object) + 0x92);
        return state;
    } else {
        return NULL;
    }
}

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

/* Masks the random value to seven bits and forces bits 0x60 in the result. */
static __inline__ u8 particle_alpha_from_random(s32 random_bits)
{
    return (random_bits & 0x7F) | 0x60;
}

/* Updates a dungeon effect, spawning particles and fading the actor model through its states. */
void advance_actor_tint_particle_sequence(TintParticleSequence *effect, void *effect_pos, void *effect_data)
{
    ObjectPosition *position = effect_pos;
    void *effect_context = effect_data;
    void *burst_tail;
    u32 sprite_rgb;
    u32 neutral_color;
    ObjectNodeHeader *model_color;
    void *animation_m;
    s32 enabled;
    SpriteFrameState *sprite;
    ObjectNodeHeader *particle;
    ObjectPosition *world_offset;
    u8 *spawn_data;
    u8 *particle_script;
    s32 particle_index;
    s32 initial_color;
    s32 particle_color;
    void *init_object;
    s32 state;
    s16 timer;
    u16 old_state;
    s32 particle_level;
    s32 particle_x;
    s16 texture_rect[6];
    s32 component;
    u32 bits;
    u32 bits_2;
    u32 mode_a = 0;
    u32 mode_b = 0;
    u32 mode_c = 0;

    effect->tick = (u16)(effect->tick + 1);
    state = effect->state.s;
    effect_context = effect_data;
    switch (state) {
    case 0:
        enabled = 1;
        initial_color = 0x00808080;
        F(primary_actor_record, s32, 0xF4) = 0;
        F(((u8 *)(&reference_tile_object)), u16, 6) = 6;
        effect->display_a = create_packed_sprite_effect(effect, position, effect_context, D_80025704,
                                                     enabled, 0x1000, 0x1000, initial_color);
        effect->display_b = create_packed_sprite_effect(effect, position, effect_context, D_80025710,
                                                     2, 0xE00, 0xE00, 0x00E0E0E0);
        old_state = effect->state.u;
        F(&tint_particle_effect_updated, u16, 0) = (u16)enabled;
        effect->state.u = (u16)(old_state + 1);

    case 1:
        if ((effect->animation->flags & 0x80) == 0) {
            return;
        }
        init_object = effect;
        {
            void *actor = primary_actor_record;
            effect->timer.u = (u16)((u32)(0x14));
            F(actor, u16, 0xA6) = (u16)(F(actor, u16, 0xA6) - 1);
            F(actor, u8, 0xA8) = effect->variant;
        }
        component = F(primary_actor_record, u16, 0x2A);
        effect->state.u = (u16)(effect->state.u + 1);
        effect->facing.u = (u16)component;
        advance_object_spawning_displays_high(init_object, position, effect_context);
        if (effect->display_b != 0) {
            texture_rect[0] = 0x340;
            texture_rect[1] = 0x100;
            texture_rect[2] = 0x40;
            texture_rect[3] = 0x40;
            texture_rect[4] = 0x360;
            texture_rect[5] = 0x120;
            draw_transformed_sprite_with_clip_rect(effect->display_b, texture_rect, &texture_rect[4], 0, 1);
        }
        if (effect->display_a == 0) {
            return;
        }
        {
            texture_rect[0] = 0x340;
            texture_rect[1] = 0x100;
            texture_rect[2] = 0x40;
            texture_rect[3] = 0x40;
            texture_rect[4] = 0x360;
            texture_rect[5] = 0x120;
            draw_transformed_sprite_with_clip_rect(effect->display_a, texture_rect, &texture_rect[4], 1, 1);
        }
        return;

    case 2:
        timer = (s16)((u16)effect->timer.u - 1);
        effect->timer.u = (u16)timer;
        if (timer <= 0) {
            effect->timer.u = 0x10;
            effect->state.u = (u16)(effect->state.u + 1);
        }
        if (effect->timer.s == 0x13) {
            if (read_sound_mode_blocking_status(4) != 2) {
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            } else {
                play_sound_if_enabled(AUDIO_RESUME_CD);
            }
        }
        if (effect->timer.s < 11) {
            u8 *dungeon = ((u8 *)(&reference_tile_object));
            if (get_sprite_attachment_vector(F(dungeon, void *, 8), dungeon,
                              (u8 *)effect + 0xC, 0) != 0) {
                particle_index = 0;
                do
                {
                    sprite_rgb = (u32)rand();
                    particle_color = 0x200000;
                    sprite_rgb = particle_alpha_from_random(sprite_rgb);
                    particle_level = effect->facing.s;
                    particle_x = effect->attachment_x.s;
                    particle_color |= 0x20F0;
                    handle_spawn_initialize_randomized_offset_parent((u8 *)primary_actor_record - 0x20,
                                  particle_level, particle_color,
                                  sprite_rgb,
                                  particle_x, effect->attachment_y.s,
                                  effect->attachment_z.s);
                    particle_index++;
                }
                while (particle_index < 4);
                particle_index = 0;
                spawn_data = advance_timed_effect_animation;
                world_offset = &view_reference_entity;
                sprite_rgb = 0x80;
                do {
                    particle = allocate_flagged_object_node(0x212);
                    if (particle != 0) {
                        F(particle, s16, 0x4A) = 8;
                        particle->update_callback = spawn_data;
                        register_node(particle, project_sprite_chain);
                        sprite = particle->sprite;
                        sprite->flags = (u16)(sprite->flags | 0xC);
                        position = particle->position;
                        if ((rand() & 1) == 0) {
                            sprite->flags = (u16)(sprite->flags | 1);
                        }
                        position->x.w.i = effect->attachment_x.u;
                        position->y.w.i = effect->attachment_y.u;
                        position->z.w.i = effect->attachment_z.u;
                        position->x.w.i = (u16)(*(u16 *)&position->x.w.i + *(u16 *)&world_offset->x.w.i);
                        position->y.w.i = (u16)(*(u16 *)&position->y.w.i + *(u16 *)&world_offset->y.w.i);
                        position->z.w.i = (u16)(*(u16 *)&position->z.w.i + *(u16 *)&world_offset->z.w.i);
                        if (particle_index != 0) {
                            bits = (u32)rand() & 0x1F;
                            component = *(u16 *)&position->x.w.i;
                            component -= 0x10;
                            component += bits;
                            position->x.w.i = (u16)component;
                            bits = (u32)rand() & 0x1F;
                            component = *(u16 *)&position->y.w.i;
                            component -= 0x10;
                            component += bits;
                            position->y.w.i = (u16)component;
                            bits = (u32)rand() & 0x1F;
                            component = *(u16 *)&position->z.w.i;
                            component -= 0x10;
                            component += bits;
                            position->z.w.i = (u16)component;
                        }
                        sprite = particle->sprite;
                        {
                            void *anim_sprite = sprite;
                            if (particle_index != 0) {
                                void *animation = timed_projectile_sprite_entries;
                                void *anim_context = 0;
                                mode_c = 0x20;
                                sprite->tpage_abr = mode_c;
                                sprite->scale_y = 0x1000;
                                sprite->scale_x = 0x1000;
                                select_record_entry_and_value(anim_sprite, animation, anim_context);
                            } else {
                                void *animation = high_particle_sprite_entries;
                                void *anim_context = 0;
                                sprite->scale_y = 0x2000;
                                sprite->scale_x = 0x2000;
                                sprite->tpage_abr = (u16)0x20;
                                select_record_entry_and_value(anim_sprite, animation, anim_context);
                            }
                        }
                        sprite->color.c.b = (u8)sprite_rgb;
                        sprite->color.c.g = (u8)sprite_rgb;
                        sprite->color.c.r = (u8)sprite_rgb;
                    }
                    particle_index++;
                } while (particle_index < 4);
                if (effect->timer.s < 6) {
                    effect->midpoint_x.s =
                        (effect->attachment_x.s + effect->previous_x.s) / 2;
                    effect->midpoint_y.s =
                        (effect->attachment_y.s + effect->previous_y.s) / 2;
                    effect->midpoint_z.s =
                        (effect->attachment_z.s + effect->previous_z.s) / 2;
                    particle_index = 0;
                    do {
                        sprite_rgb = (u32)rand();
                        particle_color = 0x200000;
                        sprite_rgb = particle_alpha_from_random(sprite_rgb);
                        particle_level = effect->facing.s;
                        particle_x = effect->midpoint_x.s;
                        particle_color |= 0x20F0;
                        handle_spawn_initialize_randomized_offset_parent((u8 *)primary_actor_record - 0x20,
                                      particle_level, particle_color,
                                      sprite_rgb,
                                      particle_x, effect->midpoint_y.s,
                                      effect->midpoint_z.s);
                        particle_index++;
                    } while (particle_index < 4);
                    particle_index = 0;
                    spawn_data = advance_timed_effect_animation;
                    world_offset = &view_reference_entity;
                    sprite_rgb = 0x80;
                    do
                    {
                        particle = allocate_flagged_object_node(0x212);
                        if (particle != 0) {
                            F(particle, s16, 0x4A) = 8;
                            particle->update_callback = spawn_data;
                            register_node(particle, project_sprite_chain);
                            sprite = particle->sprite;
                            sprite->flags = (u16)(sprite->flags | 0xC);
                            position = particle->position;
                            if ((rand() & 1) == 0) {
                                sprite->flags = (u16)(sprite->flags | 1);
                            }
                            position->x.w.i = effect->midpoint_x.u;
                            position->y.w.i = effect->midpoint_y.u;
                            position->z.w.i = effect->midpoint_z.u;
                            position->x.w.i = (u16)(*(u16 *)&position->x.w.i + *(u16 *)&world_offset->x.w.i);
                            position->y.w.i = (u16)(*(u16 *)&position->y.w.i + *(u16 *)&world_offset->y.w.i);
                            position->z.w.i = (u16)(*(u16 *)&position->z.w.i + *(u16 *)&world_offset->z.w.i);
                            if (particle_index != 0) {
                                bits = (u32)rand() & 0xF;
                                component = *(u16 *)&position->x.w.i;
                                component -= 8;
                                component += bits;
                                position->x.w.i = (u16)component;
                                bits = (u32)rand() & 0xF;
                                component = *(u16 *)&position->y.w.i;
                                component -= 8;
                                component += bits;
                                position->y.w.i = (u16)component;
                                bits = (u32)rand() & 0x1F;
                                component = *(u16 *)&position->z.w.i;
                                component -= 0x10;
                                component += bits;
                                position->z.w.i = (u16)component;
                                sprite = particle->sprite;
                            } else {
                                sprite = particle->sprite;
                            }
                            {
                                neutral_color = (s32)(sprite);
                                if (particle_index != 0) {
                                    void *animation = timed_projectile_sprite_entries;
                                    void *anim_context = 0;
                                    mode_a = 0x20;
                                    F((void *)neutral_color, u16, 0x10) = mode_a;
                                    F((void *)neutral_color, u16, 0x1E) = 0x1000;
                                    F((void *)neutral_color, u16, 0x1C) = 0x1000;
                                    F((void *)neutral_color, u8, 0xE) = (u8)sprite_rgb;
                                    F((void *)neutral_color, u8, 0xD) = (u8)sprite_rgb;
                                    F((void *)neutral_color, u8, 0xC) = (u8)sprite_rgb;
                                    select_record_entry_and_value((void *)neutral_color, animation, anim_context);
                                } else {
                                    void *animation = high_particle_sprite_entries;
                                    void *anim_context = 0;
                                    F((void *)neutral_color, u16, 0x1E) = 0x2000;
                                    F((void *)neutral_color, u16, 0x1C) = 0x2000;
                                    mode_b = 0x20;
                                    F((void *)neutral_color, u16, 0x10) = mode_b;
                                    F((void *)neutral_color, u8, 0xE) = (u8)sprite_rgb;
                                    F((void *)neutral_color, u8, 0xD) = (u8)sprite_rgb;
                                    F((void *)neutral_color, u8, 0xC) = (u8)sprite_rgb;
                                    select_record_entry_and_value((void *)neutral_color, animation, anim_context);
                                }
                            }
                        }
                        particle_index++;
                    }
                    while (particle_index < 4);
                }
                {
                    bits = effect->attachment_x.u;
                    component = effect->attachment_y.u;
                    neutral_color = effect->attachment_z.u;
                    effect->previous_x.u = (u16)bits;
                    effect->previous_y.u = (u16)component;
                    effect->previous_z.u = (u16)neutral_color;
                }
            }
        }

        if (effect->timer.s != 11) {
            return;
        }
        particle = allocate_flagged_object_node(0x212);
        if (particle == 0) {
            return;
        }
        init_object = particle;
        animation_m = project_sprite_chain;
        F(particle, s16, 0x4A) = 6;
        particle->update_callback = (void *)((u32)&expand_rotating_countdown_sprite);
        register_node(init_object, animation_m);
        bits = 0x20;
        sprite = particle->sprite;
        {
            void *actor_position;
            F(sprite, u16, 0x10) = (u16)bits;
            F(sprite, u16, 6) = 8;
            actor_position = primary_actor_record;
            F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
            position = particle->position;
            actor_position = ((ObjectNodeHeader *)((u8 *)actor_position - 0x20))->position;
            position->x.v = F(actor_position, u32, 0);
            position->y.v = F(actor_position, u32, 4);
            F(position, u32, 8) = F(actor_position, u32, 8);
        }
        {
            u8 *dungeon = ((u8 *)(&reference_tile_object));
            if (get_sprite_attachment_vector(F(dungeon, void *, 8), dungeon,
                              (u8 *)effect + 0xC, 0) != 0) {
                *(u32 *)&position->x.v += (u32)(effect->attachment_x.s << 16);
                *(u32 *)&position->y.v += (u32)(effect->attachment_y.s << 16);
                *(u32 *)&position->z.v += (u32)(effect->attachment_z.s << 16);
            }
        }
        sprite = particle->sprite;
        sprite->scale_y = 0x80;
        sprite->scale_x = 0x80;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        *(EffectPacked12 *)((u8 *)particle + 146) = *(EffectPacked12 *)D_800256EC;
        sprite->source = (u8 *)particle + 146;
        return;

    case 3:
        if (effect->timer.s >= 13) {
            particle_index = 0;
            particle_script = advance_timed_effect_animation;
            spawn_data = ((u8 *)(&reference_tile_object));
            world_offset = &view_reference_entity;
            do {
                particle = allocate_flagged_object_node(0x212);
                if (particle != 0) {
                    burst_tail = (u8 *)particle + 0x20;
                    F(burst_tail, s16, 0x2A) = 12;
                    particle->update_callback = particle_script;
                    register_node(particle, project_sprite_chain);
                    sprite = particle->sprite;
                    sprite->flags = (u16)(sprite->flags | 0xC);
                    sprite->tpage_abr = 0x60;
                    if ((rand() & 1) == 0) {
                        sprite->flags = (u16)(sprite->flags | 1);
                    }
                    position = particle->position;
                    if (get_sprite_attachment_vector(F(spawn_data, void *, 8), spawn_data, (u8 *)effect + 0xC, 0) != 0) {
                        effect->attachment_x.u = (u16)(effect->attachment_x.u + *(u16 *)&world_offset->x.w.i);
                        effect->attachment_y.u = (u16)(effect->attachment_y.u + *(u16 *)&world_offset->y.w.i);
                        effect->attachment_z.u = (u16)(effect->attachment_z.u + *(u16 *)&world_offset->z.w.i);
                        if (particle_index != 0) {
                            F(burst_tail, s16, 0x2A) = 8;
                            sprite->tpage_abr = 0x20;
                            sprite_rgb = (u32)rand();
                            bits = sprite_rgb & 0x3F;
                            component = effect->attachment_x.u;
                            component -= 0x20;
                            component += bits;
                            effect->attachment_x.u = (u16)component;
                            sprite_rgb = (u32)rand();
                            bits = sprite_rgb & 0x3F;
                            component = effect->attachment_y.u;
                            component -= 0x20;
                            component += bits;
                            effect->attachment_y.u = (u16)component;
                            sprite_rgb = (u32)rand();
                            bits = sprite_rgb & 0x3F;
                            component = effect->attachment_z.u;
                            component -= 0x20;
                            component += bits;
                            effect->attachment_z.u = (u16)component;
                        }
                    }
                    position->x.w.i = effect->attachment_x.u;
                    position->y.w.i = effect->attachment_y.u;
                    position->z.w.i = effect->attachment_z.u;
                    sprite = particle->sprite;
                    sprite->scale_y = 0x1000;
                    sprite->scale_x = 0x1000;
                    sprite->color.c.b = 0x80;
                    sprite->color.c.g = 0x80;
                    sprite->color.c.r = 0x80;
                    if (particle_index != 0) {
                        select_record_entry_and_value(sprite, high_particle_sprite_entries, 0);
                    } else {
                        select_record_entry_and_value(sprite, effect_sprite_sources, 0);
                    }
                }
                particle_index++;
            } while (particle_index < 4);
        }
        {
            s32 fade;
            animation_m = F(primary_actor_record, void *, 0x60);
            if (animation_m != 0) {
                F(animation_m, u32, 0x1C) |= 0x10000000;
                {
                    model_color = ((ObjectNodeHeader *)((u8 *)animation_m - 0x20))->sprite;
                    fade = effect->timer.s * 0x7F;
                    if (fade < 0) {
                        fade += 15;
                    }
                    F(model_color, s8, 0xC) = (s8)((fade >> 4) - 0x80);
                    fade = (16 - effect->timer.s) << 3;
                    F(model_color, s8, 0xE) = (s8)fade;
                    F(model_color, s8, 0xD) = (s8)fade;
                }
            }
        }
        if ((F(((u8 *)(&reference_tile_object)), u16, 0x14) & 0x8000) == 0) {
            effect->timer.u = (u16)(effect->timer.u - 1);
            if (effect->timer.s >= 0) {
                return;
            }
        }
        effect->state.u = 4;
        return;

    case 4:
        if (F(&tint_particle_effect_updated, s16, 0) == 0) {
            animation_m = F(primary_actor_record, void *, 0x60);
            if (animation_m != 0) {
                bits = (u32)0xEFFFFFFF;
                neutral_color = 0x00808080;
                component = (s32)F(animation_m, u32, 0x1C);
                model_color = ((ObjectNodeHeader *)((u8 *)animation_m - 0x20))->sprite;
                component &= (s32)bits;
                F(animation_m, u32, 0x1C) = (u32)component;
                model_color->sprite = (u32)neutral_color;
            }
            {
                DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
                bits_2 = ((u16)dungeon_state->activity_counts.parts.pending_action_count);
                F(dungeon_state, u32, 0xC) = 0;
                F(((u8 *)(&reference_tile_object)), u16, 6) = 0;
                dungeon_state->activity_counts.parts.pending_action_count = (u16)(bits_2 - 1);
            }
            F(effect, u16, -2) = (u16)(F(effect, u16, -2) | 0x8000);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        F(&tint_particle_effect_updated, s16, 0) = 0;
    }
}
