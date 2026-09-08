#include "common.h"

extern void func_800702F0(s32 arg0);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_8007CAA8(s32 arg0);
extern s32 func_8040153C(void);
extern void func_80401578(void);
extern s32 func_80401B80(void);
extern void func_80408654(s32 arg0);
extern s32 D_80408AA0[];
extern u8 D_80400038[];
extern u8 D_804000F8[];

/* Starts the selected card operation and maps its completion status. */
s32 func_8001AB30(s32 card_index) {
    s32 *card_entry;
    s32 count;
    s32 result;

    count = 0;
    ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    func_80408654(0);
    func_80408654(1);
    func_80401578();
    card_entry = D_80408AA0;
    if (card_index != 0) {
        card_entry++;
    }
    func_8007CAA8(*card_entry);
    result = func_8040153C();
    if (result == 0) {
        count++;
        ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        func_800702F0(0);
        return func_80401B80();
    }
    func_8007C040(D_80400038, D_804000F8, count);
    if (result != 1) {
        if (result == 3) {
            result = 4;
        } else {
            result = 5;
        }
    }
    return result;
}
