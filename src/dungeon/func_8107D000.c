/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_8107D000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8107D000_0;   /* temp_v0 in BODY_NAME */

typedef struct S_8107D000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_8107D000_1;   /* var_s0 in BODY_NAME */

typedef struct S_8107D000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8107D000_2;   /* temp_s4 in BODY_NAME */

typedef struct S_8107D000_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_8107D000_3;   /* temp_s2 in BODY_NAME */

typedef struct S_8107D000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xD];
    s16 unk_AA;
} S_8107D000_4;   /* temp_s5 in BODY_NAME */



void *func_8003FD64();
s32 func_8004491C();
s16 func_800A48F0();
s32 func_800A6D30();
void func_800A9C18();
s32 func_800AA36C();
extern M2C_UNK D_8014CAA4;
extern M2C_UNK D_8014CF68;
extern M2C_UNK D_8014FFB8;
extern M2C_UNK D_80150000;

#ifdef __mips__
void func_8014C800(void);
static const u32 bank_words[] __asm__("func_8014C800")
__attribute__((section(".text.func_8014C800"), aligned(4))) = {
    0x8014C898, 0x8014CAA4, 0x8014D394, 0x8014D394,
    0x8014D394, 0x8014D3C0, 0x8014D340, 0x8014D340,
    0x8014D340, 0x8014D2EC, 0x8014D324, 0x8014D3C0,
    0x8014D3C0, 0x8014D384, 0x8014EAF0, 0x8014EAE8,
    0x8014EAE0, 0x8014EAF8, 0x8014EAA0, 0x8014EA98,
    0x8014EA90, 0x97824081, 0x8E828582, 0x40819482,
    0x85828282, 0x93829282, 0x92828582, 0x44818B82,
    0x00000000, 0x00000000, 0x8014FCBC, 0x8014FD60,
    0x8014FDD8, 0x8014FE10, 0x8014FCBC, 0x8014FD60,
    0x8014FDD8, 0x8014FE70,
};
__asm__(".globl func_8014C800\n"
        ".size func_8014C800,676");
#define BODY_NAME func_8014C898
#else
#define BODY_NAME func_8014C800
#endif

void *BODY_NAME(s16 input0, s16 input1, s16 input2, s16 input3) {
    S_8107D000_1 *record;
    s32 value;
    u16 flags98;
    S_8107D000_3 *child_0C;
    S_8107D000_2 *child_08;
    S_8107D000_4 *record_alias;
    void *allocation;
    s8 saved_input1;
    s16 saved_input3;
    s8 saved_input2;
    void *allocation_arg;
    void *call_a1;

    record = NULL;
    saved_input1 = input1;
    saved_input3 = input3;
    saved_input2 = input2;
    allocation = func_8003FD64(0x112, ((M2C_UNK *)&D_80083498.next));
    if (allocation != NULL) {
        record = allocation + 0x20;
        ((S_8107D000_0 *)allocation)->unk_10 = &D_8014CAA4;
        record->unk_13 = 0x2B;
        func_8004491C(allocation, func_80045340);
        child_08 = ((S_8107D000_0 *)allocation)->unk_08;
        child_08->unk_0A = saved_input3;
        child_0C = ((S_8107D000_0 *)allocation)->unk_0C;
        value = input0 & 3;
        child_0C->unk_25 = saved_input2;
        record_alias = record;
        child_0C->unk_2C = &D_8014FFB8;
        child_0C->unk_24 = saved_input1;
        if (value == 1) {
            flags98 = record->unk_98;
            record->unk_14 = (s32) (record->unk_14 | 0x6000);
            record->unk_98 = (u16) (flags98 | 0x4000);
            record->unk_1C = (s32) (record->unk_1C | 0x6000);
        } else if (value >= 2) {
            flags98 = record->unk_98;
            record->unk_14 = (s32) (record->unk_14 | 0x2000);
            record->unk_98 = (u16) (flags98 | 0x4000);
            record->unk_1C = (s32) (record->unk_1C | 0x2000);
        } else if (((input0 & ~3) << 0x10) == 0) {
            if (!(record->unk_14 & 0x200)) {
                value = func_800A6D30();
                if (value & 1) {
                    record->unk_1C = (s32) (record->unk_1C | 0x200);
                    func_800A48F0(record, 1, (func_800A6D30() & 0x3F) | 0x20);
                    child_0C->unk_2C = &D_80150000;
                }
            }
        }
        allocation_arg = allocation;
        func_800A9C18(allocation_arg, child_08, child_0C, input0);
        record_alias->unk_9A = 0xFF;
        record_alias->unk_9C = -1;
        record_alias->unk_8C = &D_8014CF68;
        child_0C->unk_14 = (u16) (child_0C->unk_14 | 0xC);
        record_alias->unk_AA = (s16) ((u16) record->unk_14 & 7);
        func_800AA36C(record_alias, child_08, child_0C, record);
    }
    return record;
}
