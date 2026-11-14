#include "modules/main_title_callbacks.h"
#include "common.h"
#include "frontend/libcard.h"

#include "slus/resource_transition_task.h"

/* Assigns the object descriptor when the object check succeeds. */
void start_settings_after_transition(void *object_data_addr) {
    ObjectNodeHeader *object;

    object = object_data_addr;
    object -= 1;
    if (create_resource_transition_for_descriptor_check(object) != 0) {
        object->update_callback = create_settings_controller_and_flag_removal;
    }
}
