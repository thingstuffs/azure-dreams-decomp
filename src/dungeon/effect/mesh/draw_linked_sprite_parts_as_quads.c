#include "common.h"
#include "shared/object_node.h"

/* The registered three-word callback traverses the registry's +0x18 link.
 * register_node writes that link; dispatch_registered_draw_callbacks supplies payload and +8/+C. */
extern void transform_sprite_parts_to_quads(s32, void *, void *, s16);

s32 draw_linked_sprite_parts_as_quads(void *payload, void *position, void *render_state)
{
    ObjectNodeHeader *next;
    do {
        transform_sprite_parts_to_quads((s32)payload, position, render_state, *(s16 *)((u8 *)render_state + 6));
        next = ((ObjectNodeHeader *)((u8 *)payload - 0x20))->chain_next;
        if (next == 0) break;
        payload = (u8 *)next + 0x20;
        position = next->unk_08;
        render_state = next->unk_0C;
    } while (1);
    return 0;
}
