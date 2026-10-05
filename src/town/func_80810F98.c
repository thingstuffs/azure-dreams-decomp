#include "common.h"


extern s32 D_80084D5C;


typedef struct S_80810F98_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80810F98_0;   /* ptr in func_8052BB98 */

typedef struct S_80810F98_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80810F98_1;   /* object in func_8052BB98 */

void func_8052BB98(S_80810F98_0 *ptr)
{
    s16 state;
    S_80810F98_1 *object;

    state = ptr->unk_00;
    object = ptr->unk_04;
    switch (state) {
    case 0:
        if (object->unk_0C & 2) {
            ptr->unk_00 = state + 1;
        }
        break;
    case 1:
        ptr->unk_08 -= 0x80808;
        if (ptr->unk_08 <= 0x80808) {
            *(u16 *)((u8 *)ptr - 2) |= 0x8000;
            D_80084D5C |= 0x8000;
        }
        break;
    }
}
