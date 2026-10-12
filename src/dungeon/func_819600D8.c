#include "modules/dungeon_ovl_197e800.h"
#include "modules/dungeon_draw_chain.h"

/* Object-list node header (0x20 bytes) that precedes each payload. */




struct S_8195FD40_1;
struct S_8195FD40_3;

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
