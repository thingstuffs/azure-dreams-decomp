#include "common.h"
#include "shared/object_node.h"

/* The registered three-word callback traverses the registry's +0x18 link.
 * func_8004491C writes that link; dispatch_registered_draw_callbacks supplies payload and +8/+C. */
extern void project_depth_sliced_quads(void *, void *, void *, s16);

s32 draw_linked_depth_sliced_quads(void *payload, void *position, void *render_state)
{
    ObjectNodeHeader *next;
    do {
        project_depth_sliced_quads(payload, position, render_state, 0);
        next = ((ObjectNodeHeader *)((u8 *)payload - 0x20))->chain_next;
        if (next == 0) break;
        payload = (u8 *)next + 0x20;
        position = next->unk_08;
        render_state = next->unk_0C;
    } while (1);
    return 0;
}
