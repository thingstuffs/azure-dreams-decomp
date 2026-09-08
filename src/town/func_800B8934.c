#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6094_4 {
    u8 pad_00[0x38];
    void * unk_38;
} S_800B6094_4;   /* temp_v1 in func_800B6094 */

typedef struct S_800B6094_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6094_5;   /* ((S_800B6094_4 *)temp_v1)->unk_38 in func_800B6094 */

typedef struct S_800B6094_6 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800B6094_6;   /* ((S_800B6094_5 *)(((S_800B6094_4 *)temp_v1)->unk_38))->unk_04 in func_800B6094 */




s32 func_800439BC();
M2C_UNK func_800498EC();
s32 func_80049918();
s32 func_80049944();
M2C_UNK func_800B5264();
M2C_UNK func_800B53BC();
s32 func_800B6030();
extern u8 D_8006DE24[];

typedef struct S_800B6094_0 {
    u8 unk_00;
    u8 unk_01;
} S_800B6094_0;   /* held_arg0 in func_800B6094 */

typedef struct S_800B6094_1 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x8];
    s32 unk_2C;
    u8 pad_30[0x8];
    s32 * unk_38;
} S_800B6094_1;   /* temp_s1 in func_800B6094 */

typedef struct S_800B6094_2 {
    s32 unk_00;
    u8 pad_04[0xC];
    u8 unk_10;
} S_800B6094_2;   /* temp_s0 in func_800B6094 */

typedef struct S_800B6094_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2C];
    void * unk_38;
} S_800B6094_3;   /* temp_v1 in func_800B6094 */

/* Populate a display row with entry text and a positioned icon. */
void func_800B6094(void *entry_data, s32 display_base, s32 row_index) {
    register S_800B6094_0 *entry ASM_REG("$19") = entry_data;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 row_base = display_base;
    s32 row = row_index;
    register s32 first_zero ASM_REG("$6") = 0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    M2C_UNK text_buffer[3];
    s32 *icon_slot;
    s32 icon_id;
    s32 text_y;
    s32 display_value;
    S_800B6094_2 *entry_info;
    register void *row_display ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_800B6094_3 *display_node;

    text_y = (row * 0x10) + 0xD8;
    row_display = (void *) (row * 4);
    ASM_KEEP(row);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    entry_info = (entry->unk_00 * 0x14) + D_8006DE24;
    row_display = (void *) ((s8 *)row_display + (s32)row_base);
    func_800B5264(((S_800B6094_1 *)row_display)->unk_20, entry_info->unk_00, first_zero, 0x58, text_y);
    func_800B53BC(((S_800B6094_1 *)row_display)->unk_2C, func_800B6030(entry->unk_01, text_buffer), 0, 0xA0, text_y);
    ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    icon_id = func_80049944(entry_info->unk_10);
    icon_slot = ((S_800B6094_1 *)row_display)->unk_38;
    if (func_800439BC(entry->unk_00) != 0) {
        display_value = func_800498EC(icon_id);
    } else {
        display_value = func_80049918(icon_id);
    }
    display_node = (row * 4) + row_base;
    ASM_KEEP(display_value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(row_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(row);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    *icon_slot = display_value;
    ((S_800B6094_6 *)(((S_800B6094_5 *)(((S_800B6094_4 *)display_node)->unk_38))->unk_04))->unk_08 = -0x30;
    display_node = display_node->unk_38;
    display_value = (row * 0x10) + 0x67;
    display_node = display_node->unk_04;
    display_node->unk_0A = (s16) display_value;
}
