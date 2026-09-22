#include "common.h"

typedef struct Func808816D8Callbacks {
    u8 pad68[0x68];
    void (*func68)(void *, void *, s32);
    u8 pad6C[8];
    void (*func74)(s32);
} Func808816D8Callbacks;

typedef struct Func808816D8Owner {
    u8 pad10[0x10];
    u8 *data;
} Func808816D8Owner;

extern s32 D_80700740[3];
extern Func808816D8Callbacks *D_8070100C[3];
extern Func808816D8Owner *D_80701000[3];
extern s32 * volatile D_80701008[];
extern u8 D_807007A8[16];
extern u8 D_807007D0[16];
extern u8 D_80700704[16];
extern void func_80700EB4(void);


/* Devkit list redraw: raise the busy flag, rebuild the list and re-key every row. */
void func_808816D8(void) {
    u8 *row_cursor;
    u8 *row_base;

    if (D_80700740[0] != 0) {
        D_8070100C[0]->func68(D_807007A8, D_807007D0, 0x4B);
        D_8070100C[0]->func74(1);
    }
    {
        *(s32 *)0x80700740 = 1;
    }
    func_80700EB4();
    D_80701000[0]->data = D_80700704;
    row_base = D_80701000[0]->data;
    {
        s32 limit;
        s32 check;
        s32 sentinel;
        check = row_base[1];
        limit = 0x80;
        if (check != limit) {
            sentinel = 0x80;
            row_cursor = row_base + 1;
            loop_0: {
                *(volatile s32 *)(row_cursor + 0xB) = D_80701008[0][*(volatile s32 *)(row_cursor + 0xB)];
                row_cursor += 0x14;
            } if (*row_cursor != sentinel) goto loop_0;
        }
    }
}
