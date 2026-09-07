#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} CopyFields;

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Part;

typedef struct {
    u8 pad0[8];
    CopyFields *copy;
    Part *part;
    u8 pad10[0x50];
    s32 field60;
} Object;

extern void func_8004491C(Object *, void *);
extern u8 D_80045340[9];

#ifdef __mips__
extern void func_80170A5C(void);
extern void func_80170C24(void);
extern void func_80171410(void);
extern void func_8017143C(void);
extern void func_801713BC(void);
extern void func_80171384(void);
extern void func_80171400(void);
extern void func_80172CF0(void);
extern void func_80172CE8(void);
extern void func_80172CE0(void);
extern void func_80172CF8(void);
extern void func_80172CA0(void);
extern void func_80172C98(void);
extern void func_80172C90(void);
extern void func_80174D74(void);
extern void func_80174D80(void);
extern void func_80174DB4(void);
extern void func_80174EA4(void);
extern void func_80174F78(void);
extern void func_80175084(void);
extern void func_801750B8(void);
extern void func_80175138(void);
extern void func_801751C0(void);

static void (*const bank_table[])(void)
    __attribute__((section(".text.func_80C93000"))) = {
    func_80170A5C, func_80170C24, func_80171410, func_80171410,
    func_80171410, func_8017143C, func_801713BC, func_801713BC,
    func_801713BC, func_80171384, func_80171384, func_8017143C,
    func_8017143C, func_80171400, func_80172CF0, func_80172CE8,
    func_80172CE0, func_80172CF8, func_80172CA0, func_80172C98,
    func_80172C90, 0, func_80174D74, func_80174D80,
    func_80174DB4, func_80174EA4, func_80174F78, func_80175084,
    func_801750B8, func_80175138, func_801751C0,
};

#define BODY_NAME func_80C93000
#else
#define BODY_NAME func_80C93000
#endif

void BODY_NAME(Object *arg0, s32 arg1, CopyFields *arg2)
{
    Part *part;
    CopyFields *copy;

    arg0->field60 = arg1;
    func_8004491C(arg0, D_80045340);

    part = arg0->part;
    part->field10 = 0x20;
    part->field14 |= 0xC;

    copy = arg0->copy;
    copy->x = arg2->x;
    copy->y = arg2->y;
    copy->z = arg2->z;

    part = arg0->part;
    part->field1E = 0x1000;
    part->field1C = 0x1000;
    part->b = 0x80;
    part->g = 0x80;
    part->r = 0x80;
}

#ifdef __mips__
#endif
