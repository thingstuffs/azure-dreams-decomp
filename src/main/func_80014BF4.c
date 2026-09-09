#include "common.h"

extern s8 D_80080A84[];
extern s8 D_80080A88[];
extern u8 D_80082E60[];
extern u8 D_80082E6A[];

extern void func_80020F18(void);
extern void func_800585A0(void);
extern void SD_Call(s32 arg0);

#ifndef NON_MATCHING
register s32 match_v1 ASM_REG("$3");
#endif

void func_80027BF4(void) {
#ifndef NON_MATCHING
    match_v1 = (s32)0x80080000;
    ((s8 *)match_v1)[0xA84] = 2;
    func_80020F18();
    func_800585A0();
    match_v1 = D_80082E6A[0];
    if (match_v1 == 1) {
        SD_Call(0x200);
    } else {
        D_80080A88[0] = 0;
        do { } while (0);
    }
    match_v1 = (s32)0x80080000;
    ASM_KEEP(match_v1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    match_v1 += 0x2E60;
    ((u8 *)match_v1)[0xF] &= 0x7F;
#else
    D_80080A84[0] = 2;
    func_80020F18();
    func_800585A0();
    if (D_80082E6A[0] == 1) {
        SD_Call(0x200);
    } else {
        D_80080A88[0] = 0;
        do { } while (0);
    }
    D_80082E60[0xF] &= 0x7F;
#endif
}
