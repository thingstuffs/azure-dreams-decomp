#include "common.h"

typedef struct S_80091958_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x2C];
    void * unk_C8;
} S_80091958_0;   /* arg0 in func_80091958 */

typedef struct S_80091958_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80091958_1;   /* &D_80082EB0 in func_80091958 */

typedef struct S_80091958_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80091958_2;   /* arg3 in func_80091958 */

typedef struct S_80091958_3 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80091958_3;   /* ((S_80091958_0 *)arg0)->unk_C8 in func_80091958 */



extern s32 D_80082EB0;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];

void *func_800BA074(s32);

void func_80091958(S_80091958_0 *arg0, s32 arg1, s32 arg2, S_80091958_2 *arg3)
{
    void *temp;

    switch (arg0->unk_9B) {
    case 0:
        temp = func_800BA074(D_80082EB0);
        arg0->unk_C8 = temp;
        if (temp == 0) {
            break;
        }
        arg0->unk_9B++;
    case 1:
        if (((S_80091958_3 *)(arg0->unk_C8))->unk_1E & 0x8000) {
            arg0->unk_C8 = 0;
            arg0->unk_9B++;
        }
        break;
    case 2:
        ((S_80091958_1 *)(&D_80082EB0))->unk_08 = 0;
        if (arg3->unk_1C & 0x100000) {
            arg0->unk_8C = D_8008EAC8;
        } else {
            arg0->unk_8C = &D_8008ACDC;
        }
        break;
    }
}

/* MECHANISM: True-space function naming turns 0x80091A20/24 into local CFG joins.
   A natural 0/1/2 switch preserves the median dispatch and case fallthrough;
   the four-argument ABI keeps the live context in a3 and arg0 held in s0. */
