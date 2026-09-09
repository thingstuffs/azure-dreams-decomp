#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800A32A4_1 {
    u8 pad_00[0x14A8];
    s32 unk_14A8;
} S_800A32A4_1;   /* page_base in func_800A32A4 */

typedef struct S_800A32A4_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    void * unk_D0;
} S_800A32A4_2;   /* temp_a0 in func_800A32A4 */

typedef struct S_800A32A4_3 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800A32A4_3;   /* temp_s2 in func_800A32A4 */

typedef struct S_800A32A4_4 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_800A32A4_4;   /* computed_dest in func_800A32A4 */

typedef struct S_800A32A4_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A32A4_5;   /* var_a2 in func_800A32A4 */

typedef struct S_800A32A4_6 {
    u8 pad_00[0x1C];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
} S_800A32A4_6;   /* temp_a0_2 in func_800A32A4 */

struct S_800E3E48 {
  u8 pad00[0x14];
  s32 unk14;
  u8 pad18[0x1C - 0x18];
  s32 unk1C;
  u8 pad20[0x8C - 0x20];
};
struct S_16 {
  s32 w0;
  s32 w4;
  s32 w8;
  s32 wC;
};
struct S_12 {
  s32 w0;
  s32 w4;
  s32 w8;
};
typedef struct S_800E3E48 S_800E3E48;
extern S_800E3E48 D_800E3E48[];
extern s32 D_800E3DF0[];
extern s32 D_80083460[3];
extern void func_80042B68(void *, s32);
extern M2C_UNK func_800A18E8();
extern M2C_UNK func_800A31D0();

s32 func_800A32A4(void *arg0) {
    register M2C_UNK var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 *temp_a0_2 ASM_REG("$4"); /* MATCH: keep the counter base in a0 after replacing the label call with local control flow. */
    s32 temp_a1_2;
    s32 temp_v1;
    s32 temp_v1_2;
    register s32 flag_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 tail_w0;
    s32 tail_w4;
    s32 tail_w8;
    volatile s32 *tail_src;
    s32 var_v1;
    register S_800A32A4_4 *computed_dest ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    S_800A32A4_2 *temp_a0;
    S_800A32A4_3 *temp_s2;
    void *var_a2;
    void *var_a3;
    u8 *page_base;
    register u8 *status_page ASM_REG("$2"); /* MATCH: keep the page immediate and flag mask in v0 while the counter base uses a0. */
    register s32 flags_mask ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    S_800E3E48 *copy_base;
    s32 *registry;
    void *copy_end;

    var_s1 = 0;
    ASM_KEEP_NV(var_s1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_s2 = 0;
    func_80042B68(arg0, 0x1A);
    func_80042B68(arg0, 0x1C);
    func_80042B68(arg0, 0x1D);
    if (!(((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 & 0x20000000)) {
        func_800A31D0(arg0);
        var_v1 = 0;
        page_base = (u8 *)0x80080000;
        flags_mask = ~0x4000;
        registry = D_800E3DF0;
        copy_base = D_800E3E48;
        copy_end = arg0 + 0x80;
loop_2:
        temp_a1_2 = var_v1 * 4;
        temp_a0 = temp_a1_2 + ((S_800A32A4_1 *)page_base)->unk_14A8;
        var_v1 += 1;
        if (temp_a0->unk_AC == arg0) {
            ((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 = (s32)(((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 & flags_mask);
            temp_a0->unk_AC = 0;
            flag_value = ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32;
            flag_value |= 0x04000000;
            flag_value |= 0x00020000;
            ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = flag_value;
            temp_s2 = temp_a0->unk_D0;
            temp_s2->unk_03 = (u8)(temp_s2->unk_03 & 0xDF);
            computed_dest = (void *)((S_800A32A4_1 *)page_base)->unk_14A8;
            computed_dest = (void *)((u32)temp_a1_2 + (u32)computed_dest);
            computed_dest->unk_D0 = 0;
            var_s1 = 3;
            var_a3 = arg0;
            temp_v1 = temp_s2->unk_03 & 0x1F;
            ASM_USE(var_s1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            computed_dest = (void *)((temp_v1 * sizeof(*copy_base)) + (s32)copy_base);
            var_a2 = computed_dest;
            registry[temp_v1] = (s32)var_a2;
            do {
                *(struct S_16 *)var_a2 = *(struct S_16 *)var_a3;
                var_a3 += 0x10;
                var_a2 += 0x10;
            } while (var_a3 != copy_end);
            tail_src = (volatile s32 *)var_a3;
            tail_w0 = tail_src[0];
            tail_w4 = tail_src[1];
            tail_w8 = tail_src[2];
            ((S_800A32A4_5 *)var_a2)->unk_00 = tail_w0;
            ((S_800A32A4_5 *)var_a2)->unk_04 = tail_w4;
            ((S_800A32A4_5 *)var_a2)->unk_08 = tail_w8;
            goto block_8;
        }
        if (var_v1 >= 4) {
            goto block_8;
        }
        goto loop_2;
    }
block_8:
    if (var_s1 == 0) {
        temp_v1_2 = ((Rec_D_800E3D7C *)arg0)->unk_14.as_s32;
        var_s1 = 3;
        if (!(temp_v1_2 & 0x4000)) {
            status_page = (u8 *)(temp_v1_2 & 0x2000);
            if (status_page) {
                status_page = (u8 *)0x80080000;
                ASM_KEEP_NV(status_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                temp_a0_2 = (s32 *)(status_page + 0x3460);
                if (((S_800A32A4_6 *)temp_a0_2)->unk_1C.s != 0) {
                    ((S_800A32A4_6 *)temp_a0_2)->unk_1C.s = (s16)(((S_800A32A4_6 *)temp_a0_2)->unk_1C.u - 1);
                }
                var_s1 = 2;
            } else {
                status_page = (u8 *)0x80080000;
                ASM_KEEP_NV(status_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                temp_a0_2 = (s32 *)(status_page + 0x3460);
                if (((S_800A32A4_6 *)temp_a0_2)->unk_1C.s != 0) {
                    ((S_800A32A4_6 *)temp_a0_2)->unk_1C.s = (s16)(((S_800A32A4_6 *)temp_a0_2)->unk_1C.u - 1);
                }
                var_s1 = 1;
            }
        }
    }
block_18:
    if (!(((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 & 0x20000000)) {
        func_800A18E8(((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v, var_s1);
    }
    return (s32)temp_s2;
}
