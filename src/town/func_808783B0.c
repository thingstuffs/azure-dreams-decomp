/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

void func_80701FEC();                     /* extern */
void func_8070207C();                     /* extern */
s32 func_80702260();                                /* extern */
void func_807022BC();                            /* extern */
s32 func_80702314();                             /* extern */
void func_80702360();                            /* extern */
M2C_UNK func_80702924();                         /* extern */
void func_80702A78();                    /* extern */

extern s32 D_80701DC4_0[];
extern s32 D_80701DC4_1[];
extern s32 D_80701DC4_2[];
extern s32 D_80701DC4_3[];
extern s32 D_80701DC8_0[];
extern s32 D_80701DC8_1[];

/* Run the shop's open sequence and return the resulting handle. */
s32 func_807023B0(void) {
    s32 handle;

    func_8070207C(0);
    func_80701FEC(0);
    func_807022BC();
    handle = func_80702260();
    D_80701DC4_0[0] = handle;
    D_80701DC8_0[0] = func_80702314(handle);
    func_80702360();
    func_80701FEC(0);
    func_80702A78(D_80701DC4_1[0], D_80701DC8_1[0]);
    func_80702924(D_80701DC4_2[0]);
    return D_80701DC4_3[0];
}
