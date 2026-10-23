/* Service calls with saved player values
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00678 - PD:town/ll34_5db800_80016000:800183C8, PD:town/ll34_5db800_80016000:800183D0.
 * PD:town/ll34_5db800_80016000:800183C8
 * PD:town/ll34_5db800_80016000:800183D0
 */
#include "town/scene/service.h"

/* Private declarations retained from the member sources. */
/* Service calls with saved player values */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00678 - PD:town/ll34_5db800_80016000:800183C8, PD:town/ll34_5db800_80016000:800183D0. */

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"

typedef void (*Callback)(s32);

extern s32 scene_saved_player_value;
extern s32 D_800183D0;

/* Save the state value in D_800183C8 and invoke the state callback with 0. */
void save_player_value_and_run_service_44(void) {
    scene_saved_player_value = ((TownPositionState *)town_scene_root->position)->unk_3C;
    town_scene_root->services->callback_044(0);
}

/* Call the context callback with the two global values. */
void run_service_4c_with_saved_values(void) {
    town_scene_root->services->callback_04C(scene_saved_player_value, D_800183D0);
}
