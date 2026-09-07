#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK LoadImage();                      /* extern */

/* --- port/hal accessor shims (mechanical, no HAL dependency) --- */
#define U8AT(b, o)  (*(u8  *)((u8 *)(b) + (o)))
#define S8AT(b, o)  (*(s8  *)((u8 *)(b) + (o)))
#define U16AT(b, o) (*(u16 *)((u8 *)(b) + (o)))
#define S16AT(b, o) (*(s16 *)((u8 *)(b) + (o)))
#define U32AT(b, o) (*(u32 *)((u8 *)(b) + (o)))
#define S32AT(b, o) (*(s32 *)((u8 *)(b) + (o)))
#define PPTR(v)     ((void *)(u32)(v))
#define PVAL(p)     ((u32)(p))

/* port body: port/hal/resident_gap2.c:632 */
void func_8003ADF4(s16 x, s16 y, s16 w, s16 h, const void *data)
{
    s16 rect[4];

    rect[0] = x; rect[1] = y; rect[2] = w; rect[3] = h;
    LoadImage(rect, data);
}
