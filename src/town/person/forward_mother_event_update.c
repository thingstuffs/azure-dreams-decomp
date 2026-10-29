#include "common.h"
#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"

/* Forward the object and parameters to apply_object_setup_and_update. */
void forward_mother_event_update(void *object, void *param_1, void *param_2) {
    apply_object_setup_and_update(object, param_1, param_2);
}
