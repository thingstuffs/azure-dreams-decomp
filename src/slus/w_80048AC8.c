#include "common.h"

/* Struct with a 16-bit flags field at offset 0x14, matching the sibling
 * func_80048374's Struct_80048374 layout. */
typedef struct {
    u8 pad[0x14];
    u16 unk14;
} S_80048AC8;

extern void func_800477F4(void *arg0);
extern void func_80048998(void *arg0, void *arg1);

/* Updates the entity, then handles flags 0x1220 with the context and clears bit 0x20 if any are set. */
void func_80048AC8(S_80048AC8 *entity, void *context)
{
    func_800477F4(entity);
    if (entity->unk14 & 0x1220) {
        func_80048998(entity, context);
        entity->unk14 &= 0xFFDF;
    }
}
