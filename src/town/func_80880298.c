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

void func_80880298(s32 arg0) {
    u8 *var_a0;
    void *temp_a0;

    if (D_80700B0C != 0) {
        D_807013B4[0]->callback68(D_80700B94, D_80700BBC, 0x59);
        D_807013B4[0]->callback74(1);
    }
    D_80700B0C = 1;
    func_80701274();
    D_807013A8[0]->field10 = (void *)D_80700B04[arg0];
    temp_a0 = D_807013A8[0]->field10;
    if (((u8 *)temp_a0)[1] != 0x80) {
        s32 limit = 0x80;
        var_a0 = temp_a0 + 1;
        do {
            *(volatile s32 *)(var_a0 + 0xB) = D_807013B0[0][*(volatile s32 *)(var_a0 + 0xB)];
            var_a0 += 0x14;
        } while (*var_a0 != limit);
    }
}
