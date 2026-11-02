#ifndef FRONTEND_LIBCARD_CARD_CHOOSER_H
#define FRONTEND_LIBCARD_CARD_CHOOSER_H
#include "common.h"
/* Request, channel state and child-panel pointers used by every chooser kind
 * initialized through init_card_boot_request_object. */
typedef struct CardChooserPresence {
    s32 first;
    s32 second;
} CardChooserPresence;
typedef struct CardChooserBody {
    s32 mode;
    u8 pad_04[8];
    s32 selected_channel;
    u8 pad_10[4];
    void *request;
    CardChooserPresence card_presence;
    void *backdrop;
    void *choices;
    u8 pad_28[0xC];
    s32 unk_34;
    s32 wait_notice_state;
    s32 unk_3C;
    s32 unk_40;
} CardChooserBody;
#endif
