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
extern void func_8016AA5C(void);
extern void func_8016AC24(void);
extern void func_8016B410(void);
extern void func_8016B43C(void);
extern void func_8016B3BC(void);
extern void func_8016B384(void);
extern void func_8016B400(void);
extern void func_8016CCF0(void);
extern void func_8016CCE8(void);
extern void func_8016CCE0(void);
extern void func_8016CCF8(void);
extern void func_8016CCA0(void);
extern void func_8016CC98(void);
extern void func_8016CC90(void);
extern void func_8016ED74(void);
extern void func_8016ED80(void);
extern void func_8016EDB4(void);
extern void func_8016EEA4(void);
extern void func_8016EF78(void);
extern void func_8016F084(void);
extern void func_8016F0B8(void);
extern void func_8016F138(void);
extern void func_8016F1C0(void);

static void (*const bank_table[])(void)
    __attribute__((section(".text.func_80C99000"))) = {
    func_8016AA5C, func_8016AC24,
    func_8016B410, func_8016B410, func_8016B410,
    func_8016B43C,
    func_8016B3BC, func_8016B3BC, func_8016B3BC,
    func_8016B384, func_8016B384,
    func_8016B43C, func_8016B43C,
    func_8016B400,
    func_8016CCF0, func_8016CCE8, func_8016CCE0, func_8016CCF8,
    func_8016CCA0, func_8016CC98, func_8016CC90,
    0,
    func_8016ED74, func_8016ED80, func_8016EDB4, func_8016EEA4,
    func_8016EF78, func_8016F084, func_8016F0B8, func_8016F138,
    func_8016F1C0,
};

#define BODY_NAME func_80C99000
#else
#define BODY_NAME func_80C99000
#endif

/* Initializes object part defaults and copies the supplied coordinates. */
void BODY_NAME(Object *object, s32 field60_value, CopyFields *source_coords)
{
    Part *part;
    CopyFields *copy;

    object->field60 = field60_value;
    func_8004491C(object, D_80045340);

    part = object->part;
    part->field10 = 0x20;
    part->field14 |= 0xC;

    copy = object->copy;
    copy->x = source_coords->x;
    copy->y = source_coords->y;
    copy->z = source_coords->z;

    part = object->part;
    part->field1E = 0x1000;
    part->field1C = 0x1000;
    part->b = 0x80;
    part->g = 0x80;
    part->r = 0x80;
}

#ifdef __mips__
#endif
