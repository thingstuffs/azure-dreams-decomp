#include "common.h"


extern s8 D_80016000[];

typedef void (*Callback)(s32);


typedef struct S_8051EAF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8051EAF8_0;   /* position in func_8051EAF8 */

s32 func_8051EAF8(void) {
    void *object;
    S_8051EAF8_0 *position;
    Callback callback;
    s32 x;
    s32 y;

    object = *(void **)D_80016000;
    object = (*(void * *)((u8 *)object + 0x20));
    callback = (*(Callback *)((u8 *)object + 0x248));
    callback(1);

    object = *(void **)D_80016000;
    position = (*(void * *)((u8 *)object + 0x1C));
    x = position->unk_04;
    y = position->unk_08;
    if ((u32)(x - 0x341) < 0x5FU) {
        if (y < 0x3F0) {
            return 1;
        }
    }
    return 0;
}

/* MECHANISM: The global is an established byte array, so both pointer loads use
   the D_80016000 hi/lo address form. Separate reloads straddle the indirect call;
   sibling scalar locals eagerly load both fields; nested explicit returns encode
   the retail two-branch result CFG without boolean-materialization moves. */
