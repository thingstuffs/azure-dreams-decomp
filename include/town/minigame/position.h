#ifndef TOWN_MINIGAME_POSITION_H
#define TOWN_MINIGAME_POSITION_H
/* Prototypes of the functions defined in src/town/minigame/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct SpinPhaseWork;

/* fade_delayed_scene_tile_on_completion.c */
void fade_delayed_scene_tile_on_completion(void *effect);

/* fade_scene_tile_across_terminal_phase.c */
void fade_scene_tile_across_terminal_phase(void *effect);

/* fade_scene_tile_after_completion_flag.c */
void fade_scene_tile_after_completion_flag(void *state);

/* fade_scene_tile_after_linked_flag.c */
void fade_scene_tile_after_linked_flag(void *effect);

/* fade_scene_tile_when_linked_state_clears.c */
void fade_scene_tile_when_linked_state_clears(void *entry);

/* show_delayed_scene_tile_until_complete.c */
void show_delayed_scene_tile_until_complete(void *object);

/* update_effect_position_spin_phases.c */
void update_effect_position_spin_phases(struct SpinPhaseWork *state_arg, ObjectPosition *target_arg, SpriteFrameState *effect_arg);

#endif
