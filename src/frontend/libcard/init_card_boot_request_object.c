#include "shared/runtime_dispatch.h"
#include "common.h"
#include "engine/scene.h"
#include "frontend/libcard.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"

/* Linked-list node shape shared with find_active_list_node/mark_active_nodes_by_callback's Node/
 * S_80081498: next ptr @0x0, a pointer field @0x10, a 16-bit flags field
 * @0x1E. D_8002BB08 is accessed via %hi/%lo (not $gp), so declare it with
 * a size well past the -G8 small-data threshold. */
typedef CardChooser Node8002BB08;

extern Node8002BB08 D_8002BB08;

/* ((u8 *)&D_80082E60): shared global state struct; only the flags byte at offset 0xF
 * is touched here. Size >8B forces %hi/%lo. */


/* Address-only use; size clears the small-data threshold. */


/* Create or reset the shared node and initialize its request and mode. */
Node8002BB08 *init_card_boot_request_object(void *request, s32 mode) {
    Node8002BB08 *node = &D_8002BB08;
    void *node_data = (u8 *)node + 0x20;

    if (find_active_list_node(node) == 0) {
        node = initialize_scene_object_in_buffer(0, node, 25);
    } else {
        card_boot_destroy_card_chooser(node);
        node->header.flags &= 0x7FFF;
        bzero(node_data, 0x44);
    }
    runtime_dispatch_state.flags0F |= 0x80;
    card_boot_init_channel_record(node_data, request, mode);
    node->header.update_callback = &D_80027A9C[0];
    return node;
}
