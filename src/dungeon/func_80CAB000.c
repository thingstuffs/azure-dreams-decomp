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
extern void func_80158A5C(void);
extern void func_80158C24(void);
extern void func_80159410(void);
extern void func_8015943C(void);
extern void func_801593BC(void);
extern void func_80159384(void);
extern void func_80159400(void);
extern void func_8015ACF0(void);
extern void func_8015ACE8(void);
extern void func_8015ACE0(void);
extern void func_8015ACF8(void);
extern void func_8015ACA0(void);
extern void func_8015AC98(void);
extern void func_8015AC90(void);
extern void func_8015CD74(void);
extern void func_8015CD80(void);
extern void func_8015CDB4(void);
extern void func_8015CEA4(void);
extern void func_8015CF78(void);
extern void func_8015D084(void);
extern void func_8015D0B8(void);
extern void func_8015D138(void);
extern void func_8015D1C0(void);

static void (*const bank_table[])(void)
    __attribute__((section(".text.func_80CAB000"))) = {
    func_80158A5C, func_80158C24, func_80159410, func_80159410,
    func_80159410, func_8015943C, func_801593BC, func_801593BC,
    func_801593BC, func_80159384, func_80159384, func_8015943C,
    func_8015943C, func_80159400, func_8015ACF0, func_8015ACE8,
    func_8015ACE0, func_8015ACF8, func_8015ACA0, func_8015AC98,
    func_8015AC90, 0, func_8015CD74, func_8015CD80,
    func_8015CDB4, func_8015CEA4, func_8015CF78, func_8015D084,
    func_8015D0B8, func_8015D138, func_8015D1C0,
};

#define BODY_NAME func_80CAB000
#else
#define BODY_NAME func_80CAB000
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
