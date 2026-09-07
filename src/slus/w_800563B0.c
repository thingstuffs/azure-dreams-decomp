#include "common.h"

/* Sets up D_80084918 (a fixed-size record) from an index into D_80073740 and two s16 params, then dispatches it via func_8005F134. */
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

s32 func_800563B0(s32 a0, s16 a1, s16 a2) {
    S_80084918 *p = &D_80084918;
    s32 v0;

    p->field4 = 15;
    v0 = D_80073740[a0];
    p->field8 = a1;
    p->fieldA = a2;
    p->fieldC = 0;
    p->fieldE = 0;
    p->field0 = v0;
    return func_8005F134(p);
}
