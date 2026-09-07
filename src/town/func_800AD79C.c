#include "common.h"

extern u16 D_80083780[];
extern u16 D_800834B8[];
typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
} Record;
extern Record D_80100E40[];

void func_800AAEFC(void) {
    s32 i;
    u16 *src0;
    u16 *src1;
    volatile Record *dst;

    i = 0;
    src0 = D_80083780;
    src1 = D_800834B8;
    dst = D_80100E40;
    do {
        dst->field_0 = src0[1];
        dst->field_2 = src0[3];
        dst->field_4 = src0[5];
        i++;
        dst->field_6 = src1[8];
        dst++;
    } while (i < 8);
}
