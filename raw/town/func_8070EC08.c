#include "common.h"

extern void *D_80016650[43];

extern char D_8001B14C[];
extern char D_8001C018[];
extern char D_8001C6D0[];
extern char D_8001D000[];
extern char D_8001D3CC[];
extern char D_80022694[];

extern s32 func_8001A8EC(s32);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern char *func_80016E48(void);

char *func_80017C08(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 selector ASM_REG("$4") = arg2;
    register u32 index ASM_REG("$3");
    register void **table ASM_REG("$2");
    register u32 page ASM_REG("$2");
    void *target;
    static void *const keepalive[] = {
        &&L0, &&L1, &&L2, &&L12, &&Ldefault
    };

    index = selector - 12;
    if (index >= 43) {
        goto Ldefault;
    }
    ASM_KEEP(selector);
    ASM_KEEP(index);
    table = D_80016650;
    ASM_KEEP(table);
    target = table[index];
    goto *target;

L0:
    page = 0x80020000;
    ASM_KEEP(page);
    return (char *)(page - 0x3FE8);

L1:
    page = 0x80020000;
    ASM_KEEP(page);
    return (char *)(page + 0x2694);

L2:
    if (func_8001A8EC(6) != 0) {
        func_8001A554(0x93A);
    }
    if (func_8001A8EC(0xB) != 0) {
        func_8001A554(0x93B);
    }
    goto L5;

L5:
    if (func_8001A64C(0x93A) != 0) {
        goto L9;
    }
    if (func_8001A64C(0x93B) != 0) {
        goto L9;
    }
    if (func_8001A64C(0x948) == 0) {
        goto L6;
    }
    {
        s32 status = func_8001A64C(0x94A);
        if (status == 0) {
            goto L7tail;
        }
    }
    goto L6;

L9:
    if (func_8001A64C(0x93A) == 0) {
        goto L10;
    }
    if (func_8001A64C(0x93B) == 0) {
        goto L7tail;
    }

L10:
    if (func_8001A64C(0x93A) != 0) {
        goto L7;
    }
    if (func_8001A64C(0x93B) == 0) {
        goto L7;
    }
    goto L6;

L6:
    func_8001A554(0x948);
    page = 0x80020000;
    ASM_KEEP(page);
    return (char *)(page - 0x3000);

L7:
    if (func_8001A64C(0x93A) == 0) {
        goto L8;
    }
    if (func_8001A64C(0x93B) == 0) {
        goto L8;
    }

L7tail:
    func_8001A554(0x94A);
    func_8001A554(0x12C7);
    page = 0x80020000;
    ASM_KEEP(page);
    return (char *)(page - 0x2C34);

L8:
    page = 0x80020000;
    ASM_KEEP(page);
    return (char *)(page - 0x3930);

L12:
    return func_80016E48();

Ldefault:
    page = 0x80020000;
    ASM_KEEP(page);
    return (char *)(page - 0x4EB4);
}
