#include "common.h"

typedef struct S_func_80406AA8_0 {
    u8 pad_00[4];
    s32 unk_04;
    u8 pad_08[4];
    s32 unk_0C[6];
    s32 unk_24;
    u8 pad_28[4];
    s32 unk_2C;
    u8 pad_30[4];
    void (*unk_34)(void);
    u8 pad_38[8];
    s32 unk_40;
} S_func_80406AA8_0;

typedef struct S_func_80406AA8_1 {
    u8 pad_00[0x10];
    void (*unk_10)(void);
} S_func_80406AA8_1;

extern void func_80406844(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80402084(s32 arg0, s32 arg1);
extern void func_80403144(void *arg0);
extern void func_80405A00(s32 arg0, s32 arg1);
extern void func_80404688(s32 arg0);
extern void func_80400908(void);
extern void func_804069FC(void);
extern void func_80406A74(void);
extern void func_80406DA0(void);
extern s32 D_80010208;

/* Updates the state and selects its next callback based on the current entry check. */
void func_80406AA8(S_func_80406AA8_0 *state)
{
    void (*next_callback)(void);
    S_func_80406AA8_1 *state_base;
    s32 check_result;

    func_80406844(0x80010000, state->unk_2C,
                  state->unk_24);
    check_result = func_80402084(state->unk_2C, 0x80010000);
    state_base = (S_func_80406AA8_1 *)((u8 *)state - 0x20);
    if (check_result == 0) {
        state->unk_34 = func_80406DA0;
        func_80403144(state_base);
        next_callback = func_804069FC;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    } else {
        func_80405A00(state->unk_04, state->unk_2C);
        func_80404688(*(s32 *)((u8 *)state + (0xC + state->unk_2C * 4)));
        if (D_80010208 != 0) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            next_callback = func_80406A74;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        } else {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            next_callback = func_80406DA0;
        }
    }
    ((S_func_80406AA8_1 *)((u8 *)state - 0x20))->unk_10 = next_callback;
    func_80400908();
    state->unk_40 = 0;
}
