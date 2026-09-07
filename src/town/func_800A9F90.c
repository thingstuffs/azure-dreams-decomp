#include "common.h"

typedef struct S_func_800A9F90 S_func_800A9F90;

struct S_func_800A9F90 {
    u8 pad00[0x50];
    void (*callback)(S_func_800A9F90 *self);
    u8 pad54[0x6C - 0x54];
    u16 counter;
};

extern void func_80033D08(void);
extern s32 func_800A7760(void);
extern u32 D_800814A0[3];

s32 func_800A76F0(S_func_800A9F90 *self)
{
    void (*callback)(S_func_800A9F90 *self);
    u16 counter;

    counter = self->counter - 1;
    self->counter = counter;
    if ((counter << 16) <= 0) {
        func_80033D08();
        *(u16 *)((u8 *)self - 2) =
            (u16)(*(u16 *)((u8 *)self - 2) | 0x8000);
        D_800814A0[0] |= 0x8000;
        return func_800A7760();
    }

    callback = self->callback;
    if (callback != 0) {
        callback(self);
    }
}
