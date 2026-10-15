#include "common.h"
#include "shared/object_node.h"

/* The registered three-word callback traverses the registry's +0x18 link.
 * func_8004491C writes that link; func_800402F4 supplies payload and +8/+C. */
extern void func_800D07C8(s32, void *, void *, s16);

s32 func_800D0774(void *payload, void *position, void *render_state)
{
    ObjectNodeHeader *next;
    do {
        func_800D07C8((s32)payload, position, render_state, *(s16 *)((u8 *)render_state + 6));
        next = ((ObjectNodeHeader *)((u8 *)payload - 0x20))->chain_next;
        if (next == 0) break;
        payload = (u8 *)next + 0x20;
        position = next->unk_08;
        render_state = next->unk_0C;
    } while (1);
    return 0;
}
