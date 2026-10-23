/* Cache scaled service result.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00738 - PD:town/ll34_581000_80016000:80017FB8, PD:town/ll34_594800_80016000:80019268.
 */
#include "town/scene/service/cache_scaled_service_result_g00738.h"

/* Call the callback with fixed arguments and cache three quarters of its result. */
u32 invoke_state_callback(void) {
    s8 callback_args[4];
    u32 scaled_result;

    callback_args[1] = 1;
    callback_args[0] = 1;
    callback_args[2] = 0;
    callback_args[3] = 0;
    scaled_result = (u32) (town_scene_root->services->callback_050(callback_args) * 3) >> 2;
    D_80017FB8 = scaled_result;
    return scaled_result;
}

/* Pass the four-byte request 1, 1, 0, 0 to func_800168BC. */
void pass_four_byte_request_1(void) {
    s8 request[4];

    request[1] = 1;
    request[0] = 1;
    request[2] = 0;
    request[3] = 0;
    func_800168BC(request);
}
