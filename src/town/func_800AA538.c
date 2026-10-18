#include "common.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_800A7C98_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A7C98_0_pre;   /* the 0x10 bytes before arg0 in initialize_resource_object, addressed as arg0[-1] */

typedef struct S_800A7C98_0 {
    u8 pad_00[0x50];
    M2C_UNK unk_50;
} S_800A7C98_0;   /* arg0 in initialize_resource_object */



extern void func_80033CD8();
extern void clear_object_status_and_dispatch_target();
extern M2C_UNK D_800A7DF8;
extern M2C_UNK D_800F8F68;

/* Clear the object state field and initialize its resource data and callback. */
void initialize_resource_object(void *object, M2C_UNK unused, M2C_UNK context) {
    ((S_800A7C98_0_pre *)object)[-1].unk_00 = &D_800A7DF8;
    ((S_800A7C98_0 *)object)->unk_50 = 0;
    clear_object_status_and_dispatch_target(object, context, &D_800F8F68, 0);
    func_80033CD8(object, func_80045340);
}
