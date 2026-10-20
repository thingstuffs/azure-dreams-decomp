#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"

typedef struct S_800A7C98_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800A7C98_0_pre;   /* the 0x10 bytes before arg0 in initialize_resource_object, addressed as arg0[-1] */

typedef struct S_800A7C98_0 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800A7C98_0;   /* arg0 in initialize_resource_object */



extern void register_node_if_unregistered();
extern void clear_object_status_and_dispatch_target();
void handle_object_bounds_and_cleanup(void *object, void *check_data, void *fallback_data);
extern M2C_UNK D_800F8F68;

/* Clear the object state field and initialize its resource data and callback. */
void initialize_resource_object(void *object, s32 unused, s32 context) {
    ((S_800A7C98_0_pre *)object)[-1].unk_00 = &handle_object_bounds_and_cleanup;
    ((S_800A7C98_0 *)object)->unk_50 = 0;
    clear_object_status_and_dispatch_target(object, context, &D_800F8F68, 0);
    register_node_if_unregistered(object, project_sprite_chain);
}
