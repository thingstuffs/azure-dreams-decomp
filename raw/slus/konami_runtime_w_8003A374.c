#include "common.h"

#include "common.h"

typedef struct {
    u8 pad0[0x1C];
    u8 *volatile read_ptr;
    u8 pad20[0x60];
    u8 *table;
} Func8003A374State;

void func_8003A374(Func8003A374State *arg0) {
    u8 *temp_v0;
    u32 temp_t0;
    u32 temp_t1;
    u32 temp_v1;
    u8 *temp_a1;
    u32 temp_a2;
    u32 temp_a3;
    u32 temp_a1_value;
    u32 table_base;

    temp_v0 = arg0->read_ptr;
    temp_t0 = temp_v0[0];
    temp_v0++;
    arg0->read_ptr = temp_v0;
    temp_t1 = temp_v0[0];
    temp_a1 = temp_v0 + 1;
    arg0->read_ptr = temp_a1;
    temp_v1 = temp_v0[1];
    temp_a2 = temp_a1[1];
    temp_a3 = temp_a1[2];
    temp_a1_value = temp_a1[3];
    arg0->read_ptr = temp_v0 + 5;
    table_base = (u32)arg0->table;
    temp_t1 <<= 2;
    temp_a2 <<= 8;
    do {
        temp_v1 += temp_a2;
    } while (0);
    temp_a3 <<= 16;
    temp_v1 += temp_a3;
    temp_a1_value <<= 24;
    temp_v1 += temp_a1_value;
    temp_v1 += temp_t1;
    temp_t0 <<= 2;
    temp_t0 += table_base;
    *(s32 *)(u32)*(u8 *)temp_v1 =
        *(s32 *)(temp_t0 + 0x48);
}
