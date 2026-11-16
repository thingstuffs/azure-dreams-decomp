#include "common.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"
#include "town/devkit/runtime_callback_owner_data.h"

typedef struct Func808816D8Owner {
    u8 pad10[0x10];
    u8 *data;
} Func808816D8Owner;

typedef struct Func808816D8Rec {
    u8 tag;
    u8 pad1[0x13];
} Func808816D8Rec;

extern s32 D_80700740[3];
extern Func808816D8Owner *D_80701000[3];
extern s32 * D_80701008[];
extern u8 D_807007A8[16];
extern u8 D_807007D0[16];
extern u8 D_80700704[16];


/* Devkit list redraw: raise the busy flag, rebuild the list and re-key every row. */
void redraw_busy_entry_list(void) {
    u8 *row_cursor;
    u8 *row_base;

    if (D_80700740[0] != 0) {
        devkit_runtime_callback_owner[0]->func68(D_807007A8, D_807007D0, 0x4B);
        devkit_runtime_callback_owner[0]->func74(1);
    }
    *(s32 *)0x80700740 = 1;
    func_80700EB4();
    D_80701000[0]->data = D_80700704;
    row_base = D_80701000[0]->data;
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
                *(s32 *)((u8 *)&rec[i] + 0xB) = D_80701008[0][*(s32 *)((u8 *)&rec[i] + 0xB)];
                i++;
            } while (rec[i].tag != sentinel);
        }
    }
}
