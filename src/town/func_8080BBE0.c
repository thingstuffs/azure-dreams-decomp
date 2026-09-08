#include "common.h"
#include "m2c_compat.h"

typedef struct S_805267E0_0_pre {
    u16 unk_00;
} S_805267E0_0_pre;   /* the 0x2 bytes before arg0 in func_805267E0, addressed as arg0[-1] */

typedef struct S_805267E0_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0xA];
    u16 unk_16;
} S_805267E0_0;   /* arg0 in func_805267E0 */

typedef struct S_805267E0_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_805267E0_1;   /* sub in func_805267E0 */


extern s32 D_80084D5C;

/* Advances a delayed fade and sets completion flags when the color reaches its threshold. */
void func_805267E0(void *effect) {
    s16 state;
    s32 color;
    u16 timer;
    void *linked_obj;
    s16 next_state;
    u16 flags;

    state = ((S_805267E0_0 *)effect)->unk_00;
    linked_obj = ((S_805267E0_0 *)effect)->unk_04;
    switch (state) {
    case 0:
        timer = ((S_805267E0_0 *)effect)->unk_02 - 1;
        ((S_805267E0_0 *)effect)->unk_02 = timer;
        if ((timer << 0x10) <= 0) {
            next_state = ((S_805267E0_0 *)effect)->unk_00;
            flags = ((S_805267E0_0 *)effect)->unk_16;
            next_state = (s16) (next_state + 1);
            flags &= 0xFFFD;
            ((S_805267E0_0 *)effect)->unk_16 = flags;
            ((S_805267E0_0 *)effect)->unk_00 = next_state;
            return;
        }
        return;
    case 1:
        if (((S_805267E0_1 *)linked_obj)->unk_2A & 1) {
            ((S_805267E0_0 *)effect)->unk_00 = (s16) (state + 1);
            return;
        }
        break;
    case 2:
        color = ((S_805267E0_0 *)effect)->unk_08 + 0xFFF7F7F8;
        ((S_805267E0_0 *)effect)->unk_08 = color;
        if (color <= 0x80808) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_805267E0_0_pre *)effect)[-1].unk_00 | 0x8000);
            D_80084D5C |= 0x8000;
        }
        break;
    }
}
