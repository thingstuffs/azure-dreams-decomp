#include "common.h"

typedef void (*TownCallback)(void *, void *, s32);

typedef struct {
    u8 pad68[0x68];
    TownCallback func68;
} TownCallbackOwner;

extern u8 D_807007B4[];
extern u8 D_807007C0[];
extern u8 D_807007C8[];
extern u8 D_807007D0[];
extern TownCallbackOwner *D_80700E4C[];
extern s32 D_80700710[];
extern s32 D_8070070C[];

/* Invoke the town callback for three entries using the supplied and stored values. */
void func_80883004(s32 first_value) {
    u8 *callback_data = D_807007B4;
    TownCallback callback;

    callback = D_80700E4C[0]->func68;
    callback(callback_data, D_807007C0, first_value);
    callback = D_80700E4C[0]->func68;
    callback(callback_data, D_807007C8, D_80700710[0]);
    callback = D_80700E4C[0]->func68;
    callback(callback_data, D_807007D0, D_8070070C[0]);
}
