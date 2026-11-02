#ifndef FRONTEND_LIBCARD_CARD_CHOOSER_H
#define FRONTEND_LIBCARD_CARD_CHOOSER_H
#include "common.h"
/* Common request prefix initialized for every card-chooser kind. Child
 * pointers and status fields beyond this prefix keep their separate views. */
typedef struct CardChooserBody {
    s32 mode;
    u8 pad_04[8];
    s32 selected_channel;
    u8 pad_10[4];
    void *request;
} CardChooserBody;
#endif
