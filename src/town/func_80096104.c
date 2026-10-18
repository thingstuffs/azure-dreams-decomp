#include "common.h"
#include "shared/object_node.h"

extern void initialize_scene_action_record(void *, s32, s32);

/* Initialize the global context record using its two stored values. */
void initialize_town_context_action(void) {
    ObjectNodeHeader *context = &D_80083498;
    initialize_scene_action_record((u8 *)context + 0x20,
                  ((s32)context->unk_08),
                  ((s32)context->unk_0C));
}
