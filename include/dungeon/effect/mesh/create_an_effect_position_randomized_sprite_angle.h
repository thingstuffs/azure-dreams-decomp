#ifndef DUNGEON_OVL_1930844_H
#define DUNGEON_OVL_1930844_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_80024170_arg0.h"
#include "shared/game_work.h"
#include "shared/ot_link.h"
#include "shared/gpu_packets.h"
#include "shared/scratchpad.h"
#include "shared/entity_height_offsets.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/level.h"
#include "dungeon/system.h"
typedef struct ovl_1930844_81910844_S_81910844_0_pre {
    u16 unk_00;
} ovl_1930844_81910844_S_81910844_0_pre;
typedef struct ovl_1930844_81910844_S_81910844_0 {
    void * unk_00;
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   
    s16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
} ovl_1930844_81910844_S_81910844_0;
typedef struct ovl_1930844_81910844_S_81910844_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} ovl_1930844_81910844_S_81910844_1;
typedef struct ovl_1930844_81910844_S_81910844_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} ovl_1930844_81910844_S_81910844_2;
typedef struct ovl_1930844_81910844_S_81910844_3 {
    u8 pad_00[0x1A];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} ovl_1930844_81910844_S_81910844_3;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
typedef struct ovl_1930844_81910970_S_80024170_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} ovl_1930844_81910970_S_80024170_0;
typedef struct ovl_1930844_81910970_S_80024170_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
} ovl_1930844_81910970_S_80024170_1;
typedef struct ovl_1930844_81910970_S_80024170_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} ovl_1930844_81910970_S_80024170_4;
typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} ovl_1930844_81910970_Copy6;
typedef struct {
    u32 addr : 24;
    u32 len : 8;
} ovl_1930844_81910EC0_P_TAG;
#define ovl_1930844_81910EC0_U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define ovl_1930844_81910EC0_S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define ovl_1930844_81910EC0_U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define ovl_1930844_81910EC0_S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define ovl_1930844_81910EC0_U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define ovl_1930844_81910EC0_PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define ovl_1930844_81910EC0_GFX_ROOT_SLOT ((u8 *)&g_game_work)
typedef struct ovl_1930844_819112CC_S_819112CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    u8 pad_14[0x2C];
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
} ovl_1930844_819112CC_S_819112CC_0;
typedef struct ovl_1930844_819112CC_S_819112CC_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_1930844_819112CC_S_819112CC_1;
typedef struct ovl_1930844_819112CC_S_819112CC_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    s8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
} ovl_1930844_819112CC_S_819112CC_2;
typedef struct ovl_1930844_819112CC_S_819112CC_3 {
    u8 pad_00[0x18];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_18;   
    u8 pad_1C[0x10];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_2C;   
} ovl_1930844_819112CC_S_819112CC_3;
typedef struct ovl_1930844_819112CC_S_819112CC_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    s8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
} ovl_1930844_819112CC_S_819112CC_5;
typedef struct {
    unsigned addr: 24;
    unsigned len: 8;
    u8 r0, g0, b0, code;
} ovl_1930844_819112CC_P_TAG;
typedef struct {} ovl_1930844_819112CC_EmptyArg;
#define ovl_1930844_819112CC_SP16(off) (scratch->h[(off) / 2])
#define ovl_1930844_819112CC_setaddr(p, _addr) (((ovl_1930844_819112CC_P_TAG *)(p))->addr = (u32)(_addr))
#define ovl_1930844_819112CC_getaddr(p) (u32)(((ovl_1930844_819112CC_P_TAG *)(p))->addr)
#define ovl_1930844_819112CC_SP32(off) (scratch->w[(off) / 4])
#define ovl_1930844_819112CC_GFX_ROOT_SLOT ((u8 *)&g_game_work)
typedef struct ovl_1930844_81911A8C_S_81911A8C_0_pre {
    u16 unk_00;
} ovl_1930844_81911A8C_S_81911A8C_0_pre;
typedef struct ovl_1930844_81911A8C_S_81911A8C_0 {
    void * unk_00;
} ovl_1930844_81911A8C_S_81911A8C_0;
typedef struct ovl_1930844_81911A8C_S_81911A8C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} ovl_1930844_81911A8C_S_81911A8C_1;
typedef struct ovl_1930844_81911A8C_S_81911A8C_2 {
    union { void * s; s32 u; } unk_00;   
} ovl_1930844_81911A8C_S_81911A8C_2;
typedef struct ovl_1930844_81911A8C_S_81911A8C_3 {
    u8 pad_00[0x4];
    u8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 unk_07;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} ovl_1930844_81911A8C_S_81911A8C_3;
