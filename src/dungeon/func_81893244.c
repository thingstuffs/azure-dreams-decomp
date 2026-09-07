#include "common.h"
#include "m2c_compat.h"

typedef struct Func81893244Data Func81893244Data;
typedef struct Func81893244Sub Func81893244Sub;
typedef struct Func81893244Status Func81893244Status;
typedef struct Func81893244Object Func81893244Object;

struct Func81893244Data {
    union {
        s32 word0;
        struct { u16 half0; u16 field2; } halves0;
    } u0;
    union {
        s32 word4;
        struct { u16 half4; u16 field6; } halves4;
    } u4;
    s32 word8;
    union {
        s32 wordC;
        struct { u8 fieldC; u8 fieldD; u8 fieldE; u8 padF; } bytesC;
    } uC;
    s32 field10;
    s32 field14;
};

struct Func81893244Sub {
    union {
        s32 word0;
        struct { u16 half0; u16 field2; } halves0;
    } u0;
    union {
        s32 word4;
        struct { u16 half4; u16 field6; } halves4;
    } u4;
    s32 word8;
    union {
        s32 wordC;
        struct { u8 fieldC; u8 fieldD; u8 fieldE; u8 padF; } bytesC;
    } uC;
    u16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
};

struct Func81893244Status {
    s32 field20;
    s16 field24;
    s16 field26;
};

struct Func81893244Object {
    u8 pad0[8];
    Func81893244Data *field8;
    Func81893244Sub *fieldC;
    void *field10;
    u8 pad14[12];
    Func81893244Status status;
};

extern s32 D_800E2178;
extern u8 D_80045340[];
M2C_UNK func_80024824(s32, Func81893244Sub *, s32, s32);
Func81893244Object *func_8003FC64(s32);
void func_8003DB94(Func81893244Sub *, s32 *, s32);
M2C_UNK func_8004491C(Func81893244Object *, u8 *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
s32 rand(void);
extern M2C_UNK D_800248F8;
extern M2C_UNK D_800249B8;
extern s32 D_800253BC;
void func_81893244(s32 arg0, Func81893244Data *arg1, s16 arg2) {
    Func81893244Sub *sub;
    Func81893244Data *payload;
    Func81893244Object *obj;
    Func81893244Status *status;
    s32 var_s3;
    s32 var_s2;
    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        status = &obj->status;
        obj->field10 = &D_800248F8;
        status->field20 = arg0;
        status->field24 = 0;
        status->field26 = arg2;
        sub = obj->fieldC;
        sub->uC.bytesC.fieldE = 0x80;
        sub->uC.bytesC.fieldD = 0x80;
        sub->uC.bytesC.fieldC = 0x80;
        func_8003DB94(sub, &D_800E2178, 0);
        sub->field1E = 0x1800;
        sub->field1C = 0x1800;
        func_8004491C(obj, D_80045340);
        payload = obj->field8;
        *payload = *arg1;
        func_80024824(arg0, payload, 8, -0x40);
    }
    var_s2 = 0;
    do {
        obj = func_8003FC64(0x212);
        status = &obj->status;
        if (obj != NULL) {
            obj->field10 = &D_800249B8;
            var_s3 = 0x80;
            status->field20 = arg0;
            status->field24 = 0;
            status->field26 = arg2;
            sub = obj->fieldC;
            sub->uC.bytesC.fieldE = var_s3;
            sub->uC.bytesC.fieldD = var_s3;
            sub->uC.bytesC.fieldC = var_s3;
            func_8003DB94(sub, &D_800253BC, 0);
            sub->field1E = 0x800;
            sub->field1C = 0x800;
            sub->field14 = (u16) (sub->field14 | 0xC);
            sub->field10 = (u16) (sub->field10 | 0x60);
            func_8004491C(obj, D_80045340);
            payload = obj->field8;
            *payload = *arg1;
            payload->u0.halves0.field2 = (u16) (payload->u0.halves0.field2 + ((s32) (func_800644B8(rand()) * 2) >> 8));
            payload->u4.halves4.field6 = (u16) (payload->u4.halves4.field6 + ((s32) (func_80064584(rand()) * 2) >> 8));
        }
        var_s2 += 1;
    } while (var_s2 < 8);
}
