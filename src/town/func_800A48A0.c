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

/* Allocate an object and initialize its payload, display transform, and color. */
void *func_800A2000(s32 object_key, s32 payload_value, s32 payload_param, s32 payload_halfword, s32 object_param, s32 object_value) {
    void *obj = func_8003FD64(0x136, object_key - 0x20);
    S_800A2000_2 *display;
    S_800A2000_1 *payload;

    if (obj == 0) {
        return 0;
    }
    display = ((S_800A2000_0 *)obj)->unk_0C;
    ((S_800A2000_0 *)obj)->unk_10 = object_param;
    ((S_800A2000_0 *)obj)->unk_20 = object_value;
    payload = (u8 *)obj + 0x20;
    payload->unk_10 = object_key;
    payload->unk_14 = payload_param;
    payload->unk_20 = payload_halfword;
    payload->unk_40 = payload_value;
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
