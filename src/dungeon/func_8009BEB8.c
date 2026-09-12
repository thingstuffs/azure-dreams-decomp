#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern void func_80048224(s16, s32, s32, s32);
extern u8 D_800E3DA0[];
extern u8 D_800E3DB0[];
extern u8 D_800E3DE0[];
/* Selects a slot by type and ID, clearing flags for special IDs. */
u8 *func_800A1618(s32 requested_id, s32 requested_type) {
    u8 *result;
    register u8 *table ASM_REG("$3");
    u8 *ram_base;
    s32 slot_type;
    s32 match_id;
    s32 short_id;
    s16 slot_id;
    register s32 saved_type ASM_REG("$9");
    s32 slot_index;
    u8 *entry_id;
    u8 *candidate;
    u8 *entry;
    slot_id = requested_id;
    candidate = 0;
    saved_type = requested_type;
    slot_type = requested_type;
    short_id = requested_id;
    short_id = (s16)short_id;
    if (short_id == 0x38) {
        table = D_800E3DB0;
        result = table + 0x10;
        ram_base = (u8 *)0x800E0000;
        ASM_KEEP4(result, table, ram_base, saved_type);
        table[0x11] = 0;
        table = ram_base + 0x3DA0;
        table[2] = 0;
        goto clear_flags;
    }
    match_id = 0x31;
    if (short_id == 0x31) {
        table = D_800E3DB0;
        result = table + 8;
        ram_base = (u8 *)0x800E0000;
        ASM_KEEP4(result, table, ram_base, saved_type);
        table[9] = 0;
        table = ram_base + 0x3DA0;
clear_flags:
        table[1] = 0;
        ram_base[0x3DA0] = 0;
        return result;
    }
    if (short_id == 0x39) slot_id = 2;
    if ((s16)slot_type == 3) {
        u8 *scan_base;
        register u8 *scan_start ASM_REG("$3");
        scan_base = (u8 *)0x800E0000;
        ASM_KEEP(scan_base);
        scan_start = scan_base + 0x3DD0;
        ASM_KEEP_DEP_NV(scan_start, scan_base);
        entry = scan_start;
        slot_index = 4;
        goto scan;
    }
    if ((s16)slot_type == 2) {
        u8 *result;
        result = D_800E3DE0;
        return result;
    }
    entry = D_800E3DB0;
    if (entry[0x11] == 0x38) {
        s32 start_index;
        start_index = 3;
        entry += 0x18;
        slot_index = start_index;
        goto scan;
    }
    ASM_KEEP(candidate);
    slot_index = 0;
    if (entry[9] == 0x31) {
        entry += 0x10;
        slot_index = 2;
        goto scan;
    }
    ASM_KEEP(slot_index);
scan:
    if (slot_index < 6) {
        s32 type_one;
        s32 type_three;
        s32 type_two;
        s8 *slot_ids;
        slot_type = (s16)saved_type;
        type_one = 1;
        type_three = 3;
        ASM_USE(saved_type);
        match_id = (s16)slot_id;
        type_two = 2;
        slot_ids = (s8 *)D_800E3DA0;
        entry_id = entry + 1;
        do {
            if (((slot_type != type_one) && (slot_type != type_three)) || (*entry == slot_type)) {
                if ((*entry_id == 0) || (*entry_id == match_id)) {
                    if (slot_type == type_two) {
                        register u8 *result;
                        D_800E3DA0[6] = 0;
                        result = entry;
                        return result;
                    }
                    candidate = entry;
                    if ((*entry_id == match_id) || (*(s8 *)((unsigned long)slot_index + (unsigned long)slot_ids) == match_id)) break;
                }
            } else break;
            slot_index++;
            entry_id += 8;
            entry += 8;
        } while (slot_index < 6);
    }
    if (candidate) func_80048224((s16)slot_id, slot_type, slot_index, match_id);
    return candidate;
}
