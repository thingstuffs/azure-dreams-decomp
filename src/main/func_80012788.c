#include "common.h"

typedef struct S_80025788_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_80025788_0_pre;   /* the 0x10 bytes before arg0 in func_80025788, addressed as arg0[-1] */

typedef struct S_80025788_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x8];
    void * unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
} S_80025788_0;   /* arg0 in func_80025788 */

typedef struct S_80025788_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80025788_1;   /* cursor in func_80025788 */



extern void func_80020984(void);
extern s32 func_8002219C(s32 arg0);
extern void func_8002316C(void *arg0);
extern void func_80024298(s32 arg0);
extern u8 D_80024F7C[];
extern u8 D_8002593C[];

void func_80025788(void *arg0) {
    u8 *cursor;
    s32 count;

    if (((S_80025788_0 *)arg0)->unk_38 != 0) {
        ((S_80025788_0_pre *)arg0)[-1].unk_00 = D_8002593C;
        return;
    }

    if (func_8002219C(((S_80025788_0 *)arg0)->unk_28) != 0) {
        ((S_80025788_0_pre *)arg0)[-1].unk_00 = D_8002593C;
        count = 0;
        cursor = arg0;
        do {
            func_80024298(((S_80025788_1 *)cursor)->unk_04);
            cursor += 4;
            count++;
        } while (count < 5);
    } else {
        ((S_80025788_0 *)arg0)->unk_34 = D_8002593C;
        func_8002316C((u8 *)arg0 - 0x20);
        ((S_80025788_0_pre *)arg0)[-1].unk_00 = D_80024F7C;
    }

    func_80020984();
    ((S_80025788_0 *)arg0)->unk_40 = 0;
}
