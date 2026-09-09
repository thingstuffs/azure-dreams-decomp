#include "common.h"
#include "m2c_compat.h"



#define M2C_BREAK() M2C_ERROR(0)
#define M2C_SYNC() M2C_ERROR(0)

M2C_UNK func_80033AA8();
M2C_UNK func_80033AE8();
M2C_UNK Control_CD();
M2C_UNK func_8003F320();
M2C_UNK func_800B7934();
extern u8 D_80010000[];
extern M2C_UNK D_800D1BF4;
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];

typedef struct S_800B98B4_0 {
    u8 unk_00;
    u8 unk_01;
} S_800B98B4_0;   /* temp_v1 in func_800B98B4 */

typedef struct S_800B98B4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B98B4_1;   /* var_s1 in func_800B98B4 */

typedef struct S_800B98B4_2 {
    u8 unk_00;
} S_800B98B4_2;   /* temp_v2 in func_800B98B4 */

/* Processes enabled entries across 33 slots and handles entries of type 1. */
void func_800B98B4(void) {
    u8 *state_base;
    u8 *slot_data;
    u8 *entry_table;
    s32 slot_index;
    u8 entry_id;
    S_800B98B4_0 *entry;
    S_800B98B4_2 *reloaded_entry;

    Control_CD(6, &D_800D1BF4, 0);
    slot_index = 0;
    func_8003F320();
    func_80033AE8(0x12C3);
    entry_table = D_800D2644;
    slot_data = D_800D2EA4;
    state_base = (u8 *)0x80010000;
    do {
        entry_id = M2C_FIELD(state_base, u8 *, 0x33A4 + (slot_index * 2));
        if (entry_id != 0) {
            entry = (void *)((u32)(entry_id << 5) + (u32)entry_table);
            if (entry->unk_01 != 0) {
                func_800B7934(((S_800B98B4_1 *)slot_data)->unk_00, ((S_800B98B4_1 *)slot_data)->unk_01, entry->unk_00);
            }
            reloaded_entry = (void *)((u32)(M2C_FIELD(state_base, u8 *, 0x33A4 + (slot_index * 2)) << 5) + (u32)entry_table);
            if (reloaded_entry->unk_00 == 1) {
                func_80033AA8(0x12C3);
            }
        }
        slot_data += 8;
        slot_index += 1;
    } while (slot_index < 0x21);
}
