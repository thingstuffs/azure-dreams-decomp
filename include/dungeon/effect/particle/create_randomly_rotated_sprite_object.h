#ifndef DUNGEON_OVL_18B2800_H
#define DUNGEON_OVL_18B2800_H
struct B22_81893474_EffectState;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/tile_object.h"
#include "modules/dungeon_native_abi.h"

typedef struct B22_81893474_ColorPart {
    u8 pad[0xC];
    u32 color;
} B22_81893474_ColorPart;
/* Target coordinates passed to terrain helpers; the original work area is
 * sixteen bytes, followed by the independent orientation probe and flags. */
typedef struct EffectTargetPosition {
    Fixed1616 x, y, z;
    u8 pad_0C[4];
} EffectTargetPosition;
typedef struct B22_81893474_Scratch {
    EffectTargetPosition work;
    u8 gap[8];
    s16 probe[3];
    u8 result_gap[2];
    s16 result;
    u16 map_flags;
} B22_81893474_Scratch;
typedef struct B22_81893244_Func81893244Data B22_81893244_Func81893244Data;
typedef struct B22_81893244_Func81893244Sub B22_81893244_Func81893244Sub;
typedef struct B22_81893244_Func81893244Object B22_81893244_Func81893244Object;
typedef struct B22_818931B8_S_818931B8_1 B22_818931B8_S_818931B8_1;
struct B22_81893244_Func81893244Data {
    s32 u0;
    s32 u4;
    s32 word8;
    s32 uC;
    s32 field10;
    s32 field14;
};
struct B22_81893244_Func81893244Sub {
    s32 u0;
    s32 u4;
    s32 word8;
    s32 uC;
    u16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
};
typedef struct AnimatedSpriteBurstBody {
    union {
        B22_818931B8_S_818931B8_1 *counter_state;
        s32 source_value;
    } target;
    u16 update_count;
    s16 update_limit;
} AnimatedSpriteBurstBody;
typedef struct VerticalAccelerationSpriteBody {
    union { void *owner; s32 state_value; } target;
    s16 update_count;
    s16 update_limit;
} VerticalAccelerationSpriteBody;
struct B22_81893244_Func81893244Object {
    u8 pad0[8];
    B22_81893244_Func81893244Data *field8;
    B22_81893244_Func81893244Sub *fieldC;
    void *field10;
    u8 pad14[12];
    AnimatedSpriteBurstBody status;
};
struct B22_818931B8_S_818931B8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
};
typedef struct B22_818931B8_S_818931B8_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} B22_818931B8_S_818931B8_2;
typedef struct B22_818930F8_S_818930F8_0 {
    void * unk_00;
    u16 unk_04;
    s16 unk_06;
} B22_818930F8_S_818930F8_0;
typedef struct B22_818930F8_S_818930F8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} B22_818930F8_S_818930F8_1;
typedef struct {
    s8 unk0[8];
    ObjectPosition *data;
    s8 unkC[4];
    void *callback;
    s8 unk14[12];
    s32 params;
} B22_81893024_M2C_OBJECT;
typedef struct B22_81892C5C_S_81892C5C_0 {
    u8 pad_00[0x18];
    union { void * s; u32 * u; } unk_18;   /* accessed as both */
    u8 pad_1C[0x48];
    s16 unk_64;
    s16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    s16 unk_6E;
    u16 unk_70;
    u8 pad_72[0x2];
    s16 unk_74;
    s16 unk_76;
    u16 unk_78;
    u8 pad_7A[0x3A];
    union { s32 s; u32 u; } unk_B4;   /* accessed as both */
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u16 unk_E0;
    u16 unk_E2;
} B22_81892C5C_S_81892C5C_0;
typedef struct B22_81892C5C_S_81892C5C_1_pre {
    void * unk_00;
    u8 pad_04[0x4];
} B22_81892C5C_S_81892C5C_1_pre;
typedef struct TimedTransformCopyEffectBody {
    union { void *linked_counter; s32 owner_value; } owner;
    union { u16 frame_count; s16 base_height; } frame;
    s16 frame_limit;
} TimedTransformCopyEffectBody;
typedef struct B22_81892C5C_S_81892C5C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} B22_81892C5C_S_81892C5C_2;
typedef struct B22_81892C5C_S_81892C5C_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} B22_81892C5C_S_81892C5C_3;
typedef struct B22_81892C5C_S_81892C5C_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
} B22_81892C5C_S_81892C5C_4;
typedef struct B22_81892C5C_S_81892C5C_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} B22_81892C5C_S_81892C5C_5;
typedef struct B22_81892C5C_S_81892C5C_7 {
    u8 pad_00[0x8];
    void * unk_08;
} B22_81892C5C_S_81892C5C_7;
struct B22_81892C5C_OtCtxS { void *cur; };
typedef struct {
    unsigned addr: 24;
    unsigned len: 8;
    u8 r0, g0, b0, code;
} B22_81892C5C_P_TAG;
typedef struct B22_81892BF8_S_81892BF8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} B22_81892BF8_S_81892BF8_1;
typedef struct B22_81892AF0_Copy24 {
    s32 words[6];
} B22_81892AF0_Copy24;
typedef struct B22_81892AF0_S_81892AF0_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} B22_81892AF0_S_81892AF0_3;
typedef struct B22_818928F8_S_818928F8_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s16 unk_10;
    s16 unk_12;
} B22_818928F8_S_818928F8_0;
typedef struct B22_818928F8_Copy24 {
    s32 word[6];
} B22_818928F8_Copy24;
typedef struct B22_818928F8_Sprite {
    u8 pad0[8];
    void *callback;
    u8 color[3];
    u8 padF[11];
    s16 rotation;
    s16 scale_x;
    s16 scale_y;
} B22_818928F8_Sprite;
typedef struct B22_818928F8_Object {
    u8 pad0[8];
    B22_818928F8_Copy24 *dst;
    B22_818928F8_Sprite *sprite;
    void *callback;
} B22_818928F8_Object;
typedef struct B22_81892800_Link {
    u8 pad_00[0x14];
    u16 counter;
} B22_81892800_Link;
typedef struct B22_81892800_Entity {
    u16 flags;
    u8 pad_02[0xA];
    B22_81892800_Link *link;
    s16 timer;
    s16 limit;
} B22_81892800_Entity;
typedef struct B22_81892800_Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} B22_81892800_Motion;
typedef struct B22_81892800_Aux {
    u8 pad_00[0x1A];
    u16 angle;
} B22_81892800_Aux;
void advance_accelerating_spin_effect(B22_81892800_Entity *entity, B22_81892800_Motion *motion, B22_81892800_Aux *aux);
void *create_randomly_rotated_sprite_object(struct B22_81893474_EffectState *context, B22_818928F8_Copy24 *src_data, s16 state_value);
void accelerate_and_expire_animated_sprite(VerticalAccelerationSpriteBody *step_state, void *accumulator, SpriteFrameState *target);
void *create_vertical_acceleration_sprite(s32 state_value, B22_81892AF0_Copy24 *source_transform, s16 variant);
void expire_counted_child_effect(TimedTransformCopyEffectBody *counter_state);
s32 draw_red(TimedTransformCopyEffectBody *effect, B22_81892C5C_S_81892C5C_2 *center);
void *create_timed_transform_copy_effect(s32 object_arg, ObjectPosition *source_data, s16 initial_value, s16 field_delta);
void emit_animated_transform_copies(void *state, ObjectPosition *draw_context, SpriteFrameState *update_context);
void step_sprite_height_and_animation(AnimatedSpriteBurstBody *entry, B22_818931B8_S_818931B8_2 *source, SpriteFrameState *target);
void create_animated_sprite_burst(s32 source, B22_81893244_Func81893244Data *initial_data, s16 status_param);
void update_effect_launch_travel_impact_cleanup(struct B22_81893474_EffectState *effect_state, ObjectPosition *effect_motion, B22_81893474_ColorPart *color_part);
void select_record_entry_and_value(void *state, void *entries, short index);
extern void SetDrawMode(void *, s32, s32, s32, s32);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 rcos(s32);
extern s32 rsin(s32);
extern s32 generate_random_value(void);
extern void func_80042640(void *, s32);
extern void *create_actor_at_tile(u8, s16, s16, s16); /* Unprototyped: retail call narrows its arguments to this declaration; no shared prototype keeps it */
extern void initialize_timed_motion_step(s32, s32);
extern s32 check_left_tile_and_center_height(s32, s32, s32);
extern s16 get_surface_height_at_record(void *);
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
#endif
