#ifndef SLUS_KONAMI_RUNTIME_GP_COUNT_H
#define SLUS_KONAMI_RUNTIME_GP_COUNT_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"

#include "common.h"

typedef struct {
    void *field_0;
    void *field_4;
} Func8003C6F8Entry;

extern Func8003C6F8Entry D_8006B200[];
extern void *D_80081460;

extern void file_load_com(void *data);

/* Stores data in the selected entry, activates its pointers, and applies a mode-specific flag. */

void func_8003C6F8(void *data, s32 entry_index);

#endif
