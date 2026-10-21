#include "common.h"
#include "engine/resource.h"

typedef struct Entry {
    s32 word0;
    s32 word1;
} Entry;

extern Entry runtime_resource_directory[];

/* Moves the selected entry to the front, shifting preceding entries back one slot. */
void runtime_move_entry_to_front(s32 index)
{
    Entry selected;

    selected.word0 = runtime_resource_directory[index].word0;
    selected.word1 = runtime_resource_directory[index].word1;

    if (index > 0) {
        do {
            runtime_resource_directory[index].word0 = runtime_resource_directory[index - 1].word0;
            runtime_resource_directory[index].word1 = runtime_resource_directory[index - 1].word1;
            index--;
        } while (index > 0);
    }

    runtime_resource_directory[0].word0 = selected.word0;
    runtime_resource_directory[0].word1 = selected.word1;
}
