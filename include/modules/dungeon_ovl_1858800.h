#ifndef DUNGEON_OVL_1858800_H
#define DUNGEON_OVL_1858800_H
#include "shared/dungeon_projectile_views.h"
#include "shared/slus_callbacks.h"
extern int abs(int);
extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800A3820(s16 entry_index);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern s32 func_800BCB04(s32 x, s32 y, s16 min_height);
extern s32 func_800A4688(s32 world_x, s32 world_y, s16 world_z, u32 direction, s32 disabled);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void func_800A56E0(s32);
extern void func_80044A50(void *);
extern u8 D_800DEA68[];
extern s32 func_80065420(SVECTOR *, s16 *, s32 *, s32 *);
extern void func_800666F4(POLY_FT4 *);
extern void func_80066640(POLY_FT4 *, s32);
extern u16 func_80066460(s32, s32, s32, s32);
extern u16 func_8006649C(s32, s32);
void func_800478B8(void *);                 /* extern */
extern u8 D_800DEC70[];
extern SpriteSourceEntry D_800DED28;
void func_80024020(ProjectileState *, ProjectileMotion *, ProjectileSprite *);
s32 func_800248F8(RenderRecord *, PositionFields *);
void func_80024B58(void *, void *, void *);
#endif
