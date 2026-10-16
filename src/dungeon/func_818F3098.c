#include "modules/dungeon_ovl_191284c.h"

s32 func_80024898(void *state, void *position, void *appearance) {
    Row_818F3098_GapNode *node;
    for (;;) {
        func_8002404C(state, position, appearance, *(s16 *)((u8 *)appearance + 6));
        node = *(Row_818F3098_GapNode **)((u8 *)state - 8);
        state = (u8 *)node + 0x20;
        if (node == 0) break;
        position = node->position;
        appearance = node->appearance;
    }
    return 0;
}
