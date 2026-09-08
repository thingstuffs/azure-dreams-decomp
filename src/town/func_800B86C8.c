#include "common.h"

extern void func_8004E5A0(s32, s32, void *);
extern void func_8004E69C(void *);
extern void strcat(void *, const void *);
extern s32 func_800B5E10(s32);
extern s32 func_8004AC18(s32);
extern void func_800B5264(s32, s32, s32, s32, s32);
extern void func_800B53BC(s32, const void *, s32, s32, s32);
extern void *func_800B544C(void *, void *);
extern void *func_800B557C(void *, void *);

extern s32 D_80089308[2];
extern u8 D_80089310[8];
extern u8 D_80089318[8];
extern u8 D_8008931C[8];
extern u8 D_80089324[8];
extern u8 D_80089340[8];

/* Formats and draws entity stats and detail text in the panel. */
void func_800B5E28(void *entity, void *panel) {
    u8 number_text[0x40];
    u8 text[0x40];
    s32 display_value;
    s32 text_style;

    memcpy(text, D_80089308, 5);
    func_8004E5A0(*((u8 *)entity + 0x11), 2, &number_text);
    func_8004E69C(&number_text);
    strcat(&text, &number_text);
    strcat(&text, D_80089310);
    strcat(&text, D_80089318);

    func_8004E5A0(*((u8 *)entity + 0x28), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, D_8008931C);

    func_8004E5A0(*((u8 *)entity + 0x29), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, D_80089340);

    func_8004E5A0(*((u8 *)entity + 0x25), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, D_8008931C);

    func_8004E5A0(*((u8 *)entity + 0x66), 3, &number_text);
    strcat(&text, &number_text);

    func_800B53BC(*(s32 *)((u8 *)panel + 0x14), &text, 0, 0x6C, 0x98);
    display_value = func_8004AC18(func_800B5E10(*((u8 *)entity + 0x13)));
    text_style = 0;
    if (*((u8 *)entity + 0x43) >= 0x41) {
        text_style = 3;
    }
    func_800B5264(*(s32 *)((u8 *)panel + 0x18), display_value, text_style, 0x68, 0x98);
    func_800B53BC(*(s32 *)((u8 *)panel + 0x4C), D_80089324, 0, 0x48, 0xB8);
    func_800B53BC(*(s32 *)((u8 *)panel + 0x1C), func_800B544C(&text, entity), 0, 0x48, 0xC8);
    func_800B53BC(*(s32 *)((u8 *)panel + 0x48), func_800B557C(&text, entity), 0, 0x48, 0xB8);
}
