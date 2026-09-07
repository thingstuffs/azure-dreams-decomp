#include "common.h"

#include "common.h"

typedef void (*FuncPtr)(char *);

extern char *strcpy(char *dst, char *src);
extern char *strcat(char *dst, char *src);
extern char *strrchr(char *s, int c);
extern char D_80083E18[0x100];
extern char D_80071404[];
extern FuncPtr D_800714A4[];
extern s32 D_80081550;
extern s32 D_80081548;
extern s32 D_8008154C;

/* Builds and dispatches a control-coded string, then resets its referenced words. */
void func_8004DF8C(char *text)
{
    char *buffer;
    char *cursor;
    char *text_start;
    u32 word_addr;
    s32 *word_ptr;
    FuncPtr handler;

    cursor = D_80083E18;
    cursor = cursor + 1;
    strcpy(cursor, (D_80083E18[0] = 8, text));
    do { } while (0);
    text_start = cursor;
    ASM_KEEP(text_start);   /* MATCH pin: slus-diff */
    strcat(text_start, D_80071404);
    buffer = D_80083E18;
    cursor = strrchr(buffer, 0);
    *cursor = 0x19;
    cursor = cursor + 1;
    *cursor = 2;
    cursor = cursor - (-1);
    *cursor = 0x1A;
    cursor = cursor + 1;
    word_ptr = &D_80081548;
    word_addr = (u32)word_ptr;
    cursor[1] = (char)(word_addr >> 8);
    cursor[2] = (char)(word_addr >> 16);
    cursor[0] = (char)word_addr;
    cursor[3] = (char)(word_addr >> 24);
    cursor = cursor + 4;
    word_ptr = &D_8008154C;
    word_addr = (u32)word_ptr;
    cursor[1] = (char)(word_addr >> 8);
    cursor[2] = (char)(word_addr >> 16);
    cursor[0] = (char)word_addr;
    cursor[3] = (char)(word_addr >> 24);
    handler = D_800714A4[D_80081550];
    handler(buffer);
    word_ptr[-1] = 0x2300030C;
    D_8008154C = 0x2300040C;
}
