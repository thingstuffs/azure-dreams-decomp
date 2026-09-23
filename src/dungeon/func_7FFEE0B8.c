#include "common.h"

typedef void (*Callback)(void);

extern void func_8008B9D8(void);
extern void func_8008BA00(void);
extern void *func_8004491C(void *, void *);
extern void func_80033C1C(void *, s32);
extern void func_800375C0(void *, u32);
extern void func_8003DB94(void *, void *, s32);
extern void func_80033D08(void *);

extern u8 D_80033D54;
extern u8 D_80037714;
extern u8 D_800794AC;
extern u32 D_80082ABC;
extern u32 D_800CFB74[];
extern u8 D_800CFC38[];
extern u32 D_800CFC44[];

/* Initialize the object context, callbacks, and display settings for the selected mode. */
void func_8008B818(s32 mode, s32 *list, u8 *init_context, u8 *target_object) {
    u8 *context = init_context;
    u8 *object = target_object;
    u8 *record;
    u8 *transform;
    u8 *display;
    s32 list_value;
    u32 *mode_table;
    u32 mode_entry;


    *(Callback *)(context + 0x10) = func_8008B9D8;
    func_8004491C(context, &D_80033D54);
    transform = *(u8 **)(context + 8);
    display = *(u8 **)(context + 0xC);

    record = context + 0x20;
    list_value = 0;
    if (list != 0) {
        list_value = *list;
    }
    func_80033C1C(object, list_value);
    mode_table = D_800CFB74;
    *(u8 **)(context + 0x20) = object;
    *(u32 *)(object + 0x60) = 2;
    *(u32 *)(record + 4) = 0;
    *(u16 *)(record + 0x66) = (u16)mode;
    mode_entry = mode_table[mode];
    if (mode_entry != 0) {
        *(u8 **)(record + 8) = &D_80037714;
        func_800375C0(record, mode_entry);
    } else {
        *(u8 **)(record + 8) = 0;
    }
    *(u16 *)(record + 0x60) = 0;
    *(u32 *)(display + 0xC) = 0x00808080;
    if ((u32)(mode - 9) < 2U) {
        func_8003DB94(display, &D_800794AC, 0);
    } else {
        *(u32 *)(display + 8) = 0;
    }
    if (mode == 0) {
        *(s16 *)(transform + 2) = 0x20;
        *(s16 *)(transform + 6) = -0x20;
        *(s16 *)(transform + 0xA) = 0x200;
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
