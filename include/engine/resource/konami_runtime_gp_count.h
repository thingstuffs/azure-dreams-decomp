#ifndef SLUS_KONAMI_RUNTIME_GP_COUNT_H
#define SLUS_KONAMI_RUNTIME_GP_COUNT_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"


typedef struct {
    void *field_0;
    void *field_4;
} Func8003C6F8Entry;

extern Func8003C6F8Entry runtime_resource_directory[];
extern void *runtime_resource_load_target;


/* Stores data in the selected entry, activates its pointers, and applies a mode-specific flag. */

void bind_and_load_indexed_resource_record(void *data, s32 entry_index);

#endif
