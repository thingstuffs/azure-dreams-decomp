#include "town/player/state.h"
#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"

struct S_8046C8C4_1;


typedef struct S_8046C8C4_0 {
    u8 pad_00[0x10];
    struct S_8046C8C4_1 *unk_10;
} S_8046C8C4_0;   /* arg0 in pass_indexed_entry */

typedef struct S_8046C8C4_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[2];
} S_8046C8C4_1;

/* Set the script flag named by the indexed entry's identifier. */
void pass_indexed_entry(S_8046C8C4_0 *table, s32 entry_index) {
    S_8046C8C4_1 *entry;

    entry = (S_8046C8C4_1 *)(entry_index * 0x10 + (unsigned long)table->unk_10);
    set_script_flag_bit(entry->unk_0C);
}
