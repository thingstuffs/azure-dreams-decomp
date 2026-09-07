#include "common.h"

typedef long long s64;

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_800478B8();
extern s32 func_80065420();

extern s32 D_800814A0;
extern s16 D_80083228;
extern s8 D_800DCECC[8];

typedef struct {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

void func_80170AD0(void *arg0, void *arg1, void *arg2)
{
    StackWork work;
    register void *coords ASM_REG("$7");
    void *effect;
    s16 level;
    s16 count;
    s32 value;
    register s32 product ASM_REG("$2");
    s32 first;
    s32 second;
    s32 amount;
    void *other;

    coords = arg1;
    ASM_KEEP(coords);

    level = FIELD(arg0, s16, 0x96);
    effect = arg2;
    if (level < 0x15) {
        value = (level << 7) / 20;
        FIELD(effect, s8, 0xC) = FIELD(effect, s8, 0xD) =
            FIELD(effect, s8, 0xE) = value;
    }

    level = FIELD(arg0, s16, 0x96);
    if (level >= 0x2B) {
        amount = FIELD(effect, u16, 0x1E) + 0x2BC;
        goto set_amount;
    }
    if (level >= 0x28) {
        amount = FIELD(effect, u16, 0x1E) + 0x226;
        goto set_amount;
    }
    if (level >= 0x26) {
        amount = FIELD(effect, u16, 0x1E) + 0x190;
        goto set_amount;
    }
    if (level >= 0x24) {
        amount = FIELD(effect, u16, 0x1E) + 0xC8;
        goto set_amount;
    }
    if (level >= 0x1A) {
        amount = FIELD(effect, u16, 0x1E) + 0x64;
set_amount:
        FIELD(effect, u16, 0x1E) = amount;
        FIELD(effect, u16, 0x1C) = amount;
    }

    {
        register void *stats ASM_REG("$3");

        stats = FIELD(effect, void *, 8);
        ASM_KEEP(stats);
        product = (FIELD(stats, u8, 0xB) + FIELD(stats, s8, 3)) *
                  FIELD(effect, u16, 0x1E);
        ASM_KEEP(product);
    }
    if (product < 0) {
        product += 0xFFF;
    }
    product >>= 12;
    product = -product;
    FIELD(effect, s16, 0x22) = product / 2;

    if (FIELD(arg0, s16, 0xA2) == 0) {
        work.xyz[0] = FIELD(coords, u16, 2);
        work.xyz[1] = FIELD(coords, u16, 6);
        work.xyz[2] = FIELD(coords, u16, 0xA);
        first = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);

        other = FIELD(arg0, void *, 0xA8);
        work.xyz[0] = FIELD(other, u16, 2);
        work.xyz[1] = FIELD(other, u16, 6);
        work.xyz[2] = FIELD(other, u16, 0xA);
        second = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);
        FIELD(effect, s16, 6) = first - second -
            (D_800DCECC[((D_80083228 + FIELD(arg0, s16, 0x94) + 0x100) >> 9) & 7] * 2);
        goto position_done;
    }

    FIELD(effect, s16, 6) = 4;
position_done:
    func_800478B8(effect);
    count = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = count;
    if ((count << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
