#include "common.h"

typedef struct S_802EE3A0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_802EE3A0_2;   /* temp_v1 in func_802EE3A0 */

typedef struct S_802EE3A0_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_802EE3A0_3;   /* ((S_802EE3A0_2 *)temp_v1)->unk_04 in func_802EE3A0 */




typedef struct Local64 { s32 word; s8 byte; u8 pad[59]; } Local64;
typedef struct Local16 { u8 data[16]; } Local16;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_8003830C();
s32 func_80051B50();
s32 func_8007BF50();
s32 func_80402268();
void func_80405454();
void *memcpy(void *dst, const void *src, u32 n);
extern u8 D_804006C4[];
extern u8 D_804006EC[];
extern s32 D_80400714;
extern u8 D_8040071C[];

typedef struct S_802EE3A0_0 {
    u8 pad_00[0xB18];
    void * unk_B18;
} S_802EE3A0_0;   /* (base + var_v1) in func_802EE3A0 */

typedef struct S_802EE3A0_1 {
    s32 unk_00;
} S_802EE3A0_1;   /* temp_v1 in func_802EE3A0 */

/* Builds count-dependent text and sets its display position. */
void func_802EE3A0(s32 panel_addr) {
    s32 panel_base;
    s32 count;
    Local64 count_text;
    Local16 number_text;
    Local64 *count_text_ptr;
    Local16 *number_text_ptr;
    s32 line_index;
    s32 line_offset;
    s32 text_offset;
    S_802EE3A0_1 *text_entry;
    s32 prefix_word;
    s32 layout_gate;

    panel_base = panel_addr;
    count = func_80402268();
    if (count >= 3) goto build_count_text;
    func_80051B50(panel_base + 0x80, D_804006C4, 1);
    func_80405454(panel_base + 0x188, D_804006EC);
    goto check_layout;
build_count_text:
    memcpy(&count_text, &D_80400714, 5);
    number_text_ptr = &number_text;
    func_8003830C(count / 3, number_text_ptr);
    count_text_ptr = &count_text;
    func_8007BF50(count_text_ptr, number_text_ptr);
    func_8007BF50(count_text_ptr, D_8040071C);
    func_80051B50(panel_base + 0x80, count_text_ptr, 1);
position_text:
    line_index = 0;
    while (count < 3 ? line_index < 2 : line_index < 1) {
        line_offset = line_index * 4;
        text_entry = ((S_802EE3A0_0 *)((panel_base + line_offset)))->unk_B18;
        text_offset = (line_index * 0x108) + 0x80;
        text_entry->unk_00 = (s32) (panel_base + text_offset);
        ((S_802EE3A0_3 *)(((S_802EE3A0_2 *)text_entry)->unk_04))->unk_08 = 0xA9;
        ((S_802EE3A0_3 *)(((S_802EE3A0_2 *)text_entry)->unk_04))->unk_0A = (s16) ((line_index * 0x10) + 0x110);
        line_index += 1;
    }
    return;
check_layout:
    prefix_word = D_80400714;
    if (prefix_word != 0) layout_gate = 0;
    else if (prefix_word < 0) layout_gate = 0;
    else layout_gate = 0;
    if (layout_gate != 0) goto position_text;
    return;
}
