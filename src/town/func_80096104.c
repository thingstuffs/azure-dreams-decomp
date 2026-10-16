#include "common.h"
#include "shared/object_node.h"

extern void townInitializeSceneActionRecord(void *, s32, s32);

/* Initialize the global context record using its two stored values. */
void townInitializeTownContextAction(void) {
    ObjectNodeHeader *context = &D_80083498;
    townInitializeSceneActionRecord((u8 *)context + 0x20,
                  ((s32)context->unk_08),
                  ((s32)context->unk_0C));
}
