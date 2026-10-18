#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);

/* Forward the object and parameters to apply_object_setup_and_update. */
void forward_reaction_update(void *object, s32 param_1, s32 param_2) {
    apply_object_setup_and_update(object, param_1, param_2);
}
