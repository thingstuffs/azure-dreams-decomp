#include "common.h"

#include "common.h"

typedef struct {
    u32 word0;
    u32 word1;
    u32 word2;
    u32 word3;
} CopyBlock;

extern CopyBlock D_8006ADBC[3];
extern CopyBlock map_change_state[3];

/* Copy three blocks from D_8006ADEC to D_8006ADBC. */
void runtime_copy_three_global_blocks(void) {
    CopyBlock *destination = D_8006ADBC;
    CopyBlock *source = map_change_state;
    CopyBlock *source_end = source + 3;

    do {
        *destination = *source;
        source++;
        destination++;
    } while (source != source_end);
}
