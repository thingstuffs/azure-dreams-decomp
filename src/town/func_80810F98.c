#include "common.h"


extern s32 D_80084D5C;


typedef struct S_80810F98_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80810F98_0;   /* arg0 in func_8052BB98 */

typedef struct S_80810F98_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80810F98_1;   /* object in func_8052BB98 */

s32 func_8052BB98(void *arg0)
{
    /* retail reserves 8 bytes of frame and never touches them - no sw/lw/sh/sb with (sp) exists
       anywhere in the row's 39 words, and there is no `sw ra` (a leaf).  An unused local of frame
       size is the honest cause; without it the prologue/epilogue pair disappears (length-drift). */
    s32 unused_slot[2];
    s16 state;
    register s32 call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *object;

    state = ((S_80810F98_0 *)arg0)->unk_00;
    object = ((S_80810F98_0 *)arg0)->unk_04;
    call_arg = state;
    if ((state & 0xffff) == 0) {
        goto state_0;
    }
    call_arg = 0xFFF70000;
    if (state == 1) {
        goto state_1;
    }
    return 1;

state_0: {

        if (((S_80810F98_1 *)object)->unk_0C & 2) {
            s32 result;
            result = call_arg + 1;
            ((S_80810F98_0 *)arg0)->unk_00 = result;
            return result;
        }
        return call_arg + 1;
    }
state_1: {
        s32 result;
        call_arg |= 0xF7F8;
        result = (((S_80810F98_0 *)arg0)->unk_08 += call_arg);
        if (result <= 0x80808) {
            (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
            result = D_80084D5C | 0x8000;
            D_80084D5C = result;
        }
        return result;
    }
}
