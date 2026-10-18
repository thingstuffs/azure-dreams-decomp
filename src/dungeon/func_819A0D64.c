#include "modules/dungeon_ovl_19c088c.h"

s32 draw_linked_effect_chain(void *state, void *position, void *appearance) {
    Row_819A0D64_GapNode *node;
    for (;;) {
        func_8002408C(state, position, appearance, 0);
        node = *(Row_819A0D64_GapNode **)((u8 *)state - 8);
        state = (u8 *)node + 0x20;
        if (node == 0) break;
        position = node->position;
        appearance = node->appearance;
    }
    return 0;
}
