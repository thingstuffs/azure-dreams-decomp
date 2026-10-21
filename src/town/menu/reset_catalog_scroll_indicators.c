#include "common.h"

typedef struct {
    s32 unk00[12];
    s32 *unk30;
    s32 *unk34;
    s32 unk38[12];
    s32 *unk68;
    s32 *unk6C;
} State;

extern State catalog_display_node_slots;

/* Reset the controller fields and clear four shared state values. */
void reset_catalog_scroll_indicators(void *controller) {
    State *state = &catalog_display_node_slots;

    *((u8 *)controller + 0xC) = 1;
    *((s16 *)((u8 *)controller + 8)) = 0;
    *((u8 *)controller + 0xE) = 0;
    *state->unk30 = 0;
    *state->unk34 = 0;
    *state->unk68 = 0;
    *state->unk6C = 0;
}
