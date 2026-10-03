#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_81984BF0_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_81984BF0_0;   /* link in func_81984BF0 */

typedef struct S_81984BF0_1 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_81984BF0_1;   /* object in func_81984BF0 */


/* Clears flag 0x2000 on every object in the circular list. */
void func_81984BF0(void)
{
    void *link;
    void *object;
    void *head;
    s32 link_value;
    s32 next;

    link = D_800814A8;
    next = ((S_81984BF0_0 *)link)->unk_5C;
    link_value = (u32)link;
    next += 0x20;
    link = next;
    if (link == (void *)(u32)link_value) {
        return;
    }
    head = (void *)(u32)link_value;
    do {
        object = link - 0x20;
        next = ((S_81984BF0_1 *)object)->unk_1E;
        next &= 0xDFFF;
        ((S_81984BF0_1 *)object)->unk_1E = next;
        link_value = ((S_81984BF0_0 *)link)->unk_5C;
        link = (void *)(link_value + 0x20);
    } while (link != head);
}
