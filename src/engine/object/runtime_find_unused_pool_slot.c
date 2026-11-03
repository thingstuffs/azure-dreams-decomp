#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "slus/data.h"

/* --- port/hal accessor shims (mechanical, no HAL dependency) --- */
#define PVAL(p)     ((u32)(p))

/*
 * Returns the first unused slot in the twenty-entry pool, or NULL if full.
 *
 * port body: port/hal/resident_gap2.c:201
 */
void *runtime_find_unused_pool_slot(void)
{
    u8 *slot = runtime_object_pool;
    s32 slot_index;

    for (slot_index = 0; slot_index < 20; slot_index++, slot += 100) {
        if (*slot == 0)
            return slot;
    }
    return NULL;
}
