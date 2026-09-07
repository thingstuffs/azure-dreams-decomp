#include "common.h"

/* Struct with a 16-bit flags field at offset 0x14, matching the sibling
 * func_80048374's Struct_80048374 layout. */
typedef struct {
    u8 pad[0x14];
    u16 unk14;
} S_80048AC8;

extern void func_800477F4(void *arg0);
extern void func_80048998(void *arg0, void *arg1);

/* Runs func_800477F4 on the entity, and if certain flag bits (0x1220) are set
 * in its 0x14 flags field, forwards to func_80048998 and clears bit 0x20. */
void func_80048AC8(S_80048AC8 *a0, void *a1)
{
    func_800477F4(a0);
    if (a0->unk14 & 0x1220) {
        func_80048998(a0, a1);
        a0->unk14 &= 0xFFDF;
    }
}
