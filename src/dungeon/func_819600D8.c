#include "modules/dungeon_draw_chain.h"

typedef struct DrawChainNode {
    u8 pad_00[8];
    void *position;
    void *render;
} DrawChainNode;

typedef struct DrawChainRender {
    u8 pad_00[6];
    s16 depth;
} DrawChainRender;

struct S_8195FD40_1;
struct S_8195FD40_3;
extern void func_80025540(s32, struct S_8195FD40_1 *, struct S_8195FD40_3 *, s16);

/* Draw each payload in the linked object chain. The next header is stored
 * eight bytes before the current payload; each new payload starts at +0x20.
 */
s32 func_800258D8(void *payload, void *position, void *render)
{
    DrawChainNode *next;
    do {
        func_80025540((s32)payload, position, render, ((DrawChainRender *)render)->depth);
        next = *(DrawChainNode **)((u8 *)payload - 8);
        payload = (u8 *)next + 0x20;
        if (next == 0) break;
        position = next->position;
        render = next->render;
    } while (1);
    return 0;
}
