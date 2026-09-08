#include "common.h"

typedef struct {
    u8 pad00[0x50];
    void *unk50;
    u8 pad54[0x68 - 0x54];
    s16 unk68;
    u8 pad6A[0x72 - 0x6A];
    s16 unk72;
} S800A3088Arg0;

typedef struct {
    u8 pad0[2];
    s16 unk2;
    u8 pad4[2];
    s16 unk6;
} S800A3088Arg2;

extern s32 func_800A0668(S800A3088Arg0 *);
extern s32 func_800A0F10(S800A3088Arg0 *arg0, s32 arg1);
extern void func_8009A674(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_800A0884[16];

void func_800A07E8(S800A3088Arg0 *arg0, s32 arg1, S800A3088Arg2 *arg2) {
    register s32 t1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S800A3088Arg2 *t2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    t1 = arg1;
    t2 = arg2;
    if (arg0->unk68 == 0) {
        s32 result;

        result = func_800A0668(arg0);
        if (result == 0) {
            if (func_800A0F10(arg0, t1) != 0) {
                arg0->unk50 = D_800A0884;
                func_8009A674(arg0->unk72, t2->unk2, t2->unk6);
            }
        }
    } else if ((func_800A0668(arg0) != 0) && (func_800A0F10(arg0, t1) != 0)) {
        arg0->unk50 = D_800A0884;
        func_8009A674(arg0->unk72, t2->unk2, t2->unk6);
    }
}
