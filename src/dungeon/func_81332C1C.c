#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec3i;

typedef struct {
    u8 pad0[6];
    s16 field6;
    void *field8;
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} SubObject;

typedef struct {
    u8 pad0[8];
    Vec3i *field8;
    SubObject *fieldC;
    void *field10;
    u8 pad14[0x24];
    s16 field38;
    u8 pad3A[0xE];
    PackedVec3i field48;
} Object;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80045340[9];
extern s32 D_80083780[];
extern u8 D_80169754[9];
extern u8 D_80173B40[12];



typedef struct S_80169C1C_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80169C1C_0;   /* sub in func_80169C1C */

void func_80169C1C(void)
{
    void *object;
    S_80169C1C_0 *sub;
    Vec3i *dst;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        (*(s16 *)((u8 *)object + 0x38)) = 0;
        (*(void * *)((u8 *)object + 0x10)) = D_80169754;
        func_8004491C(object, D_80045340);

        sub = (*(void * *)((u8 *)object + 0xC));
        sub->unk_10 = 0x20;
        sub->unk_06 = 0;
        sub->unk_14 |= 0xC;

        dst = (*(Vec3i * *)((u8 *)object + 8));
        dst->x = D_80083780[0];
        dst->y = D_80083780[1];
        dst->z = D_80083780[2];

        sub = (*(void * *)((u8 *)object + 0xC));
        sub->unk_1E = 0x1000;
        sub->unk_1C = 0x1000;
        sub->unk_0E = 0x80;
        sub->unk_0D = 0x80;
        sub->unk_0C = 0x80;
        sub->unk_14 |= 0x80;

        (*(PackedVec3i *)((u8 *)object + 0x48)) = *(PackedVec3i *)D_80173B40;
        sub->unk_08 = (u8 *)object + 0x48;
    }
}
