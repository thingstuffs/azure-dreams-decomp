#ifndef DUNGEON_OVL_188E800_H
#define DUNGEON_OVL_188E800_H
#include "shared/dungeon_effect_views.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"

/* Promoted Layer-2 record names and layouts are shared without changing the bodies. */

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Scratch8002416C {
    u16 x;
    u16 y;
    u16 z;
    u8 pad_06[0x12];
    u8 *cursor;         /* next free packet */
    u8 pad_1C[4];
    u32 *ot;            /* ordering table */
    u8 pad_24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad_98[0x28];
    u32 index;          /* ordering table slot */
} Scratch8002416C;

/* Shaded point primitive (code 0x6A, 3 words). */

typedef struct { u8 b[32]; } AggU32;
typedef struct {
    s16 x;
    s16 y;
} OffsetPair;
typedef struct S_8186EDA8_0 {
    s32 unk_00;
    s32 unk_04;
} S_8186EDA8_0;
typedef struct {
    s16 state;
    u16 timer;
    u8 pad4[6];
    s16 count;
    s16 angle;
    u16 angle2;
    u8 pad10[0x3C];
    s32 base0;
    s32 base1;
} DungeonState;
typedef struct {
    u8 pad0[0xC];
    u8 c;
    u8 d;
    u8 e;
    u8 padF[5];
    u16 flags14;
    u8 pad16[6];
    u16 x1C;
    u16 y1E;
} DungeonEffect;
typedef struct { u32 addr:24; u32 length:8; } PacketTag;
typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    union {
        s32 unk8;
        struct {
            u16 unk8_lo;
            u16 unkA;
        } half;
    } value;
} UnkArg1;
extern const u8 no_effect_target_prefix[48];
extern const u8 no_effect_target_period[4];
extern const s16 D_80024038[8][2];
extern s16 D_80025308;
/* Work at node +0x20 for the moving color effect. The two views keep
 * signed flight arithmetic and unsigned countdown updates on the same bytes. */
typedef struct MovingColorWork {
    u8 *owner;
    struct { u16 flags; } *animation;
    u8 pad_08;
    u8 variant;
    s16 state;
    u8 pad_0C[0x6C];
    union { s16 s; u16 u; } target_height;
    u8 flags;
    union { s8 s; u8 u; } flight_ticks;
    u8 pad_7C[2];
    s16 direction;
    u8 pad_80[2];
    s16 timer;
    u8 pad_84[4];
    s16 initial_ticks;
    s16 ticks_squared;
    u8 pad_8C[6];
    s16 sprite_phase;
    union {
        u8 bytes[12];
        struct { u8 pad_00[8]; u8 unk_9C; u8 pad_09[3]; } fields;
    } sprite_data;
    u8 next_tile_x;
    u8 next_tile_y;
} MovingColorWork;

void update_moving_effect_particles_and_cleanup(MovingColorWork *effect_data, ObjectPosition *effect_pos, SpriteFrameState *effect_display);
void advance_rotating_fading_effect(DungeonState *anim, S_8186EDA8_0 *position, DungeonEffect *input_effect);
s32 draw_linked_brightness_points(PointRecord *start_node, ObjectPosition *start_coords);
void lift_attached_particle_above_terrain_and_age(u8 *state, UnkArg1 *position);
void apply_random_actor_value_adjustment(ActorRecord *entity, s32 effect_param, void *context);
void spawn_parent_attached_effect( ObjectNodeHeader *source, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
#endif
