#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80033C84();                         /* extern */
M2C_UNK func_80035090();                      /* extern */
M2C_UNK func_8003FFF0();                      /* extern */
M2C_UNK func_80044A50();                      /* extern */

/* --- port/hal accessor shims (mechanical, no HAL dependency) --- */
#define U8AT(b, o)  (*(u8  *)((u8 *)(b) + (o)))
#define S8AT(b, o)  (*(s8  *)((u8 *)(b) + (o)))
#define U16AT(b, o) (*(u16 *)((u8 *)(b) + (o)))
#define S16AT(b, o) (*(s16 *)((u8 *)(b) + (o)))
#define U32AT(b, o) (*(u32 *)((u8 *)(b) + (o)))
#define S32AT(b, o) (*(s32 *)((u8 *)(b) + (o)))
#define PPTR(v)     ((void *)(u32)(v))
#define PVAL(p)     ((u32)(p))

/* port body: port/hal/resident_gap2.c:353 */
void func_800350D4(void *ctl)
{
    u8 *head = (u8 *)ctl + 8;
    u8 *node = (u8 *)PPTR(U32AT(head, 0x08));

    while (node != head) {
        u8 *owner = (u8 *)PPTR(U32AT(node, 0x00));
        u8 *obj;

        if (U32AT(owner, 0x00) != 0) func_80033C84(PPTR(U32AT(owner, 0x00)));
        func_80035090(node);
        obj = owner - 32;
        func_80044A50(obj);
        func_8003FFF0(obj);
        node = (u8 *)PPTR(U32AT(head, 0x08));
    }
}
