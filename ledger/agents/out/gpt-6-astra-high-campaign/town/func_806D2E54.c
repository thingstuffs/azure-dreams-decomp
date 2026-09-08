#include "common.h"

extern s32 func_80016D78(s16);

/* Check whether every flag in the zero-terminated list is set. */
s32 func_80016654(s16 *flag_ids) {
    s16 *flag_id = flag_ids;

    while (*flag_id != 0) {
        if (func_80016D78(*(u16 *)flag_id) == 0) {
            break;
        }
        flag_id++;
    }

    return *flag_id == 0;
}
