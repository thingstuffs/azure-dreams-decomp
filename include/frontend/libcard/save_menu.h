#ifndef FRONTEND_LIBCARD_SAVE_MENU_H
#define FRONTEND_LIBCARD_SAVE_MENU_H

#include "common.h"

/* Observed save-menu body prefix. The callback itself belongs to the
 * ObjectNodeHeader preceding this body, not to any of these members. */
typedef struct CardSaveMenuBody {
    void *backdrop;
    void *surface;
    void *heading;
    void *slots[5];
    void *request;
    s32 mode;
    s32 state;
    s32 selection;
    s32 repeat_ticks;
    void *saved_callback;
    u8 pad_38[4];
    s32 countdown;
    s32 unk_40;
} CardSaveMenuBody;

/* Common saved-callback projection for generic card-menu restoration.
 * Only this field is shared; the rest of each body keeps its own type. */
typedef struct CardMenuCallbackPrefix {
    u8 pad_00[0x34];
    void *saved_callback;
} CardMenuCallbackPrefix;

#endif
