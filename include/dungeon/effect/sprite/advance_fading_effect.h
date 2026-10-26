#ifndef DUNGEON_OVL_188298C_H
#define DUNGEON_OVL_188298C_H
#include "sdk/libc.h"
#include "dungeon/level.h"
#include "dungeon/system.h"

struct SpriteFrameState;
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dir_step.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
struct RegistrationNode;
typedef struct {
    u8 pad00[0x14];
    u16 unk14;
} ovl_188298c_8186298C_SubEnt;
typedef struct {
    ovl_188298c_8186298C_SubEnt *unk00;
    u8 unk04;
} ovl_188298c_8186298C_Arg0Ent;
typedef struct {
    u8 pad00[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 pad0F[0x14 - 0xF];
    u16 unk14;
    u8 pad16[0x1C - 0x16];
    u16 unk1C;
    u16 unk1E;
} ovl_188298c_8186298C_Arg2Ent;
typedef struct ovl_188298c_81862B74_S_81862B74_0_pre {
    u16 unk_00;
} ovl_188298c_81862B74_S_81862B74_0_pre;
typedef struct ovl_188298c_81862B74_S_81862B74_0 {
    void * unk_00;
    u16 unk_04;
} ovl_188298c_81862B74_S_81862B74_0;
typedef struct ovl_188298c_81862B74_S_81862B74_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} ovl_188298c_81862B74_S_81862B74_1;
typedef struct ovl_188298c_81862C28_S_81862C28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} ovl_188298c_81862C28_S_81862C28_0;
typedef struct ovl_188298c_81862C28_S_81862C28_1 {
    u8 unk_00;
    u8 pad_01[0x1];
    union { u16 s; s16 u; } unk_02;   
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} ovl_188298c_81862C28_S_81862C28_1;
typedef struct ovl_188298c_81862C28_S_81862C28_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   
} ovl_188298c_81862C28_S_81862C28_2;
typedef struct ovl_188298c_81862ED8_S_800246D8_0 {
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
} ovl_188298c_81862ED8_S_800246D8_0;
typedef struct ovl_188298c_81862ED8_S_800246D8_2 {
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
} ovl_188298c_81862ED8_S_800246D8_2;
typedef struct ovl_188298c_81862ED8_S_800246D8_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x10];
    u16 unk_22;
    u8 pad_24[0x2];
    u16 unk_26;
    u8 pad_28[0x2];
    u16 unk_2A;
    u8 pad_2C[0xE];
    u16 unk_3A;
    u8 pad_3C[0x2];
    u16 unk_3E;
    u8 pad_40[0x2];
    u16 unk_42;
} ovl_188298c_81862ED8_S_800246D8_3;
typedef union {
    s32 word;
    struct {
        u16 low;
        s16 high;
    } half;
} ovl_188298c_81862ED8_PackedDelta;
typedef union ovl_188298c_818632E4_Fixed32 {
    s32 val;
    struct {
        u16 lo;
        s16 hi;
    } h;
} ovl_188298c_818632E4_Fixed32;
typedef struct ovl_188298c_818632E4_Motion {
    ovl_188298c_818632E4_Fixed32 x;
    ovl_188298c_818632E4_Fixed32 y;
    ovl_188298c_818632E4_Fixed32 z;
    ovl_188298c_818632E4_Fixed32 dx;
    ovl_188298c_818632E4_Fixed32 dy;
    ovl_188298c_818632E4_Fixed32 dz;
} ovl_188298c_818632E4_Motion;
typedef struct ovl_188298c_818632E4_Lookup {
    u8 pad00[8];
    void *key;
    u8 pad0C[8];
    u16 flags;
    u8 pad16[14];
    u8 cell_x;
    u8 cell_y;
} ovl_188298c_818632E4_Lookup;
typedef struct ovl_188298c_818632E4_RootPrefix {
    u8 pad00[8];
    ovl_188298c_818632E4_Motion *motion;
    ovl_188298c_818632E4_Lookup *lookup;
} ovl_188298c_818632E4_RootPrefix;
typedef struct ovl_188298c_818632E4_Controller {
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
    u8 slots[8];
    u8 pad1E[2];
    ovl_188298c_818632E4_Motion saved;
    ovl_188298c_818632E4_Fixed32 target[3];
    u8 pad44[12];
    s16 cell_x;
    s16 cell_y;
} ovl_188298c_818632E4_Controller;
typedef union ovl_188298c_818632E4_WideProduct {
    long long value;
    struct {
        s32 upper;
        s32 lower;
    } word;
} ovl_188298c_818632E4_WideProduct;
typedef struct ovl_188298c_818632E4_LargeFlag {
    u32 value;
    u32 pad[2];
} ovl_188298c_818632E4_LargeFlag;
extern void *dungeon_actor_ring_anchor;
extern u8 current_spell_effect_variant;
extern s32 check_entity_interaction_compatibility(void *kind, void *actor);
extern s32 generate_random_value(void);
extern void try_apply_status_effect(void *actor, s32 mode, s32 amount);
extern s32 abs(s32);
extern s32 rising_sprite_entries[3];
extern void advance_sprite_animation_and_textures(void *a0);
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct RegistrationNode *entry, void *registration_id);
extern s32 check_left_tile_and_center_height(s32, s32, s16);
extern u16 get_surface_height_at_record(void *);
extern u8 countdown_sprite_entries[];
extern s32 RotTransPers(void *, void *, void *, void *);
extern s32 resolve_record_orientation_or_fallback();
extern s32 check_layer_offset_height();
static __inline__ s32 first_delta_s32_s32(s32 end, s32 start);
void apply_status_to_nearby_actors(s32 x, s32 y, void *kind, s32 flags);
void advance_fading_effect(ovl_188298c_8186298C_Arg0Ent *state, void *unused, ovl_188298c_8186298C_Arg2Ent *effect);
void spawn_jittered_type_212_effect(s32 owner, void *source);
void advance_counter_and_propagate_target_flags(void *state, M2C_UNK context,struct SpriteFrameState *target);
void create_radius_directional_effects(s32 effect_param, void *origin_arg, s16 radius_arg, u8 *blocked_dirs);
s32 project_and_queue_shaded_line(void *line, void *unused_render_context);
void move_to_linked_object_and_apply_arrival_effects(ovl_188298c_818632E4_Controller *ctrl, ovl_188298c_818632E4_Motion *motion, void *render_data);
#endif
