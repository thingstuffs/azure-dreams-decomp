#include "common.h"

typedef void (*PrintValue)(char *format, char *name, s32 value);

typedef struct PrintInterface {
    u8 pad_00[0x68];
    PrintValue print_value;
} PrintInterface;

extern PrintInterface *D_807030B8;
extern char D_80701FCC[];
extern char D_80701FD8[];
extern char D_80701FE0[];
extern char D_80701FE8[];
extern s32 D_80701DC4;
extern s32 D_80701DC8;

/* Prints the kind and two global values with their labels. */
void func_80701FEC(s32 kind)
{
    D_807030B8->print_value(D_80701FCC, D_80701FD8, kind);
    D_807030B8->print_value(D_80701FCC, D_80701FE0, D_80701DC8);
    D_807030B8->print_value(D_80701FCC, D_80701FE8, D_80701DC4);
}
