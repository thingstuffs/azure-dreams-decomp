#ifndef FRONTEND_LIBCARD_CARD_CHOOSER_H
#define FRONTEND_LIBCARD_CARD_CHOOSER_H
#include "common.h"
#include "shared/object_node.h"
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
    struct ObjectNodeHeader *request;
    CardChooserPresence card_presence;
    struct ObjectNodeHeader *backdrop;
    struct ObjectNodeHeader *choices;
    u8 pad_28[4];
    void (*resume_input)(struct CardChooserBody *menu);
    s32 slot_status;
    s32 unk_34;
    s32 wait_notice_state;
    s32 format_answer;
    s32 format_countdown;
} CardChooserBody;

struct CardSlotScreenEffect {
    ObjectNodeHeader node;
    CardChooserBody body;
};
#endif
