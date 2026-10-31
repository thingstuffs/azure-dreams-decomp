#include "common.h"
#include "shared/transition_slots.h"
#include "shared/object_flags.h"

#include "common.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "slus.h"
extern s8 node_update_mode;
#define D_80080A86_store (*(s8 *)0x80080A86)
extern s32 D_800814A0_load[3];
#define D_800814A0_store (*(s32 *)0x800814A0)
typedef struct S_80043FD0_Node
{
    struct S_80043FD0_Node *next;
    u8 pad[0x1E - 4];
    u16 field_1E;
}
S_80043FD0_Node;
/* Advances the controller state and updates node and global status flags. */
void update_deferred_resource_transition_task(ScheduleDeferredResourceTransitionBody *controller)
{
    s16 state = controller->state;
    S_80043FD0_Node *node;
    s32 global_flags;
    if (state == 2) {
        if ((*((u8 *) controller->resource)) != 0) {
            s16 slot_arg = controller->slot_argument;
            if (slot_arg != 0) {
                controller->slot_index = reserve_runtime_slot(5, slot_arg);
            }
            clear_flags_on_resource_list();
            D_80080A86_store = 0;
            controller->state = 0;
        }
        return;
    }
    if (runtime_transition_slots[controller->slot_index].type != 0) {
        return;
    }
    if (state != 0) {
        node = controller->load_or_dispatch(controller->resource);
        if (node == 0) {
            runtime_transition_slots[controller->slot_index].type = 6;
            runtime_transition_slots[controller->slot_index].unk_2 = 1;
            runtime_transition_slots[controller->slot_index].param = 1;
            runtime_transition_slots[controller->slot_index].unk_6 = 0;
            return;
        }
        mark_resource_list_flags_ten_and_eleven();
        D_80080A86_store = (state = 1);
        node->field_1E &= 0xF3FF;
    }
    *((u16 *) (((char *) controller) - 2)) |= 0x8000;
    global_flags = D_800814A0_load[0];
    global_flags |= 0x8000;

    D_800814A0_store = global_flags;
}
