#ifndef DUNGEON_EFFECT_MOTION_H
#define DUNGEON_EFFECT_MOTION_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
struct S_7FFE83DC_3;
struct S_80024EF8_0;
void create_positioned_color_sprite(struct S_7FFE83DC_3 *source, s32 color);
void * create_indexed_color_sprite(MovingPosition *origin, u16 index);
s32 draw_counter_rotating_cylinders(struct S_80024EF8_0 *effect, MovingPosition *center, s32 unused_value);
void spawn_jittered_child_effect( void *source, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void spawn_variant_effect_with_random_motion(s32 pos_x, s32 pos_y, s32 pos_z, u32 variant);


void animate_object_motion_and_scale(void *object, ObjectPosition *motion, void *display);


/* Body allocated with flags 0x201 by the bank timed-visual sequence and its
 * relinks. create_cylindrical_effect decrements +0x48, advances +0x4C and
 * toggles +0x58. The spawner copies the attachment origin to +0x0C..+0x10. */
typedef struct CylindricalEffectWork {
    u8 pad_00[0xC];
    s16 origin_x, origin_y, origin_z;
    u8 pad_12[0x36];
    union { s16 s; u16 u; } timer;
    u8 pad_4A[2];
    s16 stage;
    u8 pad_4E[0xA];
    s32 shade;
} CylindricalEffectWork;

/* Effect parameters and countdown used by process_effect_modes_and_completion. */
typedef struct AndInitializeEffectObjectBody {
    u8 pad_00[0xC];
    ActorRecord *unk_0C;
    u8 pad_10[0x16];
    s16 unk_26;
    u8 pad_28[0x4];
    s16 unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
} AndInitializeEffectObjectBody;

/* Set to 1 by running particle/point effects every frame; the effect
 * controller in entry_play_sound_if_enabled clears it and finishes the effect
 * once a whole period passes with it still clear. */
extern s16 particle_effect_active;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 draw_concentric_effect_layers(void *effect, s32 position, s32 render_param);
s32 draw_cylindrical(void *effect, s32 position, s32 render_param);
void process_effect_modes_and_completion(void *state);

void advance_linked_object_counter(void *entry, s32 unused, SpriteFrameState *target);

void copy_selected_table_pair(ActorRecord *record_field, s32 pair_index);

/* Orbit center and angle for the indexed-color sprite. */
typedef struct IndexedColorSpriteBody {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
} IndexedColorSpriteBody;

/* Target ownership marker written when the homing effect completes. */
typedef struct MarkOwnerOnTargetCompletionBody {
    u8 pad_00[0x8];
    s16 unk_08;
} MarkOwnerOnTargetCompletionBody;

/* Radius, rotation, and countdown for a spiraling effect. */
typedef struct SpiralingBody {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x10];
    union { s16 s; u16 u; } unk_24;
    u8 pad_26[0x2];
    union { s16 s; u16 u; } unk_28;
    u16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x6];
    s16 unk_34;
} SpiralingBody;

s32 get_a_random_in_n_0_limit_zero_limit_zero_rejection_sampling(s32 limit);

#endif
