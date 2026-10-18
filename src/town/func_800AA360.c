#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_800A7AC0_0 {
    M2C_UNK * unk_00;
} S_800A7AC0_0;   /* arg0 in initialize_effect_object; pointer addresses record offset 0x10 */


M2C_UNK func_80033CD8();           /* extern */
void clear_object_status_and_dispatch_target(); /* extern */
extern M2C_UNK D_800A7B14;
extern M2C_UNK D_800F838C;

/* Initialize the object with its state, resource data, and callback. */
void initialize_effect_object(void *object, M2C_UNK unused, M2C_UNK context) {
    ((S_800A7AC0_0 *)((u8 *)object - 0x10))->unk_00 = &D_800A7B14;
    clear_object_status_and_dispatch_target(object, context, &D_800F838C, 0);
    func_80033CD8(object, func_80045340);
}
