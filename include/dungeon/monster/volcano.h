#ifndef MODULE_DUNGEON_OVL_E0365C_H
#define MODULE_DUNGEON_OVL_E0365C_H
#include "sdk/libc.h"
#include "dungeon/system.h"
#include "dungeon/actor/state.h"
#include "dungeon/actor/status.h"
#include "shared/dungeon_sprite_data.h"
#include "engine/graphics.h"
#include "engine/texture.h"

struct E_80170A58_S_80170A58_2;
#include "common.h"
#include "dungeon/actor.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "records/Rec_D_80082E80.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_func_80173204_arg0.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
struct ObjectPosition;
struct SpriteFrameState;

typedef ActorActionHandler E_80170854_ActorAction;
typedef struct {
 u8 pad00[0x13]; u8 kind; s32 flags14; u8 pad18[4]; s32 flags1C;
 u8 pad20[0x6C]; E_80170854_ActorAction handler;
} E_80170854_SpawnActor;
typedef struct {
 u8 pad00[0x8C]; E_80170854_ActorAction handler; u8 pad90[0xA]; u8 action_id;
 u8 pad9B; s8 direction;
} E_80170854_SpawnState;
typedef struct { u8 pad00[0xA]; s16 height; } E_80170854_SpawnMotion;

typedef struct { ObjectNodeHeader header; } E_80170854_SpawnObject;

extern u8 volcano_frame_set_6[8],volcano_frame_set_2[8];
/* Allocate an actor, initialize its action and sprite views, then apply spawn flags. */

typedef void (*E_80170A58_Callback)(void *, void *, void *, void *);

typedef struct E_80170A58_S_80170A58_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} E_80170A58_S_80170A58_0;   /* monster in func_80170A58 */

typedef struct E_80170A58_S_80170A58_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} E_80170A58_S_80170A58_1;   /* actor in func_80170A58 */

typedef struct E_80170A58_S_80170A58_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} E_80170A58_S_80170A58_2;   /* motion in func_80170A58 */

/* Updates monster facing, runs actor callbacks, and applies motion and floor contact. */

typedef struct E_80170E5C_S_80170E5C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} E_80170E5C_S_80170E5C_0;   /* arg0 in func_80170E5C */

typedef struct E_80170E5C_S_80170E5C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} E_80170E5C_S_80170E5C_1;   /* arg3 in func_80170E5C */

typedef struct E_80170E5C_S_80170E5C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} E_80170E5C_S_80170E5C_2;   /* arg2 in func_80170E5C */

/* Update actor actions, facing, and animation according to dungeon state. */

/* Updates actor movement, recording the path and refreshing the tile position and height. */

typedef struct E_80171B68_S_80171570_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} E_80171B68_S_80171570_0;   /* state in func_80171B68 */

typedef struct E_80171B68_S_80171570_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} E_80171B68_S_80171570_2;   /* arg0 in func_80171B68 */

typedef struct E_80171B68_S_80171570_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} E_80171B68_S_80171570_3;   /* (u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A in func_80171B68 */

/* Advances the entity along its stored path and updates movement timing. */

// Initialize object state and apply the table entry for its eight-way orientation.

typedef struct E_80171E10_S_80171E00_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} E_80171E10_S_80171E00_3;   /* arg0 in func_80171E10 */

         /* extern */
typedef struct E_80171E10_Ent E_80171E10_Ent;
 /* extern */
                     /* extern */
             /* extern */
                          /* extern */
                     /* extern */
 /* extern */

/* Check movement conditions and initialize the actor action and directional animation. */

typedef struct E_80171FD4_S_80171FC4_1 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} E_80171FD4_S_80171FC4_1;   /* arg0 in func_80171FD4 */

         /* extern */

 /* extern */
                          /* extern */
 /* extern */

/* Update action state and start a directional animation if the actor passes the checks. */

typedef struct E_801720EC_S_801720EC_0 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} E_801720EC_S_801720EC_0;   /* entity in func_801720EC */

typedef struct E_801720EC_S_801720EC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} E_801720EC_S_801720EC_1;   /* arg2 in func_801720EC */

typedef struct E_801720EC_S_801720EC_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} E_801720EC_S_801720EC_2;   /* output in func_801720EC */

/* Checks the tile ahead and updates the entity's action when the height permits. */

typedef struct E_8017236C_S_8017236C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} E_8017236C_S_8017236C_1;   /* arg0 in func_8017236C */

/* Updates actor flags and starts a directional animation when the actor is ready. */




typedef struct E_801724E8_S_801724E8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} E_801724E8_S_801724E8_0;   /* arg0 in func_801724E8 */

