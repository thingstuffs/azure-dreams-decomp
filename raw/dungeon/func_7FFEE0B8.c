#include "common.h"

typedef void (*Callback)(void);

extern void func_8008B9D8(void);
extern void func_8008BA00(void);
extern void *func_8004491C(void *, void *);
extern void func_80033C1C(void *, s32);
extern void func_800375C0(void *);
extern void func_8003DB94(void *, void *, s32);
extern void func_80033D08(void *);

extern u8 D_80033D54;
extern u8 D_80037714;
extern u8 D_800794AC;
extern u32 D_80082ABC;
extern u32 D_800CFB74[];
extern u8 D_800CFC38[];
extern u32 D_800CFC44[];

void func_8008B818(s32 arg0, s32 *arg1, u8 *arg2, u8 *arg3) {
    register s32 mode ASM_REG("$21") = arg0;
    register s32 *list ASM_REG("$22") = arg1;
    register u8 *context ASM_REG("$17") = arg2;
    register u8 *object ASM_REG("$19") = arg3;
    register u8 *record ASM_REG("$16");
    register u8 *s4 ASM_REG("$20");
    register u8 *s2 ASM_REG("$18");
    s32 list_value;
    u32 *table_base;
    register u32 table_word ASM_REG("$5");
    register u32 object_state ASM_REG("$2");

    ASM_KEEP4_NV(mode, list, context, object);

    *(Callback *)(context + 0x10) = func_8008B9D8;
    func_8004491C(context, &D_80033D54);
    s4 = *(u8 **)(context + 8);
    s2 = *(u8 **)(context + 0xC);

    record = context + 0x20;
    list_value = 0;
    if (list != 0) {
        list_value = *list;
    }
    func_80033C1C(object, list_value);
    object_state = 2;
    table_base = D_800CFB74;
    *(u8 **)(context + 0x20) = object;
    *(u32 *)(object + 0x60) = object_state;
    ASM_SET(object_state);
    *(u32 *)(record + 4) = 0;
    *(u16 *)(record + 0x66) = (u16)mode;
    table_word = table_base[mode];
    if (table_word != 0) {
        *(u8 **)(record + 8) = &D_80037714;
        func_800375C0(record);
    } else {
        ASM_SET(table_word);
        *(u8 **)(record + 8) = 0;
    }
    *(u16 *)(record + 0x60) = 0;
    *(u32 *)(s2 + 0xC) = 0x00808080;
    if ((u32)(mode - 9) < 2U) {
        func_8003DB94(s2, &D_800794AC, 0);
    } else {
        *(u32 *)(s2 + 8) = 0;
    }
    if (mode == 0) {
        *(s16 *)(s4 + 2) = 0x20;
        *(s16 *)(s4 + 6) = -0x20;
        *(s16 *)(s4 + 0xA) = 0x200;
    }
    if (mode == 10) {
        *(u32 *)(record + 0x74) = 0;
        D_80082ABC = *(u8 *)(*(u8 **)(record + 0x7C));
    }
    *(Callback *)(record + 0x68) = func_8008BA00;
    *(s16 *)(record + 0x64) = (s16)(s8)D_800CFC38[mode];
    *(u32 *)(record + 0x6C) = D_800CFC44[mode];
    if (mode == 9) {
        func_80033D08(record);
    }
}
