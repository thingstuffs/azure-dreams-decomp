#include "common.h"

extern s32 update_actor_hop_and_grow(void);
extern u8 pulunpa_action_resume_address;
extern u8 pulunpa_advance_actor_state_and_dispatch_address;

/* Selects object data from its variant flag when the condition is met. */
void select_variant_object_data(void *object)
{
    u8 *selected_data;

    if (update_actor_hop_and_grow() != 0) {
        if (*(u8 *)((u8 *)object + 0xA7) != 0) {
            selected_data = &pulunpa_advance_actor_state_and_dispatch_address;
        } else {
            selected_data = &pulunpa_action_resume_address;
        }
        *(u8 **)((u8 *)object + 0x8C) = selected_data;
    }
}
