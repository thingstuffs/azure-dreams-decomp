#include "common.h"

#include "common.h"
#include "engine/resource.h"

typedef struct {
    u32 word0;
    u32 word1;
    u32 word2;
    u32 word3;
} CopyBlock;

extern CopyBlock map_runtime_state[3];
extern CopyBlock map_change_state[3];

/* Copies three blocks from map_change_state into map_runtime_state. */
void runtime_copy_three_global_blocks(void) {
    CopyBlock *destination = map_runtime_state;
    CopyBlock *source = map_change_state;
    CopyBlock *source_end = source + 3;

    do {
        *destination = *source;
        source++;
        destination++;
    } while (source != source_end);
}
