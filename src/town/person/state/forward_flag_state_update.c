#include "common.h"
#include "town/person/object_setup.h"

/* Forward the object and update arguments to apply_object_setup_and_update. */
void forward_flag_state_update(void *object, void *context, void *update_data) {
    apply_object_setup_and_update(object, context, update_data);
}
