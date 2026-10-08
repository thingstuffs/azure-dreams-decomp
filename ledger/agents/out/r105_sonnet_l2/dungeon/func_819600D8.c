#include "modules/dungeon_draw_chain.h"

/* Object-list node header (0x20 bytes) that precedes each payload. */
typedef struct DrawChainNode {
    u8 pad_00[8];
    void *position;
    void *render;
    u8 pad_10[8];
    struct DrawChainNode *next; /* header of the next object in the chain */
    u8 pad_1C[4];
} DrawChainNode;

typedef struct DrawChainRender {
    u8 pad_00[6];
    s16 depth;
} DrawChainRender;

struct S_8195FD40_1;
struct S_8195FD40_3;
extern void func_80025540(s32, struct S_8195FD40_1 *, struct S_8195FD40_3 *, s16);

/* Draw each payload in the linked object chain: the payload follows its node
 * header, and the header's link leads to the next object's header.
 */
s32 func_800258D8(void *payload, void *position, void *render)
{
    DrawChainNode *next;
    while (1) {
        func_80025540((s32)payload, position, render, ((DrawChainRender *)render)->depth);
        next = ((DrawChainNode *)payload - 1)->next;
        if (next == 0) return 0;
        payload = next + 1;
        position = next->position;
        render = next->render;
    }
}
