#include "common.h"

extern void *D_800814A8;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_81984BF0(void)
{
    register void *link ASM_REG("$4");
    register void *object ASM_REG("$2");
    register void *head ASM_REG("$5");
    register s32 next ASM_REG("$3");

    link = D_800814A8;
    ASM_KEEP(link);
    next = FIELD(link, s32, 0x5C);
    ASM_KEEP(next);
    object = link;
    ASM_KEEP(object);
    link = next + 0x20;
    ASM_KEEP(link);
    if (link == object) {
        return;
    }
    head = object;
    ASM_KEEP(head);
    object = link - 0x20;
    do {
        FIELD(object, u16, 0x1E) = FIELD(object, u16, 0x1E) & 0xDFFF;
        object = FIELD(link, s32, 0x5C);
        link = object + 0x20;
        ASM_KEEP(link);
        object = link - 0x20;
    } while (link != head);
}

/* MECHANISM: Frameless leaf with cursor/head/object held in $a0/$a1/$v0.
   Keeping the cursor breaks CSE so both object = cursor - 0x20 addiu sites survive.
   Keeping the $v1 next-link immediately after its load yields retail's load-delay move order. */
