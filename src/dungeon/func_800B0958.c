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

s32 func_800B60B8(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    s32 temp_s4;
    D_800E39C8_entry *temp_s0;
    D_800E3648_entry *temp_base;
    D_800E3648_entry *temp_v1;

    temp_s4 = arg3;
    temp_s1 = func_800B500C(arg0, arg1, arg2);
    var_s1 = temp_s1 << 0x10;
    if (var_s1 < 0) {
        temp_s1 = func_800B5128();
        var_s1 = temp_s1 << 0x10;
        if (var_s1 < 0) {
            temp_s1 = 0x1F;
        }
    }
    temp_s1 = temp_s1 << 0x10;
    temp_s1 = temp_s1 >> 0x10;
    func_800B5F80(temp_s1);
    temp_base = D_800E3648;
    temp_v1 = &temp_base[temp_s1];
    temp_v1->field1 = 0x15;
    temp_v1->field3 = 0xC0;
    temp_v1->field0 = temp_s4;
    temp_v1->field2 = 0;
    D_800E39C8[temp_s1].field6 = (s8) arg0;
    D_800E39C8[temp_s1].field7 = (s8) arg1;
    func_8009A21C(arg0, arg1, 0x20);
    D_800E39C8[temp_s1].field10 = arg2;
    D_800E39C8[temp_s1].field14 = 0;
    D_800E39C8[temp_s1].fieldC = arg4;
    D_800E39C8[temp_s1].field8 = *(s32 *)(((s32) (temp_s4 << 0x10) >> 0xE) + D_800DF258);
    return temp_s1;
}
