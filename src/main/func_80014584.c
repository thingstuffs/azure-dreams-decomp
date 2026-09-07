#include "common.h"

typedef struct S_80027584_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_80027584_0_pre;   /* the 0x10 bytes before arg0 in func_80027584, addressed as arg0[-1] */

typedef struct S_80027584_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x1C];
    void * unk_2C;
    u8 pad_30[0x8];
    s32 unk_38;
} S_80027584_0;   /* arg0 in func_80027584 */



extern void func_80020984(void);
extern s32 func_80021A84(s32 arg0);
extern void func_80022E9C(void *arg0);
extern void func_8002302C(void *arg0);
extern void func_80023054(void *arg0);
extern u8 D_800274A8[];
extern u8 D_800274D8[];
extern u8 D_8002789C[];

void func_80027584(void *arg0) {
    s32 state_five;
    s32 result;
    s32 count;
    void *context;

    count = 0;
    state_five = 5;
    do {
        result = func_80021A84(((S_80027584_0 *)arg0)->unk_0C);
        if (result != state_five) {
            break;
        }
    } while (count++ < 6);

    ((S_80027584_0 *)arg0)->unk_38 = 0;
    func_80020984();
    if (result == 1) {
        context = (u8 *)arg0 - 0x20;
        ((S_80027584_0 *)arg0)->unk_2C = D_8002789C;
        func_80023054(context);
        ((S_80027584_0_pre *)arg0)[-1].unk_00 = D_800274D8;
    } else if (result == 4) {
        context = (u8 *)arg0 - 0x20;
        ((S_80027584_0 *)arg0)->unk_2C = D_8002789C;
        func_80022E9C(context);
        ((S_80027584_0_pre *)arg0)[-1].unk_00 = D_800274A8;
    } else {
        context = (u8 *)arg0 - 0x20;
        ((S_80027584_0 *)arg0)->unk_2C = D_8002789C;
        func_8002302C(context);
        ((S_80027584_0_pre *)arg0)[-1].unk_00 = D_800274D8;
    }
}
