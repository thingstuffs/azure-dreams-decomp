#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/response_checks.h"

/* Selects an interaction response from a table, a progress flag, and a one-time response latch. */
s32 select_one_time_interaction_response(void *object, s32 check_value, s32 selection)
{
    void *response_table;
    s32 default_response;
    s32 response;

    if (check_table_result_below_minus_47() != 0) {

        return &D_8001B7AE;
    }

    response_table = &D_8001A99C;
    default_response = func_80019ABC(response_table, &scene_override_context, object, selection);
    response = default_response;
    if (func_80019A04(response_table, object, selection) != 0) {
        if (func_8001A510(*(s16 *)((s8 *)object + 0x18)) != 0) {

            response = &D_8001F543;
        } else {
            u8 *state_page;

            state_page = (u8 *)0x80020000;
            if (*(s32 *)(state_page - 0x4DF8) == 0) {

                *(s32 *)(state_page - 0x4DF8) = 1;
                response = &D_8001EF6C;
            } else {

                response = &D_8001EDD0;
            }
        }
    }
    return response;
}
