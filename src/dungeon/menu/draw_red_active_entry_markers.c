#include "common.h"
#include "shared/record_ptrs.h"

extern void submit_activation_command(void);
extern void create_transformed_render_object(u8, u8, s32, s32, s32);


/* Create red markers at the owner positions of active list entries. */
void draw_red_active_entry_markers(s32 setup_arg_0, s32 setup_arg_1, s32 setup_arg_2, s32 setup_arg_3)
{
    u8 *node;
    u8 *owner;
    s32 marker_count;

    node = ((u8 *)dungeon_actor_ring_anchor);
    submit_activation_command();
    marker_count = 0;
    while ((node = *(u8 **)(node + 0x5C) + 0x20) != ((u8 *)dungeon_actor_ring_anchor)) {
        if (*(s8 *)(node + 0x13) > 0) {
            owner = *(u8 **)(node - 0x14);
            create_transformed_render_object(owner[0x24], owner[0x25], 0x202080, 4,
                          marker_count++);
        }
    }
}
