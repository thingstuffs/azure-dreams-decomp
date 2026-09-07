#include "common.h"

typedef struct S_80407E64_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_80407E64_0_pre;   /* the 0x10 bytes before arg0 in func_80407E64, addressed as arg0[-1] */

typedef struct S_80407E64_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x1C];
    void * unk_2C;
    u8 pad_30[0x8];
    s32 unk_38;
} S_80407E64_0;   /* arg0 in func_80407E64 */



extern void func_80400908(void);
extern s32 func_80401B30(s32 arg0);
extern void func_804030F4(void *arg0);
extern void func_80403284(void *arg0);
extern void func_804032AC(void *arg0);
extern u8 D_80407D90[];
extern u8 D_80407DB8[];
extern u8 D_804081AC[];

void func_80407E64(void *arg0) {
    s32 state_five;
    s32 result;
    s32 count;
    void *context;

    count = 0;
    state_five = 5;
    do {
        result = func_80401B30(((S_80407E64_0 *)arg0)->unk_0C);
        if (result != state_five) {
            break;
        }
    } while (count++ < 6);

    ((S_80407E64_0 *)arg0)->unk_38 = 0;
    func_80400908();
    if (result == 1) {
        context = (u8 *)arg0 - 0x20;
        ((S_80407E64_0 *)arg0)->unk_2C = D_804081AC;
        func_804032AC(context);
        ((S_80407E64_0_pre *)arg0)[-1].unk_00 = D_80407DB8;
    } else if (result == 4) {
        context = (u8 *)arg0 - 0x20;
        ((S_80407E64_0 *)arg0)->unk_2C = D_804081AC;
        func_804030F4(context);
        ((S_80407E64_0_pre *)arg0)[-1].unk_00 = D_80407D90;
    } else {
        context = (u8 *)arg0 - 0x20;
        ((S_80407E64_0 *)arg0)->unk_2C = D_804081AC;
        func_80403284(context);
        ((S_80407E64_0_pre *)arg0)[-1].unk_00 = D_80407DB8;
    }
}
