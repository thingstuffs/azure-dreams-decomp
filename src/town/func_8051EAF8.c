#include "common.h"


extern s8 D_80016000[];

typedef void (*Callback)(s32);


typedef struct S_8051EAF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8051EAF8_0;   /* position in func_8051EAF8 */

/* Invokes the object's callback with 1, then checks its position against the target region. */
s32 func_8051EAF8(void) {
    void *currentObject;
    S_8051EAF8_0 *position;
    Callback callback;
    s32 x;
    s32 y;

    currentObject = *(void **)D_80016000;
    currentObject = (*(void * *)((u8 *)currentObject + 0x20));
    callback = (*(Callback *)((u8 *)currentObject + 0x248));
    callback(1);

    currentObject = *(void **)D_80016000;
    position = (*(void * *)((u8 *)currentObject + 0x1C));
    x = position->unk_04;
    y = position->unk_08;
    if ((u32)(x - 0x341) < 0x5FU) {
        if (y < 0x3F0) {
            return 1;
        }
    }
    return 0;
}
