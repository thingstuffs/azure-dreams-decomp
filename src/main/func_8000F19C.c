#include "common.h"

extern s32 func_800214FC(void);
extern void func_80021538(void);
extern void func_80021B18(void *arg0, s32 arg1);
extern void func_800220DC(void);
extern s32 func_800221DC(void) __attribute__((noreturn));
extern void func_8005FE18(s32 arg0);
extern void _card_wait(s32 arg0);
extern void erase(void *arg0);

typedef struct {
    s32 unk0[32];
} Unk80083E98Elem;

typedef struct {
    s32 unk0[8];
} Sp10Buf;

extern Unk80083E98Elem D_80083E98[];

s32 func_8002219C(s32 arg0) {
    Sp10Buf sp10;
    s32 temp_v0;

    func_80021B18(&sp10, arg0);
    _card_wait(0);
    _card_wait(1);
    func_80021538();
    erase(&sp10);
    temp_v0 = func_800214FC();
    if (temp_v0 == 0) {
        func_8005FE18(0);
        return func_800221DC();
    }
    if (arg0 < 5) {
        D_80083E98[arg0].unk0[0] = 0;
        func_800220DC();
    }
    return temp_v0 == 1;
}