/* Updates an actor's hop toward its tile and handles movement completion. */




typedef struct E_801728B4_S_801728B4_0 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} E_801728B4_S_801728B4_0;   /* obj in func_801728B4 */

typedef struct E_801728B4_S_801728B4_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
} E_801728B4_S_801728B4_1;   /* entity in func_801728B4 */

typedef struct E_801728B4_S_801728B4_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} E_801728B4_S_801728B4_2;   /* actor in func_801728B4 */

 /* extern */
                      /* extern */
                     /* extern */
             /* extern */
/* Advances the object state from entity flags and updates the actor. */

/* extern */
         /* extern */
      /* extern */
              /* extern */
                      /* extern */
                     /* extern */
       /* extern */
                      /* extern */

typedef struct E_80172A58_S_80172A58_0 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} E_80172A58_S_80172A58_0;   /* arg0 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    s8 unk_72;
    s8 unk_73;
} E_80172A58_S_80172A58_1;   /* arg3 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_2 {
    u8 pad_00[0x12];
    u8 unk_12;
} E_80172A58_S_80172A58_2;   /* ((*var_s0 * 0x14) + D_8006DE24) in func_80172A58 */

typedef struct E_80172A58_S_80172A58_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} E_80172A58_S_80172A58_3_pre;   /* the 0x14 bytes before var_v0 in func_80172A58, addressed as var_v0[-1] */

typedef struct E_80172A58_S_80172A58_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} E_80172A58_S_80172A58_4;   /* temp_v1_3 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} E_80172A58_S_80172A58_5;   /* arg2 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} E_80172A58_S_80172A58_6;   /* arg1 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_7 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} E_80172A58_S_80172A58_7;   /* D_800814A8 in func_80172A58 */


typedef struct E_80172ED0_S_80172ED0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } timer;   /* accessed as both */
    u8 pad_98[0x3];
    u8 phase;
} E_80172ED0_S_80172ED0_0;   /* arg0 in func_80172ED0 */

/* Damp entity movement and align it to its tile before starting an action or resetting state. */

/* Forward all four bank callback arguments to the resident handler. */




/* Resume the bank action after the resident callback completes. */

typedef struct E_80173254_S_80173254_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} E_80173254_S_80173254_0;   /* arg0 in func_80173254 */

/* Updates the entity action state and selects its directional animation. */

typedef struct E_8017357C_S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} E_8017357C_S_8017357C_0;   /* arg0 in func_8017357C */

/* Advance the actor state and select its directional effect. */







extern u8 volcano_frame_set_3[8],volcano_frame_set_2[8];







/* Resume the bank action after the resident callback completes. */




/* Resume the bank action after the resident callback completes. */




/* Resume the bank action after the resident callback completes. */




/* Resume the bank action after the resident callback completes. */




/* Resume the bank action after the resident callback completes. */

typedef struct E_80173A20_S_80173A20_2 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} E_80173A20_S_80173A20_2;   /* shadow in func_80173A20 */

typedef struct E_80173A20_S_80173A20_3 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0xA];
    u32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 s; s16 u; } unk_88;   /* accessed as both */
} E_80173A20_S_80173A20_3;   /* creature in func_80173A20 */

typedef struct E_80173A20_S_80173A20_4 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} E_80173A20_S_80173A20_4;   /* object in func_80173A20 */

/* Advance the actor state and spawn an adjacent object when entity flags allow. */

typedef struct E_80173CE0_S_80173CE0_0 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} E_80173CE0_S_80173CE0_0;   /* arg0 in func_80173CE0 */

typedef struct E_80173CE0_S_80173CE0_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} E_80173CE0_S_80173CE0_1;   /* arg2 in func_80173CE0 */

/* Advance the action state and update the entity when action flags permit. */

/* extern */
                      /* extern */
 /* extern */
 /* extern */

typedef struct E_80173E48_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} E_80173E48_S_80172628_0;   /* hold_arg0 in func_80173E48 */

/* Update entity state and flags according to the state query result. */

typedef struct {
    u8 pad14[0x14];
    u16 flags;
    u8 pad16[6];
    u16 field1c;
    u16 field1e;
} E_80173F8C_Func80DE678C_Obj;

/* Update object motion unless its flags trigger termination. */

typedef s32 E_80174084_M2C_UNK;

typedef struct E_80174084_S_80DE6884_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} E_80174084_S_80DE6884_0;   /* setup_arg1 in func_80174084 */

