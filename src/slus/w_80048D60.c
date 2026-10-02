#include "common.h"

/* sub_obj is the "sub-object" pointer (entity_base + 0x20 in sibling functions
 * func_8004ECAC/func_8004EDA8/func_800511B4): a u16 flags word lives at sub_obj - 2
 * (entity offset 0x1E), and a generic pointer field (function-ptr in siblings,
 * data-ptr here) lives at sub_obj - 0x10 (entity offset 0x10). */

extern int D_800212DC[8]; /* hi/lo global; only its address is used here */
extern void func_8004B568(void);

/* Clear flag 0x2000, reset the data pointer, and update the flagged sub-object. */
void func_80048D60(void *sub_obj)
{
    unsigned char *base = (unsigned char *)sub_obj;

    if (*(unsigned short *)(base - 2) & 0x2000) {
        *(unsigned short *)(base - 2) &= 0xDFFF;
        *(void **)(base - 0x10) = &D_800212DC;
        func_8004B568();
    }
}
