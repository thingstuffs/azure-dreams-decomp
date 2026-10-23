/* Threshold counter test and subtraction
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00672 - PD:town/ll34_581000_80016000:80017FB8, PD:town/ll34_594800_80016000:80019268, PD:town/ll34_5b2000_80016000:80017788.
 * PD:town/ll34_581000_80016000:80017FB8
 * PD:town/ll34_594800_80016000:80019268
 * PD:town/ll34_5b2000_80016000:80017788
 */
#include "town/scene.h"

/* Private declarations retained from the member sources. */
/* Threshold counter test and subtraction */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00672 - PD:town/ll34_581000_80016000:80017FB8, PD:town/ll34_594800_80016000:80019268, PD:town/ll34_5b2000_80016000:80017788. */

#include "common.h"
#include "m2c_compat.h"

typedef struct { u8 pad[0x2D5C]; u32 counter; } Counter;

typedef struct { u8 pad[0x38]; Counter *work; } State;

extern State *town_scene_root;
extern u32 D_80017FB8;

s32 check_counter_threshold(void) { return town_scene_root->work->counter >= D_80017FB8; }

void subtract_threshold_from_counter(void) { town_scene_root->work->counter -= D_80017FB8; }
