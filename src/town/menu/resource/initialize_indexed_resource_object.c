#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800A7E7C_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800A7E7C_0_pre;   /* the 0x10 bytes before arg0 in initialize_indexed_resource_object, addressed as arg0[-1] */


typedef struct S_800A7E7C_1 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_800A7E7C_1;   /* arg2 in initialize_indexed_resource_object */



void register_node_if_unregistered(void *block_data, void *registration_id);
extern s32 item_effect_descriptor;
extern void D_800A7EC0();

/* Initialize the object state from its byte value and set the context resource and callback. */
void initialize_indexed_resource_object(void *object, s32 unused, S_800A7E7C_1 *context) {
    ((S_800A7E7C_0_pre *)object)[-1].unk_00 = &D_800A7EC0;
    ((Rec_func_80094268_arg0 *)object)->unk_60 = (s32) ((Rec_func_80094268_arg0 *)object)->unk_96.as_u8;
    context->unk_08 = &item_effect_descriptor;
    register_node_if_unregistered(object, project_sprite_chain);
}
