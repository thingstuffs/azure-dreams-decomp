#include "common.h"

extern s32 update_actor_hop_and_grow(void);
extern u8 D_80170F20;
extern u8 D_80173B98;

/* Selects object data from its variant flag when the condition is met. */
void select_variant_object_data(void *object)
{
    u8 *selected_data;

    if (update_actor_hop_and_grow() != 0) {
        if (*(u8 *)((u8 *)object + 0xA7) != 0) {
            selected_data = &D_80173B98;
        } else {
            selected_data = &D_80170F20;
        }
        *(u8 **)((u8 *)object + 0x8C) = selected_data;
    }
}
