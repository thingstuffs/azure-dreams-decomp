#ifndef TOWN_MINIGAME_H
#define TOWN_MINIGAME_H
#include "town/minigame/object.h"

#include "common.h"
#include "town/scene/collection.h"
#include "town/scene/list_setup.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/scene.h"
#include "records/Rec_func_80021E88_arg1.h"
#include "town/minigame/pickup_data.h"
#include "town/minigame/effect.h"
#include "town/minigame/state.h"
struct SpinPhaseWork;

/* Slot-payout pickup body received by update_bouncing_pickup_after_hit. */
typedef struct BouncingPickupAfterHitObject {
    /* 0x00 */ State8081FF68 *slot_state;
    /* 0x04 */ union { s16 s; u16 u; } state;
    /* 0x06 */ union { s16 s; u16 u; } timer;
    /* 0x08 */ TownSceneListNode scene;
    /* 0x20 */ u8 pad_20[0x30];
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

/* Per-column scroll state and position for the minigame display children. */
typedef struct MinigameDisplayObjectsBody {
    /* 0x00 */ void *parent;
    /* 0x04 */ union { s16 s; u16 u; } state;
    /* 0x06 */ u16 ticks;
    /* 0x08 */ s16 column;
    /* 0x0A */ s16 column_offset;
    /* 0x0C */ union { s16 s; u16 u; } step;
    /* 0x0E */ union { s16 s; u16 u; } scroll_offset;
} MinigameDisplayObjectsBody;

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

/* Body of a tako projectile. update_tako_target fills one from the target's timing table while the minigame
 * state's flag 0x1 is set, and create_tako_projectile copies it into a new node, the only one that installs
 * update_object_movement_proximity_reactions: phase 1 accelerates it along X; close to the player the minigame
 * counter decides between a deflection (3 to 5, two points) and a one-point hit (6 to 9), and a projectile that
 * gets past (X at or below 0x427FFFF) bursts instead. */
typedef struct TakoProjectileBody {
    /* 0x00 */ struct TakoChildBody *target; /* the target that threw it; the updater sets and clears the target's flags */
    /* 0x04 */ s32 velocity_x; /* added to the position's X in the flight phases (1 and 3); a deflection sets it to
                              * 0x180000 and a one-point hit hands it to the sparks */
    /* 0x08 */ s32 acceleration_x; /* added to velocity_x each phase-1 update */
    /* 0x0C */ s16 phase; /* 0 wind-up, 1 flight, 2 and 4 particle bursts, 3 flight after a deflection, 0xFF removal */
    /* 0x0E */ s16 timer; /* ticks left in the wind-up and burst phases */
    /* 0x10 */ u16 flags; /* 0x4: already deflected or hit */
} TakoProjectileBody;

/* Body of the two shrinking sprites a one-point hit leaves: update_object_movement_proximity_reactions creates them
 * and installs drift_and_shrink_reaction_effect, the only one to do so, which moves them by drift_x and keeps the
 * target's live-projectile flag set until they have shrunk away. */
typedef struct TakoHitSparkBody {
    /* 0x00 */ struct TakoChildBody *target; /* the target of the projectile that left them */
    /* 0x04 */ s32 drift_x; /* the projectile's velocity_x when it was hit, added to X each update */
} TakoHitSparkBody;

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
    /* 0x04 */ TownEffect *owner; /* betting effect that spawned the column */
} ApproachMotionObject;

/* initialize_minigame_display.c */
void initialize_minigame_display(void *context);

/* Object-pool callbacks: motion is the separate node +8 position record. */
void update_bouncing_pickup(minigame_pickup_source *pickup, ObjectPosition *motion, SpriteFrameState *sprite);
void update_bouncing_pickup_after_hit(BouncingPickupAfterHitObject *object, ObjectPosition *motion, SpriteFrameState *sprite);
void update_snowball_minigame_actor(TownCollectionActor *object, ObjectPosition *motion, SpriteFrameState *sprite);
void update_minigame_approach_motion(ApproachMotionObject *motion_state, ObjectPosition *motion);

void update_collection_cutscene_step(TownCollectionSequence *scene);

void create_minigame_display_objects(void);

