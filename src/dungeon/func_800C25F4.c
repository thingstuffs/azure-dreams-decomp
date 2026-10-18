#include "common.h"

typedef void (*Callback)(s16, s16, s16, s16);

typedef struct CallbackEntry {
    Callback callback;
    s16 stored_arg0;
    s16 stored_arg1;
    s16 stored_arg2;
    s16 stored_arg3;
} CallbackEntry;

extern CallbackEntry *D_800DF640[4];
extern u8 D_800DF64C[9];
extern void submit_indexed_entry_and_finalize(u32);

/* Runs the selected callback list (after submitting its CD entry) with each entry's stored arguments. */
void run_indexed_callback_list(s16 list_index) {
    CallbackEntry *entry;

    submit_indexed_entry_and_finalize(D_800DF64C[list_index]);
    entry = D_800DF640[list_index];
    while (entry->callback != 0) {
        entry->callback(entry->stored_arg0, entry->stored_arg1, entry->stored_arg2, entry->stored_arg3);
        entry++;
    }
}
