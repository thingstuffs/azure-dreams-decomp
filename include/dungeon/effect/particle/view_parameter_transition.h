#ifndef DUNGEON_OVL_188E800_H
#define DUNGEON_OVL_188E800_H
#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_native_abi.h"

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
typedef struct S_8186EDA8_1 {
    u16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u16 unk_04;
    u8 pad_06[0x6];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
} S_8186EDA8_1;
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
typedef struct S_8002416C_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    u8 * unk_18;
    u8 pad_1C[0x4];
    union { u8 * p; u32 * p2; } unk_20;   /* accessed as both */
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_8002416C_1;
typedef struct S_8002416C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8002416C_2;
typedef struct S_8002416C_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_8002416C_3;
typedef struct S_8002416C_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_8002416C_4_pre;
typedef struct S_8002416C_4 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_8002416C_4;
typedef struct S_8002416C_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_8002416C_5;
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
typedef struct S_func_8186E800_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_func_8186E800_0;
typedef struct S_80024488_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_80024488_0;
typedef struct S_80024488_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80024488_1;
typedef struct S_80024488_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80024488_2;
typedef struct S_80024488_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80024488_3;
typedef struct S_80024488_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80024488_4;
typedef struct S_80024488_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80024488_5;
typedef struct S_80024488_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024488_6;
extern const u8 D_80024004[48];
extern const u8 D_80024034[4];
extern const s16 D_80024038[8][2];
extern s16 D_80025308;
void update_moving_effect_particles_and_cleanup(u8 *effect_data, u8 *effect_pos, u8 *effect_display);
void advance_rotating_fading_effect(DungeonState *anim, S_8186EDA8_0 *position, DungeonEffect *input_effect);
s32 begin_view_parameter_transition(PointRecord *start_node, EntityRec *start_coords);
void create_randomized_transform_effect(u8 *state, UnkArg1 *position);
void apply_random_actor_value_adjustment(S_func_8186E800_0 *entity, s32 effect_param, void *context);
void spawn_parent_attached_effect( ObjectNodeHeader *source, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
#endif
