#ifndef FRONTEND_CARD_SAVE_OPERATION_H
#define FRONTEND_CARD_SAVE_OPERATION_H
#include "common.h"
/* Devkit save-screen body shared by the input and operation callbacks. */
typedef struct CardSaveOperationBody {
    struct ObjectNodeHeader *background;
    struct CardDevSlotWindow *windows[5];
    struct ObjectNodeHeader *options;
    struct ObjectNodeHeader *information;
    struct ObjectNodeHeader *request;
    s32 window_index;
    s32 entry_index;
    s32 saved_entry_index;
    s32 repeat_ticks;
    void *completion_callback;
    s32 dialog_answer;
    s32 countdown;
    s32 state;
    s32 option_index;
    s32 slot_mode;
} CardSaveOperationBody;
#endif
