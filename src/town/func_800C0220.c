#include "common.h"
#include "m2c_compat.h"

void func_8003DB94(void *, void *, s32, void *);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BD688;
extern M2C_UNK D_800BD898;
extern M2C_UNK D_800E9E14;

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[2];
} Copy8;


typedef struct S_800BD980_0 {
    u8 pad_00[0xC];
    volatile u16 unk_0C;
    volatile u16 unk_0E;
    volatile u16 unk_10;
} S_800BD980_0;   /* temp_v1 in func_800BD980 */

typedef struct S_800BD980_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800BD980_1;   /* temp_a3 in func_800BD980 */

typedef struct S_800BD980_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BD980_2;   /* temp_a0 in func_800BD980 */

s32 func_800BD980(void *arg0) {
    void *src;
    s32 var_s1;
    s32 var_s4;
    S_800BD980_2 *temp_a0;
    S_800BD980_1 *temp_a3;
    void *temp_v0;
    S_800BD980_0 *temp_v1;
    void *var_s3;
    M2C_UNK *bd898;

    src = arg0;
    var_s3 = NULL;
    temp_v0 = func_8003FD64(0x202, &D_80083498);
    if (temp_v0 != NULL) {
        var_s3 = temp_v0 + 0x20;
        (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = &D_800BD688;
        (*(Copy16 *)((u8 *)temp_v0 + 0x28)) = (*(Copy16 *)((u8 *)src + 0));
        (*(Copy8 *)((u8 *)temp_v0 + 0x38)) = (*(Copy8 *)((u8 *)src + 0x10));
    }
    var_s1 = 1;
    bd898 = &D_800BD898;
    var_s4 = 0x300000;
    var_s3 = var_s3 + 4;
    do {
        temp_v0 = func_8003FD64(0x312, &D_80083498);
        if (temp_v0 != NULL) {
            s32 xoff;
            s32 color;
            u16 first;
            u16 second;
            s32 offset0;
            s32 offset4;
            s32 offset8;

            func_8004491C(temp_v0, &D_80045340);
            xoff = 0xFFF88000;
            color = 0x800000;
            temp_a3 = (*(void **)((u8 *)temp_v0 + 8));
            color |= 0x8080;
            (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = bd898;
            *(void **)var_s3 = temp_a3;
            temp_a0 = (*(void **)((u8 *)temp_v0 + 0xC));
            ASM_KEEP(temp_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
            first = (*(u16 *)((u8 *)src + 2));
            temp_v1 = temp_v0 + 0x20;
            temp_v1->unk_0C = first;
            second = (*(volatile u16 *)((u8 *)src + 6));
            temp_v1->unk_0E = second;
            temp_v1->unk_10 = (*(volatile u16 *)((u8 *)src + 0xA));
            offset0 = var_s4 + 0x01400000;
            temp_a3->unk_00 = (s32) ((*(s32 *)((u8 *)src + 0)) + offset0);
            {
                s32 input4;
                input4 = (*(s32 *)((u8 *)src + 4));
                offset4 = var_s1 << 0x15;
                temp_a3->unk_04 = (s32) (input4 + offset4);
            }
            offset8 = (var_s1 << 0x13) + 0xFF800000;
            temp_a3->unk_08 = (s32) ((*(s32 *)((u8 *)src + 8)) + offset8);
            ASM_KEEP_NV(xoff);   /* MATCH pin: retail immediate-load split depends on it */
            temp_a3->unk_0C = (s32) (xoff - (var_s1 << 0x10));
            temp_a0->unk_1E = 0x1000;
            temp_a0->unk_1C = 0x1000;
            temp_a0->unk_0C = color;
            func_8003DB94(temp_a0, &D_800E9E14, 0, temp_a3);
        }
        var_s4 += 0xFFD00000;
        var_s1 -= 1;
        var_s3 = (void *)((s8 *)var_s3 - 4);
    } while (var_s1 >= 0);
    return 0;
}
