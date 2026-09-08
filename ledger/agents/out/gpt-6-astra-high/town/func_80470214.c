#include "common.h"

extern s32 func_80017E98(void *, s32);
extern s32 func_80019A04(void *, void *, s32);
extern s32 func_80019ABC(void *, void *, void *, s32);
extern s32 func_8001A510(s16);

extern s32 D_8001A99C;
extern s32 D_8001B1F8;
extern s32 D_8001B208;
extern s8 D_8001B7AE;
extern s8 D_8001EDD0;
extern s8 D_8001EF6C;
extern s8 D_8001F543;

/* Selects a response using object flags and one-time interaction state. */
s32 func_80017214(void *object, s32 check_value, s32 selection)
{
    void *response_table;
    s32 default_response;
    s32 response;

    if (func_80017E98(object, check_value) != 0) {
        s32 fallback_page;

        fallback_page = (s32)0x80020000;
        ASM_KEEP(fallback_page);
        return fallback_page - 0x4852;
    }

    response_table = &D_8001A99C;
    default_response = func_80019ABC(response_table, &D_8001B1F8, object, selection);
    response = default_response;
    if (func_80019A04(response_table, object, selection) != 0) {
        if (func_8001A510(*(s16 *)((s8 *)object + 0x18)) != 0) {
            s32 flagged_page;

            flagged_page = (s32)0x80020000;
            ASM_KEEP(flagged_page);
            response = flagged_page - 0xABD;
        } else {
            u8 *state_page;

            state_page = (u8 *)0x80020000;
            ASM_KEEP(state_page);
            if (*(s32 *)(state_page - 0x4DF8) == 0) {
                s32 first_page;

                *(s32 *)(state_page - 0x4DF8) = 1;
                first_page = (s32)0x80020000;
                ASM_KEEP(first_page);
                response = first_page - 0x1094;
            } else {
                s32 repeat_page;

                repeat_page = (s32)0x80020000;
                ASM_KEEP(repeat_page);
                response = repeat_page - 0x1230;
            }
        }
    }
    return response;
}
