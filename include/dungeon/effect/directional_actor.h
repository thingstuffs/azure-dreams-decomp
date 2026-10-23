#ifndef DUNGEON_OVL_190081C_H
#define DUNGEON_OVL_190081C_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
typedef struct Row_818E0800_S_818E0800_0_pre {
    u16 unk_00;
} Row_818E0800_S_818E0800_0_pre;   /* the 0x2 bytes before arg0 in func_8002401C, addressed as arg0[-1] */

typedef struct Row_818E0800_S_818E0800_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} Row_818E0800_S_818E0800_1_pre;   /* the 0x14 bytes before object in func_8002401C, addressed as object[-1] */

typedef struct Row_818E0800_S_818E0800_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} Row_818E0800_S_818E0800_1;   /* object in func_8002401C */

typedef struct Row_818E0800_S_818E0800_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} Row_818E0800_S_818E0800_2;   /* arg1 in func_8002401C */

typedef struct Row_818E0800_S_818E0800_3 {
    u8 pad_00[0x8];
    void * unk_08;
} Row_818E0800_S_818E0800_3;   /* base in func_8002401C */

typedef struct Row_818E0800_S_818E0800_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} Row_818E0800_S_818E0800_4;   /* alternate in func_8002401C */

typedef struct Row_818E0800_S_818E0800_5 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x2E];
    u16 unk_48;
    u8 pad_4A[0x2];
    u16 unk_4C;
} Row_818E0800_S_818E0800_5;   /* work in func_8002401C */

typedef struct Row_818E0800_S_818E0800_7 {
    u8 pad_00[0x4];
    void * unk_04;
} Row_818E0800_S_818E0800_7;   /* page in func_8002401C */

typedef struct Row_818E0800_S_818E0800_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} Row_818E0800_S_818E0800_8;   /* header in func_8002401C */

typedef struct Row_818E0800_S_818E0800_9_pre {
    void * unk_00;
    u8 pad_04[0x10];
} Row_818E0800_S_818E0800_9_pre;   /* the 0x14 bytes before result in func_8002401C, addressed as result[-1] */

typedef struct Row_818E0800_S_818E0800_10 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_818E0800_S_818E0800_10;   /* arg2 in func_8002401C */

typedef struct Row_818E0800_S_818E0800_11 {
    u8 unk_00;
} Row_818E0800_S_818E0800_11;   /* D_800E3D68 in func_8002401C */

typedef struct Row_818E0800_S_818E0800_12 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818E0800_S_818E0800_12;   /* ((Row_818E0800_S_818E0800_3 *)base)->unk_08 in func_8002401C */

typedef struct Row_818E0800_S_818E0800_13 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} Row_818E0800_S_818E0800_13;   /* ((Row_818E0800_S_818E0800_4 *)alternate)->unk_08 in func_8002401C */

typedef struct Row_818E0800_S_818E0800_14 {
    u16 unk_00;
} Row_818E0800_S_818E0800_14;   /* ((S_818E0800_0 *)arg0)->unk_04 in func_8002401C */

typedef struct Row_818E0800_S_818E0800_15 {
    u8 pad_00[0x14];
    s32 unk_14;
} Row_818E0800_S_818E0800_15;   /* ((Row_818E0800_S_818E0800_1 *)object)->unk_60 in func_8002401C */

/* Updates target-directed movement, spawns particles, and advances the effect state. */
typedef struct Row_818E0D94_S_818E0D94_0_pre {
    u16 unk_00;
} Row_818E0D94_S_818E0D94_0_pre;   /* the 0x2 bytes before arg0 in func_80024594, addressed as arg0[-1] */

typedef struct Row_818E0D94_S_818E0D94_0 {
    void * unk_00;
    u8 pad_04[0x14];
    u16 unk_18;
    u8 pad_1A[0x2E];
    union { u16 u16; s16 s16; u8 u8; } unk_48;   /* accessed as both */
} Row_818E0D94_S_818E0D94_0;   /* arg0 in func_80024594 */

typedef struct Row_818E0D94_S_818E0D94_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} Row_818E0D94_S_818E0D94_1;   /* inner in func_80024594 */

typedef struct Row_818E0D94_S_818E0D94_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818E0D94_S_818E0D94_3;   /* arg1 in func_80024594 */

typedef struct {
    u8 bytes[8];
} Row_818E0D94_Unaligned8;

typedef struct {
    void *field0;
    void *field4;
    Row_818E0D94_Unaligned8 field8;
    Row_818E0D94_Unaligned8 field10;
    s16 field18;
    s16 field1A;
    u32 unused1C;
} Row_818E0D94_CallRecord;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} Row_818E0D94_OutputVector;

/* Advances effect motion and sprite appearance, marking completion after 32 ticks. */
void *allocate_list_node(s32, void *);
void *func_8003FD64(s32, void *);
void register_node(void *, void *);
void func_8004491C(void *, void *);
s32 rand(void);
void jitter_effect_position_and_fade(void *, s32);
void initialize_timed_motion_step(s32, s32);
void *scan_actor_along_heading();
s32 get_definition_entry_byte_13(s16 entry_index);
s32 try_trigger_target_record_effect(void *, s32, void *);
void play_sound_if_enabled(s32);
s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);
void try_apply_effect_four_by_chance(void *, s32, s32);
void advance_sprite_animation_and_textures(void *);
s32 rsin(s32);
s32 rand(void);
void transform_rotated_vertices(void *);
extern u8 directional_effect_entries[];
extern u8 current_spell_effect_variant[];
void update_directional_actor_effect(EntityRec *effect_arg, void *motion_arg, Row_818E0800_S_818E0800_10 *actor_state);
void shrink_spiraling_sprite_effect(void *effect, Row_818E0D94_S_818E0D94_3 *position, Rec_D_80082E80 *sprite);
#endif
