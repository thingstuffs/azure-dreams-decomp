#ifndef SLUS_RUNTIME_DIRECTORY_H
#define SLUS_RUNTIME_DIRECTORY_H

#include "common.h"

/* Four resource keys paired with their load destinations; 0x20 bytes on PS1. */
typedef struct RuntimeResourceEntry {
    void *key;
    u8 *data;
} RuntimeResourceEntry;

typedef struct {
    RuntimeResourceEntry entries[4];
} GpTablePrefix;

extern s32 runtime_directory_entry_count;
extern GpTablePrefix runtime_resource_directory;
extern GpTablePrefix runtime_directory_defaults;
extern u8 runtime_dispatch_mode_alias[];
extern u8 runtime_single_resource_data[];

void bind_and_load_indexed_resource_record(void *data, s32 entry_index);

s32 find_runtime_table_key_index(void *key);
s32 find_or_load_runtime_resource_key(void *key);
void initialize_runtime_resource_directory(void);

#endif
