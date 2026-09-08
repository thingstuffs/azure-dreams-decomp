#include "common.h"
#include "m2c_compat.h"

typedef struct S_800249B4_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800249B4_3;   /* temp_v0 in func_800249B4 */

typedef struct S_800249B4_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800249B4_4;   /* ((S_800249B4_3 *)temp_v0)->unk_04 in func_800249B4 */




extern void *func_8004DA74(void *a0, u8 *a1, s32 a2);
extern u8 *D_800283EC[];

typedef struct S_800249B4_0 {
    u8 pad_00[0xB4C];
    void * unk_B4C;
} S_800249B4_0;   /* var_a1 in func_800249B4 */

typedef struct S_800249B4_1 {
    s32 unk_00;
    void * unk_04;
} S_800249B4_1;   /* temp_v0 in func_800249B4 */

typedef struct S_800249B4_2 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800249B4_2;   /* temp_v1 in func_800249B4 */

/* Initialize two resource buffers and assign them to vertically spaced entries. */
void func_800249B4(void *context) {
    s32 entry_index;
    s16 x;
    s16 y;
    s32 buffer_offset;
    void *buffer;
    S_800249B4_1 *entry;
    S_800249B4_2 *position;
    void *entry_cursor;

    func_8004DA74((u8 *)context + 0x84, D_800283EC[0], 1);
    func_8004DA74((u8 *)context + 0x204, D_800283EC[1], 1);
    entry_index = 0;
    x = 0xA9;
    y = 0x110;
    buffer_offset = 0x84;
    entry_cursor = context;
    do {
        buffer = (u8 *)context + buffer_offset;
        entry = ((S_800249B4_0 *)entry_cursor)->unk_B4C;
        buffer_offset += 0x180;
        position = entry->unk_04;
        entry_cursor = (u8 *)entry_cursor + 4;
        entry->unk_00 = buffer;
        position->unk_08 = x;
        entry_index += 1;
        ((S_800249B4_4 *)(((S_800249B4_3 *)entry)->unk_04))->unk_0A = y;
        y += 0x10;
    } while (entry_index < 2);
}
