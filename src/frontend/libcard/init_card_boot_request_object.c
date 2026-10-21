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
typedef struct Node8002BB08 {
    struct Node8002BB08 *next; /* 0x00 */
    u8 pad4[0x10 - 0x4];
    void *field_10;            /* 0x10 */
    u8 pad14[0x1E - 0x14];
    u16 field_1E;              /* 0x1E */
    u8 pad20[0x28 - 0x20];
} Node8002BB08;

extern Node8002BB08 D_8002BB08;

/* ((u8 *)&D_80082E60): shared global state struct; only the flags byte at offset 0xF
 * is touched here. Size >8B forces %hi/%lo. */


/* Address-only use; size clears the small-data threshold. */

extern void card_boot_destroy_card_chooser(void *a0);

/* Create or reset the shared node and initialize its request and mode. */
Node8002BB08 *init_card_boot_request_object(s32 request, s32 mode) {
    Node8002BB08 *node = &D_8002BB08;
    void *node_data = (u8 *)node + 0x20;

    if (find_active_list_node(node) == 0) {
        node = initialize_scene_object_in_buffer(0, node, 25);
    } else {
        card_boot_destroy_card_chooser(node);
        node->field_1E &= 0x7FFF;
        bzero(node_data, 0x44);
    }
    runtime_dispatch_state.flags0F |= 0x80;
    func_80027A68(node_data, request, mode);
    node->field_10 = &D_80027A9C[0];
    return node;
}
