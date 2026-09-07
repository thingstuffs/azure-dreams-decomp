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

/* Update the active index and reset the previous entry's state and offsets. */
void func_800260C8(void *object, s16 new_index) {
    s16 old_index;
    s32 entry_index;
    s32 direction;
    S_800260C8_2 *entry_offsets;
    S_800260C8_3 *linked_state;
    S_800260C8_0 *index_state;
    void *entries;
    ResidentPage *resident_page;

    index_state = object + 0x20;
    old_index = index_state->unk_26;
    if (old_index != new_index) {
        entries = ((S_800260C8_1 *)object)->unk_20;
        if (entries != NULL) {
            ((S_800260C8_6 *)(((S_800260C8_4 *)(((old_index * 4) + entries)))->unk_0C))->unk_B6 = 4;
            resident_page = (ResidentPage *)0x80010000;
            entry_index = index_state->unk_26;
            entry_offsets = ((S_800260C8_7 *)(((S_800260C8_5 *)(((entry_index * 4) + ((S_800260C8_1 *)object)->unk_20)))->unk_0C))->unk_0C;
            direction = (resident_page->table[entry_index] + 2) & 7;
            entry_offsets->unk_24 = (s8) (D_8006CCD8[direction] + 1);
            entry_offsets->unk_25 = (s8) (D_8006CCE8[direction] + 1);
        }
        index_state->unk_26 = new_index;
        linked_state = ((S_800260C8_1 *)object)->unk_20;
        if (linked_state != NULL) {
            linked_state->unk_26 = new_index;
        }
    }
}
