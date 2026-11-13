#ifndef R108_BANK42_H
#define R108_BANK42_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
typedef struct { u16 x,y,w,h; } __attribute__((packed)) Rect;
typedef struct { s16 x,y; } Point;
typedef struct { s16 x; u16 y; } OctantOffset; /* one of the eight 32-unit octant steps in rising_effect_octant_offsets */
typedef struct { OctantOffset value[8]; } __attribute__((packed)) CoordTable;
typedef struct { u32 word[3]; } __attribute__((packed)) Packed12;
extern const Rect D_80024038, rising_effect_texture_rect;
extern const CoordTable rising_effect_octant_offsets;
extern s16 D_80025630;
void try_lower_actor_level(void *,s32,void *);
struct PointRecord; struct EntityRec; struct ObjectPosition;
s32 draw_dimmed_height_effect_points(struct PointRecord *,struct ObjectPosition *);
struct EffectRecord; struct EntityRec;
void raise_effect_toward_terrain_height(struct EffectRecord *,struct ObjectPosition *);
void spawn_rising_effect_under_parent(ObjectNodeHeader *,s16,s32,s16,s16,s16,s16);
s32 random_value_below_limit(s32);
struct ShuffledSpriteClearBody;
void update_shuffled_rect_clear_effect(struct ShuffledSpriteClearBody *,s32 *,void *);
struct S_func_8190B2D0_0;
void update_rising_capture_effect(struct S_func_8190B2D0_0 *,void *,void *);
void draw_transformed_sprite_with_clip_rect(void *,void *,void *,s32,s32);
#endif
