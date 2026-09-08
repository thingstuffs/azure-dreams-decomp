#include "common.h"

typedef long long s64;

typedef struct S_80170AD0_0 {
    u8 pad_00[0x94];
    s16 unk_94;
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0xA];
    s16 unk_A2;
    u8 pad_A4[0x4];
    void * unk_A8;
} S_80170AD0_0;   /* arg0 in func_80170AD0 */

typedef struct S_80170AD0_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
} S_80170AD0_1;   /* effect in func_80170AD0 */

typedef struct S_80170AD0_2 {
    u8 pad_00[0x3];
    s8 unk_03;
    u8 pad_04[0x7];
    u8 unk_0B;
} S_80170AD0_2;   /* stats in func_80170AD0 */

typedef struct S_80170AD0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170AD0_3;   /* coords in func_80170AD0 */

typedef struct S_80170AD0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170AD0_4;   /* other in func_80170AD0 */



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
    void *coords;
    void *effect;
    s16 level;
    s16 count;
    s32 value;
    register s32 product ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 first;
    s32 second;
    s32 amount;
    void *other;

    coords = arg1;

    level = ((S_80170AD0_0 *)arg0)->unk_96.s;
    effect = arg2;
    if (level < 0x15) {
        value = (level << 7) / 20;
        ((S_80170AD0_1 *)effect)->unk_0C = ((S_80170AD0_1 *)effect)->unk_0D =
            ((S_80170AD0_1 *)effect)->unk_0E = value;
    }

    level = ((S_80170AD0_0 *)arg0)->unk_96.s;
    if (level >= 0x2B) {
        amount = ((S_80170AD0_1 *)effect)->unk_1E + 0x2BC;
        goto set_amount;
    }
    if (level >= 0x28) {
        amount = ((S_80170AD0_1 *)effect)->unk_1E + 0x226;
        goto set_amount;
    }
    if (level >= 0x26) {
        amount = ((S_80170AD0_1 *)effect)->unk_1E + 0x190;
        goto set_amount;
    }
    if (level >= 0x24) {
        amount = ((S_80170AD0_1 *)effect)->unk_1E + 0xC8;
        goto set_amount;
    }
    if (level >= 0x1A) {
        amount = ((S_80170AD0_1 *)effect)->unk_1E + 0x64;
set_amount:
        ((S_80170AD0_1 *)effect)->unk_1E = amount;
        ((S_80170AD0_1 *)effect)->unk_1C = amount;
    }

    {
        void *stats;

        stats = ((S_80170AD0_1 *)effect)->unk_08;
        product = (((S_80170AD0_2 *)stats)->unk_0B + ((S_80170AD0_2 *)stats)->unk_03) *
                  ((S_80170AD0_1 *)effect)->unk_1E;
    }
    if (product < 0) {
        product += 0xFFF;
    }
    product >>= 12;
    product = -product;
    ((S_80170AD0_1 *)effect)->unk_22 = product / 2;

    if (((S_80170AD0_0 *)arg0)->unk_A2 == 0) {
        work.xyz[0] = ((S_80170AD0_3 *)coords)->unk_02;
        work.xyz[1] = ((S_80170AD0_3 *)coords)->unk_06;
        work.xyz[2] = ((S_80170AD0_3 *)coords)->unk_0A;
        first = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);

        other = ((S_80170AD0_0 *)arg0)->unk_A8;
        work.xyz[0] = ((S_80170AD0_4 *)other)->unk_02;
        work.xyz[1] = ((S_80170AD0_4 *)other)->unk_06;
        work.xyz[2] = ((S_80170AD0_4 *)other)->unk_0A;
        second = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);
        ((S_80170AD0_1 *)effect)->unk_06 = first - second -
            (D_800DCECC[((D_80083228 + ((S_80170AD0_0 *)arg0)->unk_94 + 0x100) >> 9) & 7] * 2);
        goto position_done;
    }

    ((S_80170AD0_1 *)effect)->unk_06 = 4;
position_done:
    func_800478B8(effect);
    count = ((S_80170AD0_0 *)arg0)->unk_96.u - 1;
    ((S_80170AD0_0 *)arg0)->unk_96.u = count;
    if ((count << 16) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
