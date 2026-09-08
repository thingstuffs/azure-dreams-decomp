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

/* Populates the global descriptor from a table entry and source fields, then processes it. */
s32 func_80056D44(s32 table_index, S_80056D44_Arg1 *source) {
    S_80084918 *descriptor = &D_80084918;
    descriptor->field4 = 0x60100;
    D_80084918.field0 = D_80073740[table_index];
    descriptor->field3A = source->field60;
    descriptor->field3C = source->field64;
    descriptor->field24 = source->field68;
    return func_8005F134(descriptor);
}
