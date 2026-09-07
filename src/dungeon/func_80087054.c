#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

typedef struct S_8008C7B4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8008C7B4_0;   /* arg0 in func_8008C7B4 */

typedef struct S_8008C7B4_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8008C7B4_1;   /* flags in func_8008C7B4 */

typedef struct S_8008C7B4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008C7B4_2;   /* control in func_8008C7B4 */




extern M2C_UNK func_80048A44();
extern M2C_UNK func_8009F644();
extern s32 func_800A5C70(void);
extern u16 D_80013714;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_800DCFB0;
extern M2C_UNK D_800DD0B8;

void func_8008C7B4(void *arg0, s32 arg1, void *arg2, void *arg3) {
#ifndef NON_MATCHING
    u8 *flags;
    s32 initial_state;
#else
    M2C_UNK *flags = &D_80083160;
#endif

#ifndef NON_MATCHING
    initial_state = 0x1C;
    ASM_KEEP_NV(initial_state);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_8008C7B4_0 *)arg0)->unk_9A = initial_state;
    flags = (u8 *)0x80080000;
#else
    ((S_8008C7B4_0 *)arg0)->unk_9A = 0x1C;
#endif
    ((S_8008C7B4_0 *)arg0)->unk_9B = 0;
    ((S_8008C7B4_0 *)arg0)->unk_8C = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
#ifndef NON_MATCHING
    ASM_KEEP_NV(flags);   /* MATCH pin: retail immediate-load split depends on it */
#endif
    if (D_80013714 & 2) {
        goto set_control;
    }
#ifndef NON_MATCHING
    flags += 0x3160;
    ASM_KEEP_NV(flags);   /* MATCH pin: retail immediate-load split depends on it */
#endif
    if (!(((S_8008C7B4_1 *)flags)->unk_08 & 0x20) || (func_800A5C70() == 0)) {
        goto after_control;
    }
set_control:
    {
        M2C_UNK *control = &D_80083460;

        ((S_8008C7B4_2 *)control)->unk_02 = (u16)(((S_8008C7B4_2 *)control)->unk_02 | 0x80);
    }
after_control:
    func_8009F644(arg3, 0x10, 0, 0);
    {
#ifndef NON_MATCHING
        u8 *lookup;
#else
        u8 *lookup;
#endif

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x100000) {
#ifndef NON_MATCHING
            u8 *tail_page;

            tail_page = (u8 *)0x800E0000;
            ASM_KEEP(tail_page);   /* MATCH pin: load-bearing for the whole function shape */
            lookup = tail_page - 0x2F48;
#else
            lookup = (u8 *)&D_800DD0B8;
#endif
        } else {
#ifndef NON_MATCHING
            u8 *tail_page;

            ASM_SET(tail_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            tail_page = (u8 *)0x800E0000;
            ASM_KEEP(tail_page);   /* MATCH pin: load-bearing for the whole function shape */
            lookup = tail_page - 0x3050;
#else
            lookup = &D_800DCFB0;
#endif
        }
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = lookup;
#ifndef NON_MATCHING
        {
            u8 *element;

            element = lookup + (((s32)(D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7);
            func_80048A44(arg2, *element, 0, 1);
        }
#else
        func_80048A44(arg2, lookup[((s32)(D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
#endif
    }
}
