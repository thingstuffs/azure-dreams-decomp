#include "common.h"
#include "records/Rec_D_800E3D7C.h"


#ifdef NON_MATCHING
#define LEGACY_ASM_KEEP(value) ((void)0)
#else
#define LEGACY_ASM_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#endif

extern void func_80047784(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174D48(void *, void *, void *);

extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_801710F4[];
extern u8 D_80174F00[];


typedef struct S_80174BF8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174BF8_0;   /* arg0 in func_80174BF8 */


typedef struct S_80174BF8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_80174BF8_2;   /* arg2 in func_80174BF8 */

typedef struct S_80174BF8_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174BF8_3;   /* counter in func_80174BF8 */

void func_80174BF8(S_80174BF8_0 *arg0, void *arg1, S_80174BF8_2 *arg2, Rec_D_800E3D7C *arg3)
{
    void *call_arg;
    u8 *counter;
    u16 timer;
    u8 state;

    state = arg0->unk_9B;
    if (state != 0) {
        if (state != 1) {
            return;
        }
        goto active;
    }

    func_800A56E0(0x50C);
    arg0->unk_96 = 10;
    func_80174D48(arg1, arg2, arg3);
    arg3->unk_48.at00_s8.v = 0;
    arg3->unk_48.at01_s8.v = 0;
    arg0->unk_9B++;

active:
    if (!(arg2->unk_14 & 0x8000)) {
        timer = arg0->unk_96;
        arg0->unk_96 = timer - 1;
        if ((s16)timer > 0) {
            return;
        }
    }

    call_arg = arg3;
    LEGACY_ASM_KEEP(call_arg);
    counter = D_80083460;
    LEGACY_ASM_KEEP(counter);
    ((S_80174BF8_3 *)counter)->unk_0A--;
    arg2->unk_2C = D_80174F00;
    func_800AD594(call_arg, 0x200);
    func_80047784(arg2,
        arg2->unk_2C[((D_80083228[0] + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    arg0->unk_8C = D_801710F4;
    func_800A4ACC(arg3);
    arg3->unk_6D.as_s8 = 0;
    arg3->unk_44.at02_u16.v &= 0x7FFF;
}
