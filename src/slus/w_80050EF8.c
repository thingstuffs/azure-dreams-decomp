#include "common.h"

typedef struct S_80050EF8_sub {
    u8 pad00[0x20];  /* +0x00: unknown, used by other functions */
    void *field20;   /* +0x20: arg passed to func_8004FDE0 */
    s32 field24;     /* +0x24 */
    void *field28;   /* +0x28: result object pointer */
} S_80050EF8_sub;

typedef struct S_80050EF8 {
    u8 pad00[0x10];
    s32 field10;       /* +0x10 */
    u8 pad14[0xC];     /* +0x14 */
    S_80050EF8_sub sub; /* +0x20 */
} S_80050EF8;

extern void *func_8004FDE0(void *a0);
extern int func_8004CAA0(void *a0, int a1, void *a2);
extern void func_8004491C(void *a0, void *a1);

/* Lazily allocates/initializes the sub-object's result pointer via
 * func_8004FDE0 (using field20 as its input), storing the result into
 * field28. On success (or if already initialized), if field24 holds a
 * pending value, moves it into obj->field10 and registers a callback
 * (func_8004CAA0) via func_8004491C. Returns the (possibly still-NULL)
 * result pointer. */
void *func_80050EF8(S_80050EF8 *obj)
{
    S_80050EF8_sub *sub = &obj->sub;

    if (sub->field28 != 0 || (sub->field28 = func_8004FDE0(sub->field20)) != 0) {
        if (sub->field24 != 0) {
            obj->field10 = sub->field24;
            sub->field24 = 0;
        }
        func_8004491C(obj, (void *)func_8004CAA0);
    }
    return sub->field28;
}
