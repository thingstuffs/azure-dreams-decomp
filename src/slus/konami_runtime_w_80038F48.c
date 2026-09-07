#include "common.h"

#include "common.h"

typedef struct RuntimeContext {
    u8 pad0[0x1C];
    u8 *read_ptr;
    u8 pad20[0x5C];
    u8 **return_ptr;
    u8 *base;
} RuntimeContext;

extern void func_80039640(RuntimeContext *);
extern void func_8003AD08(s32, u8 *);
extern u8 *D_8006A944[];

void func_80038F48(RuntimeContext *arg0) {
    u8 *temp_s1;
    u32 var_v0_2;
    s8 temp_v1;
    u8 var_v1;
    u8 *temp_a0;
    u8 *temp_a1;
    u8 *temp_v1_2;

    var_v1 = *arg0->read_ptr;
    temp_s1 = arg0->base;
    while ((u8)(var_v1 + 3) < 3U || var_v1 == 0) {
        temp_a0 = arg0->read_ptr;
        temp_v1 = *(s8 *)temp_a0;
        if (temp_v1 == -3) {
            *arg0->return_ptr = temp_a0 + 2;
            temp_v1_2 = arg0->read_ptr;
            arg0->return_ptr++;
            arg0->read_ptr = temp_v1_2 + 1;
            func_8003AD08(*(s32 *)(temp_s1 + (temp_v1_2[1] * 4) + 0x48),
                          arg0->base + 0x14);
            arg0->read_ptr = arg0->base + 0x14;
        } else if (temp_v1 == -2) {
            *arg0->return_ptr = temp_a0 + 2;
            temp_a0 = arg0->read_ptr;
            arg0->return_ptr++;
            arg0->read_ptr = temp_a0 + 1;
            arg0->read_ptr = D_8006A944[temp_a0[1]];
        } else if (temp_v1 == -1) {
            *arg0->return_ptr = temp_a0 + 5;
            temp_a0 = arg0->read_ptr;
            temp_a1 = temp_a0 + 1;
            arg0->return_ptr++;
            arg0->read_ptr = temp_a1;
            var_v0_2 = (u32)temp_a0[1] + ((u32)temp_a1[1] << 8) +
                       ((u32)temp_a1[2] << 16) + ((u32)temp_a1[3] << 24);
            arg0->read_ptr = *(u8 **)var_v0_2;
        } else {
            func_80039640(arg0);
        }
        var_v1 = *arg0->read_ptr;
    }
}
