#include "common.h"

/* Boot/init: video+CD+pad+graphics subsystem bring-up, config-global reset,
 * and CD-stream state-pointer advance past its default sentinel. */
extern s32 SetVideoMode(s32 mode);
extern void CdInit(void);
extern s32 ResetGraph(s32 mode);
extern s32 SetGraphDebug(s32 level);
extern s32 InitPAD(u8 *buf1, s32 siz1, u8 *buf2, s32 siz2);
extern void bzero(void *ptr, s32 len);

extern void func_8003CAC4(void);
extern void func_8003D56C(s32 a0);
extern void func_80053DCC(s16 arg0);
extern void func_80053E14(s16 a0);

extern void func_8003E34C(void);
extern void func_80053F98(void);
extern void func_80053DF0(s16 a0);
extern void StartPAD(void);
extern void InitGeom(void);
extern void func_8003D468(void);
extern void func_80043674(void);

/* D_80083160[0] holds the current CD/streaming state pointer; default value is
 * the sentinel D_801C9E40. size>8 to force %hi/%lo. */
extern void *D_80083160[3];
extern u8 D_801C9E40[16];
extern u32 D_80083208[3];

/* short globals D_80080A94/98/9C read via %hi/%lo; accessed via fixed
 * absolute-address casts (see D_80013180 group note below) so gcc reuses the
 * base==dest lbu/lhu macro form the retail binary shows for each (a solitary
 * hi/lo read immediately consumed as a call arg). */

/* pad-buffer arrays passed to InitPAD */
extern u8 D_800830C0[0x22];
extern u8 D_800830E8[0x22];

extern u8 D_80081468[8];
extern u8 D_80082E6B;

/* D_80012094, D_80012098, D_80012D6E, D_80013180, D_80013184, D_80013186 all
 * share the same %hi() page (0x8001xxxx) in the retail binary and are
 * accessed off ONE materialised base register across this whole block,
 * despite being far apart -- so the retail source used fixed absolute
 * addresses here (like the established `bzero((void*)0x80013564, ...)`
 * idiom elsewhere in this codebase), letting gcc CSE/constant-fold the
 * shared %hi at compile time instead of via 6 independent extern symbols. */

/* mirror/shadow copies of the same three D_80013180-group fields */
extern u32 D_80081494[3];
extern u8 D_800814AC[12];
extern u8 D_800814A4[12];

extern u32 D_80081478[3];
extern u8 D_801D8D7A[12];
extern u8 D_801E964E[12];

void func_8003D5A4(void)
{
    void **s0 = D_80083160;
    s32 i;
    u8 *p;

    SetVideoMode(0);
    CdInit();
    func_8003E34C();
    ResetGraph(0);
    func_80053F98();

    func_80053DCC(*(s16 *)0x80080A94);
    func_80053DF0(*(s16 *)0x80080A98);
    func_80053E14(*(s16 *)0x80080A9C);

    for (i = 0; i < 0x22; i++) {
        D_800830C0[i] = 0xFF;
        D_800830E8[i] = 0xFF;
    }
    InitPAD(D_800830C0, 0x22, D_800830E8, 0x22);

    StartPAD();
    func_8003D56C(1);
    SetGraphDebug(0);
    InitGeom();

    D_80082E6B = 0;
    bzero(D_80081468, 8);

    func_8003D468();

    {
        u8 *pg = (u8 *)0x80010000;
        u32 val0 = 0x2A080808;
        u8 val4, val6;

        *(u32 *)(pg + 0x3180) = val0; /* D_80013180 */
        *(u32 *)0x80081494 = val0;
        val4 = 0x20;
        *(u8 *)(pg + 0x3184) = val4; /* D_80013184 */
        *(u8 *)0x800814AC = val4;
        val6 = 3;
        *(u8 *)(pg + 0x3186) = val6; /* D_80013186 */
        *(u8 *)0x800814A4 = val6;
        *(s16 *)(pg + 0x2094) = 5;   /* D_80012094 */
        *(u8 *)(pg + 0x2D6E) = 0;    /* D_80012D6E */
        *(s16 *)(pg + 0x2098) = 2;   /* D_80012098 */
    }
    func_80043674();

    p = (u8 *)D_801C9E40;
    if (*s0 == (void *)D_801C9E40) {
        p = p + 0x108D4;
    }
    *s0 = p;
    *(u32 *)(p + 0x8D0) = (u32)(p + 0x8D4);
    D_80083208[0] = 0x2C808080;
    func_8003CAC4();

    {
        u32 *q = D_80081478;
        *q = (u32)D_801D8D7A;
        q[1] = (u32)D_801E964E;
    }
}
