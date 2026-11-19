#ifndef DUNGEON_OVL_18B8824_H
#define DUNGEON_OVL_18B8824_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/system.h"
#include "sdk/abs.h"
#include "sdk/rand.h"
/* Owner of the launched sprite sequence and its child counter at +0x14. */
typedef struct LaunchedEffectBody {
    void *owner;
    void *image;
    u8 unk8;
    u8 id;
    s16 state;
    s16 unkC;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 child_updates;
    s16 x;
    s16 y;
    s16 z;
    u8 status;
    u8 pad1D[0x7B];
} LaunchedEffectBody;

typedef struct RandomRotationSpriteEffectBody {
    u8 pad_00[0xC];
    LaunchedEffectBody *owner;
    s16 ticks;
    s16 lifetime;
} RandomRotationSpriteEffectBody;
/* Owner link and child counter for the randomized grayscale emitter. */
typedef struct RandomizedGrayscaleEffectBody {
    LaunchedEffectBody *owner;
    u16 ticks;
} RandomizedGrayscaleEffectBody;
/* Owner link and milestone counter for the counted sprite emitter. */
typedef struct CountedSpriteEffectBody {
    LaunchedEffectBody *owner;
    s16 ticks;
} CountedSpriteEffectBody;
/* Parent link stored by the sprite that copies its initial motion data. */
typedef struct SpriteEffectWithDataBody {
    LaunchedEffectBody *owner;
} SpriteEffectWithDataBody;
typedef struct ovl_18b8824_81898EBC_ColorPart {
    u8 pad[0xC];
    u32 color;
} ovl_18b8824_81898EBC_ColorPart;
typedef struct ovl_18b8824_81898EBC_Scratch {
    s16 work[8];
    u8 gap[8];
    s16 ovl_18b8824_81898EBC_probe[3];
    u8 result_gap[2];
    s16 ovl_18b8824_81898EBC_result;
    u16 ovl_18b8824_81898EBC_map_flags;
} ovl_18b8824_81898EBC_Scratch;
#define ovl_18b8824_81898EBC_U8_AT(p, n) (*(u8 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))
#define ovl_18b8824_81898EBC_probe scratch.ovl_18b8824_81898EBC_probe
#define ovl_18b8824_81898EBC_result scratch.ovl_18b8824_81898EBC_result
#define ovl_18b8824_81898EBC_map_flags scratch.ovl_18b8824_81898EBC_map_flags
extern void register_node(void *, void *);
extern u8 D_80024E88[];
extern void advance_sprite_animation_and_textures(void *target);
void select_record_entry_and_value(void *state, void *entries, short index);
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_80024EF4[];
extern SpriteSourceEntry D_80024E40[];
extern u8 D_80024FC4[];
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s16 get_surface_height_at_record(void *);
extern s32 check_left_tile_and_center_height(s32, s32, s32);
extern void *create_actor_sprite_at_tile(u8, s16, s16, s16); /* Unprototyped: retail call narrows its arguments to this declaration; no shared prototype keeps it */
extern void func_80042640(void *, s32);
extern s32 generate_random_value(void);
void interpolate_view_parameters(RandomRotationSpriteEffectBody *state, ObjectPosition *motion, SpriteFrameState *transform);
void *create_random_rotation_sprite_effect(LaunchedEffectBody *context, ObjectPosition *copy_src, s16 initial_value);
void update_randomized_grayscale_effect(RandomizedGrayscaleEffectBody *entry, ObjectPosition *unused, SpriteFrameState *target);
void *create_randomized_grayscale_effect(LaunchedEffectBody *owner, ObjectPosition *initial_state);
void update_counted_sprite_effect(CountedSpriteEffectBody *entry, ObjectPosition *position, SpriteFrameState *target);
void *create_counted_sprite_effect(LaunchedEffectBody *owner, ObjectPosition *initial_state);
void animate_sprite_once_counting_owner_ticks(SpriteEffectWithDataBody *object_ref, ObjectPosition *unused, SpriteFrameState *target);
ObjectNodeHeader *create_sprite_effect_with_data(LaunchedEffectBody *owner, ObjectPosition *initial_data);
void advance_launched_effect(LaunchedEffectBody *state, ObjectPosition *motion, ovl_18b8824_81898EBC_ColorPart *part);
#endif
