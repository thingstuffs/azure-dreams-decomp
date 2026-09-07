#include "common.h"

#include "common.h"

extern u8 D_8006A86C[];
extern u8 D_800809C0[];

extern void func_8003AB14(void *arg0, void *arg1);
extern void func_80037D50(u8 *arg0, u8 arg1);
extern void func_80038A10(void);

typedef struct {
    u8 pad00[0x08];
    s16 field08;
    s16 field0A;
    s16 field0C;
    u8 pad0E[0x02];
    void (*field10)(void);
    u8 pad14[0x08];
    void *field1C;
    s16 field20;
    s16 field22;
    u8 field24;
    u8 pad25[0x03];
    u8 field28;
    u8 pad29[0x01];
    u8 field2A;
    u8 pad2B[0x13];
    u8 field3E[0x3E];
    u8 *field7C;
    u8 *field80;
} RuntimeObject;

typedef struct {
    u8 pad00[0x02];
    u8 field02;
    u8 field03;
    u8 field04;
    u8 pad05[0x87];
    RuntimeObject object;
} RuntimeInput;

void func_80037D9C(RuntimeInput *arg0, u8 arg1) {
    RuntimeObject *obj = &arg0->object;
    u8 value;

    obj->field80 = (u8 *)arg0;
    func_8003AB14(obj, D_8006A86C);
    obj->field2A = 1;
    obj->field24 = 0x20;
    obj->field0C = (s16)0xFC;
    obj->field08 = 0;
    obj->field0A = 0;
    obj->field1C = D_800809C0;
    obj->field22 = 0;
    obj->field20 = 0;
    ((u8 *)obj)[0x2E] = 0;
    value = arg0->field03;
    arg0->field04 = value;
    obj->field28 = value;
    obj->field7C = (u8 *)arg0 + 0xC8;
    obj->field10 = func_80038A10;
    arg0->field02 = arg1;
    func_80037D50((u8 *)arg0, arg1);
}
