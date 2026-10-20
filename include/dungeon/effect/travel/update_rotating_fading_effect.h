#ifndef DUNGEON_OVL_18CA83C_H
#define DUNGEON_OVL_18CA83C_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "records/Rec_func_800243B8_arg0.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
typedef struct ovl_18ca83c_818AABB8_S_800243B8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} ovl_18ca83c_818AABB8_S_800243B8_0;
typedef struct ovl_18ca83c_818AABB8_S_800243B8_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[0x2];
    u16 unk_3A;
} ovl_18ca83c_818AABB8_S_800243B8_1;
typedef struct ovl_18ca83c_818AABB8_S_800243B8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} ovl_18ca83c_818AABB8_S_800243B8_3;
typedef struct ovl_18ca83c_818AABB8_S_800243B8_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} ovl_18ca83c_818AABB8_S_800243B8_4;
typedef struct ovl_18ca83c_818AABB8_S_800243B8_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} ovl_18ca83c_818AABB8_S_800243B8_6;
typedef struct ovl_18ca83c_818AAE60_S_80024660_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} ovl_18ca83c_818AAE60_S_80024660_1;
typedef struct ovl_18ca83c_818AAE60_S_80024660_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} ovl_18ca83c_818AAE60_S_80024660_2;
typedef struct ovl_18ca83c_818AAE60_S_80024660_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} ovl_18ca83c_818AAE60_S_80024660_3;
typedef struct ovl_18ca83c_818AAE60_S_80024660_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} ovl_18ca83c_818AAE60_S_80024660_4;
typedef struct ovl_18ca83c_818AAE60_S_80024660_5 {
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
} ovl_18ca83c_818AAE60_S_80024660_5;
typedef struct ovl_18ca83c_818AAE60_S_80024660_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_18ca83c_818AAE60_S_80024660_6;
typedef struct ovl_18ca83c_818AAE60_S_80024660_7_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
} ovl_18ca83c_818AAE60_S_80024660_7_pre;
typedef struct ovl_18ca83c_818AAE60_S_80024660_8 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   
} ovl_18ca83c_818AAE60_S_80024660_8;
typedef struct ovl_18ca83c_818AAE60_S_80024660_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} ovl_18ca83c_818AAE60_S_80024660_9;
typedef struct ovl_18ca83c_818AAE60_S_80024660_10 {
    u8 pad_00[0x18];
    s32 unk_18;
} ovl_18ca83c_818AAE60_S_80024660_10;
typedef struct ovl_18ca83c_818AAE60_S_80024660_12 {
    u8 pad_00[0x14];
    u16 unk_14;
} ovl_18ca83c_818AAE60_S_80024660_12;
typedef struct {
    s32 pos[3];
    u8 pad18[0xC];
    u16 dist[3];
} ovl_18ca83c_818AAE60_Func818AAE60Scratch;
extern void draw_animated_shaded_lines(void);
extern void func_8002488C(void);
extern void func_800248D4(void);
extern void func_80024DF0(void);
extern void func_80024F30(void);
extern void func_80024FB0(void);
extern void create_effect_render_object(void);
extern void func_800250E0(void);
extern void func_80025118(void);
extern s32 try_trigger_target_record_effect(void *, s32);
extern s32 get_random_scaled_value(s16 input_value);
extern void apply_clamped_actor_value_delta(void *);
extern void cap_pending_actor_value_delta(void *);
extern void create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern void func_8003DB94(void *, void *, s32);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern M2C_UNK D_800DECF8;
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern u8 D_800777DC[];
extern int abs(int);
s32 resolve_record_orientation_or_fallback();
s32 check_layer_offset_height(s32, s32, s16, s32);
s32 play_sound_if_enabled();
s32 sample_terrain_surface_height(s32, s32, s16);
void func_8002403C(void *target, s32 amount_input, void *owner);
void update_rotating_fading_effect(void *effect, void *position, void *sprite);
void *create_randomized_target_effect(Rec_func_800243B8_arg0 *source, ovl_18ca83c_818AABB8_S_800243B8_3 *start, ovl_18ca83c_818AABB8_S_800243B8_4 *center, s16 index);
void advance_target_travel_effect(void *effect, void *motion, void *appearance);
#endif
