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

/* Polls status with bounded retries and dispatches the corresponding context update. */
void func_80027584(void *state) {
    s32 retry_status;
    s32 status;
    s32 retry_count;
    void *context;

    retry_count = 0;
    retry_status = 5;
    do {
        status = func_80021A84(((S_80027584_0 *)state)->unk_0C);
        if (status != retry_status) {
            break;
        }
    } while (retry_count++ < 6);

    ((S_80027584_0 *)state)->unk_38 = 0;
    func_80020984();
    if (status == 1) {
        context = (u8 *)state - 0x20;
        ((S_80027584_0 *)state)->unk_2C = D_8002789C;
        func_80023054(context);
        ((S_80027584_0_pre *)state)[-1].unk_00 = D_800274D8;
    } else if (status == 4) {
        context = (u8 *)state - 0x20;
        ((S_80027584_0 *)state)->unk_2C = D_8002789C;
        func_80022E9C(context);
        ((S_80027584_0_pre *)state)[-1].unk_00 = D_800274A8;
    } else {
        context = (u8 *)state - 0x20;
        ((S_80027584_0 *)state)->unk_2C = D_8002789C;
        func_8002302C(context);
        ((S_80027584_0_pre *)state)[-1].unk_00 = D_800274D8;
    }
}
