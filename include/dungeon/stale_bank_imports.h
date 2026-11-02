#ifndef DUNGEON_STALE_BANK_IMPORTS_H
#define DUNGEON_STALE_BANK_IMPORTS_H
/*
 * Imports of the seven stale DUNGEON banks at +0x129B000..+0x12C5000 (bank_129b000 .. bank_12bf000, the old Beldo
 * code under src/dungeon/monster/beldo_old), linked 0x1000 below the regular bank slots and against an OLDER
 * dungeon engine: their engine calls land mid-function in the retail engine.  Each import is declared once with
 * its address spelling (the bytes need it); the comment names the current-engine function it corresponds to, by
 * twin alignment of the calls of relocation-masked twin functions (tools/headers/foreign_twins.py: the n-th jal of
 * a stale-bank function and of its masked twin in a live bank call the same function; the engine moved by
 * +0x1200 / +0x1210 between the two builds).
 *
 * foreign-program: dungeon 0x129B000-0x12C5000
 */
#include "common.h"

/* --- imports (tools/headers/foreign_imports.py): one declaration per address --- */
s32 func_8003DA40(s32, void *, s16 *, s16);   /* probably resolve_record_orientation_or_fallback (0x8003DE58, +0x418; 98 twin call pairs; delta not shared by a neighbouring import) */
void func_80047454(void *);   /* current advance_sprite_animation_and_textures (0x800478B8, +0x464; 147 twin call pairs) */
void func_80098E28(s32);   /* current unlink_entity_node (0x8009A028, +0x1200; 112 twin call pairs) */
s16 func_80098F70(void *, void *);   /* current check_entity_relation (0x8009A180, +0x1210; 1932 twin call pairs) */
void func_8009900C(s32, s32, s32);   /* current cycle_map_cell_flags (0x8009A21C, +0x1210; 1694 twin call pairs) */
s16 func_80099330(s32, s32, s32, s16);   /* current check_diagonal_side_height (0x8009A540, +0x1210; 3192 twin call pairs) */
s16 func_800996B0(s16, void *, void *, s32);   /* current check_directional_move_and_terrain (0x8009A8C0, +0x1210; 1022 twin call pairs) */
s16 func_8009EB6C(s32, s32, s32, s32);   /* current compare_monster_neighbor_values (0x8009FD7C, +0x1210; 3241 twin call pairs) */
s16 func_8009EF24(void *, void *);   /* current get_actor_height_difference (0x800A0134, +0x1210; 3192 twin call pairs) */
void *func_8009F09C(void *, u8, u8);   /* current find_valid_monster_neighbor (0x800A02AC, +0x1210; 1596 twin call pairs) */
void *func_8009F2E0(void *, u8, u8, s16);   /* current place_actor_at_directional_neighbor (0x800A04F0, +0x1210; 3192 twin call pairs) */
s16 func_8009F608(s32, s32, s32, s32, void *);   /* current get_rounded_facing_and_rounding_flag (0x800A0818, +0x1210; 6482 twin call pairs) */
void func_800A06B4(void *, void *, s32, s32, void *);   /* current update_actor_proximity_flag (0x800A19E4, +0x1330; 1596 twin call pairs) */
void func_800A4398(s32);   /* current play_sound_if_enabled (0x800A56E0, +0x1348; 308 twin call pairs) */
s32 func_800A59E8(void);   /* current generate_random_value (0x800A6D30, +0x1348; 1694 twin call pairs) */
void func_800A86C4(void *);   /* current update_actor_status_and_food (0x800A9A0C, +0x1348; 5775 twin call pairs) */
s16 func_800BB784(s32, s32, s16);   /* probably sample_terrain_surface_height (0x800BCB04, +0x1380; 1645 twin call pairs; delta not shared by a neighbouring import) */
/* --- end of imports --- */

#endif
