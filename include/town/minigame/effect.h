#ifndef TOWN_MINIGAME_EFFECT_H
#define TOWN_MINIGAME_EFFECT_H
/* Prototypes of the functions defined in src/town/minigame/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"

struct S_80026978_1;

/* create_brief_randomized_particle.c */
void create_brief_randomized_particle(struct S_80026978_1 *origin);

/* create_randomized_trail_particle.c */
void create_randomized_trail_particle(ObjectPosition *source);

/* create_tinted_animated_particle.c */
void create_tinted_animated_particle(s32 color, s32 x, s32 y, s32 z);

/* retire_transient_line_effect.c */
void retire_transient_line_effect(void *record);

#endif
