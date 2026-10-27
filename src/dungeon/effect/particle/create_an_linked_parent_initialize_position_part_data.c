#include "shared/object_node_flags.h"
/* Timed display slots, parent-linked sprites, and a palette and particle transition. */
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/particle/create_an_linked_parent_initialize_position_part_data.h"
#include "shared/game_work.h"
void (*const dungeon_19b4800_entry)(struct TransitionState *, void *, void *) = update_palette_particle_transition;
const RectTable linked_particle_texture_rects = {{
 {0x340,0x140,0x40,0x40}, {0x340,0x180,0x40,0x40},
 {0x340,0x1C0,0x40,0x40}, {0x380,0x100,0x40,0x40},
 {0x380,0x140,0x40,0x40}, {0x380,0x180,0x40,0x40},
 {0x380,0x1C0,0x40,0x40}, {0x340,0x100,0x40,0x40}
}};
#include "dungeon/effect/particle/create_an_linked_parent_initialize_position_part_data.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/entity.h"

typedef struct S_81994800_0_pre {
    u16 unk_00;
} S_81994800_0_pre;   /* the 0x2 bytes before arg0 in func_8002405C, addressed as arg0[-1] */

typedef struct S_81994800_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    u8 unk_0D;
    s8 unk_0E;
} S_81994800_1;   /* arg2 in func_8002405C */

typedef struct S_81994800_2 {
    u8 pad_00[0x46];
    s16 unk_46;
} S_81994800_2;   /* ((((Rec_D_800E3D7C *)arg0)->unk_32 * 2) + ((Rec_D_800E3D7C *)arg0)->unk_60.as_s32) in func_8002405C */

extern s16 parent_effect_update_flag;
void fade_linked_display_sprite(void *effect, void *unused_context, void *effect_params);
/* Advance the effect countdown, update its parameters, and flag completion. */
void fade_linked_display_sprite(void *effect, void *unused_context, void *effect_params) {
    s32 scale;
    u16 ticks_left;

    ticks_left = ((u16)((EntityRec *)effect)->facing) - 1;
    scale = (s32)((s32)(ticks_left << 0x10) >> 9) / (s16)((EntityRec *)effect)->unk_2C;
    parent_effect_update_flag = 1;
    ((EntityRec *)effect)->facing = ticks_left;
    ((S_81994800_1 *)effect_params)->unk_0D = (u8)(((S_81994800_1 *)effect_params)->unk_0D - 4);
    ((S_81994800_1 *)effect_params)->unk_0E = (s8)scale;
    ((S_81994800_1 *)effect_params)->unk_0C = (s8)scale;
    if (((S_81994800_1 *)effect_params)->unk_06 >= -6) {
        ((S_81994800_1 *)effect_params)->unk_06 = (s16)((u16)((S_81994800_1 *)effect_params)->unk_06 - 2);
    }
    if ((s16)((u16)((EntityRec *)effect)->facing) <= 0) {
        ((S_81994800_2 *)(((((EntityRec *)effect)->unk_32 * 2) + ((u8 *)((EntityRec *)effect)->target))))->unk_46 = 0;
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_81994800_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
#include "dungeon/effect/particle/create_an_linked_parent_initialize_position_part_data.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

typedef struct S_80024104_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x4];
    s16 unk_32;
    u8 pad_34[0x2C];
    void * unk_60;
    u8 pad_64[0x16];
    u8 unk_7A;
    u8 unk_7B;
} S_80024104_0;   /* work in func_80024104 */

typedef struct {
    u32 word[4];
} __attribute__((packed)) PackedBlock;

typedef struct {
    u32 word[4];
} AlignedBlock;

typedef struct {
    u8 pad0[6];
    s16 field6;
    void *vector;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    s16 scaleY;
    s16 scaleX;
} Display;

extern PackedVec3 D_8002533C;
extern s16 parent_effect_update_flag;

