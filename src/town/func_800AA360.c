#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_800A7AC0_0 {
    s32 * unk_00;
} S_800A7AC0_0;   /* arg0 in initialize_effect_object; pointer addresses record offset 0x10 */
void func_80033CD8(void *block_data, s32 registration_id);           /* extern */
void clear_object_status_and_dispatch_target(); /* extern */
void finalize_checked_object_or_fallback(void *object, void *check_data, void *fallback_data);
extern M2C_UNK D_800F838C;

/* Initialize the object with its state, resource data, and callback. */
void initialize_effect_object(void *object, s32 unused, s32 context) {
    ((S_800A7AC0_0 *)((u8 *)object - 0x10))->unk_00 = &finalize_checked_object_or_fallback;
    clear_object_status_and_dispatch_target(object, context, &D_800F838C, 0);
    func_80033CD8(object, func_80045340);
}
