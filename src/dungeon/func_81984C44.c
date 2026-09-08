#include "common.h"

typedef struct S_81984C44_0 {
    u8 pad_00[0x14A8];
    void * unk_14A8;
} S_81984C44_0;   /* page0 in func_81984C44 */

typedef struct S_81984C44_1 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_81984C44_1;   /* entity in func_81984C44 */

typedef struct S_81984C44_2_pre {
    void * unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_81984C44_2_pre;   /* the 0x14 bytes before node in func_81984C44, addressed as node[-1] */

typedef struct S_81984C44_2 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_81984C44_2;   /* node in func_81984C44 */

typedef struct S_81984C44_3 {
    u8 pad_00[0x14A8];
    void * unk_14A8;
} S_81984C44_3;   /* page in func_81984C44 */

typedef struct S_81984C44_4 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_81984C44_4;   /* owner in func_81984C44 */



extern void func_8002652C(void) __attribute__((noreturn));
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2CB8(void *, void *);
extern s32 func_800A41F0(void *);
void *func_81984C44(void *arg0)
{
    void *node;
    u8 *page;
    register void *entity ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 limit;
    u8 *page0;
    s32 limit0;
    register void *next ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *tail_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s8 floor;
    S_81984C44_4 *owner;

    entity = arg0;
    page0 = (u8 *)0x80080000;
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(page0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    node = ((S_81984C44_0 *)page0)->unk_14A8;
    limit0 = 0x100;
    if (((S_81984C44_1 *)entity)->unk_26 < 0) {
        limit0 = 4;
    }
    next = ((S_81984C44_2 *)node)->unk_5C;
    node = (u8 *)next + 0x20;
    if (node != ((S_81984C44_0 *)page0)->unk_14A8) {
        page = page0;
        limit = limit0;
        do {
            if (((func_800A2CB8(((S_81984C44_3 *)page)->unk_14A8, node) << 16) != 0) &&
                ((func_800A41F0(node) << 16) != 0) &&
                !(((S_81984C44_2_pre *)node)[-1].unk_12 & 0x2000)) {
                floor = ((S_81984C44_1 *)entity)->unk_26;
                owner = ((S_81984C44_2_pre *)node)[-1].unk_00;
                if (floor >= 0) {
                    if (floor == owner->unk_26) {
                        tail_value = node;
                        ASM_KEEP(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                        func_8002652C();
                    }
                } else {
                    if (func_8009FD40(owner, entity) < limit) {
                        return node;
                    }
                }
            }
            next = ((S_81984C44_2 *)node)->unk_5C;
            node = (u8 *)next + 0x20;
        } while (node != ((S_81984C44_3 *)page)->unk_14A8);
    }
    return 0;
}

/* MECHANISM: Split pre-call page/limit in a0/a1 from held s1/s3; pin arg/node in s2/s0.
   A v0 next temp preserves non-destructive list updates; zero-arg noreturn triggers LEAD 18.
   A guarded v0 tail value fills word 43's branch delay; the residue is byte-exact. */
