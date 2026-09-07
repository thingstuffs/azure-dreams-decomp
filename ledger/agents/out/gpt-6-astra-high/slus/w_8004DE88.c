#include "common.h"

typedef void (*MessageHandler)(char *buffer);

extern char *strcpy(char *dst, const char *src);
extern char *strrchr(const char *str, s32 ch);
extern u32 D_80083D88[0x24];
extern MessageHandler D_800714A4[];
extern s32 D_80081550;

/* Builds and dispatches a message with control codes and two embedded addresses. */
void func_8004DE88(char *message)
{
    char *cursor;
    u32 address;
    register char *buffer ASM_REG("$17");   /* MATCH pin: slus-diff */

    buffer = (char *)0x80080000;
    ASM_KEEP_NV(buffer);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    cursor = buffer + 0x3E18;
    ASM_KEEP_NV(cursor);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    buffer[0x3E18] = 8;
    strcpy(cursor + 1, message);

    buffer += 0x3E18;
    cursor = strrchr(buffer, 0);
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
