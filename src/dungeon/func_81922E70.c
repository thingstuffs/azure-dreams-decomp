#include "modules/dungeon_ovl_7e6e1800.h"

s32 draw_linked_shaded_quads(void *state, void *position, void *appearance) {
    Row_81922E70_GapNode *node;
    for (;;) {
        project_and_queue_shaded_quad(state, position, appearance, 0);
        node = *(Row_81922E70_GapNode **)((u8 *)state - 8);
        state = (u8 *)node + 0x20;
        if (node == 0) break;
        position = node->position;
        appearance = node->appearance;
    }
    return 0;
}