typedef struct E_80174084_S_80DE6884_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    E_80174084_M2C_UNK * unk_10;
} E_80174084_S_80DE6884_1;   /* temp_v0 in func_80174084 */


typedef struct E_80174084_S_80DE6884_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} E_80174084_S_80DE6884_3;   /* held_arg1 in func_80174084 */

typedef struct E_80174084_S_80DE6884_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} E_80174084_S_80DE6884_4;   /* temp_s0_2 in func_80174084 */

typedef struct E_80174084_S_80DE6884_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} E_80174084_S_80DE6884_5;   /* held_arg0 in func_80174084 */


#define NULL 0

static __inline__ u16 offset_coord(u16 coord, u16 offset) {
    return coord + offset;
}

static __inline__ u16 set_flags(u16 value, u16 flags) {
    return value | flags;
}

/* Spawns four effects with origin offsets, random rotation, and velocity based on the owner heading. */

/* extern */

/* Advances the counter, increments both fields for the first eight steps, and updates the record. */

typedef s32 E_801742AC_M2C_UNK;

#define NULL 0

typedef struct {
    s32 words[6];
} E_801742AC_Copy24;

typedef struct E_801742AC_S_80DE6AAC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    E_801742AC_M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} E_801742AC_S_80DE6AAC_0;   /* temp_v0 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} E_801742AC_S_80DE6AAC_1;   /* temp_s1 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} E_801742AC_S_80DE6AAC_2;   /* arg0 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} E_801742AC_S_80DE6AAC_4;   /* arg2 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
} E_801742AC_S_80DE6AAC_5;   /* temp_s0_2 in func_801742AC */

/* Creates an effect at a directional tile offset and clamps its height. */

/* Build an encoded message from the record and this bank's suffix. */

/* Build an encoded message from the record and this bank's suffix. */
extern s16 actor_turn_angle_offsets[8];
extern u8 item_action_definitions[];

extern E_801742AC_M2C_UNK D_800DEEC0;
extern u8 volcano_frame_set_3[];
extern u8 volcano_frame_set_1[];
extern u8 D_80174528[8];
extern u8 volcano_frame_set_7[];
extern u8 volcano_frame_set_2[];
extern u8 volcano_frame_set_10;
extern u8 D_80174548[];
extern s32 volcano_frame_set_8;
extern u8 volcano_frame_set_9[];
extern u8 D_80174560[];
extern E_80170A58_Callback volcano_callbacks[];
extern u8 D_801745CC[];
extern u8 D_801745F8[];
extern int abs(int);
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 resolve_record_orientation_or_fallback(s32, void *, s16 *, s32);
extern s32 get_cd_command_queue_depth(void);
extern void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern void func_80042640(void *, s32);
extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern s32 func_80042900(ActorRecord *entry, s32 effect_id);
extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
extern void func_80042B68(ActorRecord *owner, s8 match_type);
extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern s32 func_8004491C(ObjectNodeHeader *entry, void *registration_id);

void select_sprite_entry(void *object_data, s16 table_index, s16 entry_index);

extern void advance_sprite_animation_and_textures(void *arg);
extern s32 rsin(s32);
extern s32 rcos(s32);
void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *,u8 *);
u8 *clear_byte_and_advance(u8 *byte_ptr);
extern u8 *append_entity_display_text(void *,u8 *);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 check_movement_clearance_and_height(s16,void *,void *,s32);
extern s32 find_eligible_entry_at_coordinates();
extern E_80171E10_Ent * prepare_directional_attack();
extern s32 find_active_rect_containing_point(s32, s32);
extern s16 get_tile_chebyshev_distance(void *, void *);
/* Signed differences arrive sign-extended in the 32-bit v0 ABI slot.
 * The two signed comparisons explicitly narrow that slot; the other caller
 * performs modulo-16-bit arithmetic. One whole-bank declaration is used. */
extern s32 get_actor_height_difference(void *,void *);
extern s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern s32 can_entity_gain_level(void *);
extern void set_record_integer_tile_center(void *, s32, s32);
extern s32 try_claim_dungeon_action_slot();
#include "dungeon/player/object/action_state.h"
struct S_80047738;

