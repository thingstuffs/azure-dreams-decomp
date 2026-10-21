#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "slus/data.h"

/* --- port/hal accessor shims (mechanical, no HAL dependency) --- */
#define U8AT(b, o)  (*(u8  *)((u8 *)(b) + (o)))
#define S8AT(b, o)  (*(s8  *)((u8 *)(b) + (o)))
#define U16AT(b, o) (*(u16 *)((u8 *)(b) + (o)))
#define S16AT(b, o) (*(s16 *)((u8 *)(b) + (o)))
#define U32AT(b, o) (*(u32 *)((u8 *)(b) + (o)))
#define S32AT(b, o) (*(s32 *)((u8 *)(b) + (o)))
#define PPTR(v)     ((void *)(u32)(v))
#define PVAL(p)     ((u32)(p))

/* port body: port/hal/resident_gap2.c:201 */
/* Returns the first unused slot in the twenty-entry pool, or NULL if full. */
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
