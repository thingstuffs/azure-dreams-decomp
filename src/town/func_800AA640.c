/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/slus_callbacks.h"



typedef struct S_800A7C98_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800A7C98_0_pre;   

typedef struct S_800A7C98_0 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800A7C98_0;   


void register_node_if_unregistered(void *, s32);
#include "town/system/clear_object_status_and_dispatch_target_api.h"
extern s32 D_800A7DF8;
extern s32 D_800F8F98;

void func_800A7DA0(void *object, s32 unused, s32 context) {
    ((S_800A7C98_0_pre *)object)[-1].unk_00 = &D_800A7DF8;
    ((S_800A7C98_0 *)object)->unk_50 = 0;
    clear_object_status_and_dispatch_target(object, context, (int)(&D_800F8F98), 0);
    register_node_if_unregistered(object, (s32)(project_sprite_chain));
}
