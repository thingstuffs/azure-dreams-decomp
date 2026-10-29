#ifndef TOWN_MINIGAME_H
#define TOWN_MINIGAME_H

#include "common.h"
#include "town/scene/collection.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "town/scene.h"
#include "records/Rec_func_80021E88_arg1.h"
struct S_80021E88_0;
struct S_80021E88_2;
struct SpinPhaseWork;


/* initialize_minigame_display.c */
void initialize_minigame_display(void *context);

/* Object-pool callbacks: motion is the separate node +8 position record. */
void update_bouncing_pickup(void *pickup, ObjectPosition *motion, SpriteFrameState *sprite);
void update_bouncing_pickup_after_hit(void *object, ObjectPosition *motion, SpriteFrameState *sprite);
void update_snowball_minigame_actor(TownCollectionActor *object, ObjectPosition *motion, SpriteFrameState *sprite);
void update_minigame_approach_motion(void *motion_state, ObjectPosition *motion);

void count_entries_matching_search_path(TownCollectionSequence *scene);


void create_minigame_display_objects(void);

/* Callback entry points. */
s32 draw_depth_sorted_line_nodes(u8 *node);
void advance_fading_particle_until_animation_boundary(u8 *effect, u8 *motion, u8 *visual);
void rotate_gym_mesh_y(s32 unused_0, s32 unused_1, u8 *object);
void tick_scene_value_text(void *message);
void tick_summed_scene_value_text(void *entry);
void tick_timed_sound(void *object);
void update_linked_four_column_number(void *entry);
void update_minigame_image_animation(void *anim);

/* initialize_casino_minigame.c: the casino image (town +0x79D800) loads at 0x80020000. */
s32 initialize_casino_minigame(void);
/* Update callbacks it installs; their definitions take file-local views. */
void update_betting_effect();
void update_effect_position_spin_phases(struct SpinPhaseWork *state_arg, ObjectPosition *target_arg, SpriteFrameState *effect_arg);
void update_minigame_transition(struct S_80021E88_0 *controller, Rec_func_80021E88_arg1 *position, struct S_80021E88_2 *display);
/* Mode-three record setup (town/scene/configure_set_mode_n_d.c) as the minigame constructors call it. */
#include "town/scene/list_setup.h"
extern s32 pickup_reward_total[];
extern u8 D_80020014[];             /* callback data word shared by the casino models */
extern SceneImageRect D_80020018;   /* initializer of the casino palette rectangle (112, 449, 48, 1) */
extern u8 D_80024568[];             /* casino display context */
extern u8 D_80024408[];             /* betting model mode-three parameters */
extern u8 D_800243F0[];             /* payout digit mode-three parameters */
extern s32 D_80024444[];            /* payout digit mesh ids */
extern u32 D_800245C8[];            /* saved casino palette row */
struct KeimaPathActor;

struct KeimaPathActor;
void update_directional_record(struct KeimaPathActor *orientation, void *state_ptr, SpriteFrameState *record);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void create_timed_sound(s16 value);
void draw_scrolling_column(s16 column, s16 tile_index, s16 scroll_y);

#endif
