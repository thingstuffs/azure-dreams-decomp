#include "common.h"
#include "m2c_compat.h"

typedef struct S_800260C8_4 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800260C8_4;   /* ((temp_a0 * 4) + temp_v1) in func_800260C8 */

typedef struct S_800260C8_5 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800260C8_5;   /* ((temp_v0 * 4) + ((S_800260C8_1 *)arg0)->unk_20) in func_800260C8 */

typedef struct S_800260C8_6 {
    u8 pad_00[0xB6];
    s16 unk_B6;
} S_800260C8_6;   /* ((S_800260C8_4 *)(((temp_a0 * 4) + temp_v1)))->unk_0C in func_800260C8 */

typedef struct S_800260C8_7 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800260C8_7;   /* ((S_800260C8_5 *)(((temp_v0 * 4) + ((S_800260C8_1 *)arg0)->unk_20)))->unk_0C in func_800260C8 */




typedef struct ResidentPage {
    u8 pad0[0x2094];
    u16 table[1];
} ResidentPage;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

typedef struct S_800260C8_0 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_800260C8_0;   /* temp_a2 in func_800260C8 */

typedef struct S_800260C8_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800260C8_1;   /* arg0 in func_800260C8 */

typedef struct S_800260C8_2 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
} S_800260C8_2;   /* temp_a0_2 in func_800260C8 */

typedef struct S_800260C8_3 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_800260C8_3;   /* temp_a0_3 in func_800260C8 */

void func_800260C8(void *arg0, s16 arg1) {
    s16 temp_a0;
    s32 temp_v0;
    s32 temp_v1_2;
    S_800260C8_2 *temp_a0_2;
    S_800260C8_3 *temp_a0_3;
    S_800260C8_0 *temp_a2;
    void *temp_v1;
    ResidentPage *temp_page;

    temp_a2 = arg0 + 0x20;
    temp_a0 = temp_a2->unk_26;
    if (temp_a0 != arg1) {
        temp_v1 = ((S_800260C8_1 *)arg0)->unk_20;
        if (temp_v1 != NULL) {
            ((S_800260C8_6 *)(((S_800260C8_4 *)(((temp_a0 * 4) + temp_v1)))->unk_0C))->unk_B6 = 4;
            temp_page = (ResidentPage *)0x80010000;
            temp_v0 = temp_a2->unk_26;
            temp_a0_2 = ((S_800260C8_7 *)(((S_800260C8_5 *)(((temp_v0 * 4) + ((S_800260C8_1 *)arg0)->unk_20)))->unk_0C))->unk_0C;
            temp_v1_2 = (temp_page->table[temp_v0] + 2) & 7;
            temp_a0_2->unk_24 = (s8) (D_8006CCD8[temp_v1_2] + 1);
            temp_a0_2->unk_25 = (s8) (D_8006CCE8[temp_v1_2] + 1);
        }
        temp_a2->unk_26 = arg1;
        temp_a0_3 = ((S_800260C8_1 *)arg0)->unk_20;
        if (temp_a0_3 != NULL) {
            temp_a0_3->unk_26 = arg1;
        }
    }
}
