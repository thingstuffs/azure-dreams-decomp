#include "common.h"

/* Guard flag D_80085F98 prevents re-entry; if a related state D_800737A4 is
 * active, pumps func_800584E4() four times (six more up-front if a timer/counter
 * D_800869A8 equals 0x1E0=480), then always runs two cleanup calls and clears the
 * guard. D_80085F98 must be declared as a padded struct (not a plain array) so
 * gcc 2.7.2-cdk folds the %lo offset into each access while reusing one %hi load,
 * matching retail's register-reuse pattern for the load+immediate-store pair. */
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
