#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#ifndef DUNGEON_OVL_18D6800_H
#define DUNGEON_OVL_18D6800_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
typedef struct B28_818B7F38_S_80025738_0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2];
    void * unk_18;
} B28_818B7F38_S_80025738_0;
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
typedef struct B28_818B7F38_S_80025738_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} B28_818B7F38_S_80025738_3;
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
typedef struct B28_818B7F38_S_80025738_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} B28_818B7F38_S_80025738_6;
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
typedef struct B28_818B7E14_DungeonSource {
    s32 word[6];
} B28_818B7E14_DungeonSource;
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
    union { s16 s16; u8 u8; } unk_0E;   /* accessed as both */
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_18;   /* overlapping accesses */
    s16 unk_1C;
    s16 unk_1E;
} B28_818B7BD0_S_818B7BD0_1;
typedef struct B28_818B7BD0_S_818B7BD0_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x4];
    s32 unk_18;
} B28_818B7BD0_S_818B7BD0_2;
typedef struct B28_818B7BD0_S_818B7BD0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} B28_818B7BD0_S_818B7BD0_3;
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
typedef struct B28_818B7264_S_80024A64_2 {
    u8 pad_00[0x30];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
} B28_818B7264_S_80024A64_2;
typedef struct B28_818B6F90_S_818B6F90_0 {
    u8 * unk_00;
    union { s32 v; u32 v2; } unk_04;   /* accessed as both */
    u8 pad_08[0x8];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x2];
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x2];
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x2];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    u8 pad_6C[0x4];
    u16 unk_70;
    u16 unk_72;
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u16 unk_7E;
} B28_818B6F90_S_818B6F90_0;
typedef struct B28_818B6F90_S_818B6F90_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    s16 unk_0E;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x5];
    u8 unk_18;
    u8 unk_19;
    s16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x5];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
    u8 unk_2A;
    u8 pad_2B[0x1];
    u16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
    u8 unk_31;
} B28_818B6F90_S_818B6F90_2;
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
typedef struct B28_818B6954_S_818B6954_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} B28_818B6954_S_818B6954_0;
typedef struct B28_818B6954_S_818B6954_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} B28_818B6954_S_818B6954_1;
typedef struct B28_818B68B8_S_818B68B8_0_pre {
    u16 unk_00;
} B28_818B68B8_S_818B68B8_0_pre;
typedef struct B28_818B68B8_S_818B68B8_0 {
    void * unk_00;
    u16 unk_04;
} B28_818B68B8_S_818B68B8_0;
typedef struct B28_818B68B8_S_818B68B8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} B28_818B68B8_S_818B68B8_1;
typedef struct B28_818B68B8_S_818B68B8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} B28_818B68B8_S_818B68B8_2;
void interpolate_view_parameters(EntityRec *target, s32 gain_param, void *record);
void lower_animated_sprite(void *counter_state, B28_818B68B8_S_818B68B8_2 *value_state, SpriteFrameState *status);
void * create_colored_offset_sprite(s32 context_value, void *source_state, s32 render_param, s32 ignored_context);
void cycle_seven_color_fade(B28_818B6AFC_FxEffect *effect, s32 render_arg, B28_818B6AFC_FxColorOut *color_out);
s32 draw_indexed_shaded_quad(s32 texture_index, u8 *color_source);
s32 draw_two_radial_effect_bands(B28_818B7264_S_80024A64_0 *effect, B28_818B7264_S_80024A64_1 *center, s32 draw_arg);
void draw_chained_object_records(B28_818B77D4_Arg0818B77D4 *source, B28_818B77D4_Arg1818B77D4 *payload);
void update_spark_effect(B28_818B78E8_S818B78E8_Obj *obj, B28_818B78E8_S818B78E8_Vec *motion, SpriteFrameState *gfx);
s32 spawn_owner_random_variant_effect(B28_818B7BD0_S_818B7BD0_2 *owner, B28_818B7BD0_S_818B7BD0_3 *transform);
void advance_spinning_effect_motion(B28_818B7D3C_OwnerState *owner, B28_818B7D3C_VecState *vec, SpriteFrameState *entity);
s32 spawn_owned_random_spin_effect(void *owner, B28_818B7E14_DungeonSource *source);
void advance_movement_toward_reachable_tile(void *state, void *motion_in, void *render);
void select_record_entry_and_value(void *state, void *entries, short index);
extern u8 seven_color_sprite_data[];
s32 draw_linked_sprites_clipped(u8 *first_data, s32 link_value, void *value_record);
s32 func_80045C34(u8 *first_data, s32 link_value, void *value_record);
extern void *create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern s16 cap_pending_actor_value_delta(void *);
extern void apply_clamped_actor_value_delta(void *);
extern s32 get_random_scaled_value(s16 input_value);
#include "dungeon/effect/screen.h"
s32 rcos(s32);
s32 rsin(s32);
extern s32 RotAverage4(
    void *ptr0, void *ptr1, void *ptr2, void *ptr3,
    void *ptr4, void *ptr5, void *ptr6, void *ptr7,
    void *ptr8, void *ptr9);
extern s16 GetTPage(s32 value0, s32 value1, s32 value2, s32 value3);
extern s32 rand(void);
s32 check_layer_offset_height();              /* extern */
#endif
