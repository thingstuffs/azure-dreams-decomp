#include "common.h"


typedef void (*Callback)(u32);

typedef struct S_806A9100_0 {
    void * unk_00;
} S_806A9100_0;   /* D_80016000 in func_806A9100 */

typedef struct S_806A9100_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_806A9100_1;   /* ((S_806A9100_0 *)D_80016000)->unk_00 in func_806A9100 */


extern u8 D_80016000[];
extern u8 D_80017420[];
extern void *D_800174D4[];

/* Sets D_800174D4[0] to D_80017420 and invokes both object callbacks with 1. */
void func_806A9100(void) {
    Callback firstCallback;

    firstCallback = (*(Callback *)((u8 *)(((S_806A9100_1 *)(((S_806A9100_0 *)D_80016000)->unk_00))->unk_20) + 0x28C));
    D_800174D4[0] = D_80017420;
    firstCallback(1);
    (*(Callback *)((u8 *)(((S_806A9100_1 *)(((S_806A9100_0 *)D_80016000)->unk_00))->unk_20) + 0x290))(1);
}
