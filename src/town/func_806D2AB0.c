#include "common.h"


typedef void (*Callback3)(void *, void *, s32);
typedef void (*Callback1)(s32);

typedef struct S_806D2AB0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_806D2AB0_0;   /* arg0 in func_806D2AB0 */

typedef struct S_806D2AB0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_806D2AB0_1;   /* ptr in func_806D2AB0 */

typedef struct S_806D2AB0_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_806D2AB0_2;   /* (offset - index) * 4 + (u8 *)arg0 in func_806D2AB0 */

typedef struct S_806D2AB0_3 {
    u8 pad_00[0x20];
    void * unk_20;
} S_806D2AB0_3;   /* D_80016000[0] in func_806D2AB0 */


extern void *D_80016000[];
extern u8 D_80016148[16];
extern u8 D_80016170[16];

s32 func_806D2AB0(s32 *arg0, s32 arg1)
{
    s32 *ptr;
    s32 index;
    s32 offset;

    index = 0;
    if (((S_806D2AB0_0 *)arg0)->unk_08 != 0) {
        ptr = arg0;
loop:
        offset = *ptr;
        if (offset != arg1) {
            ptr += 7;
            index++;
            if (((S_806D2AB0_1 *)ptr)->unk_08 == 0) {
                offset = index * 8;
            } else {
                goto loop;
            }
        } else {
            offset = index * 8;
        }
        if (((S_806D2AB0_2 *)((offset - index) * 4 + (u8 *)arg0))->unk_08 == 0) {
            goto notify;
        }
        return index;
    } else {
notify:
        (*(Callback3 *)((u8 *)(((S_806D2AB0_3 *)(D_80016000[0]))->unk_20) + 0x168))(
            D_80016148, D_80016170, 0x36);
        (*(Callback1 *)((u8 *)(((S_806D2AB0_3 *)(D_80016000[0]))->unk_20) + 0x174))(1);
    }
    return index;
}
