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
            u32 data_page = 0x800E0000;
            ASM_KEEP(data_page);
            koyaw_data = (void *)(data_page - 0x27BC);
        } else if (flags & 0x20) {
            u32 data_page = 0x800E0000;
            ASM_KEEP(data_page);
            koyaw_data = (void *)(data_page - 0x27B0);
        } else if (flags & 0x40) {
            u32 data_page = 0x800E0000;
            ASM_KEEP(data_page);
            koyaw_data = (void *)(data_page - 0x27B8);
        } else if (flags & 0x400) {
            u32 data_page = 0x800E0000;
            ASM_KEEP(data_page);
            koyaw_data = (void *)(data_page - 0x27C0);
        } else if (flags & 0x10) {
            u32 data_page = 0x800E0000;
            ASM_KEEP(data_page);
            koyaw_data = (void *)(data_page - 0x27B4);
        } else {
            ASM_CLOBBER("$2");
            {
                u32 data_page = 0x800E0000;

                ASM_KEEP(data_page);
                koyaw_data = (void *)(data_page - 0x27C4);
            }
        }
        if (koyaw_data != 0) {
            itm_mon_koyaw_set(koyaw_data);
        }
    }
}
