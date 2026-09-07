#include "common.h"

typedef struct S_80172504_0 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x2];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_80172504_0;   /* entity in func_80172504 */

typedef struct S_80172504_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
    s16 unk_AA;
    s16 unk_AC;
    u8 unk_AE;
} S_80172504_1;   /* state in func_80172504 */

typedef struct S_80172504_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172504_2;   /* (void *)scratch in func_80172504 */



extern s32 func_8009B4B0();
extern void func_8009C93C();
extern s32 func_800A2B5C();
extern s32 func_800A44E0();
extern void func_800A4ACC();
extern s16 func_800BCB04();
extern void func_800C77D0();
extern void func_800C7930();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u16 D_80083462;

s32 func_80172504(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *entity ASM_REG("$20") = arg3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *state ASM_REG("$23") = arg0;   /* MATCH pin: retail register colouring depends on it */
    u8 *delta_base;
    register u32 initial_direction ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s16 *delta_x;
    s16 *delta_y;
    register s32 i ASM_REG("$21");   /* MATCH pin: retail register colouring depends on it */
    register s32 x ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 y ASM_REG("$18");   /* MATCH pin: load-bearing for the whole function shape */
    s32 signed_x;
    s32 signed_y;
    s32 direction_offset;
    s32 result;
    s32 initial_call_x;
    s32 call_x;
    s32 call_y;
    void *copy_dest;
    s16 height_result;
    u16 direction;
    register u32 scratch ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */

    ((S_80172504_0 *)entity)->unk_71 &= 0x7F;
    if (D_80083462 & 0x2000) {
        return -1;
    }
    if (!(((S_80172504_0 *)entity)->unk_46 & 0x8000) && (D_80083462 & 8)) {
        return -1;
    }
    if ((func_800A2B5C(entity) << 16) != 0) {
        return -1;
    }
    func_800C7930((u8 *)entity - 0x20, arg1, 8, 0x300);
    result = func_800A2B5C(entity);
    i = 0;
    if ((result << 16) == 0) {
        goto initialize;
    }
    return -1;

success:
    ((S_80172504_1 *)state)->unk_AE = 2;
    ((S_80172504_1 *)state)->unk_AC = i + 1;
    ((S_80172504_0 *)entity)->unk_60 = result;
    goto failure;

initialize:
    delta_base = (u8 *)&D_8006CCD8;
    initial_direction = (((S_80172504_0 *)entity)->unk_2A.s >> 9) & 7;
    direction_offset = initial_direction * 2;
    scratch = (u32)arg2;
    x = ((S_80172504_2 *)((void *)scratch))->unk_24;
    y = ((S_80172504_2 *)((void *)scratch))->unk_25;
    delta_x = (s16 *)(delta_base + direction_offset);
    direction = initial_direction;
    if (0) {
    }
    ((S_80172504_1 *)state)->unk_A8 = x;
    ((S_80172504_1 *)state)->unk_AA = y;

loop:
    signed_x = (s16)x;
    initial_call_x = (signed_x << 6) & 0xFFC0;
    signed_y = (s16)y;
    call_y = (signed_y << 6) & 0xFFC0;
    scratch = direction;
    if ((func_800A44E0(initial_call_x,
                       call_y,
                       ((S_80172504_0 *)entity)->unk_88.s, scratch << 9) << 16) != 0) {
        goto failure_arg;
    }

    call_x = (((signed_x + *delta_x) << 6) + 0x20) & 0xFFE0;
    delta_y = (s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    height_result = func_800BCB04(
        call_x,
        (((signed_y + *delta_y) << 6) + 0x20) & 0xFFE0,
        (s16)(((S_80172504_0 *)entity)->unk_88.u - 0x20));
    if (height_result >= 0x201) {
        goto failure;
    }
    if ((u16)(height_result - ((S_80172504_0 *)entity)->unk_88.u + 0x3F) >= 0x7F) {
        goto failure;
    }

    {
        register u32 step_x ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
        register u32 step_y ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */

        step_x = (u16)*delta_x;
        step_y = (u16)*delta_y;
        step_x = (u16)(x + step_x);
        step_y = (u16)(y + step_y);
        if (0) {
        }
        result = func_8009B4B0(entity, step_x, step_y);
    }
    if (result != 0) {
        goto success;
    }
    {
        register s32 next_x ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register s32 next_y ASM_REG("$2");   /* MATCH pin: retail keeps a computation the compiler would drop */

        i++;
        next_x = x + (u16)*delta_x;
        x = next_x;
        next_y = y + (u16)*delta_y;
        y = next_y;
        ((S_80172504_1 *)state)->unk_AA = next_y;
        ((S_80172504_1 *)state)->unk_A8 = next_x;
        if (0) {
        }
    }
    if (i < 8) {
        goto loop;
    }

failure_arg:
    ASM_KEEP(entity);   /* MATCH pin: load-bearing for the whole function shape */
failure:
    ((S_80172504_1 *)state)->unk_9A = 0x1A;
    ((S_80172504_1 *)state)->unk_9B = 0;
    ((S_80172504_1 *)state)->unk_8C = 0;
    ((S_80172504_1 *)state)->unk_96 = 8;
    ((S_80172504_0 *)entity)->unk_84 = 0x7E;
    ((S_80172504_0 *)entity)->unk_85 = 8;
    func_800A4ACC(entity);
    ((S_80172504_0 *)entity)->unk_6D--;
    copy_dest = (u8 *)entity - 0x20;
    if (((S_80172504_1 *)state)->unk_AE != 2) {
        goto copy_data;
    }
    func_8009C93C(entity, arg2, ((S_80172504_0 *)entity)->unk_2A.u,
                  (s16)(i + 1), ((S_80172504_0 *)entity)->unk_60);
    goto done;

copy_data:
    func_800C77D0(copy_dest, arg1, 8, 0x300);

done:
    return 0;
}
