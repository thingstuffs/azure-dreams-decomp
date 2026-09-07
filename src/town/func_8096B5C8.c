#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800671A8(); /* extern */
s32 func_80123200();                             /* extern */
M2C_UNK func_80123928();               /* extern */
M2C_UNK func_801239B8(); /* extern */
extern M2C_UNK D_8011ACD8;
typedef struct {
    void *image;
    void **image_ref;
    u16 unused;
    u16 width;
} ImageEntry;
extern ImageEntry D_80126E98[];

typedef struct S_80123A60_0 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_80123A60_0;   /* object in func_80123A60 */

void func_80123A60(void *arg0) {
    S_80123A60_0 *object = arg0;
    s16 sp10[4];
    ImageEntry *var_s2;
    u8 *loop_image_base;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_s0;
    s32 var_s1;
    s32 temp_v0;
    s32 temp_v1;

    sp10[0] = 0x180;
    sp10[1] = 0x80;
    sp10[2] = 0x36;
    sp10[3] = 0x60;
    func_800671A8(sp10, 0, 0, 0);
    func_801239B8(&D_8011ACD8, 0x192, 0xD0);
    func_80067014(0);
    temp_v1 = object->unk_0F;
    var_s1 = 0;
    if (temp_v1 == 3) {
        ASM_KEEP(temp_v1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        var_s1 = temp_v1;
        temp_s0 = var_s1 * 0x10;
        ASM_KEEP(temp_s0);   /* MATCH pin: load-bearing for the whole function shape */
        if (func_80123200(temp_s0 & 0xF0) & 0xFF) {
            u8 *image_base = (u8 *)D_80126E98;
            void **image_ptr;
            image_ptr = (void **)((((var_s1 << 5) + temp_s0) << 2) +
                                  (u32)image_base);
            func_80123928(*image_ptr, 0x180, 0x80);
        }
        temp_s0_2 = temp_s0 + 1;
        if (func_80123200(temp_s0_2 & 0xFF) & 0xFF) {
            func_80123928(D_80126E98[temp_s0_2].image, 0x1A4, 0xA0);
        }
        goto done;
    }
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    temp_v0 = object->unk_0F;
    ASM_KEEP(temp_v0);   /* MATCH pin: retail basic-block layout depends on it */
    loop_image_base = (u8 *)D_80126E98;
    ASM_KEEP(loop_image_base);   /* MATCH pin: retail basic-block layout depends on it */
    var_s0 = temp_v0 * 0x10;
    var_s2 = (ImageEntry *)(((((temp_v0 << 5) + var_s0) << 2)) +
                            (u32)loop_image_base);
    do {
        if (func_80123200(var_s0 & 0xFF) & 0xFF) {
            func_80123928(var_s2->image, (s16) (((var_s1 % 3) * 0x12) + 0x180), (s16) (((var_s1 / 3) * 0x10) + 0x80));
        }
        var_s1 += 1;
        var_s2 += 1;
        var_s0 += 1;
    } while (var_s1 < 0x10);
done:
    func_80067014(0);
}
/* MECHANISM: A four-halfword array establishes the 0x28 frame and exact store schedule.
   Guarded s0 holds the argument; scoped s32 keeps preserve the category/shifted roles.
   Named ImageEntry bases and byte-scaled expressions reproduce both address chains.
   A memory fence plus reload keep yields lbu/lui/addiu with no load-delay nop. */
