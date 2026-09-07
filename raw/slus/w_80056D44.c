#include "common.h"

/* Inferred struct for global D_80084918, reconciled across this wave's siblings. */
typedef struct {
    /* 0x00 */ s32 field0;
    /* 0x04 */ u32 field4;
    /* 0x08 */ u8  pad08[0x24 - 0x08];
    /* 0x24 */ s32 field24;
    /* 0x28 */ u8  pad28[0x3A - 0x28];
    /* 0x3A */ u16 field3A;
    /* 0x3C */ u16 field3C;
} S_80084918;

extern S_80084918 D_80084918;
extern s32 D_80073740[];

/* Inferred layout for the second argument struct (only fields at 0x60/0x64/0x68 used here). */
typedef struct {
    u8  pad00[0x60];
    u16 field60;
    u8  pad62[2];
    u16 field64;
    u8  pad66[2];
    s32 field68;
} S_80056D44_Arg1;

extern s32 func_8005F134(S_80084918 *arg0);

/* Populates D_80084918 from arg0-indexed table + fields of *a1, then calls func_8005F134. */
s32 func_80056D44(s32 a0, S_80056D44_Arg1 *a1) {
    S_80084918 *p = &D_80084918;
    p->field4 = 0x60100;
    D_80084918.field0 = D_80073740[a0];
    p->field3A = a1->field60;
    p->field3C = a1->field64;
    p->field24 = a1->field68;
    return func_8005F134(p);
}
