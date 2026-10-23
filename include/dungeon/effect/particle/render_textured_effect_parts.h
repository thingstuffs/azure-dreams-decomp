#ifndef DUNGEON_OVL_183A800_H
#define DUNGEON_OVL_183A800_H
#include "shared/dungeon_effect_views.h"
#include "dungeon/effect/particle.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
typedef struct S_8181A800_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s16 unk_04;
} S_8181A800_0;
typedef struct {
    u8 pad0[2];
    s16 f2;
    s16 f4;
} D8181A8C0Header;
typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    s16 fa;
} D8181A8C0Vector;
typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[4];
    u8 fc;
    u8 fd;
    u8 fe;
    u8 padf;
    s16 f10;
    s16 f12;
    u16 f14;
    u8 pad16[6];
    s16 f1c;
    s16 f1e;
} D8181A8C0Asset;
typedef struct {
    u8 pad0[8];
    D8181A8C0Vector *field8;
    D8181A8C0Asset *fieldc;
    void *field10;
} D8181A8C0Object;
typedef struct Scratch800241EC {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch800241EC;
typedef struct MotionState {
    unsigned char pad_00[2];
    u16 frames_left;
    unsigned char pad_04[20];
    s16 mode;
    s16 period;
    u16 tick;
    unsigned char pad_1E[0x3a];
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} MotionState;
typedef struct UpdateFlags {
    unsigned char pad_00[0x14];
    u16 flags;
} UpdateFlags;
typedef struct S_8181B078_0_pre {
    u16 unk_00;
} S_8181B078_0_pre;
typedef struct S_8181B078_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x18];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x37];
    s32 unk_60;
} S_8181B078_0;
typedef struct S_8181B078_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8181B078_1;
typedef struct S_8181B078_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8181B078_2;
typedef struct S_8181B1A0_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8181B1A0_4;

typedef struct S_8181B1A0_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x5C];
    s32 unk_60;
} S_8181B1A0_0;
typedef struct S_8181B1A0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8181B1A0_2;
typedef struct S_80024BE8_0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x6C];
    union { u16 u; s16 s; } unk_78;   /* accessed as both */
    u8 unk_7A;
    s8 unk_7B;
    u8 pad_7C[0x2];
    union { s16 s; u16 u; } unk_7E;   /* accessed as both */
    u8 pad_80[0x2];
    u16 unk_82;
    u16 unk_84;
    union { u16 u; s16 s; } unk_86;   /* accessed as both */
    u8 pad_88[0x1A];
    s8 unk_A2;
    s8 unk_A3;
} S_80024BE8_0;
typedef struct S_80024BE8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80024BE8_1;
typedef struct S_80024BE8_2 {
    u8 pad_00[0xC];
    union {
        struct { s32 v; } at00;
        struct { s8 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024BE8_2;
typedef struct S_80024BE8_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024BE8_3_pre;
typedef struct S_80024BE8_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_80024BE8_3;
typedef struct S_80024BE8_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80024BE8_4;
typedef struct S_80024BE8_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024BE8_5;

typedef struct S_80024BE8_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_80024BE8_7;
typedef struct S_80024BE8_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80024BE8_8;
typedef struct S_80024BE8_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80024BE8_9;
typedef struct S_80024BE8_10 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80024BE8_10;
typedef struct S_80024BE8_13 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80024BE8_13;
typedef struct S_80024BE8_14 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80024BE8_14;
typedef struct S_80024BE8_15 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_80024BE8_15;
typedef struct S_80024BE8_19 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80024BE8_19;
typedef struct S_80024BE8_20_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024BE8_20_pre;
typedef struct S_80024BE8_21 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024BE8_21;
typedef struct S_80024BE8_22 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024BE8_22;
typedef struct S_80024BE8_23_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_80024BE8_23_pre;
typedef struct S_80024BE8_23 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_80024BE8_23;
typedef struct Pair16 {
    s16 x;
    u16 y;
} Pair16;
typedef struct PathBlock {
    Pair16 entries[8];
} PathBlock;
void select_record_entry_and_value(void *, void *, s32);
s32 draw_transformed_sprite_with_clip_rect(void *, void *, void *, s32, s32);
u32 RotTransPers(void *, void *, void *, void *);
extern s16 textured_effect_update_flag;
typedef struct S_80045C34 { u8 pad0[6]; s16 unk6; u8 pad1[12]; u16 unk14; } S_80045C34;
s32 draw_linked_sprites_clipped(u8 *, s32, S_80045C34 *);
s32 func_80045C34(u8 *, s32, S_80045C34 *);
void render_textured_effect_parts(void *record_data, void *unused, void *update_data);
void create_offset_paletted_sprite(void *unused_context, void *origin, s32 unused_id, s16 offset_x, s16 offset_y, s16 offset_z);
s32 draw_shaded_point_chain(PointRecord *first_point, ObjectPosition *first_position);
void create_radial_height_offset_effect(MotionState *state, s32 *sum, SpriteFrameState *flags);
void advance_scattered_directional_particle(void *object_data, s16 *position);
void func_80024758(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void cycle_moving_effect_phase(void *object, S_8181B078_1 *position, S_8181B078_2 *source);
void decrement_object_counter(void *source, s32 offset_x, s32 offset_y, s32 offset_z, s16 effect_value);
void grow_timed_sprite_effect(void *state_data, s32 unused, void *target);

#endif
