/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef void (*Callback3)(void *, void *, s32);
typedef void (*Callback1)(s32);

typedef struct {
    u8 pad68[0x68];
    Callback3 callback68;
    u8 pad6c[8];
    Callback1 callback74;
} CallbackTable;

typedef struct {
    u8 pad10[0x10];
    void *field10;
} GlobalState;

extern s32 D_80700B0C;
extern u8 D_80700B94[];
extern u8 D_80700BBC[];
extern s32 D_80700B04[];
extern s32 *D_807013B0[];
extern CallbackTable *D_807013B4[];
extern GlobalState *D_807013A8[];
extern void func_80701274(void);

/* Selects a record list and resolves its indices through the global lookup table. */
void func_80880298(s32 list_index) {
    u8 *record_tag;
    void *records;

    if (D_80700B0C != 0) {
        D_807013B4[0]->callback68(D_80700B94, D_80700BBC, 0x59);
        D_807013B4[0]->callback74(1);
    }
    D_80700B0C = 1;
    func_80701274();
    D_807013A8[0]->field10 = (void *)D_80700B04[list_index];
    records = D_807013A8[0]->field10;
    if (((u8 *)records)[1] != 0x80) {
        s32 end_tag = 0x80;
        record_tag = records + 1;
        do {
            *(volatile s32 *)(record_tag + 0xB) = D_807013B0[0][*(volatile s32 *)(record_tag + 0xB)];
            record_tag += 0x14;
        } while (*record_tag != end_tag);
    }
}
