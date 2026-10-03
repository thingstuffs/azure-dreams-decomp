#include "common.h"
extern void *D_800814A8;

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

typedef struct S_81984C44_4 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_81984C44_4;   /* owner in func_81984C44 */


extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2CB8(void *, void *);
extern s32 func_800A41F0(void *);
/* Finds an eligible node by owner comparison, halting on a matching nonnegative floor. */
void *func_81984C44(void *source_entity)
{
    void *node;
    s16 owner_limit;
    s32 initial_limit;
    void *next_link;
    s8 entity_floor;
    S_81984C44_4 *owner;

    node = D_800814A8;
    initial_limit = 0x100;
    if (((S_81984C44_1 *)source_entity)->unk_26 < 0) {
        initial_limit = 4;
    }
    next_link = ((S_81984C44_2 *)node)->unk_5C;
    node = (u8 *)next_link + 0x20;
    if (node != D_800814A8) {
        do {
            void *next_link;
            if (((func_800A2CB8(D_800814A8, node) << 16) != 0) &&
                ((func_800A41F0(node) << 16) != 0) &&
                !(((S_81984C44_2_pre *)node)[-1].unk_12 & 0x2000)) {
                entity_floor = ((S_81984C44_1 *)source_entity)->unk_26;
                owner = ((S_81984C44_2_pre *)node)[-1].unk_00;
                if (entity_floor >= 0) {
                    if (entity_floor == owner->unk_26) {
                        return node;
                    }
                } else {
                    owner_limit = initial_limit;
                    if (func_8009FD40(owner, source_entity) < owner_limit) {
                        return node;
                    }
                }
            }
            next_link = ((S_81984C44_2 *)node)->unk_5C;
            node = (u8 *)next_link + 0x20;
        } while (node != D_800814A8);
    }
    return 0;
}
