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

/* Polls the status and selects the corresponding context update and data. */
void func_80407E64(void *state) {
    s32 retry_status;
    s32 status;
    s32 retries;
    void *context;

    retries = 0;
    retry_status = 5;
    do {
        status = func_80401B30(((S_80407E64_0 *)state)->unk_0C);
        if (status != retry_status) {
            break;
        }
    } while (retries++ < 6);

    ((S_80407E64_0 *)state)->unk_38 = 0;
    func_80400908();
    if (status == 1) {
        context = (u8 *)state - 0x20;
        ((S_80407E64_0 *)state)->unk_2C = D_804081AC;
        func_804032AC(context);
        ((S_80407E64_0_pre *)state)[-1].unk_00 = D_80407DB8;
    } else if (status == 4) {
        context = (u8 *)state - 0x20;
        ((S_80407E64_0 *)state)->unk_2C = D_804081AC;
        func_804030F4(context);
        ((S_80407E64_0_pre *)state)[-1].unk_00 = D_80407D90;
    } else {
        context = (u8 *)state - 0x20;
        ((S_80407E64_0 *)state)->unk_2C = D_804081AC;
        func_80403284(context);
        ((S_80407E64_0_pre *)state)[-1].unk_00 = D_80407DB8;
    }
}
