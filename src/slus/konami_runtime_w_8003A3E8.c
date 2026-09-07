#include "common.h"

#include "common.h"

typedef struct {
    u8 pad0[0x1C];
    u8 *volatile read_ptr;
    u8 pad20[0x60];
    u8 *table;
} Func8003A3E8State;

void func_8003A3E8(Func8003A3E8State *arg0) {
    u8 *temp_v1;
    u8 *temp_a1;
    u8 *temp_t2;
    u32 temp_t1;
    u32 temp_v0;
    u32 temp_index;
    u32 temp_t0;
    u32 temp_a2;
    u32 temp_a3;
    u32 temp_a1_value;

    temp_v1 = arg0->read_ptr;
    temp_t1 = temp_v1[0];
    temp_v1++;
    arg0->read_ptr = temp_v1;
    temp_index = temp_v1[0];
    temp_t2 = arg0->table;
    temp_index <<= 2;
    temp_index += (u32)temp_t2;
    temp_t0 = *(u32 *)(temp_index + 0x48);
    temp_a1 = temp_v1 + 1;
    arg0->read_ptr = temp_a1;
    temp_v0 = temp_v1[1];
    temp_v1 += 5;
    temp_t1 <<= 2;
    temp_a2 = temp_a1[1];
    temp_a3 = temp_a1[2];
    temp_a1_value = temp_a1[3];
    temp_t1 += (u32)temp_t2;
    arg0->read_ptr = temp_v1;
    do {
        temp_t0 <<= 2;
    } while (0);
    temp_a2 <<= 8;
    temp_v0 += temp_a2;
    temp_a3 <<= 16;
    temp_v0 += temp_a3;
    temp_a1_value <<= 24;
    temp_v0 += temp_a1_value;
    temp_v0 += temp_t0;
    *(s32 *)(u32)*(u8 *)temp_v0 =
        *(s32 *)(temp_t1 + 0x48);
}
