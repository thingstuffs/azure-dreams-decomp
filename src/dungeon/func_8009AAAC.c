#include "common.h"
extern void itm_mon_koyaw_set(void *);
extern u8 D_800DD83C[];
extern u8 D_800DD840[];
extern u8 D_800DD844[];
extern u8 D_800DD848[];
extern u8 D_800DD84C[];
extern u8 D_800DD850[];

/* Selects koyaw data from the flags and applies it unless disabled. */
void func_800A020C(s32 flags) {
    if (!(flags & 0x10000000)) {
        void *koyaw_data;
        if (flags & 8) {
            koyaw_data = (void *)D_800DD844;
        } else if (flags & 0x20) {
            koyaw_data = (void *)D_800DD850;
        } else if (flags & 0x40) {
            koyaw_data = (void *)D_800DD848;
        } else if (flags & 0x400) {
            koyaw_data = (void *)D_800DD840;
        } else if (flags & 0x10) {
            koyaw_data = (void *)D_800DD84C;
        } else {
            {

                koyaw_data = (void *)D_800DD83C;
            }
        }
        if (koyaw_data != 0) {
            itm_mon_koyaw_set(koyaw_data);
        }
    }
}
