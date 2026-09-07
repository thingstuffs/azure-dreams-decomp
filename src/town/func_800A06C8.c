#include "common.h"

extern s32 func_8009706C(s32 arg0);
extern void func_800970AC(s32 arg0, void *arg1);
extern void func_800478B8(void *arg0);

typedef struct {
    /* 0x00 */ u8 pad[0x4D];
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ u8 pad2[0x2];
    /* 0x50 */ void (*unk50)(void *, void *, s32, s32);
} EntityLike;

void func_8009DE28(EntityLike *arg0, s32 arg1, s32 arg2)
{
    u16 *flags = (u16 *)((u8 *)arg0 - 2);

    arg0->unk50(arg0, arg0, arg1, arg2);
    if (!(*flags & 0x8000)) {
        func_800970AC(func_8009706C(arg1), arg0);
        if (arg0->unk4D == 0x13) {
            func_800478B8((void *)arg2);
        }
    }
}
