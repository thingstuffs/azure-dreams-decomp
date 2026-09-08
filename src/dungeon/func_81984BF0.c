#include "common.h"

typedef struct S_81984BF0_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_81984BF0_0;   /* link in func_81984BF0 */

typedef struct S_81984BF0_1 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_81984BF0_1;   /* object in func_81984BF0 */


extern void *D_800814A8;


/* Clears flag 0x2000 on every object in the circular list. */
void func_81984BF0(void)
{
    void *link;
    register void *object ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *head;
    s32 next;

    link = D_800814A8;
    next = ((S_81984BF0_0 *)link)->unk_5C;
    object = link;
    link = next + 0x20;
    ASM_KEEP(link);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (link == object) {
        return;
    }
    head = object;
    object = link - 0x20;
    do {
        ((S_81984BF0_1 *)object)->unk_1E = ((S_81984BF0_1 *)object)->unk_1E & 0xDFFF;
        object = ((S_81984BF0_0 *)link)->unk_5C;
        link = object + 0x20;
        ASM_KEEP(link);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        object = link - 0x20;
    } while (link != head);
}

/* MECHANISM: Frameless leaf with cursor/head/object held in $a0/$a1/$v0.
   Keeping the cursor breaks CSE so both object = cursor - 0x20 addiu sites survive.
   Keeping the $v1 next-link immediately after its load yields retail's load-delay move order. */
