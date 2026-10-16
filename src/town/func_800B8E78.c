#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B65D8_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B65D8_4;   /* temp_s1 in townUpdateModeDisplaySpacing */

typedef struct S_800B65D8_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B65D8_5;   /* ((S_800B65D8_4 *)temp_s1)->unk_04 in townUpdateModeDisplaySpacing */


s32 func_80048DA0();                         /* extern */
s32 func_80048DCC();                             /* extern */
s32 func_80048DE8();                             /* extern */
void townSetMonsterStatusPanelHeight();                    /* extern */
extern u8 D_80089344[];

typedef struct S_800B65D8_0 {
    u8 pad_00[0x50];
    void * unk_50;
} S_800B65D8_0;   /* var_s4 in townUpdateModeDisplaySpacing */

typedef struct S_800B65D8_1 {
    s32 unk_00;
    void * unk_04;
} S_800B65D8_1;   /* temp_s1 in townUpdateModeDisplaySpacing */

typedef struct S_800B65D8_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B65D8_2;   /* temp_ptr in townUpdateModeDisplaySpacing */

typedef struct S_800B65D8_3 {
    u8 pad_00[0x5C];
    s32 * unk_5C;
} S_800B65D8_3;   /* base in townUpdateModeDisplaySpacing */

/* Updates two display entries for the mode and adjusts their spacing. */
void townUpdateModeDisplaySpacing(S_800B65D8_3 *base, s32 display_mode) {
    s32 mode;
    s32 total_width;
    s32 entry_index;
    u8 *lookup;
    void *entry_slot;
    s32 x_offset;
    s32 spacing;
    s32 entry_id;
    S_800B65D8_1 *entry;
    S_800B65D8_2 *position;

    entry_index = (total_width = 0);
    lookup = D_80089344;
    entry_slot = base;
    do {
        mode = display_mode;
        entry = ((S_800B65D8_0 *)entry_slot)->unk_50;
        entry_id = func_80048DA0(mode, *(u8 *)((s32)entry_index + (s32)lookup));
        if ((entry_index == 0) && (mode == 4)) {
            entry_id -= 1;
        }
        entry->unk_00 = func_80048DCC(entry_id);
        spacing = func_80048DE8(entry_id);
        if (spacing == 0x10) {
            ((S_800B65D8_5 *)(((S_800B65D8_4 *)entry)->unk_04))->unk_0A = 0;
        } else {
            x_offset = total_width - (entry_index * 8);
            position = entry->unk_04;
            total_width += spacing;
            position->unk_0A = x_offset;
        }
        entry_index += 1;
        entry_slot += 4;
    } while (entry_index < 2);
    spacing = 0;
    if (total_width != 0) {
        spacing = total_width - 0x14;
    }
    townSetMonsterStatusPanelHeight(*base->unk_5C, spacing);
}
