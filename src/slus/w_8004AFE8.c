#include "common.h"

typedef struct {
    unsigned char unk0;
    u8 unk1;
} S_8004AFE8;

/* Counts consecutive pointer entries whose target byte matches the first target byte. */
s32 func_8004AFE8(S_8004AFE8 **entries)
{
    s32 count;
    u8 first_value;
    S_8004AFE8 **entry;

    entry = entries;
    first_value = (*entry)->unk1;
    count = 0;
    if (entry != 0) {
    loop_1:
        if ((*entry)->unk1 == first_value) {
            entry += 1;
            count += 1;
            if (entry != 0) {
                goto loop_1;
            }
        }
    }
    return count;
}
