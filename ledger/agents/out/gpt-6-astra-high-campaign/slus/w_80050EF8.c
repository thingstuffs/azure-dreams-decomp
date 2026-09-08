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

/* Lazily initializes and returns the result object, applying any pending value and registering a callback when ready. */
void *func_80050EF8(S_80050EF8 *object)
{
    S_80050EF8_sub *object_state = &object->sub;

    if (object_state->field28 != 0 || (object_state->field28 = func_8004FDE0(object_state->field20)) != 0) {
        if (object_state->field24 != 0) {
            object->field10 = object_state->field24;
            object_state->field24 = 0;
        }
        func_8004491C(object, (void *)func_8004CAA0);
    }
    return object_state->field28;
}
