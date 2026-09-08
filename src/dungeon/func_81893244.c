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
/* Spawns a primary effect and eight randomly offset particles from the supplied data. */
void func_81893244(s32 source, Func81893244Data *initial_data, s16 status_param) {
    Func81893244Sub *sprite;
    Func81893244Data *payload;
    Func81893244Object *effect;
    Func81893244Status *status;
    s32 brightness;
    s32 particle_index;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        status = &effect->status;
        effect->field10 = &D_800248F8;
        status->field20 = source;
        status->field24 = 0;
        status->field26 = status_param;
        sprite = effect->fieldC;
        sprite->uC.bytesC.fieldE = 0x80;
        sprite->uC.bytesC.fieldD = 0x80;
        sprite->uC.bytesC.fieldC = 0x80;
        func_8003DB94(sprite, &D_800E2178, 0);
        sprite->field1E = 0x1800;
        sprite->field1C = 0x1800;
        func_8004491C(effect, D_80045340);
        payload = effect->field8;
        *payload = *initial_data;
        func_80024824(source, payload, 8, -0x40);
    }
    particle_index = 0;
    do {
        effect = func_8003FC64(0x212);
        status = &effect->status;
        if (effect != NULL) {
            effect->field10 = &D_800249B8;
            brightness = 0x80;
            status->field20 = source;
            status->field24 = 0;
            status->field26 = status_param;
            sprite = effect->fieldC;
            sprite->uC.bytesC.fieldE = brightness;
            sprite->uC.bytesC.fieldD = brightness;
            sprite->uC.bytesC.fieldC = brightness;
            func_8003DB94(sprite, &D_800253BC, 0);
            sprite->field1E = 0x800;
            sprite->field1C = 0x800;
            sprite->field14 = (u16) (sprite->field14 | 0xC);
            sprite->field10 = (u16) (sprite->field10 | 0x60);
            func_8004491C(effect, D_80045340);
            payload = effect->field8;
            *payload = *initial_data;
            payload->u0.halves0.field2 = (u16) (payload->u0.halves0.field2 + ((s32) (func_800644B8(rand()) * 2) >> 8));
            payload->u4.halves4.field6 = (u16) (payload->u4.halves4.field6 + ((s32) (func_80064584(rand()) * 2) >> 8));
        }
        particle_index += 1;
    } while (particle_index < 8);
}
