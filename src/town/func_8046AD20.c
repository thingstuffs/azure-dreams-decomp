#include "common.h"


typedef struct {
    u8 value[8];
} LocalValues;

typedef s32 (*GetIndex)(s32);
typedef void (*UseValue)(s16, s32);
typedef void (*CallPair)(s32, s32);
typedef s16 *(*GetHalfword)(s32, s32);

extern s8 D_80016000[];
extern LocalValues D_80019164;
extern u8 *D_8001E950;
extern s8 D_8001F2D4[];

extern s32 func_8001E670(s32);
extern void func_8001BC98();


typedef struct S_8001BD20_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001BD20_0;   /* page in func_8001BD20 */

typedef struct S_8001BD20_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001BD20_1;   /* ((S_8001BD20_0 *)page)->unk_6000 in func_8001BD20 */

typedef struct S_8001BD20_2 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8001BD20_2;   /* (*(void * *)((u8 *)page + 0x6000)) in func_8001BD20 */

typedef struct S_8001BD20_3 {
    u8 pad_00[0x40];
    void * unk_40;
} S_8001BD20_3;   /* ((S_8001BD20_2 *)((*(void * *)((u8 *)page + 0x6000))))->unk_1C in func_8001BD20 */

s32 func_8001BD20(s32 arg0, s32 arg1) {
    LocalValues local;
    void *page;
    s32 hold0;
    s32 hold1;

    hold0 = arg0;
    hold1 = arg1;
    local = D_80019164;
    if (func_8001E670(0xA3) != 0) {
        if (func_8001E670(0x408) == 0) {
            D_8001E950[1] = 1;
        } else {
            D_8001E950[1] = 2;
        }
    }

    if (D_8001E950[1] == 0) {
        hold1 = 0x80010000;
        page = (void *)hold1;
        (*(UseValue *)((u8 *)(((S_8001BD20_1 *)(((S_8001BD20_0 *)page)->unk_6000))->unk_20) + 0x2EC))(
            (*(s16 *)((u8 *)(local.value) + (*(GetIndex *)((u8 *)(((S_8001BD20_1 *)(((S_8001BD20_0 *)page)->unk_6000))->unk_20) + 0x2D4))(0) * 2)),
            0x100);

        (*(CallPair *)((u8 *)(((S_8001BD20_1 *)(((S_8001BD20_0 *)page)->unk_6000))->unk_20) + 0x2F8))(0x27, 0x200);

        ((S_8001BD20_3 *)(((S_8001BD20_2 *)((*(void * *)((u8 *)page + 0x6000))))->unk_1C))->unk_40 = D_8001F2D4;

        if ((*(GetIndex *)((u8 *)(((S_8001BD20_1 *)(((S_8001BD20_0 *)page)->unk_6000))->unk_20) + 0x2D4))(0) == 2) {
            *(*(GetHalfword *)((u8 *)(((S_8001BD20_1 *)(((S_8001BD20_0 *)page)->unk_6000))->unk_20) + 0x314))(0xC20, 0x4A0) = 0x25;

            *(*(GetHalfword *)((u8 *)(((S_8001BD20_1 *)(((S_8001BD20_0 *)page)->unk_6000))->unk_20) + 0x314))(0xD20, 0x4A0) = 0x25;
        }
        return 1;
    }

    ASM_KEEP(hold0);   /* MATCH pin: retail keeps a computation the compiler would drop */
    func_8001BC98(hold0, hold1);
    return 0;
}

/* MECHANISM: An 8-byte byte-aligned local reproduces the lwl/lwr stack copy; guarded
   s0/s1 pins preserve the argument-to-constant/page live-range reuse. One-argument
   flag calls, nested short-lived field expressions, and late literal stores close the CFG. */
