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
extern PackedResource D_80025348, D_80025360;
extern PaletteControl D_8002536C;
extern s16 D_80025384;
extern u16 D_80082E94;
extern AnimationState D_80082E80;
extern TransitionFlags D_80083160;
extern void func_800244F0(void *, void *, void *);
extern void func_80045340(void *);
extern void func_800243E4(TransitionState *, void *, void *);
extern s32 func_8003DF74(void *, AnimationState *, s16 *, s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void (*)(void *));
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void func_800B835C(PaletteControl *, RectWords *, s32, s32);
extern void func_800B8FC8(s32, s16 *, s16 *, s32, s32);

/* Five-stage palette/particle transition, reconstructed from the complete
 * retail instruction span. The object views cover only fields used here.
 *
 * Each player (D_800814A8) tint write is preceded by a write-back of the
 * actor's +0x98 halfword (REVIEWER CALL, see MECHANISM.md). Retail reads the
 * field at all five sites and never uses the value; the write-back stores the
 * unchanged value, which gcc's post-reload CSE (reload_cse_regs) deletes as a
 * redundant store after flow has already kept the load alive.
 */
void func_8002458C(TransitionState *state, void *context, void *parameters) {
    TransitionFlags *transition_flags = &D_80083160;
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
    TransitionPosition *position;
    EntityRec *target;
    TransitionRenderPart *render_part;
    union { TransitionParticlePayload *particle; s32 status; } particle_scratch;
    TransitionParticle *particle;
    EntityRec *actor;
    EntityRec *player;
    TransitionRenderPart *tint_part;

    state->ticks++;
    switch (state->phase) {
    case PHASE_SETUP: /* initialise palette/tint state, then fall into the wait */
        D_800814A8->unk_F4 = (s32)&D_80025330;
        D_80082E80.phase = 6;
        D_8002536C.low_r = 0;
        D_8002536C.low_g = 0;
        D_8002536C.low_b = 0;
        D_8002536C.high_r = 0xFF;
        D_8002536C.high_g = 0xFF;
        D_8002536C.high_b = 0xFF;
        upload_rect.xy = 0x01000340;
        upload_rect.wh = 0x400040;
        func_800B835C(&D_8002536C, &upload_rect, 1, 0);
        D_80025384 = 1;
        state->phase++;
        /* fallthrough */
    case PHASE_WAIT_CONFIRM: /* wait for the trigger bit, then snapshot facing and start the effect */
        if (*state->flags & 0x80) {
            actor = D_800814A8;
            state->countdown = 0x14;
            *(u16 *)((u8 *)actor + 0xA6) -= 1; /* halfword counter at +0xA6 (high half of unk_A4) */
            actor->unk_A8 = (u8) state->event_id;
            actor_facing = (u16)D_800814A8->facing;
            state->phase++;
            state->ticks = 0;
            state->facing = actor_facing;
            func_800243E4(state, context, parameters);
            if (state->part_b != 0) {
                source_rect[0] = 0x340;
                source_rect[1] = 0x100;
                source_rect[2] = 0x40;
                source_rect[3] = 0x40;
                destination_xy[0] = 0x360;
                destination_xy[1] = 0x120;
                func_800B8FC8(state->part_b, source_rect, destination_xy, 0, 1);
            }
            if (state->part_a != 0) {
                source_rect[0] = 0x340;
                source_rect[1] = 0x100;
                source_rect[2] = 0x40;
                source_rect[3] = 0x40;
                destination_xy[0] = 0x360;
                destination_xy[1] = 0x120;
                func_800B8FC8(state->part_a, source_rect, destination_xy, 1, 1);
            }
        }
        break;
    case PHASE_ENTER: /* countdown with flickering tint and trailing particles */
        if (state->countdown < 9) {
            if (state->countdown >= 5) {
                player = D_800814A8;
                entry_tint = TINT_FLASH_BRIGHT;
                player->unk_98 = player->unk_98; /* +0x98 write-back: retail reads the field, the unchanged store compiles away */
                tint_part = (TransitionRenderPart *)((ObjectNodeHeader *)player)[-1].unk_0C;
                tint_countdown = (u16) state->countdown;
                if (tint_countdown & 1) {
                    entry_tint = TINT_FLASH_DIM;
                }
                tint_part->color.rgb = entry_tint;
            } else {
                tint_part = (TransitionRenderPart *)((ObjectNodeHeader *)D_800814A8)[-1].unk_0C;
                entry_tint = TINT_FLASH_BRIGHT;
                D_800814A8->unk_98 = D_800814A8->unk_98; /* +0x98 write-back: retail reads the field, the unchanged store compiles away */
                tint_part->color.rgb = entry_tint;
            }
        }
        count_after_tick = state->countdown - 1;
        state->countdown = count_after_tick;
        if (count_after_tick <= 0) {
            state->countdown = 0x10;
            state->phase++;
        }
        if (state->countdown == 0x11) {
            particle_scratch.status = func_80053EF0(4);
            sound_request = 0x4300;
            if (particle_scratch.status != 2) {
                sound_request = 0x300;
            }
            func_800A56E0(sound_request);
        }
        if ((state->countdown < 9) && ((particle_scratch.status = func_8003DF74(D_80082E80.resource, &D_80082E80, &state->current_x, 0)) != 0)) {
            if (state->countdown >= 7) {
                particle = func_8003FC64(PARTICLE_ALLOC_ID);
                particle_scratch.particle = &particle->payload;
                if (particle != 0) {
                    particle_scratch.particle->lifetime = 1;
                    particle->header.unk_10 = (void *)func_800244F0;
                    func_8004491C(particle, func_80045340);
                    render_part = (TransitionRenderPart *)particle->header.unk_0C;
                    render_part->mode = PARTICLE_MODE_ADDITIVE;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = (TransitionPosition *)particle->header.unk_08;
                    position->x.w.i = state->current_x;
                    position->y.w.i = state->current_y;
                    position->z.w.i = state->current_z;
                    position->x.w.i = (u16) (position->x.w.i + D_80083780.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + D_80083780.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + D_80083780.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.channel.blue = 0xFF;
                    render_part->color.channel.green = 0xFF;
                    render_part->color.channel.red = 0xFF;
                    particle->payload.resource.packed = D_80025348;
                    render_part->resource = (void *)&particle->payload.resource;
                    particle_scratch.particle->resource.extent.width = 0x40;
                    particle_scratch.particle->resource.extent.height = 0x40;
                }
                if (!(state->countdown & 1)) {
                    goto spawn_depth_particle;
                }
            } else {
                particle = func_8003FC64(PARTICLE_ALLOC_ID);
                particle_scratch.particle = &particle->payload;
                if (particle != 0) {
                    particle_scratch.particle->lifetime = 0xC;
                    particle->header.unk_10 = (void *)func_800244F0;
                    func_8004491C(particle, func_80045340);
                    render_part = (TransitionRenderPart *)particle->header.unk_0C;
                    render_part->mode = PARTICLE_MODE_ADDITIVE;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = (TransitionPosition *)particle->header.unk_08;
                    position->x.w.i = state->current_x;
                    position->y.w.i = state->current_y;
                    position->z.w.i = state->current_z;
                    position->x.w.i = (u16) (position->x.w.i + D_80083780.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + D_80083780.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + D_80083780.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.channel.blue = 0xFF;
                    render_part->color.channel.green = 0xFF;
                    render_part->color.channel.red = 0xFF;
                    particle->payload.resource.packed = D_80025348;
                    render_part->resource = (void *)&particle->payload.resource;
                    particle_scratch.particle->resource.extent.width = 0;
                    particle_scratch.particle->resource.extent.height = 0;
                }
spawn_depth_particle:
                particle = func_8003FC64(PARTICLE_ALLOC_ID);
                if (particle != 0) {
                    particle->payload.lifetime = 1;
                    particle->header.unk_10 = (void *)func_800244F0;
                    func_8004491C(particle, func_80045340);
                    render_part = (TransitionRenderPart *)particle->header.unk_0C;
                    render_part->mode = PARTICLE_MODE_ADDITIVE;
                    render_part->depth = -4;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = (TransitionPosition *)particle->header.unk_08;
                    position->x.w.i = state->current_x;
                    position->y.w.i = state->current_y;
                    position->z.w.i = state->current_z;
                    position->x.w.i = (u16) (position->x.w.i + D_80083780.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + D_80083780.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + D_80083780.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.channel.blue = 0x80;
                    render_part->color.channel.green = 0x80;
                    render_part->color.channel.red = 0x80;
                    particle->payload.resource.packed = D_80025360;
                    render_part->resource = (void *)&particle->payload.resource;
                }
            }
            if (state->countdown < 4) {
                midpoint_sum_x = state->current_x + state->previous_x;
                state->midpoint_x = (s32)(midpoint_sum_x + (midpoint_sum_x >> 31)) >> 1;
                midpoint_sum_y = state->current_y + state->previous_y;
                state->midpoint_y = (s32)(midpoint_sum_y + (midpoint_sum_y >> 31)) >> 1;
                state->midpoint_z = (state->current_z + state->previous_z) / 2;
                particle = func_8003FC64(PARTICLE_ALLOC_ID);
                particle_scratch.particle = &particle->payload;
                if (particle != 0) {
                    particle_scratch.particle->lifetime = 0xC;
                    particle->header.unk_10 = (void *)func_800244F0;
                    func_8004491C(particle, func_80045340);
                    render_part = (TransitionRenderPart *)particle->header.unk_0C;
                    render_part->mode = PARTICLE_MODE_ADDITIVE;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = (TransitionPosition *)particle->header.unk_08;
                    position->x.w.i = state->midpoint_x;
                    position->y.w.i = state->midpoint_y;
                    position->z.w.i = state->midpoint_z;
                    position->x.w.i = (u16) (position->x.w.i + D_80083780.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + D_80083780.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + D_80083780.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.channel.blue = 0xFF;
                    render_part->color.channel.green = 0xFF;
                    render_part->color.channel.red = 0xFF;
                    particle->payload.resource.packed = D_80025348;
                    render_part->resource = (void *)&particle->payload.resource;
                    particle_scratch.particle->resource.extent.width = 0;
                    particle_scratch.particle->resource.extent.height = 0;
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
                player = D_800814A8;
                exit_tint = TINT_FLASH_BRIGHT;
                player->unk_98 = player->unk_98; /* +0x98 write-back: retail reads the field, the unchanged store compiles away */
                tint_part = (TransitionRenderPart *)((ObjectNodeHeader *)player)[-1].unk_0C;
                tint_countdown = (u16) state->countdown;
                if (tint_countdown & 1) {
                    exit_tint = TINT_FLASH_DIM;
                }
                tint_part->color.rgb = exit_tint;
            } else {
                tint_part = (TransitionRenderPart *)((ObjectNodeHeader *)D_800814A8)[-1].unk_0C;
                exit_tint = TINT_FLASH_BRIGHT;
                D_800814A8->unk_98 = D_800814A8->unk_98; /* +0x98 write-back: retail reads the field, the unchanged store compiles away */
                tint_part->color.rgb = exit_tint;
            }
        }
        if ((state->countdown >= 0xD) && ((particle_scratch.status = func_8003DF74(D_80082E80.resource, &D_80082E80, &state->current_x, 0)) != 0)) {
            particle = func_8003FC64(PARTICLE_ALLOC_ID);
            particle_scratch.particle = &particle->payload;
            if (particle != 0) {
                particle_scratch.particle->lifetime = 0xC;
                if (state->countdown != 0xD) {
                    particle_scratch.particle->lifetime = 1;
                }
                particle->header.unk_10 = (void *)func_800244F0;
                func_8004491C(particle, func_80045340);
                render_part = (TransitionRenderPart *)particle->header.unk_0C;
                render_part->mode = PARTICLE_MODE_ADDITIVE;
                render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                position = (TransitionPosition *)particle->header.unk_08;
                position->x.w.i = state->current_x;
                position->y.w.i = state->current_y;
                position->z.w.i = state->current_z;
                position->x.w.i = (u16) (position->x.w.i + D_80083780.x.w.i);
                position->y.w.i = (u16) (position->y.w.i + D_80083780.y.w.i);
                position->z.w.i = (u16) (position->z.w.i + D_80083780.z.w.i);
                scale_countdown = state->countdown;
                render_part->color.channel.blue = 0xFF;
                render_part->color.channel.green = 0xFF;
                render_part->color.channel.red = 0xFF;
                particle_scale = ((0x10 - scale_countdown) * 0x300) + PARTICLE_SCALE_BASE;
                render_part->scale_y = particle_scale;
                render_part->scale_x = particle_scale;
                particle->payload.resource.packed = D_80025348;
                render_part->resource = (void *)&particle->payload.resource;
                particle_scratch.particle->resource.extent.width = 0x40;
                particle_scratch.particle->resource.extent.height = 0x40;
            }
            if (!(state->countdown & 1)) {
                particle = func_8003FC64(PARTICLE_ALLOC_ID);
                if (particle != 0) {
                    particle->payload.lifetime = 1;
                    particle->header.unk_10 = (void *)func_800244F0;
                    func_8004491C(particle, func_80045340);
                    render_part = (TransitionRenderPart *)particle->header.unk_0C;
                    render_part->mode = PARTICLE_MODE_ADDITIVE;
                    render_part->depth = -4;
                    render_part->flags = (u16) (render_part->flags | PARTICLE_FLAGS_VISIBLE);
                    position = (TransitionPosition *)particle->header.unk_08;
                    position->x.w.i = state->current_x;
                    position->y.w.i = state->current_y;
                    position->z.w.i = state->current_z;
                    position->x.w.i = (u16) (position->x.w.i + D_80083780.x.w.i);
                    position->y.w.i = (u16) (position->y.w.i + D_80083780.y.w.i);
                    position->z.w.i = (u16) (position->z.w.i + D_80083780.z.w.i);
                    render_part->scale_y = PARTICLE_SCALE_BASE;
                    render_part->scale_x = PARTICLE_SCALE_BASE;
                    render_part->color.channel.blue = 0x80;
                    render_part->color.channel.green = 0x80;
                    render_part->color.channel.red = 0x80;
                    particle->payload.resource.packed = D_80025360;
                    render_part->resource = (void *)&particle->payload.resource;
                }
            }
        }
        target = D_800814A8->target;
        if (target != 0) {
            target->flags1C = (s32) (target->flags1C | 0x10000000);
            tint_part = (TransitionRenderPart *)((ObjectNodeHeader *)target)[-1].unk_0C;
            target_tint = 0;
            if (transition_flags->flags & 1) {
                target_tint = TINT_TARGET_HIGHLIGHT;
            }
            tint_part->color.rgb = target_tint;
        }
        if ((D_80082E94 & 0x8000) || (remaining = state->countdown - 1, state->countdown = remaining, (remaining < 0))) {
            state->phase = PHASE_FINISH;
        }
        break;
    case PHASE_FINISH: /* restore tints and release the transition */
        if (D_80025384 == 0) {
            target = D_800814A8->target;
            if (target != 0) {
                target->flags1C = (s32) (target->flags1C & 0xEFFFFFFF);
                tint_part = (TransitionRenderPart *)((ObjectNodeHeader *)target)[-1].unk_0C;
                tint_part->color.rgb = TINT_NEUTRAL;
            }
            dungeonStatus.unk_0C = 0;
            D_80082E80.phase = 0;
            dungeonStatus.unk_0A = (u16) (dungeonStatus.unk_0A - 1);
            tint_part = (TransitionRenderPart *)((ObjectNodeHeader *)D_800814A8)[-1].unk_0C;
            D_800814A8->unk_98 = D_800814A8->unk_98; /* +0x98 write-back: retail reads the field, the unchanged store compiles away */
            tint_part->color.rgb = TINT_NEUTRAL;
            ((ObjectNodeHeader *)state)[-1].flags = (u16) (((ObjectNodeHeader *)state)[-1].flags | 0x8000);
            objectFlagBlock.flags |= 0x8000;
        } else {
            D_80025384 = 0;
        }
        break;
    }
    /* Alternate palette uploads once the transition is active. */
    if ((state->phase >= 2) && (state->ticks >= 0xC)) {
        if (!(state->countdown & 1)) {
            first_palette = &D_8002536C;
            upload_value = 0;
            first_palette->low_r = upload_value;
            first_palette->low_g = upload_value;
            first_palette->low_b = upload_value;
            upload_value = 0xFF;
        } else {
            first_palette = &D_8002536C;
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
        func_800B835C(&D_8002536C, &upload_rect, 1, 0);
        if (state->ticks >= 0xF) {
            if (!(state->countdown & 1)) {
                D_8002536C.low_r = 0;
                D_8002536C.low_g = 0;
                D_8002536C.low_b = 0;
                D_8002536C.high_r = 0x50;
                D_8002536C.high_g = 0x50;
                D_8002536C.high_b = 0x50;
            } else {
                D_8002536C.low_r = 0x50;
                D_8002536C.low_g = 0x50;
                D_8002536C.low_b = 0x50;
                D_8002536C.high_r = 0;
                D_8002536C.high_g = 0;
                D_8002536C.high_b = 0;
            }
            upload_rect.xy = 0x01800380;
            upload_rect.wh = 0x400040;
            func_800B835C(&D_8002536C, &upload_rect, 1, 0);
        }
    }
}
