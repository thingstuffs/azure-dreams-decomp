#include "common.h"

#include "engine/script.h"
#include "town/player/action_initializers.h"
#include "town/player.h"

/* Run the fallback handler when the request check returns zero. */
void dispatch_fallback_request(Rec_func_80094268_arg0 *request, void *request_data, void *request_param, s32 check_param) {
    if (service_script_controller() == 0) {
        initialize_scene_action_record(request, request_data, request_param);
    }
}