/* Creates an object in the first free rectangle slot and decrements the owner timer. */
void spawn_free_slot_display_effect(void *owner) {
    s16 center[2];
    RectTable rect_table;
    u8 *copy_src;
    u8 *copy_dst;
    u8 *copy_end;
    s16 slot;
    s32 rect_offset;
    Rect16 *rect;
    ObjectNodeHeader *child;
    u8 *child_work;
    SpriteFrameState *display;
    ObjectPosition *source_words;
    ObjectPosition *child_words;
    u16 timer;

    copy_dst = (u8 *)&rect_table;
    copy_src = (u8 *)&linked_particle_texture_rects;
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

    parent_effect_update_flag = 1;

    slot = 0;
    while (slot < 8 && (*(s16 *)((u8 *)owner + 0x46 + (((s32)slot << 16) >> 15))) != 0) {
        slot++;
    }

    if (slot != 8) {
        (*(s16 *)((u8 *)owner + 0x46 + slot * 2)) = 1;
        rect_offset = (s32)slot << 3;
        rect = (Rect16 *)((u8 *)&rect_table + rect_offset);
        center[0] = rect->x + ((s16)rect->w >> 1);
        center[1] = rect->y + 0x30;
        draw_transformed_sprite_with_clip_rect((s32)primary_actor_record, rect, center, 1, 1);

        child = allocate_flagged_object_node(0x212);
        if (child != 0) {
            child_work = (u8 *)child + 0x20;
            ((S_80024104_0 *)child_work)->unk_2A = 7;
            ((S_80024104_0 *)child_work)->unk_2C = 7;
            ((S_80024104_0 *)child_work)->unk_32 = slot;
            ((S_80024104_0 *)child_work)->unk_60 = owner;
            child->update_callback = (void *)fade_linked_display_sprite;
            register_node(child, project_sprite_chain);

            display = child->sprite;
            display->depth_bias = 4;
            display->flags &= 0xFFF3;

            source_words = ((ObjectNodeHeader *)((u8 *)primary_actor_record - 0x20))->position;
            child_words = child->position;
            child_words->x.v = ((s32 *)source_words)[0];
            child_words->y.v = ((s32 *)source_words)[1];
            child_words->z.v = ((s32 *)source_words)[2];

            display = child->sprite;
            display->scale_y = 0x1000;
            display->scale_x = 0x1000;
            display->color.c.b = 0x80;
            display->color.c.g = 0x80;
            display->color.c.r = 0x80;

            *(PackedVec3 *)((u8 *)child + 0x92) = D_8002533C;
            display->source = (u8 *)child + 0x92;
            ((S_80024104_0 *)child_work)->unk_7A = (u8)rect->x - 0x40;
            ((S_80024104_0 *)child_work)->unk_7B = (u8)rect->y;
        }
    }

    timer = (*(u16 *)((u8 *)owner + 0x2A)) - 1;
    (*(u16 *)((u8 *)owner + 0x2A)) = timer;
    if ((s16)timer <= 0) {
        (*(u16 *)((u8 *)owner + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "dungeon/effect/particle/create_an_linked_parent_initialize_position_part_data.h"
#include "common.h"
#include "shared/slus_callbacks.h"
typedef struct Copy12 {
    s32 word[3];
} __attribute__((packed)) Copy12;
typedef struct {
    u8 pad0[6];
    s16 field6;
    void *ptr8;
    u8 byteC;
    u8 byteD;
    u8 byteE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Part;

/* cfail-repair: tf7-phase1-cache-v3 */

typedef struct S_800243E4_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
} S_800243E4_0;

typedef struct S_800243E4_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800243E4_1_pre;   /* the 0x18 bytes before arg0 in create_an_linked_parent_initialize_position_part_data, addressed as arg0[-1] */

typedef struct S_800243E4_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800243E4_3;

/* Create an object linked to its parent and initialize its position and part data. */
void create_an_linked_parent_initialize_position_part_data(void *parent, void *unused_context, void *unused_parameters) {
    ObjectPosition *position;
    SpriteFrameState *part;
    ObjectNodeHeader *object;
    S_800243E4_0 *state;
    S_800243E4_3 *parent_position;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        state = ((void *)object) + 0x20;
        state->unk_2A = 0x9;
        state->unk_60 = parent;
        (object->update_callback) = (s32 *)spawn_free_slot_display_effect;
        register_node(object, project_sprite_chain);
        part = object->sprite;
        part->tpage_abr = 0x20;
        part->depth_bias = 0;
        part->flags = (u16) (part->flags | 0xC);
        parent_position = ((S_800243E4_1_pre *)parent)[-1].unk_00;
        position = object->position;
        position->x.v = (s32) parent_position->unk_00;
        position->y.v = (s32) parent_position->unk_04;
        position->z.v = (s32) parent_position->unk_08;
        part = object->sprite;
        part->scale_y = 0;
        part->scale_x = 0;
        part->color.c.b = 0;
        part->color.c.g = 0;
        part->color.c.r = 0;
        (*(Copy12 *)((u8 *)object + 0x92)) = *(Copy12 *)&D_8002533C;
        part->source = (void *) (((void *)object) + 0x92);
    }
}
#include "dungeon/effect/particle/create_an_linked_parent_initialize_position_part_data.h"
#include "common.h"
#include "shared/object_flags.h"

extern s16 parent_effect_update_flag;

/*
 * Clamps nonzero primitive brightness above 64, reduces it by five, and decrements the lifetime.
 * Sets parent_effect_update_flag each update and flags removal when the signed lifetime expires.
 */
void fade_the_primitive_flag_effect_countdown_expires(void *effect, void *unused, u8 *primitive) {
    u16 ticks_left = *(u16 *)((u8 *)effect + 0x2A);

    parent_effect_update_flag = 1;
    ticks_left -= 1;
    *(u16 *)((u8 *)effect + 0x2A) = ticks_left;

    if (primitive[12] >= 65) {
        primitive[14] = 64;
        primitive[13] = 64;
        primitive[12] = 64;
    }

    if (primitive[12] != 0) {
        s32 brightness = primitive[14] - 5;

        primitive[14] = brightness;
        primitive[13] = brightness;
        primitive[12] = brightness;
    }

    if (*(s16 *)((u8 *)effect + 0x2A) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "dungeon/effect/particle/create_an_linked_parent_initialize_position_part_data.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

/* Recovered action payload; byte/halfword members follow retail access widths. */
typedef struct TransitionState {
    s32 reserved_00;
    u16 *flags;
    u8 event_id, reserved_09;
    s16 phase;
    s16 current_x, current_y, current_z;
    s16 previous_x, previous_y, previous_z;
    s16 midpoint_x, midpoint_y, midpoint_z;
    s16 reserved_1E;
    s16 countdown;
    u8 reserved_22[4];
    u16 facing;
    s16 reserved_28, ticks;
    u8 reserved_2C[0x38];
    s32 part_a, part_b;
} TransitionState;

typedef struct RectWords { u32 xy, wh; } RectWords;
typedef struct PackedResource { u32 words[3]; } __attribute__((packed)) PackedResource;
/* Object-system views recovered from all six allocation paths. */
typedef struct TransitionPosition { Fixed1616 x, y, z; } TransitionPosition;
typedef union TransitionColor {
    u32 rgb;
    struct { u8 red, green, blue, reserved_03; } channel;
} TransitionColor;
typedef struct TransitionRenderPart {
    u8 reserved_00[6];
    s16 depth;
    void *resource;
    TransitionColor color;
    s16 mode;
    u16 reserved_12, flags;
    u8 reserved_16[6];
    s16 scale_x, scale_y;
} TransitionRenderPart;
typedef union TransitionResource {
    PackedResource packed;
    struct { u8 reserved_00[8], width, height, reserved_0A[2]; } extent;
} TransitionResource;
typedef struct TransitionParticlePayload {
    u8 reserved_00[0x2A];
    s16 lifetime;
    u8 reserved_2C[0x46];
    TransitionResource resource;
} TransitionParticlePayload;
typedef struct TransitionParticle {
    ObjectNodeHeader header;
    TransitionParticlePayload payload;
} TransitionParticle;
typedef struct PaletteControl {
    u8 reserved_00[0x10];
    u8 low_r, low_g, low_b, reserved_13;
    u8 high_r, high_g, high_b;
} PaletteControl;
typedef struct AnimationState { u8 reserved_00[6]; s16 phase; void *resource; } AnimationState;
typedef struct TransitionFlags { u16 reserved_00[2]; u16 flags; } TransitionFlags;
#define TINT_NEUTRAL 0x808080
#define TINT_FLASH_BRIGHT 0x80E080
#define TINT_FLASH_DIM 0x709070
#define TINT_TARGET_HIGHLIGHT 0x80FF80
#define PARTICLE_ALLOC_ID 0x212
#define PARTICLE_SCALE_BASE 0xC00
#define PARTICLE_MODE_ADDITIVE 0x20
#define PARTICLE_FLAGS_VISIBLE 0xC

enum TransitionPhase {
    PHASE_SETUP,
    PHASE_WAIT_CONFIRM,
    PHASE_ENTER,
    PHASE_EXIT,
    PHASE_FINISH
};

extern u8 D_80025330[];
extern PackedResource linked_particle_resource_template, linked_particle_alt_resource_template;
extern PaletteControl ellipse_palette_channel_limits;
extern s16 parent_effect_update_flag;
extern u16 D_80082E94;
extern AnimationState reference_tile_object;

extern s32 get_sprite_attachment_vector(void *, AnimationState *, s16 *, s32);

extern s32 read_sound_mode_blocking_status(s32);

extern void draw_textured_ellipse(PaletteControl *, RectWords *, s32, s32);

/* Five-stage palette/particle transition, reconstructed from the complete
 * retail instruction span. The object views cover only fields used here.
 *
 * Each player (D_800814A8) tint write is preceded by a write-back of the
 * actor's +0x98 halfword (REVIEWER CALL, see MECHANISM.md). Retail reads the
 * field at all five sites and never uses the value; the write-back stores the
 * unchanged value, which gcc's post-reload CSE (reload_cse_regs) deletes as a
 * redundant store after flow has already kept the load alive.
 */
void update_palette_particle_transition(TransitionState *state, void *context, void *parameters) {
    GameWork *transition_flags = &g_game_work;
    PaletteControl *first_palette;
    RectWords upload_rect;
    s16 source_rect[4];
    s16 destination_xy[2];
    u16 actor_facing;
    u32 midpoint_sum_x, midpoint_sum_y;
    s32 sound_request;
    s16 count_after_tick;
    s16 remaining;
    s16 particle_scale;
    s32 scale_countdown;
    s32 tint_countdown;
    s32 entry_tint;
    s32 exit_tint;
    s32 target_tint;
    u32 upload_value;
    ObjectPosition *position;
    ActorRecord *target;
    SpriteFrameState *render_part;
    TransitionParticlePayload * particle_scratch;
    TransitionParticle *particle;
    ActorRecord *actor;
    ActorRecord *player;
    SpriteFrameState *tint_part;

    state->ticks++;
    switch (state->phase) {
    case PHASE_SETUP: /* initialise palette/tint state, then fall into the wait */
        ((PlayerRecord *)primary_actor_record)->unk_F4 = (s32)&D_80025330;
        reference_tile_object.phase = 6;
        ellipse_palette_channel_limits.low_r = 0;
        ellipse_palette_channel_limits.low_g = 0;
        ellipse_palette_channel_limits.low_b = 0;
        ellipse_palette_channel_limits.high_r = 0xFF;
        ellipse_palette_channel_limits.high_g = 0xFF;
        ellipse_palette_channel_limits.high_b = 0xFF;
        upload_rect.xy = 0x01000340;
        upload_rect.wh = 0x400040;
        draw_textured_ellipse(&ellipse_palette_channel_limits, &upload_rect, 1, 0);
        parent_effect_update_flag = 1;
        state->phase++;
        /* fallthrough */
    case PHASE_WAIT_CONFIRM: /* wait for the trigger bit, then snapshot facing and start the effect */
        if (*state->flags & 0x80) {
            actor = primary_actor_record;
            state->countdown = 0x14;
            *(u16 *)((u8 *)actor + 0xA6) -= 1; /* halfword counter at +0xA6 (high half of unk_A4) */
            actor->unk_A8.byte = (u8) state->event_id;
            actor_facing = (u16)primary_actor_record->facing;
            state->phase++;
            state->ticks = 0;
            state->facing = actor_facing;
            create_an_linked_parent_initialize_position_part_data(state, context, parameters);
            if (state->part_b != 0) {
                source_rect[0] = 0x340;
                source_rect[1] = 0x100;
                source_rect[2] = 0x40;
                source_rect[3] = 0x40;
                destination_xy[0] = 0x360;
                destination_xy[1] = 0x120;
                draw_transformed_sprite_with_clip_rect(state->part_b, source_rect, destination_xy, 0, 1);
            }
            if (state->part_a != 0) {
                source_rect[0] = 0x340;
                source_rect[1] = 0x100;
                source_rect[2] = 0x40;
                source_rect[3] = 0x40;
                destination_xy[0] = 0x360;
                destination_xy[1] = 0x120;
                draw_transformed_sprite_with_clip_rect(state->part_a, source_rect, destination_xy, 1, 1);
            }
        }
        break;
    case PHASE_ENTER: /* countdown with flickering tint and trailing particles */
        if (state->countdown < 9) {
            if (state->countdown >= 5) {
                player = primary_actor_record;
                entry_tint = TINT_FLASH_BRIGHT;
                player->action_state_flags = player->action_state_flags; /* BYTES: +0x98 write-back: retail reads the field, the unchanged store compiles away */
                tint_part = ((ObjectNodeHeader *)player)[-1].sprite;
                tint_countdown = (u16) state->countdown;
                if (tint_countdown & 1) {
                    entry_tint = TINT_FLASH_DIM;
                }
                tint_part->color.word = entry_tint;
            } else {
                tint_part = ((ObjectNodeHeader *)primary_actor_record)[-1].sprite;
                entry_tint = TINT_FLASH_BRIGHT;
                primary_actor_record->action_state_flags = primary_actor_record->action_state_flags; /* BYTES: +0x98 write-back: retail reads the field, the unchanged store compiles away */
                tint_part->color.word = entry_tint;
            }
        }
        count_after_tick = state->countdown - 1;
        state->countdown = count_after_tick;
        if (count_after_tick <= 0) {
            state->countdown = 0x10;
            state->phase++;
        }
        if (state->countdown == 0x11) {
            particle_scratch = (TransitionParticlePayload *)(read_sound_mode_blocking_status(4));
            sound_request = 0x4300;
            if (((s32)particle_scratch) != 2) {
                sound_request = 0x300;
            }
            play_sound_if_enabled(sound_request);
        }
        if ((state->countdown < 9) && ((particle_scratch = (TransitionParticlePayload *)(get_sprite_attachment_vector(reference_tile_object.resource, &reference_tile_object, &state->current_x, 0))) != 0)) {
            if (state->countdown >= 7) {
                particle = allocate_flagged_object_node(PARTICLE_ALLOC_ID);
                particle_scratch = &particle->payload;
                if (particle != 0) {
                    particle_scratch->lifetime = 1;
                    particle->header.update_callback = (void *)fade_the_primitive_flag_effect_countdown_expires;
                    register_node(particle, project_sprite_chain);
                    render_part = particle->header.sprite;
                    render_part->tpage_abr = PARTICLE_MODE_ADDITIVE;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = particle->header.position;
                    position->x.w.i = state->current_x;
                    position->y.w.i = state->current_y;
                    position->z.w.i = state->current_z;
                    position->x.w.i = (u16) (position->x.w.i + view_reference_entity.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + view_reference_entity.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + view_reference_entity.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.c.b = 0xFF;
                    render_part->color.c.g = 0xFF;
                    render_part->color.c.r = 0xFF;
                    particle->payload.resource.packed = linked_particle_resource_template;
                    render_part->source = (void *)&particle->payload.resource;
                    particle_scratch->resource.extent.width = 0x40;
                    particle_scratch->resource.extent.height = 0x40;
                }
                if (!(state->countdown & 1)) {
                    particle = allocate_flagged_object_node(PARTICLE_ALLOC_ID);
                    if (particle != 0) {
                        particle->payload.lifetime = 1;
                        particle->header.update_callback = (void *)fade_the_primitive_flag_effect_countdown_expires;
                        register_node(particle, project_sprite_chain);
                        render_part = particle->header.sprite;
                        render_part->tpage_abr = PARTICLE_MODE_ADDITIVE;
                        render_part->depth_bias = -4;
                        render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                        position = particle->header.position;
                        position->x.w.i = state->current_x;
                        position->y.w.i = state->current_y;
                        position->z.w.i = state->current_z;
                        position->x.w.i = (u16) (position->x.w.i + view_reference_entity.x.w.i);
                        position->y.w.i = (u16) (position->y.w.i + view_reference_entity.y.w.i);
                        position->z.w.i = (u16) (position->z.w.i + view_reference_entity.z.w.i);
                        render_part->scale_y = PARTICLE_SCALE_BASE;
                        render_part->scale_x = PARTICLE_SCALE_BASE;
                        render_part->color.c.b = 0x80;
                        render_part->color.c.g = 0x80;
                        render_part->color.c.r = 0x80;
                        particle->payload.resource.packed = linked_particle_alt_resource_template;
                        render_part->source = (void *)&particle->payload.resource;
                    }
                }
            } else {
                particle = allocate_flagged_object_node(PARTICLE_ALLOC_ID);
                particle_scratch = &particle->payload;
                if (particle != 0) {
                    particle_scratch->lifetime = 0xC;
                    particle->header.update_callback = (void *)fade_the_primitive_flag_effect_countdown_expires;
                    register_node(particle, project_sprite_chain);
                    render_part = particle->header.sprite;
                    render_part->tpage_abr = PARTICLE_MODE_ADDITIVE;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = particle->header.position;
                    position->x.w.i = state->current_x;
                    position->y.w.i = state->current_y;
                    position->z.w.i = state->current_z;
                    position->x.w.i = (u16) (position->x.w.i + view_reference_entity.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + view_reference_entity.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + view_reference_entity.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.c.b = 0xFF;
                    render_part->color.c.g = 0xFF;
                    render_part->color.c.r = 0xFF;
                    particle->payload.resource.packed = linked_particle_resource_template;
                    render_part->source = (void *)&particle->payload.resource;
                    particle_scratch->resource.extent.width = 0;
                    particle_scratch->resource.extent.height = 0;
                }
                particle = allocate_flagged_object_node(PARTICLE_ALLOC_ID);
                if (particle != 0) {
                    particle->payload.lifetime = 1;
                    particle->header.update_callback = (void *)fade_the_primitive_flag_effect_countdown_expires;
                    register_node(particle, project_sprite_chain);
                    render_part = particle->header.sprite;
                    render_part->tpage_abr = PARTICLE_MODE_ADDITIVE;
                    render_part->depth_bias = -4;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = particle->header.position;
                    position->x.w.i = state->current_x;
                    position->y.w.i = state->current_y;
                    position->z.w.i = state->current_z;
                    position->x.w.i = (u16) (position->x.w.i + view_reference_entity.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + view_reference_entity.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + view_reference_entity.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.c.b = 0x80;
                    render_part->color.c.g = 0x80;
                    render_part->color.c.r = 0x80;
                    particle->payload.resource.packed = linked_particle_alt_resource_template;
                    render_part->source = (void *)&particle->payload.resource;
                }
            }
            if (state->countdown < 4) {
                midpoint_sum_x = state->current_x + state->previous_x;
                state->midpoint_x = (s32)(midpoint_sum_x + (midpoint_sum_x >> 31)) >> 1;
                midpoint_sum_y = state->current_y + state->previous_y;
                state->midpoint_y = (s32)(midpoint_sum_y + (midpoint_sum_y >> 31)) >> 1;
                state->midpoint_z = (state->current_z + state->previous_z) / 2;
                particle = allocate_flagged_object_node(PARTICLE_ALLOC_ID);
                particle_scratch = &particle->payload;
                if (particle != 0) {
                    particle_scratch->lifetime = 0xC;
                    particle->header.update_callback = (void *)fade_the_primitive_flag_effect_countdown_expires;
                    register_node(particle, project_sprite_chain);
                    render_part = particle->header.sprite;
                    render_part->tpage_abr = PARTICLE_MODE_ADDITIVE;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = particle->header.position;
                    position->x.w.i = state->midpoint_x;
                    position->y.w.i = state->midpoint_y;
                    position->z.w.i = state->midpoint_z;
                    position->x.w.i = (u16) (position->x.w.i + view_reference_entity.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + view_reference_entity.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + view_reference_entity.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.c.b = 0xFF;
                    render_part->color.c.g = 0xFF;
                    render_part->color.c.r = 0xFF;
                    particle->payload.resource.packed = linked_particle_resource_template;
                    render_part->source = (void *)&particle->payload.resource;
                    particle_scratch->resource.extent.width = 0;
                    particle_scratch->resource.extent.height = 0;
                }
            }
            state->previous_x = state->current_x;
            state->previous_y = state->current_y;
            state->previous_z = state->current_z;
        }
        break;
    case PHASE_EXIT: /* tint flicker, growing particles, target highlight */
        if (state->countdown >= 7) {
            if (state->countdown < 0xD) {
                player = primary_actor_record;
                exit_tint = TINT_FLASH_BRIGHT;
                player->action_state_flags = player->action_state_flags; /* BYTES: +0x98 write-back: retail reads the field, the unchanged store compiles away */
                tint_part = ((ObjectNodeHeader *)player)[-1].sprite;
                tint_countdown = (u16) state->countdown;
                if (tint_countdown & 1) {
                    exit_tint = TINT_FLASH_DIM;
                }
                tint_part->color.word = exit_tint;
            } else {
                tint_part = ((ObjectNodeHeader *)primary_actor_record)[-1].sprite;
                exit_tint = TINT_FLASH_BRIGHT;
                primary_actor_record->action_state_flags = primary_actor_record->action_state_flags; /* BYTES: +0x98 write-back: retail reads the field, the unchanged store compiles away */
                tint_part->color.word = exit_tint;
            }
        }
        if ((state->countdown >= 0xD) && ((particle_scratch = (TransitionParticlePayload *)(get_sprite_attachment_vector(reference_tile_object.resource, &reference_tile_object, &state->current_x, 0))) != 0)) {
            particle = allocate_flagged_object_node(PARTICLE_ALLOC_ID);
            particle_scratch = &particle->payload;
            if (particle != 0) {
                particle_scratch->lifetime = 0xC;
                if (state->countdown != 0xD) {
                    particle_scratch->lifetime = 1;
                }
                particle->header.update_callback = (void *)fade_the_primitive_flag_effect_countdown_expires;
                register_node(particle, project_sprite_chain);
                render_part = particle->header.sprite;
                render_part->tpage_abr = PARTICLE_MODE_ADDITIVE;
                render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                position = particle->header.position;
                position->x.w.i = state->current_x;
                position->y.w.i = state->current_y;
                position->z.w.i = state->current_z;
                position->x.w.i = (u16) (position->x.w.i + view_reference_entity.x.w.i);
                position->y.w.i = (u16) (position->y.w.i + view_reference_entity.y.w.i);
                position->z.w.i = (u16) (position->z.w.i + view_reference_entity.z.w.i);
                scale_countdown = state->countdown;
                render_part->color.c.b = 0xFF;
                render_part->color.c.g = 0xFF;
                render_part->color.c.r = 0xFF;
                particle_scale = ((0x10 - scale_countdown) * 0x300) + PARTICLE_SCALE_BASE;
                render_part->scale_y = particle_scale;
                render_part->scale_x = particle_scale;
                particle->payload.resource.packed = linked_particle_resource_template;
                render_part->source = (void *)&particle->payload.resource;
                particle_scratch->resource.extent.width = 0x40;
                particle_scratch->resource.extent.height = 0x40;
            }
            if (!(state->countdown & 1)) {
                particle = allocate_flagged_object_node(PARTICLE_ALLOC_ID);
                if (particle != 0) {
                    particle->payload.lifetime = 1;
                    particle->header.update_callback = (void *)fade_the_primitive_flag_effect_countdown_expires;
                    register_node(particle, project_sprite_chain);
                    render_part = particle->header.sprite;
                    render_part->tpage_abr = PARTICLE_MODE_ADDITIVE;
                    render_part->depth_bias = -4;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = particle->header.position;
                    position->x.w.i = state->current_x;
                    position->y.w.i = state->current_y;
                    position->z.w.i = state->current_z;
                    position->x.w.i = (u16) (position->x.w.i + view_reference_entity.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + view_reference_entity.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + view_reference_entity.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.c.b = 0x80;
                    render_part->color.c.g = 0x80;
                    render_part->color.c.r = 0x80;
                    particle->payload.resource.packed = linked_particle_alt_resource_template;
                    render_part->source = (void *)&particle->payload.resource;
                }
            }
        }
        target = primary_actor_record->target;
        if (target != 0) {
            target->flags1C = (s32) (target->flags1C | 0x10000000);
            tint_part = ((ObjectNodeHeader *)target)[-1].sprite;
            target_tint = 0;
            if (transition_flags->unk_004 & 1) {
                target_tint = TINT_TARGET_HIGHLIGHT;
            }
            tint_part->color.word = target_tint;
        }
        if ((D_80082E94 & 0x8000) || (remaining = state->countdown - 1, state->countdown = remaining, (remaining < 0))) {
            state->phase = PHASE_FINISH;
        }
        break;
    case PHASE_FINISH: /* restore tints and release the transition */
        if (parent_effect_update_flag == 0) {
            target = primary_actor_record->target;
            if (target != 0) {
                target->flags1C = (s32) (target->flags1C & 0xEFFFFFFF);
                tint_part = ((ObjectNodeHeader *)target)[-1].sprite;
                tint_part->color.word = TINT_NEUTRAL;
            }
            g_dungeon_status.active_actor = 0;
            reference_tile_object.phase = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (g_dungeon_status.activity_counts.parts.pending_action_count - 1);
            tint_part = ((ObjectNodeHeader *)primary_actor_record)[-1].sprite;
            primary_actor_record->action_state_flags = primary_actor_record->action_state_flags; /* BYTES: +0x98 write-back: retail reads the field, the unchanged store compiles away */
            tint_part->color.word = TINT_NEUTRAL;
            ((ObjectNodeHeader *)state)[-1].flags = (u16) (((ObjectNodeHeader *)state)[-1].flags | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        } else {
            parent_effect_update_flag = 0;
        }
        break;
    }
    /* Alternate palette uploads once the transition is active. */
    if ((state->phase >= 2) && (state->ticks >= 0xC)) {
        if (!(state->countdown & 1)) {
            first_palette = &ellipse_palette_channel_limits;
            upload_value = 0;
            first_palette->low_r = upload_value;
            first_palette->low_g = upload_value;
            first_palette->low_b = upload_value;
            upload_value = 0xFF;
        } else {
            first_palette = &ellipse_palette_channel_limits;
            upload_value = 0x60;
            first_palette->low_r = upload_value;
            first_palette->low_g = upload_value;
            first_palette->low_b = upload_value;
            upload_value = 0x20;
        }
        first_palette->high_r = upload_value;
        first_palette->high_g = upload_value;
        first_palette->high_b = upload_value;
        upload_rect = (RectWords){0x01400380, 0x00400040};
        draw_textured_ellipse(&ellipse_palette_channel_limits, &upload_rect, 1, 0);
        if (state->ticks >= 0xF) {
            if (!(state->countdown & 1)) {
                ellipse_palette_channel_limits.low_r = 0;
                ellipse_palette_channel_limits.low_g = 0;
                ellipse_palette_channel_limits.low_b = 0;
                ellipse_palette_channel_limits.high_r = 0x50;
                ellipse_palette_channel_limits.high_g = 0x50;
                ellipse_palette_channel_limits.high_b = 0x50;
            } else {
                ellipse_palette_channel_limits.low_r = 0x50;
                ellipse_palette_channel_limits.low_g = 0x50;
                ellipse_palette_channel_limits.low_b = 0x50;
                ellipse_palette_channel_limits.high_r = 0;
                ellipse_palette_channel_limits.high_g = 0;
                ellipse_palette_channel_limits.high_b = 0;
            }
            upload_rect.xy = 0x01800380;
            upload_rect.wh = 0x400040;
            draw_textured_ellipse(&ellipse_palette_channel_limits, &upload_rect, 1, 0);
        }
    }
}
