#ifndef TOWN_OVL_6F48D0_H
#define TOWN_OVL_6F48D0_H
#include "common.h"
#include "shared/town_root.h"
#include "shared/record_ptrs.h"

typedef void (*Callback)(void);
typedef struct CallbackEntry {
    Callback callback;
    void *data;
} CallbackEntry;

s32 dispatch_town_callback_or_fallback(void);
void run_entry_callback_or_set_buffers(s32 value0, s32 value1);
void set_shared_buffer_pointers(s32 value0, s32 value1);
#endif
