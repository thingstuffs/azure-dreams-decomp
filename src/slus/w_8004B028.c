#include "common.h"

/* Struct shared with func_8004AFE8 sibling: byte field unk0 (index) and
 * unk1 (match key). */
typedef struct {
    u8 unk0;
    u8 unk1;
} S_8004AFE8;

/* For each non-null pointer entry in arg1 (until a NULL terminator), if the
 * entry's unk1 field equals arg2, mark arg0[entry->unk0] with the
 * (1-based) loop index if it hasn't already been marked. */
void func_8004B028(u8 *arg0, S_8004AFE8 **arg1, s32 arg2)
{
    s32 i;
    S_8004AFE8 *p;

    i = 0;
    while (*arg1 != 0) {
        p = *arg1;
        if (p->unk1 == arg2) {
            u8 *slot = &arg0[p->unk0];
            if (*slot == 0) {
                *slot = i + 1;
            }
        }
        arg1++;
        i++;
    }
}
