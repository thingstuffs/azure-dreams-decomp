#include "common.h"
#include "shared/object_node.h"

extern void func_80093D48(void *, s32, s32);

/* Initialize the global context record using its two stored values. */
void func_80093864(void) {
    ObjectNodeHeader *context = &D_80083498;
    func_80093D48((u8 *)context + 0x20,
                  ((s32)context->unk_08),
                  ((s32)context->unk_0C));
}
