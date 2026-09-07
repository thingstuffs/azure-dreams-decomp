#include "common.h"

typedef struct S_800A2000_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800A2000_0;   /* obj in func_800A2000 */

typedef struct S_800A2000_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
} S_800A2000_1;   /* payload in func_800A2000 */

typedef struct S_800A2000_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800A2000_2;   /* display in func_800A2000 */



extern void *func_8003FD64();
extern u8 D_80083160[];

void *func_800A2000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *obj = func_8003FD64(0x136, arg0 - 0x20);
    S_800A2000_2 *display;
    S_800A2000_1 *payload;

    if (obj == 0) {
        return 0;
    }
    display = ((S_800A2000_0 *)obj)->unk_0C;
    ((S_800A2000_0 *)obj)->unk_10 = arg4;
    ((S_800A2000_0 *)obj)->unk_20 = arg5;
    payload = (u8 *)obj + 0x20;
    payload->unk_10 = arg0;
    payload->unk_14 = arg2;
    payload->unk_20 = arg3;
    payload->unk_40 = arg1;
    display->unk_20 = 0x1000;
    display->unk_1E = 0x1000;
    display->unk_1C = 0x1000;
    display->unk_12 = 0;
    display->unk_14 = 0;
    display->unk_10 = 0;
    display->unk_0C = D_80083160[0xA8];
    display->unk_0D = D_80083160[0xA9];
    display->unk_0E = D_80083160[0xAA];
    display->unk_14 = 0;
    return obj;
}
