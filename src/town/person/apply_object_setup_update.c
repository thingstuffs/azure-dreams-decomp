#include "common.h"
#include "town/person/object_setup.h"
#include "town/person.h"

/* Forward the object and callback arguments to apply_object_setup_and_update. */
void apply_object_setup_update(void *object, void *callback_arg_1, void *callback_arg_2) {
    apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
}
