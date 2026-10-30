#ifndef TOWN_MINIGAME_H
#define TOWN_MINIGAME_H

#include "common.h"
#include "town/scene/collection.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/scene.h"
#include "records/Rec_func_80021E88_arg1.h"
#include "town/minigame/pickup_data.h"
#include "town/minigame/effect.h"
struct S_80021E88_0;
struct S_80021E88_2;
struct SpinPhaseWork;

/* Slot-payout pickup body received by update_bouncing_pickup_after_hit. */
typedef struct BouncingPickupAfterHitObject {
    /* 0x00 */ void *slot_state;
    /* 0x04 */ union { s16 s; u16 u; } state;
    /* 0x06 */ union { s16 s; u16 u; } timer;
    /* 0x08 */ u8 pad_08[0x15];
    /* 0x1D */ u8 unk_1D;
    /* 0x1E */ u8 pad_1E[0x32];
    /* 0x50 */ void *payout_callback;
    /* 0x54 */ s16 denomination;
} BouncingPickupAfterHitObject;

/* Body of a timed-sound node. The creator's node view is TimedSoundNode below. */
typedef struct TimedSoundObject {
    /* 0x00 */ u8 pad_00[0x50];
    /* 0x50 */ union { s16 s; u16 u; } state;
    /* 0x52 */ u16 timer;
} TimedSoundObject;

typedef struct TimedSoundNode {
    ObjectNodeHeader header;
    TimedSoundObject body;
} TimedSoundNode;

/* State and countdown for the slot-machine image animation. */
typedef struct MinigameImageAnimationObject {
    /* 0x00 */ u8 pad_00[0x5C];
    /* 0x5C */ union { s16 s; u16 u; } state;
    /* 0x5E */ u16 timer;
} MinigameImageAnimationObject;

/* Child object and owner state for the three-object tako shuffle minigame. */
typedef struct TakoMinigameObject {
    /* 0x00 */ u8 pad_00[0x70];
    /* 0x70 */ s16 state;
    /* 0x72 */ s16 value_72;
    /* 0x74 */ u8 pad_74[2];
    /* 0x76 */ s16 random_76;
} TakoMinigameObject;

typedef struct TakoMinigameState {
    /* 0x00 */ TakoMinigameObject *objects[3];
    /* 0x0C */ s16 state;
    /* 0x0E */ s16 timer;
    /* 0x10 */ s16 table_x;
    /* 0x12 */ s16 field_12;
    /* 0x14 */ s16 threshold;
    /* 0x16 */ u16 counter;
    /* 0x18 */ s16 table_y;
    /* 0x1A */ u16 flags;
} TakoMinigameState;

/* Countdown and owner reference for the minigame value decrease. */
typedef struct TimedValueDecreaseObject {
    /* 0x00 */ void *owner;
    /* 0x04 */ u8 pad_04[0x14];
    /* 0x18 */ union { s16 s; u16 u; } state;
    /* 0x1A */ u16 timer;
} TimedValueDecreaseObject;

/* Body of a betting-column object: update_betting_effect allocates the node (allocate_list_node(0x112, ...)),
 * stores the betting effect in `owner`, installs update_minigame_approach_motion and draws it with
 * project_sprite_chain.  The callback drops the column in, bobs it while `state` is 1/2 (0xF0 sways it by
 * `phase`) and withdraws it once the owner's +0x18 state reaches 2. */
typedef struct ApproachMotionObject {
    /* 0x00 */ s16 state;
    /* 0x02 */ u16 phase; /* sway phase for state 0xF0, 0..0x7F */
    /* 0x04 */ void *owner; /* betting effect that spawned the column */
} ApproachMotionObject;


/* initialize_minigame_display.c */
void initialize_minigame_display(void *context);

/* Object-pool callbacks: motion is the separate node +8 position record. */
void update_bouncing_pickup(minigame_pickup_source *pickup, ObjectPosition *motion, SpriteFrameState *sprite);
void update_bouncing_pickup_after_hit(BouncingPickupAfterHitObject *object, ObjectPosition *motion, SpriteFrameState *sprite);
void update_snowball_minigame_actor(TownCollectionActor *object, ObjectPosition *motion, SpriteFrameState *sprite);
void update_minigame_approach_motion(ApproachMotionObject *motion_state, ObjectPosition *motion);

void count_entries_matching_search_path(TownCollectionSequence *scene);


void create_minigame_display_objects(void);

/* Callback entry points. */
s32 draw_depth_sorted_line_nodes(u8 *node);
void advance_fading_particle_until_animation_boundary(u8 *effect, u8 *motion, u8 *visual);
void rotate_gym_mesh_y(s32 unused_0, s32 unused_1, u8 *object);
void tick_scene_value_text(void *message);
void tick_summed_scene_value_text(void *entry);
void tick_timed_sound(TimedSoundObject *object);
void update_linked_four_column_number(void *entry);
void update_minigame_image_animation(MinigameImageAnimationObject *anim);
void update_tako_minigame(TakoMinigameState *state);
void run_timed_value_decrease(TimedValueDecreaseObject *sequence, EntityRec *target);

/* initialize_casino_minigame.c: the casino image (town +0x79D800) loads at 0x80020000. */
s32 initialize_casino_minigame(void);
/* Update callbacks it installs; their definitions take file-local views. */
void update_betting_effect(TownEffect *effect);
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

s32 draw_translucent_gradient_line_list(void *first_entry);

#endif
