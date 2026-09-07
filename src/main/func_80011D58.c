#include "common.h"

typedef struct S_80024D58_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_80024D58_0;   /* base in func_80024D58 */

typedef struct S_80024D58_1 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    s32 unk_80;
    u8 pad_84[0xAB4];
    s32 unk_B38;
} S_80024D58_1;   /* work in func_80024D58 */



extern s32 func_8004B4A8(void *arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_80024EEC(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern void func_80024C70(void *arg0, s32 arg1);
extern s32 func_80024C48(void *arg0);
extern void func_80024D18(void *arg0, s32 arg1);

extern u8 D_80027DD0[];
extern u8 D_8002A990[];

void *func_80024D58(s32 arg0, s32 arg1, s32 arg2)
{
    u8 *base;
    u8 *work;

    base = D_8002A990;
    work = D_8002A990 + 0x20;
    if (func_8004B4A8(base) == 0) {
        base = func_8003FE78(0, base, 0x394);
        func_8004491C(base, D_80027DD0);
    } else {
        func_80024EEC(base);
        ((S_80024D58_0 *)base)->unk_1E &= 0x7FFF;
        bzero(work, 0xE30);
    }

    ((S_80024D58_1 *)work)->unk_7C = arg1;
    ((S_80024D58_1 *)work)->unk_80 = arg2;
    func_80024C70(work, 0x15);
    ((S_80024D58_0 *)base)->unk_0C = work + 0xB2C;
    ((S_80024D58_1 *)work)->unk_B38 = func_80024C48(work + 0xB3C);
    func_80024D18(work, arg0);
    ((S_80024D58_0 *)base)->unk_10 = 0;
    return base;
}
