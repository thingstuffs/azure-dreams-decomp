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
/* Finds an eligible node by owner comparison, halting on a matching nonnegative floor. */
void *func_81984C44(void *source_entity)
{
    void *node;
    u8 *globals;
    s32 owner_limit;
    u8 *initial_globals;
    s32 initial_limit;
    void *next_link;
    register void *matched_node ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s8 entity_floor;
    S_81984C44_4 *owner;

    initial_globals = (u8 *)0x80080000;
    ASM_KEEP(initial_globals);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    node = ((S_81984C44_0 *)initial_globals)->unk_14A8;
    initial_limit = 0x100;
    if (((S_81984C44_1 *)source_entity)->unk_26 < 0) {
        initial_limit = 4;
    }
    next_link = ((S_81984C44_2 *)node)->unk_5C;
    node = (u8 *)next_link + 0x20;
    if (node != ((S_81984C44_0 *)initial_globals)->unk_14A8) {
        globals = initial_globals;
        owner_limit = initial_limit;
        do {
            void *next_link;
            if (((func_800A2CB8(((S_81984C44_3 *)globals)->unk_14A8, node) << 16) != 0) &&
                ((func_800A41F0(node) << 16) != 0) &&
                !(((S_81984C44_2_pre *)node)[-1].unk_12 & 0x2000)) {
                entity_floor = ((S_81984C44_1 *)source_entity)->unk_26;
                owner = ((S_81984C44_2_pre *)node)[-1].unk_00;
                if (entity_floor >= 0) {
                    if (entity_floor == owner->unk_26) {
                        matched_node = node;
                        ASM_KEEP(matched_node);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                        func_8002652C();
                    }
                } else {
                    if (func_8009FD40(owner, source_entity) < owner_limit) {
                        return node;
                    }
                }
            }
            next_link = ((S_81984C44_2 *)node)->unk_5C;
            node = (u8 *)next_link + 0x20;
        } while (node != ((S_81984C44_3 *)globals)->unk_14A8);
    }
    return 0;
}

/* MECHANISM: Split pre-call page/limit in a0/a1 from held s1/s3; pin arg/node in s2/s0.
   A v0 next temp preserves non-destructive list updates; zero-arg noreturn triggers LEAD 18.
   A guarded v0 tail value fills word 43's branch delay; the residue is byte-exact. */
