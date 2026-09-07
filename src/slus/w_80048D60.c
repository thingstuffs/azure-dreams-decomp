#include "common.h"

/* Struct accessed via a "sub-object" pointer (entity_base + 0x20 in sibling
 * functions func_8004ECAC/func_8004EDA8/func_800511B4): flags u16 lives at
 * sub-object offset -2 (== entity offset 0x1E), and a generic pointer field
 * (function-ptr in siblings, data-ptr here) lives at sub-object offset
 * -0x10 (== entity offset 0x10). */
typedef struct {
    void *field_00;        /* == a0 - 0x10 */
    unsigned char pad[0x0A];
    unsigned short flags;  /* == a0 - 0x2 */
} S_80048D60;

extern int D_800212DC[8]; /* hi/lo global; only its address is used here */
extern void func_8004B568(void *arg0);

void func_80048D60(void *arg0)
{
    S_80048D60 *base = (S_80048D60 *)((unsigned char *)arg0 - 0x10);

    if (base->flags & 0x2000) {
        base->flags &= 0xDFFF;
        base->field_00 = &D_800212DC;
        func_8004B568(arg0);
    }
}