/* Callback entry points. */
struct PairedIndicators;
s32 draw_depth_sorted_line_nodes(struct PairedIndicators *node);
void fade_falling_particle_until_done(u8 *effect, ObjectPosition *motion, SpriteFrameState *visual);
struct GymMeshWork;
struct LitMeshSprite;
struct Town215E0State;
void update_minigame_rise_decay(struct Town215E0State *cycle, ObjectPosition *unused_position, struct LitMeshSprite *sprite);
void rotate_gym_mesh_y(struct GymMeshWork *work, ObjectPosition *position, struct LitMeshSprite *sprite);
void rotate_gym_mesh_x(struct GymMeshWork *work, ObjectPosition *position, struct LitMeshSprite *sprite);
void tick_scene_value_text(TownCollectionText *message);
void tick_summed_scene_value_text(TownCollectionText *entry);
void tick_timed_sound(TimedSoundObject *object);
void update_linked_four_column_number(void *entry);
void update_minigame_image_animation(MinigameImageAnimationObject *anim);
void update_minigame_scroll(MinigameDisplayObjectsBody *scroll);
void update_tako_minigame(TakoMinigameState *state);
void run_timed_value_decrease(TimedValueDecreaseObject *sequence, ObjectPosition *target);

/* initialize_casino_minigame.c: the casino image (town +0x79D800) loads at 0x80020000. */
s32 initialize_casino_minigame(void);
/* Update callbacks it installs; their definitions take file-local views. */
void update_betting_effect(TownEffect *effect);
void update_effect_position_spin_phases(struct SpinPhaseWork *state_arg, ObjectPosition *target_arg, SpriteFrameState *effect_arg);
void update_minigame_transition(MinigameTransitionObject *controller, ObjectPosition *position, SpriteFrameState *display);
/* Mode-three record setup (town/scene/configure_set_mode_n_d.c) as the minigame constructors call it. */
extern s32 pickup_reward_total[];
extern u8 D_80020014[];             /* callback data word shared by the casino models */
extern RECT D_80020018;   /* initializer of the casino palette rectangle (112, 449, 48, 1) */
extern u8 D_80024568[];             /* casino display context */
extern u8 D_80024408[];             /* betting model mode-three parameters */
extern u8 D_800243F0[];             /* payout digit mode-three parameters */
extern s32 D_80024444[];            /* payout digit mesh ids */
extern u32 D_800245C8[];            /* saved casino palette row */
struct KeimaPathActor;

struct KeimaPathActor;
void update_directional_record(struct KeimaPathActor *orientation, struct KeimaPathActor *state_ptr, SpriteFrameState *record);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void create_timed_sound(s16 value);
void draw_scrolling_column(s16 column, s16 tile_index, s16 scroll_y);

s32 draw_translucent_gradient_line_list(void *first_entry);

struct ObjectStatePositionObject;
void update_proximity_triggered_object(struct ObjectStatePositionObject *self, ObjectPosition *position, struct LitMeshSprite *target);

void create_tako_projectile(TakoProjectileBody *init_data, s32 pos_y, s32 unused_effect_arg);
s32 initialize_mogura_minigame(void *unused_arg0, void *unused_arg1, void *unused_arg2, void *unused_arg3);

struct EffectPhaseTimer16;
struct Motion;
void create_eight_linked_scene_sprites(struct TownCollectionSequence *owner);
void create_rotating_layered_line_cage(struct TownCollectionSequence *effect);
void load_keima_resource(void);
void load_town_resource(void);
void load_minigame_module(void);
void update_motion_spawn_particles(struct EffectPhaseTimer16 *state, struct Motion *motion, SpriteFrameState *sprite_data);

/* The retail dispatch wrappers initialize all four incoming argument registers. */
s32 initialize_tako_minigame(s32 unused_arg0, s32 unused_arg1, s32 unused_arg2, s32 unused_arg3);
s32 initialize_snowball_minigame(s32 unused_arg0, s32 unused_arg1, s32 unused_arg2, s32 unused_arg3);
s32 initialize_gym_minigame(s32 unused_arg0, s32 unused_arg1, s32 unused_arg2, s32 unused_arg3);

#endif
