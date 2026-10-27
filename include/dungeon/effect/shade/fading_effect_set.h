#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#ifndef DUNGEON_OVL_188898C_H
#define DUNGEON_OVL_188898C_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_80024264_arg1.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "dungeon/level.h"
#include "dungeon/system.h"
typedef struct ovl_188898c_81868A64_S_81868A64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} ovl_188898c_81868A64_S_81868A64_0;
typedef struct ovl_188898c_81868A64_S_81868A64_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_188898c_81868A64_S_81868A64_3;
typedef struct ovl_188898c_81868B84_S_81868B84_0_pre {
    u16 unk_00;
} ovl_188898c_81868B84_S_81868B84_0_pre;
typedef struct ovl_188898c_81868B84_S_81868B84_0 {
    u16 unk_00;
    union { u16 s; s16 u; } unk_02;   
    u8 pad_04[0x2];
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    void * unk_0C;
    u8 unk_10;
} ovl_188898c_81868B84_S_81868B84_0;
typedef struct ovl_188898c_81868B84_S_81868B84_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} ovl_188898c_81868B84_S_81868B84_1;
typedef struct ovl_188898c_81868B84_S_81868B84_3 {
    u8 pad_00[0x16];
    s8 unk_16;
} ovl_188898c_81868B84_S_81868B84_3;
typedef struct ovl_188898c_81868E84_S_81868E84_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} ovl_188898c_81868E84_S_81868E84_0;
typedef struct ovl_188898c_81868E84_S_81868E84_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    void * unk_0C;
    s8 unk_10;
} ovl_188898c_81868E84_S_81868E84_1;
typedef struct ovl_188898c_81868E84_S_81868E84_2 {
    u8 pad_00[0x9];
    u8 unk_09;
} ovl_188898c_81868E84_S_81868E84_2;
typedef struct ovl_188898c_81868E84_S_81868E84_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_188898c_81868E84_S_81868E84_3;
typedef struct {
    u8 pad0[8];
    void *dst;
    void *sprite;
    void *callback;
    u8 pad14[12];
    s32 value;
} ovl_188898c_81868FDC_Object;
typedef struct {
    u8 pad0[12];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    u16 flags10;
    s16 angle;
    u16 flags14;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} ovl_188898c_81868FDC_Sprite;
typedef struct ovl_188898c_818690C8_S_800248C8_0 {
    u8 pad_00[0x18];
    u32 * unk_18;
    u8 pad_1C[0x48];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
    u16 unk_6E;
    u16 unk_70;
    u8 pad_72[0x42];
    s32 unk_B4;
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u8 pad_E0[0x14];
    s32 unk_F4;
    s32 unk_F8;
} ovl_188898c_818690C8_S_800248C8_0;
typedef struct ovl_188898c_818690C8_S_800248C8_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
} ovl_188898c_818690C8_S_800248C8_2;
typedef struct ovl_188898c_818690C8_S_800248C8_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x8];
    u16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0xE];
    u16 unk_32;
    u8 pad_34[0x2];
    u16 unk_36;
    u8 pad_38[0x2];
    u16 unk_3A;
} ovl_188898c_818690C8_S_800248C8_3;
typedef union {
    s32 word;
    struct {
        u16 low;
        s16 high;
    } half;
} ovl_188898c_818690C8_PackedDelta;
typedef union ovl_188898c_818694D4_Fixed32 {
    s32 val;
    struct {
        u16 lo;
        s16 hi;
    } h;
} ovl_188898c_818694D4_Fixed32;
typedef struct ovl_188898c_818694D4_Motion {
    ovl_188898c_818694D4_Fixed32 x;
    ovl_188898c_818694D4_Fixed32 y;
    ovl_188898c_818694D4_Fixed32 z;
    ovl_188898c_818694D4_Fixed32 dx;
    ovl_188898c_818694D4_Fixed32 dy;
    ovl_188898c_818694D4_Fixed32 dz;
} ovl_188898c_818694D4_Motion;
typedef struct ovl_188898c_818694D4_Lookup {
    u8 pad00[8];
    void *key;
    u8 pad0C[8];
    u16 flags;
    u8 pad16[14];
    u8 cell_x;
    u8 cell_y;
} ovl_188898c_818694D4_Lookup;
typedef struct ovl_188898c_818694D4_RootPrefix {
    u8 pad00[8];
    ovl_188898c_818694D4_Motion *motion;
    SpriteFrameState *lookup;
} ovl_188898c_818694D4_RootPrefix;
typedef struct ovl_188898c_818694D4_Controller {
    u8 *root;
    u16 *flags;
    u8 pad08;
    u8 kind;
    s16 state;
    s16 pad0C;
    u16 angle;
    s16 timer;
    s16 pad12;
    s16 active;
    u8 ready;
    u8 pad17;
    ovl_188898c_818694D4_Motion saved;
    ovl_188898c_818694D4_Fixed32 target[3];
    u8 pad3C[12];
    s16 cell_x;
    s16 cell_y;
} ovl_188898c_818694D4_Controller;
typedef union ovl_188898c_818694D4_WideProduct {
    long long value;
    struct {
        s32 upper;
        s32 lower;
    } word;
} ovl_188898c_818694D4_WideProduct;
typedef struct ovl_188898c_818694D4_LargeFlag {
    u32 value;
    u32 pad[2];
} ovl_188898c_818694D4_LargeFlag;
extern void *dungeon_actor_ring_anchor;
extern u8 current_spell_effect_variant;
extern s32 check_entity_interaction_compatibility(void *kind, void *actor);
extern s32 generate_random_value(void);
extern void try_apply_status_effect(void *actor, s32 mode, s32 amount);
extern s32 abs(s32);
extern void advance_sprite_animation_and_textures(void *render_data);
void select_record_entry_and_value(void *state, void *entries, short index);
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
#include "shared/sprite_source.h"
struct ObjectNodeHeader;
extern SpriteSourceEntry rising_sprite_entries[];
s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern u8 D_80025368[];
extern s32 check_layer_offset_height();
static __inline__ s32 first_delta_s32_s32(s32 end, s32 start);
void apply_status_to_nearby_actors(s32 x, s32 y, void *kind, s32 flags);
void advance_fading_effect(void *effect, void *position, void *render_data);
void create_randomized_grayscale_effect(s32 user_data, ovl_188898c_81868A64_S_81868A64_3 *source_pos, u8 intensity);
void animate_spiral_grayscale_effect(void *effect, void *position);
void create_coordinate_sprite_object(void *owner, ovl_188898c_81868E84_S_81868E84_3 *coords);
void shrink_and_brighten_effect(void *state_ref, void *unused, SpriteFrameState *effect);
void delay_and_fade_particle(s32 value, void *source_data);
s32 interpolate_shade_and_queue_line(void *line_data, void *unused_render_context);
void move_linked_effect_along_path(ovl_188898c_818694D4_Controller *input_ctrl, ovl_188898c_818694D4_Motion *input_motion, void *input_render_data);
#endif
