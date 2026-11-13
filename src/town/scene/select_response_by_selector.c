#include "common.h"
#include "town/scene.h"


#ifndef NULL
#define NULL 0
#endif

extern s32 get_current_nested_record_value(); /* Unprototyped: zero or one argument; retail reads no incoming argument. */
extern s32 D_8001A20C;
extern s32 D_8001A2E7;
extern s32 D_8001A348;
extern s32 D_8001A526;
extern s32 D_8001A5E8;
extern s32 D_8001A685;
extern s32 D_8001A8BC;
extern s32 D_8001A91D;


/* Selects a response table for four selectors, choosing alternate data for statuses -0x30 and -0x38. */
s32 *select_response_by_selector(s32 value, s32 unused, s32 selector) {
    s32 *result;
    s32 status;

    result = NULL;
    if (selector == 0x1B) {
        status = get_current_nested_record_value();
        if (status == -0x30 || (status = get_current_nested_record_value()) == -0x38) {
            result = &D_8001A91D;
        } else {
            result = &D_8001A8BC;
        }
    } else if (selector == 0x2C) {
        status = get_current_nested_record_value();
        if (status == -0x30 || (status = get_current_nested_record_value()) == -0x38) {
            result = &D_8001A2E7;
        } else {
            result = &D_8001A20C;
        }
    } else if (selector == 0x31) {
        status = get_current_nested_record_value();
        if (status == -0x30 || (status = get_current_nested_record_value()) == -0x38) {
            result = &D_8001A526;
        } else {
            result = &D_8001A348;
        }
    } else if (selector == 0x34) {
        status = get_current_nested_record_value();
        if (status == -0x30 || (status = get_current_nested_record_value()) == -0x38) {
            result = &D_8001A685;
        } else {
            result = &D_8001A5E8;
        }
    }
    return result;
}
