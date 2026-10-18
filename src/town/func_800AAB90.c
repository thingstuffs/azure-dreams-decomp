#include "common.h"
#include "m2c_compat.h"

extern void func_80033CD8();
extern void func_80045340();
void finalize_object_or_select_town_record(void *object, void *check_context, void *record_holder);
extern s32 D_800D0E44;
extern M2C_UNK D_800F8A70;

/* Initialize the object state, shared counter, context resource, and callback. */
void initialize_timed_resource_object(void *object, s32 unused, void *context) {
    void *resource_base;

    *(s32 **) ((s8 *) object - 0x10) = &finalize_object_or_select_town_record;
    D_800D0E44 = 0x14;
    resource_base = &D_800F8A70;
    *(void **) ((s8 *) context + 8) = (void *) ((s8 *) resource_base + 0xF0);
    func_80033CD8(object, func_80045340);
}
