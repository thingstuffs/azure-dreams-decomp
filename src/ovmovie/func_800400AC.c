#include "common.h"

extern s32 func_8003E4FC(s32, s32, s32);
extern void func_8003F320(void);
extern void func_80053DA8(s32);
extern void func_800542BC(void);
extern void func_8005A4E8(s32, s32, s32);
extern void func_8005A56C(s32, s16, s16);
extern void func_8005FE18(s32);
extern void func_80060DE8(s32);
extern void func_80061208(s32);
extern void func_80066F78(s32);
extern void func_80067014(s32);
extern void func_8006751C(void *, s32);
extern void func_80067688(void *);
extern void func_800678E0(void *);
extern void func_80176AD8(s32);
extern void func_80176B3C(s32, s32);
extern void func_8017719C(s32, s32, s32, s32);
extern void func_8017797C(s32);

extern s8 D_80080A88;
extern s32 D_80082E60;
extern void *D_80083160;
extern s32 D_801781E0;
extern s32 D_801781E4;
extern s32 D_80189394;
extern s32 D_801B8EB8;
extern s32 D_801B8EBC;
extern u8 D_801C9E40[];

void func_800400AC(void) {
    u8 *base;
    s32 movie_flag;
    s32 e4_value;
    u8 *resident_hi = (u8 *) 0x80080000;
    register u8 *e4_hi ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    D_80082E60 &= ~1;
    if (D_80080A88 == 0) {
        func_80053DA8(0x7F);
        func_800542BC();
    }

    func_8005A4E8(0, 0, 1);
    D_801B8EBC = 0x7F;
    func_8005A56C(0, (s16) D_801B8EBC, (s16) D_801B8EBC);

    movie_flag = (u32) D_80189394 >> 31;
    e4_hi = (u8 *) 0x80180000;
    *(s32 *) (e4_hi - 0x7E1C) = movie_flag;
    func_80176AD8(movie_flag);
    func_80066F78(0);

    base = D_801C9E40;
    e4_value = *(s32 *) (e4_hi - 0x7E1C);
    base[0x6D] = 1;
    base[0x10941] = 1;
    func_80176AD8(e4_value);

    D_801781E0 = 1;
    func_80176B3C(0, ((D_80189394 & 0x40000000) == 0) * 0x10);
    func_8017719C(0, D_80189394 & 0x3FFFFFFF, D_801B8EB8, *(s32 *) (e4_hi - 0x7E1C));
    func_80066F78(0);

    {
        u8 *slot;

        slot = *(u8 **) (resident_hi + 0x3160);
        base[0x6D] = 0;
        base[0x10941] = 0;
        func_800678E0(slot + 0x5C);
    }
    func_80067014(0);
    func_8005FE18(2);
    func_80060DE8(0);
    func_8003E4FC(9, 0, 0);
    func_8003F320();
    func_8017797C(0);
    func_80061208(0);
    func_80067014(0);
    func_80176AD8(*(s32 *) (e4_hi - 0x7E1C));

    {
        u8 *slot;
        u8 *next;

        slot = *(u8 **) (resident_hi + 0x3160);
        next = base;
        base[0x6D] = 0;
        base[0x10941] = 0;
        if (slot == base) {
            next = base + 0x108D4;
        }
        *(u8 **) (resident_hi + 0x3160) = next;
        func_8006751C(next + 0x70, 0x218);
        func_80067688(*(void **) (resident_hi + 0x3160));
    }
    func_8005FE18(0);
    {
        u8 *next;

        next = base;
        if (*(u8 **) (resident_hi + 0x3160) == base) {
            next = base + 0x108D4;
        }
        *(u8 **) (resident_hi + 0x3160) = next;
        func_8006751C(next + 0x70, 0x218);
        func_80067688(*(void **) (resident_hi + 0x3160));
    }
    func_8005FE18(0);
    func_80176AD8(*(s32 *) (e4_hi - 0x7E1C));
}
