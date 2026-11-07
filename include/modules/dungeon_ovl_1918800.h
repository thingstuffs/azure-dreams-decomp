#ifndef DUNGEON_OVL_1918800_H
#define DUNGEON_OVL_1918800_H
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "m2c_compat.h"
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
extern s16 wave_effect_update_flag;
extern const PackedVector wave_texture_rect;
extern const PackedVector wave_source_rect;
extern const Copy24 wave_direction_steps;
struct CountdownRecord;
struct ParticleState;
struct PointRecord;
struct Position;
struct ProjectileSelf;
struct SpriteFrameState;

void draw_wave_distorted_sprite(void *screen_pos, u8 *wave, void *context, s32 *ordering_table, s32 draw_control);
void move_linked_effect_along_path(s32 draw_param_a, s32 draw_param_b, struct Position *restore_area, struct Position *draw_pos, u32 clear_area, s32 draw_option);
s32 draw_linked_brightness_points(struct PointRecord *start_node, ObjectPosition *start_coords);
s32 advance_effect_sequence(void);
void create_random_jitter_child( ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void advance_record_counter(struct CountdownRecord *record);
void process_five_context_entries_or_fallback(struct ParticleState *effect, void *unused, struct SpriteFrameState *output);
void advance_grayscale_fade(struct ParticleState *state, s32 unused, struct SpriteFrameState *out);
void update_timed(struct ParticleState *state, struct ObjectPosition *position_out, struct SpriteFrameState *effect_arg);
void set_record_pair_to_one(struct ProjectileSelf *self, struct ObjectPosition *position, struct SpriteFrameState *render_data);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
s32 rand(void);
#endif
