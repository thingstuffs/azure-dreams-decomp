#include "common.h"

extern void copy_callback_value_to_destination(s32, s32 *);
extern s32 D_80017AAC[];
extern s32 D_80017AC4[];
extern s32 D_80017CE0[];

/* Process the stored value and its offset by 0x14, then return the stored value. */
s32 prepare_stored_value_pair(void) {
    s32 *stored_value = D_80017CE0;

    copy_callback_value_to_destination(stored_value[0], D_80017AAC);
    copy_callback_value_to_destination(stored_value[0] + 0x14, D_80017AC4);
    return stored_value[0];
}
