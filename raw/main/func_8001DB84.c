#include "common.h"

extern s32 D_8002D690[4];
extern s32 D_8002D6A0[3];
extern s32 D_8002D6A4[3];
extern s32 D_8002D6A8[3];

void func_8001DB84(void *arg0, s32 arg1) {
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    void *temp_v1;
    s32 *base;
    void *field22c;
    s32 pad[2];

    var_a3 = 0;
    if (arg1 > 0) {
        base = D_8002D690;
        field22c = (u8 *) arg0 + 0x204;
        var_t1 = 0x294;
        do {
            var_t0 = 0x224 + var_a3 * 0x10;
            *((s32 *) *(s32 **) ((u8 *) arg0 + 0x220) + var_a3) = (s32) ((u8 *) arg0 + var_t0);
            *(s32 *) ((u8 *) arg0 + var_a3 * 0x10 + 0x294) = base[0];
            temp_v1 = (u8 *) arg0 + var_t1;
            *(s32 *) ((u8 *) arg0 + var_a3 * 0x10 + 0x298) = base[1];
            *(s32 *) ((u8 *) arg0 + var_a3 * 0x10 + 0x29C) = base[2];
            var_t1 += 0x10;
            *(s32 *) ((u8 *) arg0 + var_a3 * 0x10 + 0x2A0) = base[3];
            *(void **) ((u8 *) arg0 + var_a3 * 0x10 + 0x228) = temp_v1;
            *(s32 *) ((u8 *) arg0 + var_a3 * 0x10 + 0x22C) = (s32) field22c;
            var_a3 += 1;
        } while (var_a3 < arg1);
    }
    *(s32 *) ((u8 *) arg0 + 0x204) = D_8002D6A0[0];
    *(s32 *) ((u8 *) arg0 + 0x208) = D_8002D6A4[0];
    *(s32 *) ((u8 *) arg0 + 0x20C) = D_8002D6A8[0];
}
