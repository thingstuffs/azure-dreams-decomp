#include "common.h"
#include "engine/effect.h"
#include "engine/menu.h"

typedef struct S_80050640 {
    void (*vtable)(void *a0, s32 a1, s32 a2, s32 a3);
    s32 unk4;
    s32 counter; /* 0x8 */
    u8 pad0C[0x58 - 0xC];
    u8 buf58[8]; /* passed to set_color_components_and_scaled_fields as a0 */
} S_80050640;

extern void set_color_components_and_scaled_fields(void *a0, s32 a1, s32 a2);
extern void advance_gauge_color_then_decay(void *a0, s32 a1, s32 a2, s32 a3);

/* Starts the ratio ramp using the current counter, advances it, and updates the object. */
void start_gauge_ramp(S_80050640 *obj)
{
    set_color_components_and_scaled_fields(&obj->buf58, obj->counter++, 3);

    obj->vtable = (void (*)(void *, s32, s32, s32))advance_gauge_color_then_decay;
    handle_object_input(obj);
}
