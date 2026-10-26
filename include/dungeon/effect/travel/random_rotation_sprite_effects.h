#ifndef DUNGEON_OVL_18B8824_H
#define DUNGEON_OVL_18B8824_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_80024264_arg1.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/system.h"
typedef struct ovl_18b8824_818988CC_S_800240CC_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s16 unk_10;
    s16 unk_12;
} ovl_18b8824_818988CC_S_800240CC_0;
typedef struct ovl_18b8824_818988CC_Copy24 {
    s32 word[6];
} ovl_18b8824_818988CC_Copy24;
typedef struct ovl_18b8824_818988CC_Sprite {
    u8 pad0[8];
    void *callback;
    u8 color[3];
    u8 padF[11];
    s16 rotation;
    s16 scale_x;
    s16 scale_y;
} ovl_18b8824_818988CC_Sprite;
typedef struct ovl_18b8824_818988CC_Object {
    u8 pad0[8];
    ovl_18b8824_818988CC_Copy24 *dst;
    ovl_18b8824_818988CC_Sprite *sprite;
    void *callback;
} ovl_18b8824_818988CC_Object;
typedef struct ovl_18b8824_81898A64_S_80024264_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} ovl_18b8824_81898A64_S_80024264_0;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
typedef struct ovl_18b8824_81898B70_S_80024370_0_pre {
    u16 unk_00;
} ovl_18b8824_81898B70_S_80024370_0_pre;
typedef struct ovl_18b8824_81898B70_S_80024370_0 {
    void * unk_00;
    u16 unk_04;
} ovl_18b8824_81898B70_S_80024370_0;
typedef struct ovl_18b8824_81898B70_S_80024370_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} ovl_18b8824_81898B70_S_80024370_1;
typedef struct ovl_18b8824_81898B70_S_80024370_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} ovl_18b8824_81898B70_S_80024370_2;
typedef struct ovl_18b8824_81898C1C_S_8002441C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} ovl_18b8824_81898C1C_S_8002441C_0;
typedef struct ovl_18b8824_81898C1C_S_8002441C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} ovl_18b8824_81898C1C_S_8002441C_3;
typedef struct ovl_18b8824_81898DCC_Object {
    u8 pad0[8];
    void *data;
    void *sprite;
    void *callback;
    u8 pad14[12];
    s32 field20;
} ovl_18b8824_81898DCC_Object;
typedef struct ovl_18b8824_81898EBC_Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} ovl_18b8824_81898EBC_Motion;
typedef struct ovl_18b8824_81898EBC_Position16 {
    u16 pad0;
    s16 x;
    u16 pad4;
    s16 y;
    u16 pad8;
    s16 z;
} ovl_18b8824_81898EBC_Position16;
typedef struct ovl_18b8824_81898EBC_EffectState {
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
} ovl_18b8824_81898EBC_EffectState;
typedef struct ovl_18b8824_81898EBC_ColorPart {
    u8 pad[0xC];
    u32 color;
} ovl_18b8824_81898EBC_ColorPart;
typedef struct ovl_18b8824_81898EBC_Scratch {
    s16 work[8];
    u8 gap[8];
    s16 ovl_18b8824_81898EBC_probe[3];
    u8 result_gap[2];
    s16 ovl_18b8824_81898EBC_result;
    u16 ovl_18b8824_81898EBC_map_flags;
} ovl_18b8824_81898EBC_Scratch;
#define ovl_18b8824_81898EBC_U8_AT(p, n) (*(u8 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_S8_AT(p, n) (*(s8 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_probe scratch.ovl_18b8824_81898EBC_probe
#define ovl_18b8824_81898EBC_result scratch.ovl_18b8824_81898EBC_result
#define ovl_18b8824_81898EBC_map_flags scratch.ovl_18b8824_81898EBC_map_flags
extern s32 rand(void);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern u8 D_80024E88[];
extern void advance_sprite_animation_and_textures(void *target);
void select_record_entry_and_value(void *state, void *entries, short index);
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_80024EF4[];
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_80024E40[];
extern u8 D_80024FC4[];
extern int abs(int);
extern s16 get_rounded_facing_and_rounding_flag(u8, u8, s16, s16, s16 *);
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s16 get_surface_height_at_record(void *);
extern s32 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 check_left_tile_and_center_height(s32, s32, s32);
extern void *create_actor_sprite_at_tile(u8, s16, s16, s16);
extern void func_80042640(void *, s32);
extern s32 generate_random_value(void);
void interpolate_view_parameters(void *state, void *motion, void *transform);
void *create_a_sprite_random_rotation_copies_initial_data(void *context, ovl_18b8824_818988CC_Copy24 *copy_src, s16 initial_value);
void handle_increment_entry_counters_process_target_propagate_status_flags(void *entry, void *unused, SpriteFrameState *target);
void *create_randomized_grayscale_effect(s32 object_tag, Rec_func_80024264_arg1 *initial_state);
void advance_the_entry_counters_trigger_count_milestones_update_target(void *entry, s32 unused, void *target);
void *create_counted_sprite_effect(s32 object_id, ovl_18b8824_81898C1C_S_8002441C_3 *initial_state);
void mark_owner_on_target_completion(void *object_ref, s32 unused, SpriteFrameState *target);
ovl_18b8824_81898DCC_Object *create_sprite_effect_with_data(s32 field_value, s32 *initial_data);
void advance_launched_effect(ovl_18b8824_81898EBC_EffectState *state, ovl_18b8824_81898EBC_Motion *motion, ovl_18b8824_81898EBC_ColorPart *part);
#endif
