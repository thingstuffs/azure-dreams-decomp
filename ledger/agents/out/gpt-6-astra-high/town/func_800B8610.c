#include "common.h"

extern s8 *strcat(u8 *dst, const u8 *src);
extern void func_800B5264(s32 arg0, const u8 *arg1, s32 arg2, s32 arg3,
                         s32 arg4);
extern u8 *func_800B5D30(void *arg0);

extern s32 D_800892C0[3];
extern u8 D_8008933C[];

/* Builds and displays an entry's formatted text. */
void func_800B5D70(void *entry, void *display) {
    u8 text[64];

    memcpy(text, D_800892C0, 5);
    strcat(text, (u8 *)entry + 0x34);
    strcat(text, D_8008933C);
    strcat(text, func_800B5D30(entry));
    func_800B5264(*(s32 *)((u8 *)display + 0x10), text, 0, 0x47, 0x88);
}
