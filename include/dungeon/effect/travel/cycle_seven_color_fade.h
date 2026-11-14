#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#ifndef DUNGEON_OVL_18D6800_H
#define DUNGEON_OVL_18D6800_H
struct B28_818B6AFC_FxEffect;
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"
#include "shared/object_flags.h"
#include "shared/slus_callbacks.h"
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect.h"
#include "dungeon/effect/spell_effect.h"

/* Spell state for reachable tile travel and its spawned owner variants. */
typedef struct ReachableTileTravelBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2];
    void * unk_18;
} ReachableTileTravelBody;
typedef struct B28_818B7F38_S_80025738_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} B28_818B7F38_S_80025738_1;
typedef struct B28_818B7F38_S_80025738_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} B28_818B7F38_S_80025738_2;
typedef struct B28_818B7F38_S_80025738_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} B28_818B7F38_S_80025738_4;
typedef struct B28_818B7F38_S_80025738_5 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} B28_818B7F38_S_80025738_5;
typedef struct B28_818B7F38_S_80025738_7 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} B28_818B7F38_S_80025738_7;
typedef struct B28_818B7F38_S_80025738_8 {
    u8 pad_00[0x88];
    s16 unk_88;
} B28_818B7F38_S_80025738_8;
typedef struct B28_818B7F38_S_80025738_9 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
} B28_818B7F38_S_80025738_9;
typedef struct B28_818B7F38_S_80025738_10 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} B28_818B7F38_S_80025738_10;
typedef struct B28_818B7F38_S_80025738_11 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
} B28_818B7F38_S_80025738_11;
typedef struct B28_818B7F38_S_80025738_13 {
    u8 pad_00[0x14];
    u16 unk_14;
} B28_818B7F38_S_80025738_13;
typedef struct B28_818B7F38_S_80025738_14_pre {
    void * unk_00;
    u8 pad_04[0x14];
} B28_818B7F38_S_80025738_14_pre;
typedef struct B28_818B7F38_S_80025738_14 {
    u8 pad_00[0x88];
    s16 unk_88;
} B28_818B7F38_S_80025738_14;
typedef struct B28_818B7F38_LocalFrame {
    s32 out_x;
    s32 out_y;
    s32 out_z;
    u8 pad_C[12];
    GteOffset offset;
} B28_818B7F38_LocalFrame;
typedef struct B28_818B7E14_DungeonRenderData {
    u8 pad00[0xC];
    u8 color_r;
    u8 color_g;
    u8 color_b;
    u8 pad0F[3];
    s16 f12;
    u16 f14;
    u8 pad16[4];
    s16 f1A;
    s16 f1C;
    s16 f1E;
} B28_818B7E14_DungeonRenderData;
typedef struct B28_818B7E14_DungeonObject {
    u8 pad00[8];
    s32 *data;
    SpriteFrameState *render;
    void *update;
    u8 pad14[0xC];
    void *owner;
    u8 pad24[0xC];
    s16 f30;
    u8 pad32[2];
    u16 f34;
} B28_818B7E14_DungeonObject;
typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} B28_818B7D3C_VecState;
typedef struct {
    u8 pad00[0x14];
    u16 counter;
} B28_818B7D3C_ChildState;
typedef struct {
    B28_818B7D3C_ChildState *child;
    u8 pad04[12];
    u16 counter;
    u8 pad12[2];
    s16 limit;
} B28_818B7D3C_OwnerState;
typedef struct {
    u8 pad00[0x1A];
    u16 angle;
} B28_818B7D3C_EntityState;
typedef struct B28_818B7BD0_S_818B7BD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} B28_818B7BD0_S_818B7BD0_0;
typedef struct B28_818B7BD0_S_818B7BD0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_18;   /* overlapping accesses */
    s16 unk_1C;
    s16 unk_1E;
} B28_818B7BD0_S_818B7BD0_1;
typedef struct B28_818B7BD0_S_818B7BD0_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} B28_818B7BD0_S_818B7BD0_4;
typedef union {
    s64 value;
    s32 word[2];
} B28_818B7BD0_M2C_WIDE;
typedef struct {
    u8 pad[0x14];
    u16 field14;
} B28_818B78E8_S818B78E8_Child;
typedef struct {
    B28_818B78E8_S818B78E8_Child *child;
    u8 pad04[0xA];
    s16 state;
    s16 field10;
    u16 field12;
    s16 field14;
} B28_818B78E8_S818B78E8_Obj;
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
} B28_818B78E8_S818B78E8_Vec;
typedef struct {
    u8 pad[0xC];
    s8 fieldC;
    s8 fieldD;
    s8 fieldE;
    u8 pad0F[3];
    s16 field12;
    u16 flags;
    u8 pad16[4];
    u16 field1A;
    s16 field1C;
    s16 field1E;
} B28_818B78E8_S818B78E8_State;
typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
} B28_818B77D4_Inner818B77D4;
typedef struct {
    u8 pad0[8];
    void *unk8;
    u8 padC[4];
    void *unk10;
    u8 pad14[12];
    B28_818B77D4_Inner818B77D4 unk20;
} B28_818B77D4_Obj818B77D4;
typedef struct {
    s32 unk0;
    u8 pad4[14];
    u16 unk12;
    u8 pad14[4];
    s32 unk18;
} B28_818B77D4_Arg0818B77D4;
typedef struct {
    s32 words[6];
} B28_818B77D4_Arg1818B77D4;
typedef struct B28_818B7264_S_80024A64_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} B28_818B7264_S_80024A64_0;
typedef struct B28_818B7264_S_80024A64_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} B28_818B7264_S_80024A64_1;
/* Scratchpad slots of draw_indexed_shaded_quad: draw_two_radial_effect_bands leaves the four 16.16
 * corner positions of a band segment in positions; their integer halves become the RotAverage4
 * vertices, whose screen XY words land in screen before they are copied into the POLY_GT4. */
