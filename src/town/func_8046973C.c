#include "common.h"

extern void copy_callback_value_to_destination(s32, u32 *);
extern s32 D_80017AAC[];
extern s32 D_80017AB8[];
extern s32 D_80017AC4[];
extern s32 D_80017CA0[];

/* Apply three value tables to consecutive destinations and return their base. */
s32 build_three_value_block(void) {
    s32 *base_ptr = D_80017CA0;

    copy_callback_value_to_destination(base_ptr[0], D_80017AAC);
    copy_callback_value_to_destination(base_ptr[0] + 0x14, D_80017AB8);
    copy_callback_value_to_destination(base_ptr[0] + 0x28, D_80017AC4);
    return base_ptr[0];
}
