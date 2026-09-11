#include "common.h"


extern s32 func_8052BC28() __attribute__((noreturn));
extern s32 D_80084D5C;


typedef struct S_80810F98_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80810F98_0;   /* arg0 in func_80810F98 */

typedef struct S_80810F98_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80810F98_1;   /* object in func_80810F98 */

s32 func_80810F98(void *arg0)
{
    s16 state;
    register s32 call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *object;

    state = ((S_80810F98_0 *)arg0)->unk_00;
    object = ((S_80810F98_0 *)arg0)->unk_04;
    call_arg = state;
    if (state == 0) {
        goto state_0;
    }
    call_arg = 0xFFF70000;
    if (state == 1) {
        goto state_1;
    }
    do {
        return func_8052BC28(call_arg, arg0);
    } while (0);

state_0: {
        if (((S_80810F98_1 *)object)->unk_0C & 2) {
            s32 result;
            result = call_arg + 1;
            ((S_80810F98_0 *)arg0)->unk_00 = result;
            return func_8052BC28(call_arg, arg0);
        }
        return call_arg + 1;
    }
state_1: {
        register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        call_arg |= 0xF7F8;
        result = ((S_80810F98_0 *)arg0)->unk_08 + call_arg;
        ((S_80810F98_0 *)arg0)->unk_08 = result;
        if (result <= 0x80808) {
            (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
            result = D_80084D5C | 0x8000;
            D_80084D5C = result;
        }
        return result;
    }
}
