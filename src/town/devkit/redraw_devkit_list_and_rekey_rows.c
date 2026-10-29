/* Relinked copy of town/func_808816D8 (func_808816D8.c); the busy-flag store names this copy's flag 0x807007B0 (twin 0x80700740), otherwise retail differs only at relocation sites. */
#include "common.h"
#include "town/devkit.h"

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

typedef struct Func808816D8Rec {
    u8 tag;
    u8 pad1[0x13];
} Func808816D8Rec;

extern s32 D_807007B0[3];
extern Func808816D8Callbacks *devkit_list_methods[3];
extern Func808816D8Owner *D_80700E40[3];
extern s32 * D_80700E48[];
extern u8 D_807007D4[16];
extern u8 D_807007FC[16];
extern u8 D_80700774[16];
extern void shift_index_and_add_offset(void);


/* Devkit list redraw: raise the busy flag, rebuild the list and re-key every row. */
void redraw_devkit_list_and_rekey_rows(void) {
    u8 *row_cursor;
    u8 *row_base;

    if (D_807007B0[0] != 0) {
        devkit_list_methods[0]->func68(D_807007D4, D_807007FC, 0x4B);
        devkit_list_methods[0]->func74(1);
    }
    *(s32 *)0x807007B0 = 1;
    shift_index_and_add_offset();
    D_80700E40[0]->data = D_80700774;
    row_base = D_80700E40[0]->data;
    {
        s32 limit;
        s32 check;
        s32 sentinel;
        s32 i;
        Func808816D8Rec *rec;
        check = row_base[1];
        limit = 0x80;
        if (check != limit) {
            sentinel = 0x80;
            rec = (Func808816D8Rec *)(row_base + 1);
            i = 0;
            do {
                *(s32 *)((u8 *)&rec[i] + 0xB) = D_80700E48[0][*(s32 *)((u8 *)&rec[i] + 0xB)];
                i++;
            } while (rec[i].tag != sentinel);
        }
    }
}
