#include "common.h"
#include "m2c_compat.h"

#include "common.h"

extern u8 D_800816C0[];

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
void *func_80033BE4(void)
{
    u8 *p = D_800816C0;
    s32 i;

    for (i = 0; i < 20; i++, p += 100) {
        if (*p == 0) return p;
    }
    return NULL;
}
