#include "common.h"
extern void func_800A0150(void *);
extern void func_800A028C(void *);
extern u8 D_800DD83C[];
extern u8 D_800DD840[];
extern u8 D_800DD844[];
extern u8 D_800DD848[];
extern u8 D_800DD84C[];
extern u8 D_800DD850[];
void func_800A020C(s32 flags) {
    if (!(flags & 0x10000000)) {
        if (flags & 8) {
            register u32 page ASM_REG("$2") = 0x800E0000;   /* MATCH pin: retail basic-block layout depends on it */
            ASM_KEEP(page);   /* MATCH pin: retail basic-block layout depends on it */
            func_800A028C((void *)(page - 0x27BC));
            return;
        }
        if (flags & 0x20) {
            register u32 page ASM_REG("$2") = 0x800E0000;   /* MATCH pin: retail basic-block layout depends on it */
            ASM_KEEP(page);   /* MATCH pin: retail basic-block layout depends on it */
            func_800A028C((void *)(page - 0x27B0));
            return;
        }
        if (flags & 0x40) {
            register u32 page ASM_REG("$2") = 0x800E0000;   /* MATCH pin: retail basic-block layout depends on it */
            ASM_KEEP(page);   /* MATCH pin: retail basic-block layout depends on it */
            func_800A028C((void *)(page - 0x27B8));
            return;
        }
        if (flags & 0x400) {
            register u32 page ASM_REG("$2") = 0x800E0000;   /* MATCH pin: retail basic-block layout depends on it */
            ASM_KEEP(page);   /* MATCH pin: retail basic-block layout depends on it */
            func_800A028C((void *)(page - 0x27C0));
            return;
        }
        if (flags & 0x10) {
            register u32 page ASM_REG("$2") = 0x800E0000;   /* MATCH pin: retail basic-block layout depends on it */
            ASM_KEEP(page);   /* MATCH pin: retail basic-block layout depends on it */
            func_800A028C((void *)(page - 0x27B4));
            return;
        }
        ASM_CLOBBER("$2");   /* MATCH pin: retail basic-block layout depends on it */
        {
            u32 page = 0x800E0000;
            void *ptr;

            ASM_KEEP(page);   /* MATCH pin: retail basic-block layout depends on it */
            ptr = (void *)(page - 0x27C4);
            if (ptr != 0) {
                func_800A0150(ptr);
            }
        }
    }
}

/* MECHANISM: Every address site holds the 0x800e page in guarded $v0, exposing
   retail's split lui/addiu roles; a guarded clobber forces the final fresh lui.
   The natural 0x18-byte nonleaf frame saves only $ra at 0x10. */
