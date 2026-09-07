#include "common.h"

typedef struct S_80126620_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 unk_17;
    u8 unk_18;
} S_80126620_0;   /* arg0 in func_80126620 */



extern s32 func_80123200(s32);
extern void func_801232DC(void);
extern void func_801234F0(void);
extern void func_80123604(void);
extern void func_801237A4(void *);
extern void func_80124188(void *);
extern void func_8012656C(void *, void *, void *);

/* Initialize state defaults and run the associated setup routines. */
void func_80126620(void *state) {
    s32 one = 1;

    ((S_80126620_0 *)state)->unk_04 = 0;
    ((S_80126620_0 *)state)->unk_06 = 0;
    ((S_80126620_0 *)state)->unk_08 = 0;
    ((S_80126620_0 *)state)->unk_0A = 0;
    ((S_80126620_0 *)state)->unk_0B = 0;
    ((S_80126620_0 *)state)->unk_0C = one;
    ((S_80126620_0 *)state)->unk_0D = 0;
    ((S_80126620_0 *)state)->unk_0E = 0;
    ((S_80126620_0 *)state)->unk_0F = 0;
    ((S_80126620_0 *)state)->unk_10 = 0;
    ((S_80126620_0 *)state)->unk_11 = 0;
    ((S_80126620_0 *)state)->unk_12 = 0;
    ((S_80126620_0 *)state)->unk_13 = 0;
    ((S_80126620_0 *)state)->unk_14 = 0;
    ((S_80126620_0 *)state)->unk_16 = 0;
    ((S_80126620_0 *)state)->unk_17 = 0xFF;
    ((S_80126620_0 *)state)->unk_18 = 0xFF;

    if ((func_80123200(0x31) & 0xFF) ||
        (func_80123200(0x30) & 0xFF)) {
        ((S_80126620_0 *)state)->unk_15 = 0;
    } else {
        ((S_80126620_0 *)state)->unk_15 = one;
    }

    func_8012656C((u8 *)state + 0x48, (u8 *)state + 0x20,
                  (u8 *)state + 0x30);
    func_801237A4(state);
    func_80123604();
    func_801234F0();
    func_801232DC();
    func_80124188(state);
}
