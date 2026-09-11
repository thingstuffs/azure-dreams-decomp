#include "common.h"

typedef struct S_800B61C0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x8];
    s32 unk_2C;
    u8 pad_30[0x8];
    void * unk_38;
} S_800B61C0_0;   /* temp_s0 in func_800B61C0 */

typedef struct S_800B61C0_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B61C0_1;   /* arg0 in func_800B61C0 */

typedef struct S_800B61C0_2 {
    s32 unk_00;
    void * unk_04;
} S_800B61C0_2;   /* ((S_800B61C0_0 *)temp_s0)->unk_38 in func_800B61C0 */

typedef struct S_800B61C0_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B61C0_3;   /* ((S_800B61C0_2 *)(((S_800B61C0_0 *)temp_s0)->unk_38))->unk_04 in func_800B61C0 */


extern s32 func_8004A658();
extern s32 func_8004AC3C();
extern s32 func_800B5264();
extern s32 func_800B53BC();
extern s32 func_800B5918();


/* Populate and position a display row from an entry. */
void func_800B61C0(S_800B61C0_1 *entry, s32 widgets_base, s32 row)
{
    s32 detail_info[4];
    s32 entry_info[2];
    s32 row_offset;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 text_y;
    s32 entry_value;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 *info_out;
    S_800B61C0_0 *widgets;

    info_out = entry_info;
    entry_value = func_8004AC3C(entry, info_out);
    row_offset = row * 0x10;
    text_y = row_offset + 0xD8;
    widgets = (void *)(row * 4 + widgets_base);
    func_800B5264(widgets->unk_20, entry_value, entry_info[0], 0x58, text_y);
    func_800B53BC(widgets->unk_2C,
                  func_800B5918(entry, detail_info), 0, 0xA0, text_y);
    ((S_800B61C0_2 *)(widgets->unk_38))->unk_00 = func_8004A658(
        entry->unk_01, entry->unk_00);
    ((S_800B61C0_3 *)(((S_800B61C0_2 *)(widgets->unk_38))->unk_04))->unk_08 = -0x30;
    ((S_800B61C0_3 *)(((S_800B61C0_2 *)(widgets->unk_38))->unk_04))->unk_0A =
        (s16)(row_offset + 0x66);
}

/* MECHANISM: Sibling detail_info/entry_info arrays produce the retail 0x48 frame; keeping the
   entry_info pointer live hoists sp+0x28 and lets the $s2 save fill the first jal slot.
   Guarded $s2/$a1 value pins restore the scaled-index role and immediate return copy. */
