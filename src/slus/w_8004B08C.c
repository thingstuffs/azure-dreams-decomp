#include "common.h"

#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
} S_8004AFE8;

extern unsigned char *D_80081540;
extern s32 func_8004AE3C(void **arg0);
extern void func_8004AFC8(void *base, s32 count, s32 size, void *compar);
extern s32 func_8004AFE8(S_8004AFE8 **arg0);
extern void func_8004B028(u8 *arg0, S_8004AFE8 **arg1, s32 arg2);
extern void *memcpy(void *dst, void *src, s32 n);
extern void bzero(void *p, s32 n);
extern s32 func_8004AE68(void *a0, void *a1);
extern s32 func_8004AE98(void *a0, void *a1);

void func_8004B08C(S_8004AFE8 **arg0) {
    S_8004AFE8 *sp10[0x40];
    u8 sp110[0x80];
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    S_8004AFE8 **var_s2;
    register u8 *var_s1 ASM_REG("$17"); /* s1: copy then loop work */
    u8 *var_s4;

    var_s4 = sp110;
    D_80081540 = var_s4;
    var_s2 = arg0;
    temp_v0 = func_8004AE3C((void **)arg0);
    var_s1 = (u8 *)sp10;
    memcpy(var_s1, var_s2, temp_v0 * 4);
    ((S_8004AFE8 **)var_s1)[temp_v0] = 0;
    func_8004AFC8(var_s2, temp_v0, 4, func_8004AE68);
    var_s0 = 0;
    if (*var_s2 != 0) {
        var_s1 = var_s4;
    loop_2:
        if (var_s2 != 0) {
            temp_v0_2 = (*var_s2)->unk1;
            if (temp_v0_2 != var_s0) {
                var_s0 = temp_v0_2;
                bzero(var_s1, 0x80);
                temp_v0 = func_8004AFE8(var_s2);
                func_8004B028(var_s1, sp10, var_s0);
                func_8004AFC8(var_s2, temp_v0, 4, func_8004AE98);
                var_s2 = var_s2 + temp_v0;
            }
            if (*var_s2 != 0) {
                goto loop_2;
            }
        }
    }
}
