#include "common.h"
#include "town/scene.h"
#include "town/shop.h"

extern s32 D_80018810;
extern s32 *D_800189D8[];

/* Calls select_town_byte_array and sets the first pointer slot to D_80018810. */
void bind_selected_runtime_pointer(void) {
    select_town_byte_array();
    D_800189D8[0] = &D_80018810;
}
