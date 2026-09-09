#include "common.h"

extern void *func_8003FC64(s32);
extern s32 func_80028284(void *, s32);
extern s32 func_80027FCC(s32);
extern void func_8002823C(void *, s32, s32);
extern void func_8004491C(void *, void *);
extern void func_80028620(void *);
extern void func_8004B248(void *);
extern u8 D_8004CAA0[];
extern s32 D_800814A0[];

typedef struct {
    u8 pad00[0x84];
    s32 field84;
    s32 field88;
} Sub8181345C;

typedef struct {
    u8 pad00[0x0C];
    void *field0C;
    u8 pad10[0x0E];
    u16 flags;
    Sub8181345C sub;
} Obj8181345C;

/* Allocate and initialize a child object, marking allocation failure for cleanup. */
void *func_8002845C(s32 parent_obj, s32 descriptor_value)
{
    Obj8181345C *obj;
    Sub8181345C *sub;

    obj = func_8003FC64(0);
    sub = &obj->sub;
    if (obj != 0) {
        if (func_80028284(sub, 15) != 0) {
            obj->field0C = (u8 *)obj + 0x98;
            sub->field84 = func_80027FCC(sub->field88);
            func_8002823C(sub, parent_obj, descriptor_value);
            func_8004491C(obj, D_8004CAA0);
            func_80028620(obj);
        } else {
            func_8004B248((u8 *)obj + 0xAC);
            obj->flags |= 0x8000;
            obj = 0;
            D_800814A0[0] |= 0x8000;
        }
    }
    return obj;
}
