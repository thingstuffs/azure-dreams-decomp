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

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_80169C1C(void)
{
    void *object;
    void *sub;
    Vec3i *dst;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        FIELD(object, s16, 0x38) = 0;
        FIELD(object, void *, 0x10) = D_80169754;
        func_8004491C(object, D_80045340);

        sub = FIELD(object, void *, 0xC);
        FIELD(sub, s16, 0x10) = 0x20;
        FIELD(sub, s16, 6) = 0;
        FIELD(sub, u16, 0x14) |= 0xC;

        dst = FIELD(object, Vec3i *, 8);
        dst->x = D_80083780[0];
        dst->y = D_80083780[1];
        dst->z = D_80083780[2];

        sub = FIELD(object, void *, 0xC);
        FIELD(sub, s16, 0x1E) = 0x1000;
        FIELD(sub, s16, 0x1C) = 0x1000;
        FIELD(sub, u8, 0xE) = 0x80;
        FIELD(sub, u8, 0xD) = 0x80;
        FIELD(sub, u8, 0xC) = 0x80;
        FIELD(sub, u16, 0x14) |= 0x80;

        FIELD(object, PackedVec3i, 0x48) = *(PackedVec3i *)D_80173B40;
        FIELD(sub, void *, 8) = (u8 *)object + 0x48;
    }
}
