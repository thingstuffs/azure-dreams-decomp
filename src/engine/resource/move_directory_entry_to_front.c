#include "common.h"
#include "engine/resource.h"
#include "slus/runtime_directory.h"

typedef struct Entry {
    void *word0;
    void *word1;
} Entry;


/* Moves the selected entry to the front, shifting preceding entries back one slot. */
void move_directory_entry_to_front(s32 index)
{
    Entry selected;

    selected.word0 = runtime_resource_directory.entries[index].key;
    selected.word1 = runtime_resource_directory.entries[index].data;

    if (index > 0) {
        do {
            runtime_resource_directory.entries[index].key = runtime_resource_directory.entries[index - 1].key;
            runtime_resource_directory.entries[index].data = runtime_resource_directory.entries[index - 1].data;
            index--;
        } while (index > 0);
    }

    runtime_resource_directory.entries[0].key = selected.word0;
    runtime_resource_directory.entries[0].data = selected.word1;
}