typedef struct RadialBandQuadScratch {
    /* 0x00 */ u32 *ordering_table;
    /* 0x04 */ u32 ot_index;
    /* 0x08 */ s32 depth_cue; /* RotAverage4 depth-cue output */
    /* 0x0C */ s32 gte_flag; /* RotAverage4 GTE flag output */
    /* 0x10 */ SVECTOR vertices[4];
    /* 0x30 */ VECTOR positions[4];
    /* 0x70 */ SpriteScratchScreenPoint screen[4];
} RadialBandQuadScratch;
typedef struct B28_818B6F90_S_818B6F90_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} B28_818B6F90_S_818B6F90_3;
typedef struct B28_818B6AFC_FxOwner {
    u8 pad_00[0x14];
    u16 count;
} B28_818B6AFC_FxOwner;
typedef struct B28_818B6AFC_FxEffectPre {
    u16 flags;   /* the u16 just before the effect, addressed as effect[-1] */
} B28_818B6AFC_FxEffectPre;
typedef struct B28_818B6AFC_FxRgb {
    u8 pad_00[0xC];
    s8 r;
    s8 g;
    s8 b;
} B28_818B6AFC_FxRgb;
typedef struct B28_818B6AFC_FxColorOut {
    u8 pad_00[0xC];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } rgb;   /* overlapping accesses */
} B28_818B6AFC_FxColorOut;
typedef struct B28_818B6AFC_FxTarget {
    u8 pad_00[0x1C];
    s32 flags;
} B28_818B6AFC_FxTarget;
typedef struct B28_818B6AFC_FxTargetPre {
    void *color;
    u8 pad_04[0x10];
} B28_818B6AFC_FxTargetPre;
typedef struct B28_818B6AFC_FxEffect {
    B28_818B6AFC_FxOwner *owner;
    u8 pad_04[0x2];
    u16 frame;
    u16 tick;
    u8 pad_0A[0x2];
    u16 scroll_u;
    u16 scroll_v;
    B28_818B6AFC_FxTarget *target;
} B28_818B6AFC_FxEffect;
typedef struct {
    s32 w[6];
} B28_818B6954_Copy24;
typedef struct ColoredOffsetSpriteBody {
    union { void *owner; s32 context_value; } owner_context;
    u16 update_count;
    u16 state;
} ColoredOffsetSpriteBody;
typedef struct B28_818B68B8_S_818B68B8_0_pre {
    u16 unk_00;
} B28_818B68B8_S_818B68B8_0_pre;
typedef struct B28_818B68B8_S_818B68B8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} B28_818B68B8_S_818B68B8_1;
typedef struct B28_818B68B8_S_818B68B8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} B28_818B68B8_S_818B68B8_2;
void interpolate_view_parameters(EntityRec *target, s32 gain_param, void *record);
void lower_animated_sprite(ColoredOffsetSpriteBody *counter_state, ObjectPosition *value_state, SpriteFrameState *status);
void * create_colored_offset_sprite(s32 context_value, ObjectPosition *source_state, s32 render_param, struct B28_818B6AFC_FxEffect *ignored_context);
void cycle_seven_color_fade(B28_818B6AFC_FxEffect *effect, ObjectPosition *render_arg, B28_818B6AFC_FxColorOut *color_out);
s32 draw_indexed_shaded_quad(s32 texture_index, SpriteFrameState *color_source);
s32 draw_two_radial_effect_bands(B28_818B7264_S_80024A64_0 *effect, ObjectPosition *center, SpriteFrameState *draw_arg);
void create_randomized_radial_band_effect(B28_818B77D4_Arg0818B77D4 *source, B28_818B77D4_Arg1818B77D4 *payload);
void update_seven_color_spark_effect(B28_818B78E8_S818B78E8_Obj *obj, ObjectPosition *motion, SpriteFrameState *gfx);
s32 spawn_owner_random_variant_effect(ReachableTileTravelBody *owner, ObjectPosition *transform);
void advance_spinning_effect_motion(B28_818B7D3C_OwnerState *owner, ObjectPosition *vec, SpriteFrameState *entity);
s32 spawn_owned_random_spin_effect(ReachableTileTravelBody *owner, ObjectPosition *source);
void advance_movement_toward_reachable_tile(ReachableTileTravelBody *state, ObjectPosition *motion_in, SpriteFrameState *render);
void select_record_entry_and_value(void *state, void *entries, short index);
extern u8 seven_color_sprite_data[];
s32 draw_linked_sprites_clipped(u8 *first_data, s32 link_value, SpriteFrameState *value_record);
s32 func_80045C34(u8 *first_data, s32 link_value, void *value_record);
extern s32 get_random_scaled_value(s16 input_value);
#include "dungeon/effect/screen.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/rand.h"
s32 check_layer_offset_height();              /* extern */
#endif
