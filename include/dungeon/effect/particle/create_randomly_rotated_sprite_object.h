#ifndef DUNGEON_OVL_18B2800_H
#define DUNGEON_OVL_18B2800_H
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
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
typedef struct B22_81893474_Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} B22_81893474_Motion;
typedef struct B22_81893474_EffectState {
    void *owner;
    void *image;
    u8 unk8;
    u8 id;
    s16 state;
    s16 unkC;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 field_14;
    s16 x;
    s16 y;
    s16 z;
    u8 status;
    u8 pad1D[0x7B];
} B22_81893474_EffectState;
typedef struct B22_81893474_ColorPart {
    u8 pad[0xC];
    u32 color;
} B22_81893474_ColorPart;
typedef struct B22_81893474_Scratch {
    s16 work[8];
    u8 gap[8];
    s16 probe[3];
    u8 result_gap[2];
    s16 result;
    u16 map_flags;
} B22_81893474_Scratch;
typedef struct B22_81893244_Func81893244Data B22_81893244_Func81893244Data;
typedef struct B22_81893244_Func81893244Sub B22_81893244_Func81893244Sub;
typedef struct B22_81893244_Func81893244Status B22_81893244_Func81893244Status;
typedef struct B22_81893244_Func81893244Object B22_81893244_Func81893244Object;
struct B22_81893244_Func81893244Data {
    union {
        s32 word0;
        struct { u16 half0; u16 field2; } halves0;
    } u0;
    union {
        s32 word4;
        struct { u16 half4; u16 field6; } halves4;
    } u4;
    s32 word8;
    union {
        s32 wordC;
        struct { u8 fieldC; u8 fieldD; u8 fieldE; u8 padF; } bytesC;
    } uC;
    s32 field10;
    s32 field14;
};
struct B22_81893244_Func81893244Sub {
    union {
        s32 word0;
        struct { u16 half0; u16 field2; } halves0;
    } u0;
    union {
        s32 word4;
        struct { u16 half4; u16 field6; } halves4;
    } u4;
    s32 word8;
    union {
        s32 wordC;
        struct { u8 fieldC; u8 fieldD; u8 fieldE; u8 padF; } bytesC;
    } uC;
    u16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
};
struct B22_81893244_Func81893244Status {
    s32 field20;
    s16 field24;
    s16 field26;
};
struct B22_81893244_Func81893244Object {
    u8 pad0[8];
    B22_81893244_Func81893244Data *field8;
    B22_81893244_Func81893244Sub *fieldC;
    void *field10;
    u8 pad14[12];
    B22_81893244_Func81893244Status status;
};
typedef struct B22_818931B8_S_818931B8_0_pre {
    u16 unk_00;
} B22_818931B8_S_818931B8_0_pre;
typedef struct B22_818931B8_S_818931B8_0 {
    void * unk_00;
} B22_818931B8_S_818931B8_0;
typedef struct B22_818931B8_S_818931B8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} B22_818931B8_S_818931B8_1;
typedef struct B22_818931B8_S_818931B8_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} B22_818931B8_S_818931B8_2;
typedef struct B22_818930F8_S_818930F8_0_pre {
    u16 unk_00;
} B22_818930F8_S_818930F8_0_pre;
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
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} B22_81893024_M2C_BLOCK;
typedef struct {
    s8 unk0[8];
    B22_81893024_M2C_BLOCK *data;
    s8 unkC[4];
    void *callback;
    s8 unk14[12];
    s32 params;
} B22_81893024_M2C_OBJECT;
typedef struct B22_81893024_S_81893024_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} B22_81893024_S_81893024_0;
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
typedef struct B22_81892C5C_S_81892C5C_1 {
    u8 pad_00[0x4];
    s16 unk_04;
} B22_81892C5C_S_81892C5C_1;
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
typedef struct B22_81892BF8_S_81892BF8_0_pre {
    u16 unk_00;
} B22_81892BF8_S_81892BF8_0_pre;
typedef struct B22_81892BF8_S_81892BF8_0 {
    void * unk_00;
    u16 unk_04;
    s16 unk_06;
} B22_81892BF8_S_81892BF8_0;
typedef struct B22_81892BF8_S_81892BF8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} B22_81892BF8_S_81892BF8_1;
typedef struct B22_81892AF0_Copy24 {
    s32 words[6];
} B22_81892AF0_Copy24;
typedef struct B22_81892AF0_S_81892AF0_0 {
    u8 pad_00[0x8];
    B22_81892AF0_Copy24 * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} B22_81892AF0_S_81892AF0_0;
typedef struct B22_81892AF0_S_81892AF0_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} B22_81892AF0_S_81892AF0_1;
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
void func_80024028(B22_81892800_Entity *entity, B22_81892800_Motion *motion, B22_81892800_Aux *aux);
void *create_randomly_rotated_sprite_object(void *context, B22_818928F8_Copy24 *src_data, s16 state_value);
void func_8002420C(void *step_state, void *accumulator, void *target);
void *func_800242F0(s32 state_value, B22_81892AF0_Copy24 *source_transform, s16 variant);
void func_800243F8(void *counterState);
s32 draw_red(void *effect, B22_81892C5C_S_81892C5C_2 *center);
void *func_80024824(s32 object_arg, void *source_data, s16 initial_value, s16 field_delta);
void func_800248F8(void *state, M2C_UNK draw_context, M2C_UNK update_context);
void func_800249B8(void *entry, B22_818931B8_S_818931B8_2 *source, SpriteFrameState *target);
void func_80024A44(s32 source, B22_81893244_Func81893244Data *initial_data, s16 status_param);
void update_effect_launch_travel_impact_cleanup(B22_81893474_EffectState *effect_state, B22_81893474_Motion *effect_motion, B22_81893474_ColorPart *color_part);
void func_8003DB94(void *, void *, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern s32 generate_random_value(void);
extern void func_80042640(void *, s32);
extern void *create_actor_at_tile(u8, s16, s16, s16);
extern void func_800419EC(s32, s32);
extern s32 increment_bounded_event_counter(void);
extern s32 check_left_tile_and_center_height(s32, s32, s32);
extern s32 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s16 get_surface_height_at_record(void *);
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s16 get_rounded_facing_and_rounding_flag(u8, u8, s16, s16, s16 *);
#endif
