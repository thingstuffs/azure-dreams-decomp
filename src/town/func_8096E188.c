#include "common.h"
#include "records/Rec_func_801237A4_arg0.h"




extern s32 func_80123200(s32);
extern void func_801232DC(void);
extern void func_801234F0(void);
extern void func_80123604(void);
extern void func_801237A4(void *);
extern void func_80124188(void *);
extern void func_8012656C(void *, void *, void *);

void func_80126620(void *arg0) {
    s32 one = 1;

    ((Rec_func_801237A4_arg0 *)arg0)->unk_04.as_s16 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_06 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_08 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_0A = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_0B = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_0C = one;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_0D = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_0E = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_0F = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_10 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_11 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_12 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_13 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_14 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_16 = 0;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_17 = 0xFF;
    ((Rec_func_801237A4_arg0 *)arg0)->unk_18 = 0xFF;

    if ((func_80123200(0x31) & 0xFF) ||
        (func_80123200(0x30) & 0xFF)) {
        ((Rec_func_801237A4_arg0 *)arg0)->unk_15 = 0;
    } else {
        ((Rec_func_801237A4_arg0 *)arg0)->unk_15 = one;
    }

    func_8012656C((u8 *)arg0 + 0x48, (u8 *)arg0 + 0x20,
                  (u8 *)arg0 + 0x30);
    func_801237A4(arg0);
    func_80123604();
    func_801234F0();
    func_801232DC();
    func_80124188(arg0);
}
