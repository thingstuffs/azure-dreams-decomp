#include "common.h"

/* Inferred layout for D_80084918, shared with sibling functions in this
 * global's family (func_80055E84, func_80056654, func_800563B0,
 * func_80056D44, func_80056E10). Only the fields this function touches
 * are given exact offsets/types here. */
typedef struct S_80084918 {
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ s32 field_0x04;
    u8 pad_0x08[0x24 - 0x08];
    /* 0x24 */ s32 field_0x24;
    u8 pad_0x28[0x3A - 0x28];
    /* 0x3A */ s16 field_0x3A;
    /* 0x3C */ s16 field_0x3C;
} S_80084918;

extern S_80084918 D_80084918;
extern s32 D_80073740[];

extern void func_8005F134(S_80084918 *arg0);

/* Builds and submits a request using the indexed table value. */
void func_80056DB4(s32 request_index) {
    s32 request_value;

    D_80084918.field_0x04 = 0x60100;
    request_value = D_80073740[request_index];
    D_80084918.field_0x3A = 0;
    D_80084918.field_0x3C = 0;
    D_80084918.field_0x24 = 5;
    D_80084918.field_0x00 = request_value;
    func_8005F134(&D_80084918);
}