typedef struct ovl_1930844_81911A8C_S_81911A8C_4 {
    u8 pad_00[0x5];
    s8 unk_05;
} ovl_1930844_81911A8C_S_81911A8C_4;
typedef struct ovl_1930844_81911A8C_S_81911A8C_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} ovl_1930844_81911A8C_S_81911A8C_5;
typedef struct ovl_1930844_81911B9C_S_81911B9C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} ovl_1930844_81911B9C_S_81911B9C_0;
typedef struct ovl_1930844_81911BF4_Inner81911BF4 {
    u8 pad00[0x14];
    u16 field14;
} ovl_1930844_81911BF4_Inner81911BF4;
typedef struct ovl_1930844_81911BF4_Obj81911BF4 {
    ovl_1930844_81911BF4_Inner81911BF4 *inner;
    s16 state;
    s16 timer;
    s16 duration;
    s16 angle;
    u16 angle_step;
    s16 scale;
    u16 field10;
    s16 field12;
    s16 field14;
    s32 x[5];
    s32 y[5];
    u8 field40;
    u8 field41;
    u8 field42;
} ovl_1930844_81911BF4_Obj81911BF4;
typedef struct ovl_1930844_81912074_S_80025874_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} ovl_1930844_81912074_S_80025874_0;
typedef struct ovl_1930844_81912074_S_80025874_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2A];
    u8 unk_40;
    s8 unk_41;
    s8 unk_42;
} ovl_1930844_81912074_S_80025874_1;
typedef struct {
    s32 words[6];
} ovl_1930844_81912074_Copy24;
typedef struct ovl_1930844_81912154_S_80025954_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} ovl_1930844_81912154_S_80025954_1;
typedef struct ovl_1930844_81912154_S_80025954_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} ovl_1930844_81912154_S_80025954_2;
typedef struct ovl_1930844_81912154_S_80025954_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} ovl_1930844_81912154_S_80025954_3;
typedef struct ovl_1930844_81912154_S_80025954_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} ovl_1930844_81912154_S_80025954_4;
typedef struct ovl_1930844_81912154_S_80025954_5 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_00;   
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_04;   
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} ovl_1930844_81912154_S_80025954_5;
typedef struct ovl_1930844_81912154_S_80025954_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_1930844_81912154_S_80025954_6;
typedef struct ovl_1930844_81912154_S_80025954_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} ovl_1930844_81912154_S_80025954_7_pre;
typedef struct ovl_1930844_81912154_S_80025954_8 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_08;   
} ovl_1930844_81912154_S_80025954_8;
typedef struct ovl_1930844_81912154_S_80025954_9 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
} ovl_1930844_81912154_S_80025954_9;
typedef struct ovl_1930844_81912154_S_80025954_11 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} ovl_1930844_81912154_S_80025954_11;
typedef struct ovl_1930844_81912154_S_80025954_12 {
    s32 unk_00;
} ovl_1930844_81912154_S_80025954_12;
typedef struct ovl_1930844_81912154_S_80025954_14 {
    u8 pad_00[0x14];
    u16 unk_14;
} ovl_1930844_81912154_S_80025954_14;
typedef struct ovl_1930844_81912154_S_80025954_15 {
    u8 pad_00[0x88];
    s16 unk_88;
} ovl_1930844_81912154_S_80025954_15;
typedef struct ovl_1930844_81912154_LocalStack {
    u8 motion[0x18];
    u16 distance[4];
} ovl_1930844_81912154_LocalStack;
s32 rsin(s32);
extern s32 register_node(void *, void *);
extern s32 func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_800DE720[9];
extern s32 rcos(s32);
extern s32 RotTransPers(void *, void *, void *, void *);
extern s32 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, u16, s32);
extern u32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
void AddPrim();
void SetTile(void *);
extern int abs(int);
s32 resolve_record_orientation_or_fallback();
void apply_attack_power_and_element_effects();
s32 check_layer_offset_height();
static __inline__ s32 radial_coordinate(s32 center, s32 trig, s16 radius);
void advance_shrinking_arc_effect(void *state, ovl_1930844_81910844_S_81910844_2 *motion, ovl_1930844_81910844_S_81910844_3 *visual);
void * create_an_effect_position_randomized_sprite_angle(Rec_func_80024170_arg0 *owner, void *source_position);
void build_and_depth_sorts_five_radial_line_segments_effect(void *effect_data, void *origin, s16 step_index, s16 scale_factor);
void build_and_enqueue_five_translucent_quads_between_interpolated_points(u8 *shape, void *position, s16 scale_num, s16 scale_den);
void build_and_queue_interpolated_vertical_quads_around_five_perimeter_points(void *effect_in, ovl_1930844_819112CC_S_819112CC_1 *origin, s16 step_in, s16 duration_in);
void draw_a_full_screen_color_overlay_mark_effect_complete_countdown_ends(void *effect, void *unused, void *fade_state);
void create_object_hex_212_initialize_data_pointer_mode(s32 *initial_value);
void update_the_five_orbiting_points_advance_effect_animation(ovl_1930844_81911BF4_Obj81911BF4 *effect, s32 *position);
void *create_and_initializes_copying_n_24_bytes_source_data(s32 state_value, ovl_1930844_81912074_Copy24 *source_data, s16 initial_setting);
void update_movement_toward_target_along_direction_advances_action_phases(void *state, void *motion, void *appearance);
#endif