extern s32 check_entity_interaction_compatibility();
extern s32 check_layer_offset_height();
extern s32 display_text_with_fullwidth_adjustment(s8 *);
extern s32 generate_random_value(void);
extern void func_800A9A04(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void initialize_actor_sprite_and_animation(void *entity, void *position, SpriteFrameState *sprite, s32 init_flags);
extern s32 refresh_actor_facing_and_lifecycle();
extern void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 update_actor_movement_to_tile(void *move_state, void *motion, void *target_tile, ActorRecord *actor);
extern s32 update_linked_actor_motion(void *state, void *transform, void *config, void *object);
extern s32 update_actor_hop_and_shrink(void *,void *,struct SpriteFrameState *,void *);

extern s32 interpolate_actor_to_terrain_tile(void *,void *,void *,void *);
extern s32 update_spinning_actor_fall(void *,void *,void *,void *);
extern s32 propagate_actor_action_flag(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);
extern s32 update_actor_fade_in(void *,void *,void *,void *);
void spend_actor_mp(ActorRecord *entity, s32 base_reduction);

extern void create_actor_linked_effect(void *);
extern s16 sample_terrain_surface_height(s32,s32,s16);
extern void *create_actor_with_tile_flags(s32, s16, s16, s16); /* Unprototyped: retail call narrows its arguments to this declaration; no shared prototype keeps it */

void *spawn_mode_dependent_112_object(s16 flags,s16 attr_x,s16 attr_y,s16 attr_height);
void update_entity_facing_and_ground(void *entity, E_80170A58_S_80170A58_2 *motion, void *monster);
void update_actor_behavior_facing_and_animation_2(ActorRecord *actor_in, ObjectPosition *context_in, SpriteFrameState *sprite_in, ActorRecord *status_in);
void update_actor_targeting_and_movement(ActorRecord *object, ObjectPosition *entry_context, SpriteFrameState *tile, ActorRecord *actor);
void advance_actor_path_step(ActorRecord *action, ObjectPosition *action_id, SpriteFrameState *entity, ActorRecord *move_state);
void set_actor_directional_animation(void *object, ObjectPosition *unused, SpriteFrameState *display, void *orientation);
s32 begin_actor_directional_attack(ActorRecord *action_state, ObjectPosition *action_ctx, void *sprite, ActorRecord *actor);
void begin_actor_attack_after_status_check(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
s32 check_actor_ahead_height(ActorRecord *action_state, ObjectPosition *source_pos, SpriteFrameState *sprite, void *actor);
void start_actor_directional_animation(ActorRecord *actor_state, ObjectPosition *action_param, SpriteFrameState *sprite, ActorRecord *actor);
void move_actor_to_tile_and_check_trap(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_hop_to_tile(void *anim, ObjectPosition *motion, void *actor, ActorRecord *actor_state);
void update_linked_actor_motion_and_trap(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void resolve_actor_attack_damage(void *obj, ObjectPosition *record, void *entity, void *actor);
void update_actor_spell_action(void *state, struct E_80172A58_S_80172A58_6 *position, struct E_80172A58_S_80172A58_5 *sprite, void *actor);
void dampen_actor_movement_to_tile(E_80172ED0_S_80172ED0_0 *action, ObjectPosition *motion, SpriteFrameState *tile_state, void *entity);
void remove_defeated_volcano(void *state,void *position,void *render_state,void *entity);
void shrink_hopping_volcano(void *state,void *motion,void *sprite,void *actor);
void advance_entity_motion_fade_and_removal(void *state, ObjectPosition *action, SpriteFrameState *source, ActorRecord *target);
void finish_actor_hop_and_grow_then_resume_facing_animation(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void handle_actor_pending_action(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void handle_actor_action_effects(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_landing_and_trap(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_thrown_actor_and_trap(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void finish_actor_terrain_interpolation_then_resume_facing_animation(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void finish_spinning_actor_fall_then_resume_facing_animation(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void finish_actor_fade_in_then_resume_facing_animation(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void finish_actor_floor_trap_then_resume_facing_animation(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void finish_actor_action_flag_propagation_then_resume_facing_animation(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_state_with_child(void *actor, ObjectPosition *context, void *entity, void *creature);
void advance_actor_state_when_allowed(ActorRecord *state_ctx, ObjectPosition *entity_id, SpriteFrameState *action, ActorRecord *entity);
s32 select_actor_relation_state(void *entity_arg, ObjectPosition *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void dampen_actor_motion(void *state_data, s32 *motion, E_80173F8C_Func80DE678C_Obj *object);
void create_four_directional_effects(void *owner_arg, ObjectPosition *motion_arg, void *origin_arg);
void advance_effect_record_counters(u16 *counter, s32 unused, SpriteFrameState *record);
void * create_directional_effect_object(E_801742AC_S_80DE6AAC_2 *source, ObjectPosition *initial_position, E_801742AC_S_80DE6AAC_4 *tile_origin);
void display_formatted_actor_message(void *record);
void display_entity_action_message(void *record);
#endif
