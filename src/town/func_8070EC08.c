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

/* Selects a response from the selector and status flags, updating flags for special cases. */
char *func_80017C08(s32 unused, s32 value, s32 selection, s32 extra)
{
    register s32 selector ASM_REG("$4") = selection;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    /* MATCH: Keep the pass-through arguments in their incoming registers across computed-goto labels. */
    register s32 forward_value ASM_REG("$5") = value;
    register s32 forward_selection ASM_REG("$6") = selection;
    register s32 forward_extra ASM_REG("$7") = extra;
    u32 table_index;
    void **jump_table;
    u32 data_page;
    void *handler;
    static void *const handlers[] = {
        &&L0, &&L1, &&L2, &&L12, &&Ldefault
    };

    table_index = selector - 12;
    if (table_index >= 43) {
        goto Ldefault;
    }
    jump_table = D_80016650;
    ASM_KEEP(jump_table);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    handler = jump_table[table_index];
    goto *handler;

L0:
    data_page = 0x80020000;
    ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(data_page - 0x3FE8);

L1:
    data_page = 0x80020000;
    ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(data_page + 0x2694);

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
        s32 flag_94a_set = func_8001A64C(0x94A);
        if (flag_94a_set == 0) {
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
    data_page = 0x80020000;
    ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(data_page - 0x3000);

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
    data_page = 0x80020000;
    ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(data_page - 0x2C34);

L8:
    data_page = 0x80020000;
    ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(data_page - 0x3930);

L12:
    return func_80016E48(selector, forward_value, forward_selection, forward_extra);

Ldefault:
    data_page = 0x80020000;
    ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    return (char *)(data_page - 0x4EB4);
}
