#include "common.h"

typedef void (*MessageHandler)(char *buffer);

extern char *strcpy(char *dst, const char *src);
extern char *strrchr(const char *str, s32 ch);
extern u32 D_80083D88[0x24];
extern MessageHandler D_800714A4[];
extern s32 D_80081550;

void func_8004DE88(char *arg0)
{
    register char *cursor ASM_REG("$4");
    register u32 address ASM_REG("$2");
    register char *buffer ASM_REG("$17");

    buffer = (char *)0x80080000;
    ASM_KEEP_NV(buffer);
    cursor = buffer + 0x3E18;
    ASM_KEEP_NV(cursor);
    buffer[0x3E18] = 8;
    strcpy(cursor + 1, arg0);

    ASM_KEEP(buffer);
    buffer += 0x3E18;
    cursor = strrchr(buffer, 0);
    ASM_KEEP(cursor);
    *cursor++ = 0x19;
    *cursor++ = 2;
    *cursor++ = 0x1A;

    address = (u32)D_80083D88;
    cursor[1] = address >> 8;
    cursor[2] = address >> 16;
    cursor[0] = address;
    cursor[3] = address >> 24;
    cursor += 4;

    address += 4;
    cursor[1] = address >> 8;
    cursor[0] = address;
    cursor[2] = address >> 16;
    cursor[3] = address >> 24;

    D_800714A4[D_80081550](buffer);
    D_80083D88[0] = 0x2300030C;
    D_80083D88[1] = 0x2300040C;
}
