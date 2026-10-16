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

void dispatchTownCallbackOrFallback(s32 value0, s32 value1);
void func_80016128(s32 value0, s32 value1);
#endif
