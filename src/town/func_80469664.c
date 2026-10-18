#include "common.h"

typedef struct Entry {
    u32 value;
    s32 unused[2];
} Entry;

extern Entry D_8001791C[8];
extern s32 D_80017AAC[3];
extern s32 D_80017AB8[3];
extern s32 D_80017BD8[13];
extern void copy_callback_value_to_destination(void *, void *);

// Prepares and returns the shared buffer using the selected entry's value.
s32 *prepare_selected_entry_buffer(s32 entryIndex) {
    s32 *sharedBuffer = D_80017BD8;

    sharedBuffer[8] = D_8001791C[entryIndex].value;
    copy_callback_value_to_destination(sharedBuffer, D_80017AAC);
    copy_callback_value_to_destination(sharedBuffer + 5, D_80017AB8);
    return sharedBuffer;
}
