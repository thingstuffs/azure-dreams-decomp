#ifndef MODULE_TOWN_MAP_PROPS_H
#define MODULE_TOWN_MAP_PROPS_H
struct SpriteFrameState;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"
#include "town/map/animated_prop.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libgte.h"
#include "sdk/rand.h"
typedef struct TownPropPosition { s32 unk_00, unk_04, z; } TownPropPosition;
/* The Yorozu item constructor stores its pair of alternating mesh indices at +0xA0. */
typedef struct YorozuMeshProp {
    u8 pad_00[0x68];
    u16 phase;
    u8 pad_6A[0x36];
    const s32 *mesh_indices;
} YorozuMeshProp;
struct LitMeshSprite;
struct SpriteSourceEntry;

/* Five map rows toggle between two sprite sources. */
typedef struct YorozuToggleProp {
    u8 pad_00[0x68];
    u16 phase;
    u8 pad_6A[0x36];
    struct SpriteSourceEntry *sources[2];
} YorozuToggleProp;

struct EventToriInBody;
struct EventToriChildBody;
/* The Yorozu pose prop saves its initial height before the installed animation advances. */
typedef struct YorozuPoseProp {
    u8 pad_00[0x68];
    s16 state;
    u8 pad_6A[2];
    s16 pose_ticks;
    u8 pad_6E[0x32];
    s32 base_height;
    s32 animation_index;
} YorozuPoseProp;
struct ObjectPosition;
void *create_town_prop_graphic_object(TownPropPosition *position, void (*update)(), s32 graphics_id);
void *create_positioned_visual_object(TownPropPosition *position, void (*update)(), s32 angle, s32 mesh_index);
void fill_wrapped_tile_pair(s16 start_x, s16 start_y, s16 mode, s32 pair_index);
void fill_wrapped_four_by_four_grid(s32 start_x, s16 start_y, s32 unused_value);
void cycle_prop_output_values(struct YorozuMeshProp *record, struct ObjectPosition *unused_position, struct LitMeshSprite *output, s32 unused_value2);
void no_op_effect_callback(void);
void cycle_prop_animation(struct YorozuToggleProp *record, struct ObjectPosition *unused_position, SpriteFrameState *value);
void cycle_prop_animation_until_done(struct TownPropAnimationActor *self, struct ObjectPosition *unused_position, SpriteFrameState *destination);
void advance_actor_animation_pose(struct YorozuPoseProp *actor, struct ObjectPosition *pose, SpriteFrameState *animation);
void select_record_entry_and_value(void *destination, void *animation, s16 mode);
void *allocate_list_node(s32 object_type, void *list);
s32 register_node(void *entry, void *registration_id);
void advance_sprite_animation_and_textures(void *animation);
s32 check_town_target_and_callback(const void *object);
s32 service_script_controller(void);
int draw_linked_lit_meshes(void *body, struct ObjectPosition *position, struct SpriteFrameState *sprite);
void update_tori_pair_motion(struct EventToriInBody *pair);
void update_tori_child_sprite(struct EventToriChildBody *actor, struct ObjectPosition *motion, struct SpriteFrameState *actor_id);
void *memcpy(void *dst, const void *src, u32 n);
/* The caller's historical short arguments are explicit casts in its body.
 * The grid helper's third argument is passed by retail and unused by it. */
#endif
