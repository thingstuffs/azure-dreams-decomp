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
extern char *func_80016E48(s32, s32, s32, s32);

char *func_80017C08(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register s32 selector ASM_REG("$4") = arg2;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    /* MATCH: Keep the pass-through arguments in their incoming registers across computed-goto labels. */
    register s32 passthru1 ASM_REG("$5") = arg1;
    register s32 passthru2 ASM_REG("$6") = arg2;
    register s32 passthru3 ASM_REG("$7") = arg3;
    u32 index;
    void **table;
    u32 page;
    void *target;
    static void *const keepalive[] = {
        &&L0, &&L1, &&L2, &&L12, &&Ldefault
    };

    index = selector - 12;
    if (index >= 43) {
        goto Ldefault;
    }
    ASM_KEEP(selector);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    table = D_80016650;
    ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    target = table[index];
    goto *target;

L0:
    page = 0x80020000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(page - 0x3FE8);

L1:
    page = 0x80020000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
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
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
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
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(page - 0x2C34);

L8:
    page = 0x80020000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(page - 0x3930);

L12:
    return func_80016E48(selector, passthru1, passthru2, passthru3);

Ldefault:
    page = 0x80020000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(page - 0x4EB4);
}
