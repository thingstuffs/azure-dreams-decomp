#include "common.h"

s32 func_800352FC(s32 request, s32 request_data, s32 request_param, s32 check_param);
void initialize_scene_action_record();       /* extern */

/* Run the fallback handler when the request check returns zero. */
void dispatch_fallback_request(s32 request, s32 request_data, s32 request_param, s32 check_param) {
    if (func_800352FC(request, request_data, request_param, check_param) == 0) {
        initialize_scene_action_record(request, request_data, request_param);
    }
}
