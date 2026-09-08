#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 field0;
    u8 field1;
    u8 field2;
    u8 field3;
} D_800E3648_entry;
typedef struct {
    u8 pad0[6];
    s8 field6;
    s8 field7;
    u32 field8;
    s32 fieldC;
    s16 field10;
    u8 pad12[2];
    s16 field14;
    u8 pad16[2];
} D_800E39C8_entry;
extern D_800E3648_entry D_800E3648[];
extern u8 D_800DF258[];
s32 func_800B500C();                   /* extern */
s32 func_800B5128();                                /* extern */
M2C_UNK func_800B5F80();                         /* extern */
extern void func_8009A21C();
extern D_800E39C8_entry D_800E39C8[];

/* Selects and initializes an entry at the given position, returning its slot. */
s32 func_800B60B8(s16 x, s16 y, s16 z, s32 type_id, s32 entry_value) {
    s32 slot;
    s32 slot_sign;
    s32 entry_type;
    D_800E3648_entry *entries;
    D_800E3648_entry *entry;

    entry_type = type_id;
    slot = func_800B500C(x, y, z);
    slot_sign = slot << 0x10;
    if (slot_sign < 0) {
        slot = func_800B5128();
        slot_sign = slot << 0x10;
        if (slot_sign < 0) {
            slot = 0x1F;
        }
    }
    slot = slot << 0x10;
    slot = slot >> 0x10;
    func_800B5F80(slot);
    entries = D_800E3648;
    entry = &entries[slot];
    entry->field1 = 0x15;
    entry->field3 = 0xC0;
    entry->field0 = entry_type;
    entry->field2 = 0;
    D_800E39C8[slot].field6 = (s8) x;
    D_800E39C8[slot].field7 = (s8) y;
    func_8009A21C(x, y, 0x20);
    D_800E39C8[slot].field10 = z;
    D_800E39C8[slot].field14 = 0;
    D_800E39C8[slot].fieldC = entry_value;
    D_800E39C8[slot].field8 = *(s32 *)(((s32) (entry_type << 0x10) >> 0xE) + D_800DF258);
    return slot;
}
