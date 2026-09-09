#include "common.h"

extern void Control_CD(s32, void *, void *);
extern void func_8003F540(s32, s32, s32, s32);
extern void func_8003F6D4(s32, void *, void *, s32);
extern s32 func_800445E0(void);
extern s32 func_800A9390(s16);
extern s32 func_800A9400(s16);

extern s32 D_80024000[];
extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern s8 D_800DCF4D;
extern u8 D_800DCF59;
extern s32 D_800DD918[];
extern s32 D_800DDAB8[];
extern s32 D_800E58B0[];

/* Updates selection data and starts a message when the selection changes. */
s32 func_800A982C(s16 selection_id, s16 alternate_table) {
    register s32 changed;
    s32 change_result;
    u32 index_hi;
    register u32 doubled_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 *selection_entry;
    s32 *selection_table;
    s32 *resource_data;
    s32 *message_data;
    s32 message_offset;
    register s32 entry_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 state_value;

    resource_data = (s32 *)0x80024000;
    if (D_800DCF59 == 0) {
        changed = 0;
        if ((selection_id != (D_800DCF4D & 0x3F)) ||
            ((((u8)D_800DCF4D >> 6) & 1) != alternate_table)) {
            changed = 1;
        }
        change_result = changed;
        if (change_result != 0) {
            if (alternate_table != 0) {
                message_offset = ((s16)func_800A9390(selection_id) * 0xC) + 0x607F;
            } else {
                message_offset = ((selection_id - 1) * 0xC) + 0x607F;
            }
            message_data = D_800E58B0;
            func_8003F6D4(0xC, resource_data, message_data, message_offset);
            Control_CD(6, message_data, 0);
            Control_CD(0xFF, D_8003E140, &D_800DCF59);
            D_800DCF4D = selection_id | (alternate_table << 6);
        }

        if (alternate_table != 0) {
            selection_table = D_800DDAB8;
            index_hi = func_800A9400(selection_id) << 16;
        } else {
            selection_table = D_800DD918;
            index_hi = selection_id << 16;
        }
        doubled_index = index_hi >> 15;
        state_value = D_8006CD58[0];
        ASM_KEEP(state_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        entry_offset = (s32)(doubled_index << 16) >> 14;
        selection_entry = (s32 *)(entry_offset + (u32)selection_table);
        func_8003F540(0, state_value, selection_entry[0], selection_entry[1]);
        Control_CD(0x15, (void *)func_800445E0(), 0);

        change_result = changed;
        if (change_result != 0) {
            D_800DCF59 = 2;
            return 0;
        }
    } else {
        if (D_800DCF59 != 1) {
            return 0;
        }
        D_800DCF59 = 0;
    }
    return resource_data[0];
}
