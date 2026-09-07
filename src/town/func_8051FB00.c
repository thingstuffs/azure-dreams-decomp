#include "common.h"

typedef void (*TownCall0)(s32);
typedef void (*TownCall1)(void *);

typedef struct {
    u8 pad_0000[0x218];
    TownCall1 call_0218;
    u8 pad_021c[0x124];
    TownCall0 call_0340;
} TownDispatch;

extern void func_80018A64(s32 arg0);
extern void func_800172BC(void);
extern u8 D_80010000[];
extern u8 D_800190B8[];

void func_80017300(void) {
    TownDispatch *dispatch;

    func_80018A64(0x5C2);
    func_80018A64(0x5BF);
    func_800172BC();

    dispatch = *(TownDispatch **)(*(u8 **)(D_80010000 + 0x6000) + 0x20);
    dispatch->call_0340(0);

    dispatch = *(TownDispatch **)(*(u8 **)(D_80010000 + 0x6000) + 0x20);
    dispatch->call_0218(D_800190B8);
}
