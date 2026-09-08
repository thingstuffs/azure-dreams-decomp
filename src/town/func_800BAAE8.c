#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800B8248_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B8248_2;   /* (void *)((temp_v0 << 5) + (s32)temp_s1) in func_800B8248 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8009CDB4();
extern M2C_UNK func_8009CDCC();
extern M2C_UNK func_8009CE34();
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];
extern u8 D_800D43F0[];

typedef struct S_800B8248_0 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
} S_800B8248_0;   /* temp_t0 in func_800B8248 */

typedef struct S_800B8248_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800B8248_1;   /* temp_v0_2 in func_800B8248 */

/* Initializes the default region and processes each occupied resource slot. */
void func_800B8248(void) {
    s32 region_x;
    s32 region_y;
    s32 region_width;
    s32 region_height;
    s32 slot_index;
    s32 slot_counter;
    u8 resource_index;
    u8 *resources;
    void *state_base;
    S_800B8248_0 *slot;
    S_800B8248_1 *region;

    func_8009CDB4();
    func_8009CDCC(0x3FU, 0U, 0x10U, 0x10U, D_800D43F0);
    slot_counter = 0;
    state_base = (void *)0x80010000;
    resources = D_800D2644;
    do {
        slot_index = slot_counter & 0xFF;
        slot = (void *)((slot_index * 2) + (s32)state_base);
        resource_index = slot->unk_33A4;
        if (resource_index != 0) {
            ((S_800B8248_2 *)((void *)((resource_index << 5) + (s32)resources)))->unk_0A = 1;
            region = (slot_index * 8) + D_800D2EA4;
            region_x = region->unk_00;
            region_y = region->unk_01;
            region_width = region->unk_02;
            region_height = region->unk_03;
            resource_index = slot->unk_33A4;
            func_8009CDCC(region_x, region_y, region_width, region_height,
                          (resource_index << 5) + (D_800D2644 + 0xC));
        }
        slot_counter += 1;
    } while ((u32)(u8)slot_counter < 0x21U);
    func_8009CE34();
}
