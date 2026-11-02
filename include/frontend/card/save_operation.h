#ifndef FRONTEND_CARD_SAVE_OPERATION_H
#define FRONTEND_CARD_SAVE_OPERATION_H
#include "common.h"
/* Fields read by the save-operation completion callback. */
typedef struct CardSaveOperationBody {
    u8 pad_00[0x28];
    s32 entry_index;
    s32 saved_entry_index;
    u8 pad_30[4];
    void *completion_callback;
    u8 pad_38[8];
    s32 state;
} CardSaveOperationBody;
#endif
