#include "common.h"

typedef struct S_8009A180_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    union { s32 s; void * u; } unk_5C;   /* accessed as both */
} S_8009A180_0;   /* arg1 in func_8009A180 */

typedef struct S_8009A180_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x38];
    void * unk_58;
    s32 unk_5C;
} S_8009A180_1;   /* arg0 in func_8009A180 */

typedef struct S_8009A180_2 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8009A180_2;   /* node in func_8009A180 */


extern void func_8009A028(void *arg0);
extern void func_8009A204(void) __attribute__((noreturn));


s32 func_8009A180(void *arg0, S_8009A180_0 *arg1) {
    register u32 carrier ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 result ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 flags;
    s32 link;
    S_8009A180_2 *node;
    u32 mask;

    if (arg0 == arg1) {
        result = 0;
        flags = arg1->unk_1C;
        ASM_KEEP(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        carrier = 0x80000000;
        arg1->unk_1C = flags | carrier;
        func_8009A204();
    }

    mask = 0x80000000;
    result = ((S_8009A180_1 *)arg0)->unk_1C;
    if (result >= 0) {
        result |= mask;
        ((S_8009A180_1 *)arg0)->unk_1C = result;
        carrier = (u32)arg0;
        func_8009A028((void *)carrier);

        link = arg1->unk_5C.s;
        ((S_8009A180_1 *)arg0)->unk_5C = link;
        ASM_KEEP(link);   /* MATCH pin: load-bearing for the whole function shape */
        node = (void *)(link + 0x20);
        ASM_KEEP(node);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        carrier = (u32)node->unk_58;
        ASM_KEEP(carrier);   /* MATCH pin: retail basic-block layout depends on it */
        result = 1;
        ASM_KEEP(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_8009A180_1 *)arg0)->unk_58 = (void *)carrier;
        carrier = (u32)((u8 *)arg0 - 0x20);
        node->unk_58 = (void *)carrier;
        arg1->unk_5C.u = (void *)carrier;
        func_8009A204();
    }

    return 0;
}
