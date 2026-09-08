#include "common.h"

typedef struct Entry {
    s32 word0;
    s32 word1;
} Entry;

extern Entry D_8006B200[];

/* Moves the selected entry to the front, shifting preceding entries back one slot. */
void func_8003C67C(s32 index)
{
    Entry selected;

    selected.word0 = D_8006B200[index].word0;
    selected.word1 = D_8006B200[index].word1;

    if (index > 0) {
        do {
            s32 dest_offset = index * 8;
            Entry *source;
            Entry *destination;

            index--;
            source = (Entry *)((char *)D_8006B200 + index * 8);
            destination = (Entry *)((char *)D_8006B200 + dest_offset);
            destination->word0 = source->word0;
            destination->word1 = source->word1;
        } while (index > 0);
    }

    D_8006B200[0].word0 = selected.word0;
    D_8006B200[0].word1 = selected.word1;
}
