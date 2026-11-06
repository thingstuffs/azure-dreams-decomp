#ifndef FRONTEND_LIBCARD_FORMAT_OPERATION_H
#define FRONTEND_LIBCARD_FORMAT_OPERATION_H

#include "common.h"

/* card_boot_handle_format_answer installs the countdown callback on this body;
 * that callback installs card_boot_format_card_with_retry on the same node. */
typedef struct CardFormatOperationBody {
    u8 pad_00[0xC];
    s32 channel;
    u8 pad_10[0x1C];
    void *resume_callback;
    u8 pad_30[8];
    s32 notice_state;
    s32 answer;
    s32 countdown;
} CardFormatOperationBody;

#endif
