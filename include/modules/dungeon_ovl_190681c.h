#ifndef DUNGEON_OVL_190681C_H
#define DUNGEON_OVL_190681C_H
#include "common.h"
#include "dungeon/effect/particle.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/game_work.h"
#include "sdk/libc.h"
#include "dungeon/level.h"

/* Advance the effect through target selection, movement, impact, and cleanup. */
typedef struct Row_818E6F98_Primitive {
    u32 tag;
    u32 color;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    s16 x1;
    s16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u8 u2;
    u8 v2;
    u16 pad1;
    s16 x3;
    s16 y3;
    u8 u3;
    u8 v3;
    u8 pad2[0xE];
} Row_818E6F98_Primitive;

typedef struct Row_818E6F98_DungeonState {
    u8 pad0[0xB0];
    u32 ordering_table[0x208];
    Row_818E6F98_Primitive *next_primitive;
} Row_818E6F98_DungeonState;

typedef union Row_818E6F98_WorkOutput {
    u16 h[4];
    s32 w[2];
} Row_818E6F98_WorkOutput;

/* Queues a textured quad at the supplied world position. */
int abs(int);
void *allocate_list_node(s32, void *);
void *func_8003FD64(s32, void *);
void register_node(void *, void *);
void func_8004491C(void *, void *);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
s32 get_definition_entry_byte_13(s16 entry_index);
s32 scan_actor_along_heading(void *, u8, u8, s16, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
s32 play_sound_if_enabled(s32);
void unlink_node(void *);
void func_80044A50(void *);
void initialize_timed_motion_step(s32, s32);
void copy_selected_table_pair(void *, s16);
s32 try_trigger_target_record_effect(void *, s32, void *);
void try_apply_effect_four_by_chance(void *, s32, s32);
s32 RotTransPers(void *, void *, void *, void *);
s16 GetTPage(s32, s32, s32, s32);
s16 GetClut(s32, s32);
void SetSemiTrans(void *, s32);
void SetPolyFT4(void *);
extern u8 directional_particle_node_callback[];
extern u8 directional_particle_callback[];
extern u8 D_800249DC[];
extern u8 fading_sprite_entries[];
extern u8 current_spell_effect_variant[];
s32 project_linked_vertical_point_quads(void *sprite_data, void *position);
#endif
