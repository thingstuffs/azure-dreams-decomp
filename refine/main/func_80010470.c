#include "common.h"
#include "m2c_compat.h"

typedef struct S_80023470_0 {
    u8 pad_00[0x1A8];
    void * unk_1A8;
    u8 pad_1AC[0xC];
    void * unk_1B8;
    u8 pad_1BC[0xC];
    void * unk_1C8;
    u8 pad_1CC[0xC];
    void * unk_1D8;
} S_80023470_0;   /* var_a0 in func_80023470 */

typedef struct S_80023470_1 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_80023470_1;   /* ((S_80023470_0 *)var_a0)->unk_1C8 in func_80023470 */

typedef struct S_80023470_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023470_2;   /* ((S_80023470_0 *)var_a0)->unk_1A8 in func_80023470 */

typedef struct S_80023470_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023470_3;   /* ((S_80023470_0 *)var_a0)->unk_1B8 in func_80023470 */

typedef struct S_80023470_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023470_4;   /* ((S_80023470_0 *)var_a0)->unk_1D8 in func_80023470 */

typedef struct S_80023470_5 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x5];
    s16 unk_08;
} S_80023470_5;   /* ((S_80023470_1 *)(((S_80023470_0 *)var_a0)->unk_1C8))->unk_04 in func_80023470 */

typedef struct S_80023470_6 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023470_6;   /* ((S_80023470_2 *)(((S_80023470_0 *)var_a0)->unk_1A8))->unk_04 in func_80023470 */

typedef struct S_80023470_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023470_7;   /* ((S_80023470_3 *)(((S_80023470_0 *)var_a0)->unk_1B8))->unk_04 in func_80023470 */

typedef struct S_80023470_8 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023470_8;   /* ((S_80023470_4 *)(((S_80023470_0 *)var_a0)->unk_1D8))->unk_04 in func_80023470 */

/* Initialize three entries in each of the four object groups. */
void func_80023470(void *object) {
    s32 entry_index;
    void *entry_base;

    entry_base = object;
    entry_index = 0;
    do {
        ((S_80023470_5 *)(((S_80023470_1 *)(((S_80023470_0 *)entry_base)->unk_1C8))->unk_04))->unk_08 = 0x24;
        *((S_80023470_1 *)(((S_80023470_0 *)entry_base)->unk_1C8))->unk_04 = 0x68;
        ((S_80023470_5 *)(((S_80023470_1 *)(((S_80023470_0 *)entry_base)->unk_1C8))->unk_04))->unk_01 = 0x68;
        ((S_80023470_5 *)(((S_80023470_1 *)(((S_80023470_0 *)entry_base)->unk_1C8))->unk_04))->unk_02 = 0x60;
        ((S_80023470_6 *)(((S_80023470_2 *)(((S_80023470_0 *)entry_base)->unk_1A8))->unk_04))->unk_08 = 9;
        ((S_80023470_7 *)(((S_80023470_3 *)(((S_80023470_0 *)entry_base)->unk_1B8))->unk_04))->unk_08 = 0x42;
        entry_index += 1;
        ((S_80023470_8 *)(((S_80023470_4 *)(((S_80023470_0 *)entry_base)->unk_1D8))->unk_04))->unk_08 = 0x8F;
        entry_base += 4;
    } while (entry_index < 3);
}
