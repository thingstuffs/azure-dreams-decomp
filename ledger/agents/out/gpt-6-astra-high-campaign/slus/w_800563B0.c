#include "common.h"

typedef struct S_80084918 {
    /* 0x0 */ s32 field0;
    /* 0x4 */ s32 field4;
    /* 0x8 */ s16 field8;
    /* 0xA */ s16 fieldA;
    /* 0xC */ s16 fieldC;
    /* 0xE */ s16 fieldE;
} S_80084918;

extern S_80084918 D_80084918;
extern s32 D_80073740[];

extern s32 func_8005F134(S_80084918 *arg);

/* Fills D_80084918 with an indexed table value and two parameters, then dispatches it. */
s32 func_800563B0(s32 table_index, s16 field_8_value, s16 field_a_value) {
    S_80084918 *record = &D_80084918;
    s32 table_value;

    record->field4 = 15;
    table_value = D_80073740[table_index];
    record->field8 = field_8_value;
    record->fieldA = field_a_value;
    record->fieldC = 0;
    record->fieldE = 0;
    record->field0 = table_value;
    return func_8005F134(record);
}
