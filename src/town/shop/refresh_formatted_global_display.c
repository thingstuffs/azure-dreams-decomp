#include "common.h"

typedef struct {
    u8 pad0[8];
    u8 *data;
    u8 padC[0x44];
    void **handle;
} Func800B40ACArg;

extern s32 town_money;
extern u8 D_800D160C[];

#define READ_D_80012D5C() (*(s32 *)0x80012D5C)

extern void func_8004E5A0(s32 value, s32 width, u8 *dst);
extern u8 *remap_flagged_string_bytes(u8 *text);
extern u8 *strcat(u8 *dst, const u8 *src);
extern void flag_optional_object_for_removal(void *value);
extern void *build_positioned_text_glyphs(u8 *data, u8 *text, s32 style);

/* Refreshes the display with the formatted global value and its suffix. */
void refresh_formatted_global_display(Func800B40ACArg *display) {
    u8 text[32];
    func_8004E5A0(READ_D_80012D5C(), 10, text);
    remap_flagged_string_bytes(text);
    strcat(text, D_800D160C);
    flag_optional_object_for_removal(*display->handle);
    *display->handle = build_positioned_text_glyphs(display->data + 0x48, text, 0);
}
