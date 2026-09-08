#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 pad0A[0xA];
    s16 height;
} FuncArg1;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
extern void *D_800E3D7C;
s32 func_8009A350();            /* extern */
void *func_8009B25C();           /* extern */
s32 func_800A0548();                        /* extern */
s16 func_800BCB04();                   /* extern */
extern s8 D_800DD7DC;


typedef struct S_8009AF18_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009AF18_0;   /* arg2 in func_8009AF18 */

typedef struct S_8009AF18_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_8009AF18_1;   /* world in func_8009AF18 */

typedef struct S_8009AF18_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8009AF18_2;   /* temp_v0 in func_8009AF18 */

typedef struct S_8009AF18_3 {
    u8 pad_00[0x124];
    void * unk_124;
} S_8009AF18_3;   /* *(void **)(page + 0x3D7C) in func_8009AF18 */

typedef struct S_8009AF18_4 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8009AF18_4;   /* ((S_8009AF18_3 *)(*(void **)(page + 0x3D7C)))->unk_124 in func_8009AF18 */

s32 func_8009AF18(u32 arg0, FuncArg1 *arg1, S_8009AF18_0 *arg2, u16 arg3) {
    u16 sp10[5];
    u16 *sp20;
    s32 temp_base;
    s32 temp_a2;
    s32 temp_fp;
    register s32 temp_s2;
    s32 temp_v1;
    s32 temp_ret;
    s32 temp_bound;
    s32 temp_s1;
    register s32 var_s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 var_s6;
    s32 var_s7;
    s32 var_v0;
    s32 var_s3;
    s32 var_s4;
    S_8009AF18_2 *temp_v0;

    var_s5 = 1;
    ASM_KEEP_NV(var_s5);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    D_800DD7DC = 0;
    var_s3 = arg2->unk_24;
    var_s4 = arg2->unk_25;
    temp_a2 = (arg0 >> 9) & 7;
    sp10[4] = arg3;
    var_s7 = (var_s3 << 6) | 0x20;
    var_s6 = (var_s4 << 6) | 0x20;
    if ((arg3 << 0x10) > 0) {
        temp_fp = temp_a2;
        temp_base = (s32)D_8006CCD8;
        temp_s2 = temp_fp << 1;
        sp20 = (u16 *)(temp_base + temp_s2);
loop_2:
        temp_s1 = (s16) var_s3;
        if (func_800A0548(temp_s1, (s16) var_s4) != 0) {
            return (s16) (var_s5 - 1);
        }
        if ((func_8009A350(temp_s1, (s16) var_s4, temp_fp, sp10) << 0x10) == 0) {
            goto call_fail;
        }
        {
            register u16 *reload_sp20 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            reload_sp20 = sp20;
            ASM_KEEP_NV(reload_sp20);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            var_s3 += *reload_sp20;
        }
            var_s4 += *(u16 *)((u8 *)D_8006CCE8 + temp_s2);
            if (sp10[0] & 0x3300) {
                {
                    register u8 *page ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    S_8009AF18_1 *world;

                    page = (u8 *)0x800E0000;
                    ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    world = *(void **)(page + 0x3D7C);
                    temp_v0 = func_8009B25C(world, var_s3 & 0xFFFF, var_s4 & 0xFFFF, world->unk_88);
                }
                if (temp_v0 != NULL) {
                    if (temp_v0->unk_13 == 0x1F) {
                        if (!(temp_v0->unk_1C & 0x228)) {
                            {
                                register u8 *page ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                                do { } while (0);
                                page = (u8 *)0x800E0000;
                                ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                                if (((S_8009AF18_4 *)(((S_8009AF18_3 *)(*(void **)(page + 0x3D7C)))->unk_124))->unk_13 < 0) {
                                D_800DD7DC = 1;
                                temp_v0->unk_14 |= 0x800000;
                                goto block_19;
                                }
                            }
                        }
                    }
                    /* Duplicate return node #20. Try simplifying control flow for better match */
                    return (s16)var_s5;
                }
                goto block_19;
            }
            var_s7 += *(u16 *)((u8 *)D_800DCEAC + temp_s2);
            var_s6 += *(u16 *)((u8 *)D_800DCEBC + temp_s2);
            {
                register FuncArg1 *reload_arg1 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                reload_arg1 = arg1;
                ASM_KEEP(reload_arg1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                temp_ret = func_800BCB04(var_s7 & 0xFFFF, var_s6 & 0xFFFF, reload_arg1->height);
            }
            temp_v1 = var_s5 + 1;
            if (temp_ret < 0x200) {
                goto loop_increment;
            }
            return (s16) (var_s5 - 1);
call_fail:
            return (s16) (var_s5 - 1);
loop_increment:
            var_s5 = temp_v1;
            do { } while (0);
            {
                register s32 temp_bound_raw ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 shifted_increment;

                temp_bound_raw = sp10[4];
                shifted_increment = temp_v1 << 0x10;
                ASM_KEEP_NV(shifted_increment);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                temp_bound = temp_bound_raw << 0x10;
                ASM_KEEP_DEP_NV(temp_bound, temp_bound_raw);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                if (shifted_increment <= temp_bound) {
                    goto loop_2;
                }
            }
            goto block_19;
    }
block_19:
    var_v0 = var_s5 << 0x10;
    return var_v0 >> 0x10;
}
