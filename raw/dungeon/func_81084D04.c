#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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
    register void *entity ASM_REG("$20") = arg3;
    register void *state ASM_REG("$23") = arg0;
    register u8 *delta_base ASM_REG("$2");
    register u32 initial_direction ASM_REG("$3");
    s16 *delta_x;
    s16 *delta_y;
    register s32 i ASM_REG("$21");
    register s32 x ASM_REG("$19");
    register s32 y ASM_REG("$18");
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
    register u32 scratch ASM_REG("$8");

    FIELD(entity, u8, 0x71) &= 0x7F;
    if (D_80083462 & 0x2000) {
        return -1;
    }
    if (!(FIELD(entity, u16, 0x46) & 0x8000) && (D_80083462 & 8)) {
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
    FIELD(state, u8, 0xAE) = 2;
    FIELD(state, s16, 0xAC) = i + 1;
    FIELD(entity, s32, 0x60) = result;
    goto failure;

initialize:
    delta_base = (u8 *)&D_8006CCD8;
    initial_direction = (FIELD(entity, u16, 0x2A) >> 9) & 7;
    direction_offset = initial_direction * 2;
    scratch = (u32)arg2;
    ASM_KEEP(scratch);
    x = FIELD((void *)scratch, u8, 0x24);
    y = FIELD((void *)scratch, u8, 0x25);
    ASM_KEEP(x);
    ASM_KEEP(y);
    delta_x = (s16 *)(delta_base + direction_offset);
    direction = initial_direction;
    if (0) {
        ASM_KEEP(delta_base);
        ASM_KEEP(initial_direction);
    }
    FIELD(state, s16, 0xA8) = x;
    FIELD(state, s16, 0xAA) = y;

loop:
    signed_x = (s16)x;
    initial_call_x = (signed_x << 6) & 0xFFC0;
    signed_y = (s16)y;
    call_y = (signed_y << 6) & 0xFFC0;
    scratch = direction;
    ASM_KEEP(scratch);
    if ((func_800A44E0(initial_call_x,
                       call_y,
                       FIELD(entity, s16, 0x88), scratch << 9) << 16) != 0) {
        goto failure_arg;
    }

    call_x = (((signed_x + *delta_x) << 6) + 0x20) & 0xFFE0;
    delta_y = (s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    height_result = func_800BCB04(
        call_x,
        (((signed_y + *delta_y) << 6) + 0x20) & 0xFFE0,
        (s16)(FIELD(entity, u16, 0x88) - 0x20));
    if (height_result >= 0x201) {
        goto failure;
    }
    if ((u16)(height_result - FIELD(entity, u16, 0x88) + 0x3F) >= 0x7F) {
        goto failure;
    }

    {
        register u32 step_x ASM_REG("$5");
        register u32 step_y ASM_REG("$6");

        step_x = (u16)*delta_x;
        step_y = (u16)*delta_y;
        step_x = (u16)(x + step_x);
        step_y = (u16)(y + step_y);
        if (0) {
            ASM_KEEP(step_x);
            ASM_KEEP(step_y);
        }
        result = func_8009B4B0(entity, step_x, step_y);
    }
    if (result != 0) {
        goto success;
    }
    {
        register s32 next_x ASM_REG("$3");
        register s32 next_y ASM_REG("$2");

        i++;
        next_x = x + (u16)*delta_x;
        x = next_x;
        next_y = y + (u16)*delta_y;
        y = next_y;
        FIELD(state, s16, 0xAA) = next_y;
        FIELD(state, s16, 0xA8) = next_x;
        if (0) {
            ASM_KEEP(next_x);
            ASM_KEEP(next_y);
        }
    }
    if (i < 8) {
        goto loop;
    }

failure_arg:
    ASM_KEEP(entity);
failure:
    FIELD(state, u8, 0x9A) = 0x1A;
    FIELD(state, u8, 0x9B) = 0;
    FIELD(state, s32, 0x8C) = 0;
    FIELD(state, s16, 0x96) = 8;
    FIELD(entity, u8, 0x84) = 0x7E;
    FIELD(entity, u8, 0x85) = 8;
    func_800A4ACC(entity);
    FIELD(entity, u8, 0x6D)--;
    copy_dest = (u8 *)entity - 0x20;
    if (FIELD(state, u8, 0xAE) != 2) {
        goto copy_data;
    }
    func_8009C93C(entity, arg2, FIELD(entity, s16, 0x2A),
                  (s16)(i + 1), FIELD(entity, s32, 0x60));
    ASM_KEEP(i);
    goto done;

copy_data:
    ASM_KEEP(state);
    func_800C77D0(copy_dest, arg1, 8, 0x300);
    ASM_KEEP(entity);

done:
    return 0;
}
