#ifndef DUNGEON_OVL_18D0850_H
#define DUNGEON_OVL_18D0850_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "sdk/libc.h"
#include "dungeon/level.h"
#include "dungeon/effect.h"
typedef struct { u8 pad00[0x14]; u16 flags; } ovl_18d0850_818B097C_EffectCounter;
typedef struct { ovl_18d0850_818B097C_EffectCounter *parent; } ovl_18d0850_818B097C_EffectOwner;
typedef struct ovl_18d0850_818B09F8_SubObj {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 padF[3];
    s16 unk12;
    u16 unk14;
    u8 pad16[6];
    s16 unk1C;
    s16 unk1E;
} ovl_18d0850_818B09F8_SubObj;
typedef struct ovl_18d0850_818B09F8_VecObj {
    u16 pad0;
    u16 unk2;
    u16 pad4;
    u16 unk6;
    u16 pad8;
    u16 unkA;
} ovl_18d0850_818B09F8_VecObj;
typedef struct ovl_18d0850_818B09F8_MainObj {
    u8 pad0[8];
    ovl_18d0850_818B09F8_VecObj *vec;
    ovl_18d0850_818B09F8_SubObj *sub;
    void *callback;
    u8 pad14[0xC];
    s32 source_state;
} ovl_18d0850_818B09F8_MainObj;
typedef struct ovl_18d0850_818B0AE0_S_800242E0_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} ovl_18d0850_818B0AE0_S_800242E0_0;
typedef struct ovl_18d0850_818B0AE0_S_800242E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} ovl_18d0850_818B0AE0_S_800242E0_1;
typedef struct ovl_18d0850_818B0AE0_S_800242E0_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} ovl_18d0850_818B0AE0_S_800242E0_2;
typedef struct ovl_18d0850_818B0C3C_S_8002443C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} ovl_18d0850_818B0C3C_S_8002443C_0;
typedef struct ovl_18d0850_818B0C3C_S_8002443C_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} ovl_18d0850_818B0C3C_S_8002443C_1;
typedef struct ovl_18d0850_818B0C3C_S_8002443C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_18d0850_818B0C3C_S_8002443C_2;
typedef struct
{
  u8 pad00[0x18];
  u32 *ot;
  u8 pad1C[0x48];
  u16 unk_64;
  u16 unk_66;
  u16 unk_68;
  u8 pad6A[0x2];
  u16 unk_6C;
  u16 unk_6E;
  u16 unk_70;
  u8 pad72[0x12];
  s32 unk_84;
  s32 unk_88;
  u8 pad8C[0x28];
  s32 unk_B4;
  u8 padB8[0x20];
  u16 unk_D8;
  u16 unk_DA;
  u16 unk_DC;
  u16 unk_DE;
  u8 padE0[0x14];
  s32 unk_F4;
  s32 unk_F8;
} ovl_18d0850_818B0E10_LineSegmentScratch;
typedef struct {
    unsigned addr: 24;
    unsigned len: 8;
    u8 r0, g0, b0, code;
} ovl_18d0850_818B0E10_P_TAG;
#define ovl_18d0850_818B0E10_setaddr(p, _addr) (((ovl_18d0850_818B0E10_P_TAG *)(p))->addr = (u32)(_addr))
#define ovl_18d0850_818B0E10_getaddr(p) (u32)(((ovl_18d0850_818B0E10_P_TAG *)(p))->addr)
#define ovl_18d0850_818B0E10_addPrim(ot, p) ovl_18d0850_818B0E10_setaddr(p, ovl_18d0850_818B0E10_getaddr(ot)), ovl_18d0850_818B0E10_setaddr(ot, p)
typedef struct ovl_18d0850_818B11B4_S_818B11B4_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x4];
    u16 unk_16;
} ovl_18d0850_818B11B4_S_818B11B4_0;
typedef struct ovl_18d0850_818B11B4_S_818B11B4_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} ovl_18d0850_818B11B4_S_818B11B4_1;
typedef struct ovl_18d0850_818B1334_S_818B1334_0 {
    s32 unk_00;
    u8 pad_04[0x40];
    s32 unk_44;
} ovl_18d0850_818B1334_S_818B1334_0;
typedef struct ovl_18d0850_818B1334_S_818B1334_1 {
    u8 pad_00[0x10];
    s16 unk_10;
} ovl_18d0850_818B1334_S_818B1334_1;
typedef struct ovl_18d0850_818B1334_S_818B1334_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} ovl_18d0850_818B1334_S_818B1334_2;
typedef struct ovl_18d0850_818B1484_S_818B1484_0 {
    s32 unk_00;
    u8 pad_04[0x40];
    s32 unk_44;
} ovl_18d0850_818B1484_S_818B1484_0;
typedef struct ovl_18d0850_818B1484_S_818B1484_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x4];
    u16 unk_16;
} ovl_18d0850_818B1484_S_818B1484_1;
typedef struct ovl_18d0850_818B1484_S_818B1484_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} ovl_18d0850_818B1484_S_818B1484_2;
#define M2C_FIELD(expr, type_ptr, offset)      (*(type_ptr)((s8 *)(expr) + (offset)))
typedef struct {
    u8 pad00[0xA];
    s16 state;
} ovl_18d0850_818B15F4_Func818B15F4Arg;
struct S_818B11B4_0;
struct S_818B11B4_2;
struct S_818B1334_1;
struct S_818B1334_3;
struct S_818B1484_1;
struct S_818B1484_3;
typedef union ovl_18d0850_818B1664_FixedWord {
    s32 word;
    struct {
        u16 lo;
        s16 hi;
    } half;
} ovl_18d0850_818B1664_FixedWord;
typedef struct ovl_18d0850_818B1664_Motion {
    ovl_18d0850_818B1664_FixedWord x;
    ovl_18d0850_818B1664_FixedWord y;
    ovl_18d0850_818B1664_FixedWord z;
    ovl_18d0850_818B1664_FixedWord dx;
    ovl_18d0850_818B1664_FixedWord dy;
    ovl_18d0850_818B1664_FixedWord dz;
} ovl_18d0850_818B1664_Motion;
typedef struct ovl_18d0850_818B1664_WorkFrame {
    ovl_18d0850_818B1664_Motion target;
    s16 distance[3];
} ovl_18d0850_818B1664_WorkFrame;
typedef struct ovl_18d0850_818B1664_TargetInfo {
    u8 pad0[8];
    void *map;
    u8 padC[8];
    u16 flags;
    u8 pad16[14];
    u8 tileX;
    u8 tileY;
} ovl_18d0850_818B1664_TargetInfo;
typedef struct ovl_18d0850_818B1664_EntityHeader {
    u8 pad0[8];
    ovl_18d0850_818B1664_Motion *position;
    ovl_18d0850_818B1664_TargetInfo *info;
} ovl_18d0850_818B1664_EntityHeader;
typedef struct ovl_18d0850_818B1664_Child {
    u8 pad0[0x1C];
    u32 flags;
} ovl_18d0850_818B1664_Child;
typedef struct ovl_18d0850_818B1664_Entity {
    u8 pad0[0x2A];
    u16 flags2A;
    u8 pad2C[0x34];
    ovl_18d0850_818B1664_Child *child;
    u8 pad64[0x24];
    s16 height;
} ovl_18d0850_818B1664_Entity;
typedef struct ovl_18d0850_818B1664_EffectInner {
    u8 pad0[0xC];
    s32 value;
} ovl_18d0850_818B1664_EffectInner;
typedef struct ovl_18d0850_818B1664_Effect {
    u8 pad0[0xC];
    ovl_18d0850_818B1664_EffectInner *inner;
    u8 pad10[0xE];
    u16 flags;
} ovl_18d0850_818B1664_Effect;
typedef struct ovl_18d0850_818B1664_Resource {
    u16 flags;
} ovl_18d0850_818B1664_Resource;
typedef struct ovl_18d0850_818B1664_State {
    ovl_18d0850_818B1664_Entity *entity;
    ovl_18d0850_818B1664_Resource *resource;
    u8 pad8;
    u8 id;
    s16 state;
    u16 flags;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 field14;
    s16 timer2;
    s16 angleStep;
    s16 angles[8];
    s16 pad2A;
    ovl_18d0850_818B1664_Effect *effects[10];
} ovl_18d0850_818B1664_State;
typedef struct ovl_18d0850_818B1664_DrawInfo {
    u8 pad0[0xC];
    s32 color;
} ovl_18d0850_818B1664_DrawInfo;
typedef struct ovl_18d0850_818B1664_LargeScalar {
    s32 value;
    s32 pad[2];
} ovl_18d0850_818B1664_LargeScalar;
#include "dungeon/effect/screen.h"
#include "sdk/abs.h"
#include "sdk/libgpu.h"
extern s32 get_random_scaled_value(s16 input_value);
extern void advance_sprite_animation_and_textures(void *);
extern s32 D_800814A0;
void select_record_entry_and_value(void *state_data, void *entry_data, short index);
extern void register_node(ovl_18d0850_818B09F8_MainObj *, void *);
#include "dungeon/effect/sprite/shared_entries.h"
extern unsigned char resident_globals_page[];
#include "sdk/libgte.h"
#include "shared/scratchpad.h"
extern M2C_UNK D_8002588C;
extern s32 resolve_record_orientation_or_fallback(void *, void *, s16 *, s32);
extern s32 check_layer_offset_height(s32, s32, s32, s32);
void apply_random_actor_value_gain(EntityRec *entity, s32 value_id, void *record);
void write_fixed_palette_pixels(void *unused0, void *unused1, void *unused2);
void advance_owner_effect_counter(ovl_18d0850_818B097C_EffectOwner *owner, void *unused, SpriteFrameState *state);
ovl_18d0850_818B09F8_MainObj *create_owner_counter_sprite_effect(s32 object_value, ovl_18d0850_818B09F8_VecObj *source_vec);
void advance_height_offset_and_placement(ovl_18d0850_818B0AE0_S_800242E0_0 *state, ovl_18d0850_818B0AE0_S_800242E0_2 *position, SpriteFrameState *object);
s32 create_radial_height_offset_effect(s32 owner, void *origin, s16 motion, s16 frame);
s32 queue_shaded_line_segments(void *unused_0, void *origin, SpriteFrameState *unused_2, s32 point_scale, s32 plane_z, s32 *points_addr, u8 intensity, s32 color_phase);
s32 queue_height_offset_rings(ovl_18d0850_818B11B4_S_818B11B4_0 *source, ObjectPosition *height_ref, void *context);
s32 queue_phase_shifted_rings(ovl_18d0850_818B1334_S_818B1334_1 *source, ObjectPosition *target, SpriteFrameState *context);
s32 draw_remaining_shaded_rings(ovl_18d0850_818B1484_S_818B1484_1 *effect, ObjectPosition *target, void *context);
s32 dispatch_effect_state_handler(void *state_ptr, ObjectPosition *second_ptr, SpriteFrameState *third_ptr);
void update_radial_effect_toward_target(ovl_18d0850_818B1664_State *state_arg, ovl_18d0850_818B1664_Motion *motion_arg, ovl_18d0850_818B1664_DrawInfo *draw_info);
#endif
