#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef void (*Callback)(void *, s32, void *);

extern void func_80033D08(void);
extern s32 func_800352FC(void);
extern void func_800AAF5C(void);
extern void func_800AAFE0(void *, s32);
extern void func_800AB2F4(void);
extern void func_800AB3D0(void);
extern void func_800C2C80(void *, void *, s32, s32);
extern void func_800C2CB0(void *, void *, void *, s8);
extern s32 func_800C2E1C(s16, s16);
extern s32 func_800C2F14(s16, s16);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern s32 D_800834A8;
extern u8 D_80083780[];


typedef struct S_800AB1E0_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800AB1E0_0;   /* ref in func_800AB1E0 */

typedef struct S_800AB1E0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800AB1E0_1;   /* base in func_800AB1E0 */


void func_800AB1E0(void *arg0, s32 arg1, Rec_D_80082E80 *arg2) {
    u8 *base = D_80083160;
    s16 buf[12];
    u8 *ref;
    s32 idx;

    if (D_800834A8 == 0) {
        func_80033D08();
        (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }

    func_800AAFE0(buf, 0);
    ref = D_80083780;
    if (buf[1] != ((S_800AB1E0_0 *)ref)->unk_02 || buf[3] != ((S_800AB1E0_0 *)ref)->unk_06 ||
        buf[5] != ((S_800AB1E0_0 *)ref)->unk_0A || func_800352FC() != 0 ||
        (((S_800AB1E0_1 *)base)->unk_08 & 0xF000) != 0) {
        func_800AAF5C();
        (*(s16 *)((u8 *)arg0 + (0x90))) = 0;
        func_800AB2F4();
        return;
    }

    (*(s16 *)((u8 *)arg0 + (0x90))) = (*(s16 *)((u8 *)arg0 + (0x90))) + 1;
    if ((*(s16 *)((u8 *)arg0 + (0x90))) > 100) {
        (*(s16 *)((u8 *)arg0 + (0x90))) = 100;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    }
    (*(Callback *)((u8 *)arg0 + (0x50)))(arg0, arg1, arg2);
    if (((*(u16 *)((u8 *)arg0 + (-2))) & 0x8000) != 0) {
        return;
    }

    idx = func_800C2E1C((*(s16 *)((u8 *)arg0 + (0x72))), (*(s16 *)((u8 *)arg0 + (0x64))));
    if ((*(s16 *)((u8 *)arg0 + (0x74))) != idx) {
        func_800C2CB0(arg0, arg2, ((void **)(*(void * *)((u8 *)arg0 + (0x78))))[idx],
                      arg2->unk_04.as_s8);
        (*(s16 *)((u8 *)arg0 + (0x74))) = idx;
    }

    if (((*(u8 *)((u8 *)arg0 + (0x71))) & 1) == 0) {
        if ((s16)func_800C2F14((*(s16 *)((u8 *)arg0 + (0x72))),
                               (*(s16 *)((u8 *)arg0 + (0x64)))) == 0) {
            u16 cleared;
            cleared = arg2->unk_14.at00_u16.v & 0xFFFE;
            ASM_TAILSLOT_PIN(cleared);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800AB3D0();
            return;
        }
    } else {
        if ((s16)func_800C2F14((*(s16 *)((u8 *)arg0 + (0x72))),
                               (*(s16 *)((u8 *)arg0 + (0x64)))) != 0) {
            u16 cleared;
            cleared = arg2->unk_14.at00_u16.v & 0xFFFE;
            ASM_TAILSLOT_PIN(cleared);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800AB3D0();
            return;
        }
    }

    arg2->unk_14.at00_u16.v |= 1;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    func_800C2C80(arg0, arg2, 0, 0);
}
