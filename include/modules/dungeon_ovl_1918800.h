#ifndef DUNGEON_OVL_1918800_H
#define DUNGEON_OVL_1918800_H
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "sdk/rand.h"
typedef struct PackedVector {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));
typedef struct Pair16 {
    s16 x;
    s16 y;
} Pair16;
typedef struct {
    s16 x;
    u16 y;
} Copy4;
typedef struct {
    Copy4 entries[8];
} __attribute__((packed)) Copy24;
typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

/* Wave body built by the projectile impact (allocate_flagged_object_node(0x212)): its 0x60 levels are the per-row
 * displacement amplitudes, rotation_angle the starting sine phase and unk_9A the phase step per strip; the node
 * allocator clears the body, so a zero wave_axis displaces rows and a nonzero one columns. */
typedef struct ParticleState {
    s16 phase;
    s16 unk_02; /* fade duration or timed-wave frame, according to installed callback */
    s16 frame;
    u8 pad_06[0x4];
    s16 peak_frame;
    u8 pad_0C[0xE];
    Copy12 anim;
    u8 pad_26[0x2];
    void *parent;
    void *target;
    struct ProjectileSelf *source;
    void *flash_state;
    u8 levels[0x60];
    s16 rotation_angle;
    s16 unk_9A;
    s16 wave_axis; /* draw_wave_distorted_sprite: zero displaces rows along X, nonzero columns along Y */
} ParticleState;

typedef struct WaveScreenOrigin {
    u16 x;
    u16 y;
} WaveScreenOrigin; /* screen position draw_wave_sprite_in_draw_area draws the wave sprite at */

extern s16 wave_effect_update_flag;
extern const PackedVector wave_texture_rect;
extern const PackedVector wave_source_rect;
extern const Copy24 wave_direction_steps;
struct CountdownRecord;
struct PointRecord;
struct Position;
struct ProjectileSelf;
struct SpriteFrameState;

void draw_wave_distorted_sprite(struct WaveScreenOrigin *screen_pos, struct ParticleState *wave, void *context, u32 *ordering_table, s32 draw_control);
void draw_wave_sprite_in_draw_area(struct ParticleState *wave, void *context, struct Position *restore_area, struct Position *draw_pos, u32 clear_area, s32 draw_option);
s32 draw_linked_brightness_points(struct PointRecord *start_node, ObjectPosition *start_coords);
s32 random_unit_sign(void);
void create_random_jitter_child( ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void tick_wave_effect_countdown(struct CountdownRecord *record);
void update_expanding_wave_impact_effect(struct ParticleState *effect, void *unused, struct SpriteFrameState *output);
void advance_grayscale_fade(struct ParticleState *state, s32 unused, struct SpriteFrameState *out);
void update_timed(struct ParticleState *state, struct ObjectPosition *position_out, struct SpriteFrameState *effect_arg);
void update_wave_projectile_effect(struct ProjectileSelf *self, struct ObjectPosition *position, struct SpriteFrameState *render_data);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
#endif
