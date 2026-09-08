#include "common.h"

extern void func_80056948(void);
extern void func_800584E4(void);
extern void func_8005ACDC(void);

typedef struct {
    s32 v;
    s32 pad[2];
} S_80085F98;

extern S_80085F98 D_80085F98;
extern s32 D_800737A4[];
extern s32 D_800869A8[];

/* Prevents re-entry while processing active state updates and running cleanup. */
void func_80058700(void) {
    if (D_80085F98.v == 0) {
        D_80085F98.v = 1;
        if (D_800737A4[0] != 0) {
            if (D_800869A8[0] == 0x1E0) {
                func_800584E4();
                func_800584E4();
                func_800584E4();
                func_800584E4();
                func_800584E4();
                func_800584E4();
            }
            func_800584E4();
            func_800584E4();
            func_800584E4();
            func_800584E4();
        }
        func_80056948();
        func_8005ACDC();
        D_80085F98.v = 0;
    }
}
