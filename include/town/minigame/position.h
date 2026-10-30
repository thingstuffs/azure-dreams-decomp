#ifndef TOWN_MINIGAME_POSITION_H
#define TOWN_MINIGAME_POSITION_H
/* Prototypes of the functions defined in src/town/minigame/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct SpinPhaseWork;

/* Body of a minigame scene-tile object (the payload after its ObjectNodeHeader).  Creators allocate the node
 * with allocate_list_node(1, ...), install one of the fade_/show_ scene-tile update callbacks below and
 * register the node under build_menu_line_tile_packets, which draws every chained body as a TILE plus a
 * draw-mode packet from color/x/y/width/height/tpage_mode and flags (engine S_80053A88_Node views the same
 * 0x18 bytes).  The update callbacks step `state`, count `delay` down, watch the `linked` object's status
 * bits and fade `color` by 0x080808 per frame before setting NODE_REMOVE in the header. */
typedef struct SceneTileObject {
    /* 0x00 */ union { s16 s; u16 u; } state; /* callback phase; stepped both as s16 and u16 in retail */
    /* 0x02 */ u16 delay; /* frames before the tile is shown (state 0) */
    /* 0x04 */ void *linked; /* object whose status bits end the current phase */
    /* 0x08 */ s32 color; /* packed 0xBBGGRR tile colour (TILE code word) */
    /* 0x0C */ u16 x;
    /* 0x0E */ u16 y;
    /* 0x10 */ u16 width;
    /* 0x12 */ u16 height;
    /* 0x14 */ s16 tpage_mode; /* GetTPage semi-transparency mode */
    /* 0x16 */ u16 flags; /* bit 0: semi-transparent, bit 1: hidden (not linked into the order table) */
} SceneTileObject;

/* fade_delayed_scene_tile_on_completion.c */
void fade_delayed_scene_tile_on_completion(SceneTileObject *effect);

/* fade_scene_tile_across_terminal_phase.c */
void fade_scene_tile_across_terminal_phase(SceneTileObject *effect);

/* fade_scene_tile_after_completion_flag.c */
void fade_scene_tile_after_completion_flag(void *state);

/* fade_scene_tile_after_linked_flag.c */
void fade_scene_tile_after_linked_flag(SceneTileObject *effect);

/* fade_scene_tile_when_linked_state_clears.c */
void fade_scene_tile_when_linked_state_clears(SceneTileObject *entry);

/* show_delayed_scene_tile_until_complete.c */
void show_delayed_scene_tile_until_complete(SceneTileObject *object);

/* update_effect_position_spin_phases.c */
void update_effect_position_spin_phases(struct SpinPhaseWork *state_arg, ObjectPosition *target_arg, SpriteFrameState *effect_arg);

#endif
