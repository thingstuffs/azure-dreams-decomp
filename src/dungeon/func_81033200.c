#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80174A00_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174A00_0_pre;   /* the 0x14 bytes before arg0 in func_80174A00, addressed as arg0[-1] */

typedef struct S_80174A00_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x48];
    s32 unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
} S_80174A00_0;   /* arg0 in func_80174A00 */

typedef struct S_80174A00_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80174A00_1;   /* data in func_80174A00 */



/* Finds the first entry matching both keys, the value range, and the type filter. */
void *func_80174A00(void *node, u16 key_a, u16 key_b, s16 range_center) {
    void *head = node;

    node = (void *)(((S_80174A00_0 *)node)->unk_5C + 0x20);
    while (node != head) {
        S_80174A00_1 *node_data = ((S_80174A00_0_pre *)node)[-1].unk_00;
        void *entry = node - 0x20;
        s16 node_value;

        if ((node_data->unk_24 == key_a) &&
            (node_data->unk_25 == key_b) &&
            (node_value = ((S_80174A00_0 *)node)->unk_88, node_value <= range_center + 0x20) &&
            (node_value >= range_center - 0x20) &&
            ((u32)(((S_80174A00_0 *)node)->unk_13 - 0x33) < 4)) {
            return entry;
        }
        node = (void *)(((S_80174A00_0 *)node)->unk_5C + 0x20);
    }
    return NULL;
}
