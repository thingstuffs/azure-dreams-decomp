#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void runtime_clear_value();                         /* extern */
void runtime_unlink_doubly_linked_node();                      /* extern */
void unlink_active_node();                      /* extern */
void func_80044A50();                      /* extern */

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
/* Removes every node from the controller's list and cleans up its owning object. */
void func_800350D4(void *controller)
{
    u8 *list_head = (u8 *)controller + 8;
    u8 *node = (u8 *)PPTR(U32AT(list_head, 0x08));

    while (node != list_head) {
        u8 *owner = (u8 *)PPTR(U32AT(node, 0x00));
        u8 *object;

        if (U32AT(owner, 0x00) != 0)
            runtime_clear_value(PPTR(U32AT(owner, 0x00)));
        runtime_unlink_doubly_linked_node(node);
        object = owner - 32;
        func_80044A50(object);
        unlink_active_node(object);
        node = (u8 *)PPTR(U32AT(list_head, 0x08));
    }
}
