#ifndef SLUS_RUNTIME_DIRECTORY_H
#define SLUS_RUNTIME_DIRECTORY_H

#include "common.h"

/* Only the first 0x20 bytes are accessed by these functions. */
typedef struct {
    u32 value[8];
} GpTablePrefix;

extern s32 runtime_directory_entry_count;
extern GpTablePrefix runtime_resource_directory;
extern GpTablePrefix runtime_directory_defaults;
extern u8 runtime_dispatch_mode_alias[];
extern u8 D_80016000[];

extern void bind_and_load_indexed_resource_record(s32 key, s32 index);

s32 find_runtime_table_key_index(s32 key);
s32 find_or_load_runtime_resource_key(s32 key);
void initialize_runtime_resource_directory(void);

#endif
