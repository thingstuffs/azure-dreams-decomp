#include "common.h"

typedef struct S_80027364_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80027364_0;   /* base in func_80027364 */

typedef struct S_80027364_1 {
    u8 pad_00[0xEC];
    s32 unk_EC;
} S_80027364_1;   /* work in func_80027364 */



extern s32 func_8004B4A8(void *arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_80023A00(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern void func_8002727C(void *arg0, s32 arg1);
extern s32 func_80027254(void *arg0);
extern void func_80027324(void *arg0, s32 arg1);

extern u8 D_80027DD0[];
extern u8 D_8002B968[];

/* Creates or resets the shared object and initializes its work state. */
void *func_80027364(s32 init_value)
{
    u8 *object;
    u8 *work_state;

    object = D_8002B968;
    work_state = D_8002B968 + 0x20;
    if (func_8004B4A8(object) == 0) {
        object = func_8003FE78(0, object, 0x68);
        func_8004491C(object, D_80027DD0);
    } else {
        func_80023A00(object);
        ((S_80027364_0 *)object)->unk_1E &= 0x7FFF;
        bzero(work_state, 0x180);
    }

    func_8002727C(work_state, 4);
    ((S_80027364_0 *)object)->unk_0C = work_state + 0xE0;
    ((S_80027364_1 *)work_state)->unk_EC = func_80027254(work_state + 0xF0);
    func_80027324(work_state, init_value);
    return object;
}
