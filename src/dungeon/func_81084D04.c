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

/* Scan up to eight tiles ahead for a valid target and update the entity action state. */
s32 func_80172504(void *action_state, void *transfer_data, void *origin, void *actor) {
    register void *entity ASM_REG("$20") = actor;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *state ASM_REG("$23") = action_state;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *x_delta_table;
    register u32 initial_direction ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 *delta_x;
    s16 *delta_y;
    register s32 step_count ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 tile_x ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 tile_y;
    s32 signed_x;
    s32 signed_y;
    s32 direction_offset;
    s32 check_result;
    s32 world_x;
    s32 next_world_x;
    s32 world_y;
    void *copy_dest;
    s16 next_height;
    u16 direction;
    register u32 origin_or_direction ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

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
    func_800C7930((u8 *)entity - 0x20, transfer_data, 8, 0x300);
    check_result = func_800A2B5C(entity);
    step_count = 0;
    if ((check_result << 16) == 0) {
        goto initialize;
    }
    return -1;

success:
    ((S_80172504_1 *)state)->unk_AE = 2;
    ((S_80172504_1 *)state)->unk_AC = step_count + 1;
    ((S_80172504_0 *)entity)->unk_60 = check_result;
    goto finish;

initialize:
    x_delta_table = (u8 *)&D_8006CCD8;
    initial_direction = (((S_80172504_0 *)entity)->unk_2A.s >> 9) & 7;
    direction_offset = initial_direction * 2;
    origin_or_direction = (u32)origin;
    tile_x = ((S_80172504_2 *)((void *)origin_or_direction))->unk_24;
    tile_y = ((S_80172504_2 *)((void *)origin_or_direction))->unk_25;
    delta_x = (s16 *)(x_delta_table + direction_offset);
    direction = initial_direction;
    if (0) {
    }
    ((S_80172504_1 *)state)->unk_A8 = tile_x;
    ((S_80172504_1 *)state)->unk_AA = tile_y;

loop:
    signed_x = (s16)tile_x;
    world_x = (signed_x << 6) & 0xFFC0;
    signed_y = (s16)tile_y;
    world_y = (signed_y << 6) & 0xFFC0;
    origin_or_direction = direction;
    if ((func_800A44E0(world_x,
                       world_y,
                       ((S_80172504_0 *)entity)->unk_88.s, origin_or_direction << 9) << 16) != 0) {
        goto finish_pinned;
    }

    next_world_x = (((signed_x + *delta_x) << 6) + 0x20) & 0xFFE0;
    delta_y = (s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    next_height = func_800BCB04(
        next_world_x,
        (((signed_y + *delta_y) << 6) + 0x20) & 0xFFE0,
        (s16)(((S_80172504_0 *)entity)->unk_88.u - 0x20));
    if (next_height >= 0x201) {
        goto finish;
    }
    if ((u16)(next_height - ((S_80172504_0 *)entity)->unk_88.u + 0x3F) >= 0x7F) {
        goto finish;
    }

    {
        register u32 step_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        u32 step_y;

        step_x = (u16)*delta_x;
        step_y = (u16)*delta_y;
        step_x = (u16)(tile_x + step_x);
        step_y = (u16)(tile_y + step_y);
        if (0) {
        }
        check_result = func_8009B4B0(entity, step_x, step_y);
    }
    if (check_result != 0) {
        goto success;
    }
    {
        register s32 next_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 next_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */

        step_count++;
        next_x = tile_x + (u16)*delta_x;
        tile_x = next_x;
        next_y = tile_y + (u16)*delta_y;
        tile_y = next_y;
        ((S_80172504_1 *)state)->unk_AA = next_y;
        ((S_80172504_1 *)state)->unk_A8 = next_x;
        if (0) {
        }
    }
    if (step_count < 8) {
        goto loop;
    }

finish_pinned:
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
finish:
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
    func_8009C93C(entity, origin, ((S_80172504_0 *)entity)->unk_2A.u,
                  (s16)(step_count + 1), ((S_80172504_0 *)entity)->unk_60);
    goto done;

copy_data:
    func_800C77D0(copy_dest, transfer_data, 8, 0x300);

done:
    return 0;
}
