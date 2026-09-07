#include "common.h"

/* Count consecutive entries in a pointer array whose target's byte field at
 * offset +1 equals the first entry's field value. */
typedef struct {
    unsigned char unk0;
    u8 unk1;
} S_8004AFE8;

s32 func_8004AFE8(S_8004AFE8 **arg0)
{
    s32 count;
    u8 val;
    S_8004AFE8 **p;

    p = arg0;
    val = (*p)->unk1;
    count = 0;
    if (p != 0) {
    loop_1:
        if ((*p)->unk1 == val) {
            p += 1;
            count += 1;
            if (p != 0) {
                goto loop_1;
            }
        }
    }
    return count;
}
