#ifndef DUNGEON_OVL_1858800_H
#define DUNGEON_OVL_1858800_H
#include "shared/dungeon_height_query.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/slus_callbacks.h"
extern int abs(int);
extern void *allocate_list_node(s32, void *);
extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern s32 resolve_record_orientation_or_fallback(void *, void *, s16 *, s32);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern s32 get_definition_entry_byte_13(s16 entry_index);
extern void *scan_actor_along_heading(void *, s32, s32, s32, s32);
extern void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
extern void play_sound_if_enabled(s32);
extern void unlink_node(void *);
extern void func_80044A50(void *);
extern u8 secondary_sprite[];
extern s32 RotTransPers(SVECTOR *, s16 *, s32 *, s32 *);
extern void SetPolyFT4(POLY_FT4 *);
extern void SetSemiTrans(POLY_FT4 *, s32);
extern u16 GetTPage(s32, s32, s32, s32);
extern u16 GetClut(s32, s32);
void advance_sprite_animation_and_textures(void *);                 /* extern */
extern u8 shared_sprite_entries[];
extern SpriteSourceEntry D_800DED28;
void func_80024020(ProjectileState *, ProjectileMotion *, ProjectileSprite *);
s32 func_800248F8(RenderRecord *, EntityRec *);
void update_timed_sprite_effect(void *, void *, void *);
#endif
