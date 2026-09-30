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
            D_8006B200[index].word0 = D_8006B200[index - 1].word0;
            D_8006B200[index].word1 = D_8006B200[index - 1].word1;
            index--;
        } while (index > 0);
    }

    D_8006B200[0].word0 = selected.word0;
    D_8006B200[0].word1 = selected.word1;
}
