#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80174A00_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174A00_0_pre;   /* the 0x14 bytes before arg0 in func_80174A00, addressed as arg0[-1] */

typedef struct S_80174A00_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x48];
    s32 unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
} S_80174A00_0;   /* arg0 in func_80174A00 */

typedef struct S_80174A00_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80174A00_1;   /* data in func_80174A00 */



void *func_80174A00(void *arg0, u16 arg1, u16 arg2, s16 arg3) {
    void *head = arg0;

    arg0 = (void *)(((S_80174A00_0 *)arg0)->unk_5C + 0x20);
    while (arg0 != head) {
        S_80174A00_1 *data = ((S_80174A00_0_pre *)arg0)[-1].unk_00;
        void *result = arg0 - 0x20;
        s16 value;

        if ((data->unk_24 == arg1) &&
            (data->unk_25 == arg2) &&
            (value = ((S_80174A00_0 *)arg0)->unk_88, value <= arg3 + 0x20) &&
            (value >= arg3 - 0x20) &&
            ((u32)(((S_80174A00_0 *)arg0)->unk_13 - 0x33) < 4)) {
            return result;
        }
        arg0 = (void *)(((S_80174A00_0 *)arg0)->unk_5C + 0x20);
    }
    return NULL;
}
