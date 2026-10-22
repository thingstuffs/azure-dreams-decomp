#ifndef TOWN_SCENE_DISPATCH_TOWN_CALLBACK_FALLBACK_G00763_H
#define TOWN_SCENE_DISPATCH_TOWN_CALLBACK_FALLBACK_G00763_H
/* dispatch town callback fallback g00763. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00763 - CL:town/func_80774928. */

#include "common.h"
#include "shared/town_root.h"
#include "shared/record_ptrs.h"

typedef void (*Callback)(void);

typedef struct CallbackEntry {
    Callback callback;
    void *data;
} CallbackEntry;

typedef struct { u8 pad[0x40]; void *value; } Child;

typedef struct { u8 pad[0x1C]; Child *child; } State;

extern void *D_800174D8;
extern u8 D_80017404[], D_8001770A[];

/* Functions defined in this translation unit. */
void dispatch_town_callback_or_fallback(s32 value0, s32 value1);
void set_shared_buffer_pointers(s32 unused0, s32 unused1);

#endif
