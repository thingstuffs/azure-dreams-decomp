#include "common.h"

#include "engine/script.h"
extern s32 check_active_transform_object(void *other);
#include "town/person/object_setup.h"
extern void initialize_object_handlers(void *object, void *setupParam1, void *setupParam2);
extern u8 D_80082A39[16];

/* Select the object setup path after a successful request. */
s32 select_object_setup_path(void *object, void *request_data, void *request_param, s32 unused) {
    if (service_script_controller() == 0) {
        return 0;
    }

    if (check_active_transform_object(object) != 0 ||
        D_80082A39[0] == *(s32 *)((u8 *)object + 0x60)) {
        initialize_object_and_update(object, request_data, request_param);
        return 1;
    }

    initialize_object_handlers(object, request_data, request_param);
    return 1;
}
