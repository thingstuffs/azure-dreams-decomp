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

void func_80883004(s32 arg0) {
    u8 *base = D_807007B4;
    TownCallback callback;

    callback = D_80700E4C[0]->func68;
    callback(base, D_807007C0, arg0);
    callback = D_80700E4C[0]->func68;
    callback(base, D_807007C8, D_80700710[0]);
    callback = D_80700E4C[0]->func68;
    callback(base, D_807007D0, D_8070070C[0]);
}
