#include "common.h"
#include "m2c_compat.h"

s32 func_80069EF8();                                /* extern */

s32 func_80167088(s32 arg0) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_v1;

    var_v1 = 0;
    if (arg0 != 0) {
        if (arg0 < 5) {
            do {
                temp_v1_5 = (s32) (func_80069EF8() & 0xC) >> 2;
            } while (temp_v1_5 >= arg0);
            return temp_v1_5;
        }
        if (arg0 < 0x11) {
            do {
                temp_v1_4 = (s32) (func_80069EF8() & 0xF0) >> 4;
            } while (temp_v1_4 >= arg0);
            return temp_v1_4;
        }
        if (arg0 < 0x41) {
            do {
                temp_v1_3 = (s32) (func_80069EF8() & 0xFC) >> 2;
            } while (temp_v1_3 >= arg0);
            return temp_v1_3;
        }
        if (arg0 < 0x101) {
            do {
                temp_v1_2 = (s32) (func_80069EF8() & 0xFF0) >> 4;
            } while (temp_v1_2 >= arg0);
            return temp_v1_2;
        }
        if (arg0 < 0x1001) {
            do {
                temp_v1 = func_80069EF8() & 0xFFF;
            } while (temp_v1 >= arg0);
            return temp_v1;
        }
        do {
            var_v1 = func_80069EF8() & 0xFFFF;
        } while (var_v1 >= arg0);
        goto block_17;
    }
block_17:
    return var_v1;
}
