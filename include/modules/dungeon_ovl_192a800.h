#ifndef R108_BANK42_H
#define R108_BANK42_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
typedef struct { u16 x,y,w,h; } __attribute__((packed)) Rect;
typedef struct { s16 x,y; } Point;
typedef struct { s16 x; u16 y; } Coord;
typedef struct { Coord value[8]; } __attribute__((packed)) CoordTable;
typedef struct { u32 word[3]; } __attribute__((packed)) Packed12;
extern const Rect D_80024038, D_80024040;
extern const CoordTable D_80024064;
extern s16 D_80025630;
void try_lower_actor_level(void *,s32,void *);
struct PointRecord; struct EntityRec; struct ObjectPosition;
s32 func_80024154(struct PointRecord *,struct ObjectPosition *);
struct EffectRecord; struct EntityRec;
void handle_raise_position_toward_queried_height_set_flags_countdown_expires(struct EffectRecord *,struct ObjectPosition *);
void handle_retail_n_8190_ac_70_callee_80024470_spawn_effect_under_parent_node_placed_parent(ObjectNodeHeader *,s16,s32,s16,s16,s16,s16);
s32 get_a_random_in_n_0_limit_zero_limit_zero_rejection_sampling(s32);
void advance_the_animation_draws_rectangles_in_randomized_order(void *,s32 *,void *);
struct S_func_8190B2D0_0;
void update_a_moving_effect_target_animation_cleanup_state(struct S_func_8190B2D0_0 *,void *,void *);
void draw_transformed_sprite_with_clip_rect(void *,void *,void *,s32,s32);
#endif
