#include "common.h"

typedef struct S_80172840_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172840_0;   /* arg3 in func_80172840 */

typedef struct S_80172840_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80172840_1;   /* arg0 in func_80172840 */

typedef struct S_80172840_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172840_2_pre;   /* the 0x14 bytes before move_object in func_80172840, addressed as move_object[-1] */

typedef struct S_80172840_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172840_3;   /* record in func_80172840 */

typedef struct S_80172840_4 {
    u8 pad_00[0x4];
    union { s8 s; u8 u; } unk_04;   /* accessed as both */
    u8 pad_05[0x3];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80172840_4;   /* arg2 in func_80172840 */

typedef struct S_80172840_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172840_5;   /* arg1 in func_80172840 */

typedef struct S_80172840_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80172840_6;   /* D_800814A8[0] in func_80172840 */

typedef struct S_80172840_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172840_7;   /* spawn in func_80172840 */

typedef struct S_80172840_8 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x36];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80172840_8;   /* spawn_fields in func_80172840 */

typedef struct S_80172840_9 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80172840_9;   /* data in func_80172840 */

typedef struct S_80172840_10 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172840_10;   /* base in func_80172840 */

typedef struct S_80172840_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172840_11;   /* status in func_80172840 */

typedef struct S_80172840_12 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
} S_80172840_12;   /* ((S_80172840_7 *)spawn)->unk_08 in func_80172840 */

extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A6D30(void);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern u8 D_8006DE24[0x200];
extern u8 *D_800814A8[3];
extern s16 D_80083228[2];
extern u8 D_80083460[0x20];
extern s32 D_8008346C[3];
extern u8 D_80083498[0x10];
extern u8 D_80045340[0x10];
extern u8 D_800DEA68[0x20];
extern u8 D_80170E68[0x10];
extern void *D_80170838[];
extern u8 D_80173EC0[0x10];
extern u8 D_80174194[0x10];

/* Updates a move action, spawning particles and resetting state when it ends. */
void func_80172840(void *action, void *position, void *sprite_in, void *actor_in)
{
    s32 direction_offset;
    s32 one;
    u8 *move_slot;
    s32 phase;
    register s32 is_special;
    register s32 saved_reg ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u16 coords[7];
    volatile s32 direction_x;
    s32 direction_y;
    S_80172840_10 *effect_base;
    register s32 move_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 move_y;
    S_80172840_11 *status;
    s32 counter;
    void *particle;
    u16 source_x;
    u16 offset_x;
    u16 source_y;
    u16 offset_y;
    u16 source_z;
    u16 offset_z;
    s32 color;
    s32 effect_value;
    u8 *particle_fields;
    u32 heading;
    u8 *direction_x_ptr;
    s32 direction_x_value;
    register u8 *direction_y_table ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *direction_y_ptr;
    register void *sprite ASM_REG("$20") = sprite_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$19") = actor_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP4_NV(sprite, actor, saved_reg, heading);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    direction_x_ptr = D_8006CCD8;

    {
        heading = ((S_80172840_0 *)actor)->unk_2A.s;
        one = 1;
        counter = heading >> 8;
        direction_offset = counter & 0xE;
        direction_x_ptr = direction_offset + direction_x_ptr;
        direction_y_table = (u8 *)D_8006CCE8;
        direction_x_value = *(s16 *)direction_x_ptr;
        direction_y_ptr = (u8 *)((unsigned long)direction_offset + (unsigned long)direction_y_table);
        direction_x = direction_x_value;
    }
    phase = ((S_80172840_1 *)action)->unk_9B;
    direction_y = *(s16 *)direction_y_ptr;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    is_special = 0;

    if (phase == one) {
        goto state_1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_0;
        }
        goto done;
    }
    if (phase == 2) {
        goto state_2;
    }
    goto done;

state_0:
{
    s32 move_kind;
    void *move_object;
    s16 special_flag;

    if (((S_80172840_0 *)actor)->unk_1C & 0x2000) {
        u32 kind_index = (((S_80172840_0 *)actor)->unk_46 & 0x3FFF) - 1;
        static void *const switch_keep[] = {
            &&special_3, &&special_2, &&special_1, &&kind_none,
            &&special_3, &&special_2, &&special_1
        };

        if (kind_index >= 7) {
            goto kind_none;
        }
        (void)switch_keep;
        goto *D_80170838[kind_index];

special_3:
        is_special = 1;
        goto kind_3;
special_2:
        is_special = 1;
        goto kind_2;
special_1:
        is_special = 1;
        goto kind_1;
    }

    move_kind = ((S_80172840_0 *)actor)->unk_46 & 0x3FFF;
    if (move_kind == 2) {
        goto kind_2;
    }
    if (move_kind < 3) {
        if (move_kind == one) {
            goto kind_1;
        }
        move_slot = 0;
        goto have_selector;
    }
    if (move_kind != 3) {
        move_slot = 0;
        goto have_selector;
    }

kind_3:
    move_slot = (u8 *)actor + 0x0E;
    goto have_selector;
kind_2:
    move_slot = (u8 *)actor + 0x0B;
    goto have_selector;
kind_1:
    move_slot = (u8 *)actor + 8;
    goto have_selector;
kind_none:
    move_slot = 0;

have_selector:
    if (*move_slot != 0) {
        ((S_80172840_1 *)action)->unk_98 &= 0xFF7F;
        special_flag = is_special;
        if (special_flag != 0) {
            move_object = D_800814A8[0];
            ((S_80172840_0 *)actor)->unk_60 = move_object;
            goto copy_record;
        }
        if (D_8006DE24[(*move_slot * 20) + 0x12] == 2) {
            move_object = ((S_80172840_0 *)actor)->unk_60;
            if (move_object != 0) {
copy_record:
                {
                    register void *move_record ASM_REG("$3") =
                        ((S_80172840_2_pre *)move_object)[-1].unk_00;
                    ((S_80172840_0 *)actor)->unk_72.s = ((S_80172840_3 *)move_record)->unk_24;
                    ((S_80172840_0 *)actor)->unk_73.s = ((S_80172840_3 *)move_record)->unk_25;
                }
            }
            goto apply_move;
        }
        ((S_80172840_0 *)actor)->unk_60 = func_800A05A4(
            actor,
            ((S_80172840_4 *)sprite)->unk_24,
            ((S_80172840_4 *)sprite)->unk_25,
            ((S_80172840_0 *)actor)->unk_2A.u,
            0x10);
        move_x = ((S_80172840_0 *)actor)->unk_72.u;
        move_y = ((S_80172840_0 *)actor)->unk_73.u;
        if (move_x < 0) {
            move_x = -move_x;
        }
        if (move_y < 0) {
            move_y = -move_y;
        }
        ((S_80172840_0 *)actor)->unk_72.s = move_x;
        ((S_80172840_0 *)actor)->unk_73.s = move_y;

apply_move:
        coords[0] = ((S_80172840_5 *)position)->unk_02;
        coords[1] = ((S_80172840_5 *)position)->unk_06;
        coords[2] = ((S_80172840_5 *)position)->unk_08.at02.v;
        if (func_800A94A0(actor, move_slot, is_special,
                          (u8 *)action + 0x98) == 0) {
            goto done;
        }
        ((S_80172840_4 *)sprite)->unk_14 &= 0xF7FF;
        func_800A56E0(0x703);
        ((S_80172840_1 *)action)->unk_A8.s = -1;
        ((S_80172840_1 *)action)->unk_9B++;
        goto done;
    }

    ((S_80172840_5 *)position)->unk_14 = 0;
    ((S_80172840_5 *)position)->unk_10 = 0;
    ((S_80172840_5 *)position)->unk_0C = 0;
    func_800A2B04(position, ((S_80172840_4 *)sprite)->unk_24, ((S_80172840_4 *)sprite)->unk_25);
    D_8008346C[0] = 0;
    ((S_80172840_6 *)(D_800814A8[0]))->unk_A6--;
    func_800A4ACC(actor);
    ((S_80172840_0 *)actor)->unk_6D.s--;
    ((S_80172840_1 *)action)->unk_8C = D_80170E68;
    ((S_80172840_0 *)actor)->unk_73.s = 0;
    ((S_80172840_0 *)actor)->unk_72.s = 0;
    ((S_80172840_0 *)actor)->unk_46 &= 0x7FFF;
    goto done;
}

state_1:
    if (func_8003F270() != 0) {
        ((S_80172840_4 *)sprite)->unk_14 |= 0x800;
        goto done;
    }
    ((S_80172840_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172840_1 *)action)->unk_9B++;

state_2:
    if (((S_80172840_4 *)sprite)->unk_04.s == 1 &&
        (((S_80172840_4 *)sprite)->unk_14 & 0x1000)) {
        ((S_80172840_1 *)action)->unk_A8.u = 4;
    }
    if ((u32)(((S_80172840_4 *)sprite)->unk_04.u - 1) < 2U &&
        ((S_80172840_4 *)sprite)->unk_2C != D_80174194) {
        if (func_8003DE58(
                (s32)((S_80172840_4 *)sprite)->unk_08, sprite, &coords[4], 1) == 0) {
            coords[6] = 0;
            coords[5] = 0;
            coords[4] = 0;
        }
        ((S_80172840_1 *)action)->unk_A8.u--;
        if ((s16)((S_80172840_1 *)action)->unk_A8.u >= 0) {
            counter = 9;
            effect_base = D_800DEA68;
            for (; counter >= 0; counter--) {
                void *particle_data;
                particle = func_8003FD64(0x312, D_80083498);
                if (particle != 0) {
                    func_8004491C(particle, D_80045340);
                    particle_data = ((S_80172840_7 *)particle)->unk_0C;
                    ASM_KEEP_NV(particle_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    {
                        register void *particle_callback ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        particle_callback = D_80173EC0;
                        ((S_80172840_7 *)particle)->unk_10 = particle_callback;
                    }
                    {
                        s32 random_x;
                        s32 origin_x;
                        s32 offset_x;
                        register s32 heading_x ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        random_x = func_800A6D30() & 0x3F;
                        origin_x = ((S_80172840_5 *)position)->unk_02;
                        offset_x = coords[4];
                        heading_x = direction_x;
                        origin_x += offset_x;
                        offset_x = heading_x << 6;
                        origin_x += offset_x;
                        origin_x += random_x;
                        ((S_80172840_12 *)(((S_80172840_7 *)particle)->unk_08))->unk_02 =
                            origin_x - 0x1F;
                    }
                    ((S_80172840_12 *)(((S_80172840_7 *)particle)->unk_08))->unk_06 =
                        ((S_80172840_5 *)position)->unk_06 + coords[5] +
                        ((s32)direction_y << 6) + (func_800A6D30() & 0x3F) - 0x1F;
                    ((S_80172840_12 *)(((S_80172840_7 *)particle)->unk_08))->unk_08 = ((S_80172840_5 *)position)->unk_08.at00.v;
                    source_x = ((S_80172840_5 *)position)->unk_02;
                    offset_x = coords[4];
                    particle_fields = (u8 *)particle + 0x20;
                    ((S_80172840_8 *)particle_fields)->unk_0C = source_x + offset_x;
                    source_y = ((S_80172840_5 *)position)->unk_06;
                    offset_y = coords[5];
                    color = 0x700000;
                    ((S_80172840_8 *)particle_fields)->unk_0E = source_y + offset_y;
                    source_z = ((S_80172840_5 *)position)->unk_08.at02.v;
                    offset_z = coords[6];
                    ((S_80172840_8 *)particle_fields)->unk_48 = 4;
                    ((S_80172840_8 *)particle_fields)->unk_10 = source_z + offset_z;
                    ((S_80172840_9 *)particle_data)->unk_1E = 0x600;
                    ((S_80172840_9 *)particle_data)->unk_1C = 0x600;
                    ((S_80172840_9 *)particle_data)->unk_10 = 0x60;
                    ((S_80172840_9 *)particle_data)->unk_00 = effect_base;
                    ((S_80172840_9 *)particle_data)->unk_14 |= 0xC;
                    effect_value = effect_base->unk_04;
                    color |= 0x7070;
                    ((S_80172840_9 *)particle_data)->unk_04 = 0;
                    ((S_80172840_9 *)particle_data)->unk_05 = 0;
                    ((S_80172840_9 *)particle_data)->unk_0C = color;
                    ((S_80172840_9 *)particle_data)->unk_08 = effect_value;
                    ((S_80172840_8 *)particle_fields)->unk_4C = 0;
                }
            }
        }
    }
    if ((((S_80172840_4 *)sprite)->unk_04.s == 6 &&
         (((S_80172840_4 *)sprite)->unk_14 & 0x1000)) ||
        (((S_80172840_4 *)sprite)->unk_14 & 0xE000)) {
        ((S_80172840_4 *)sprite)->unk_14 |= 0x800;
        ((S_80172840_1 *)action)->unk_96 = 3;
        ((S_80172840_1 *)action)->unk_98 |= 0x80;
    }
    ((S_80172840_1 *)action)->unk_96--;
    if ((s16)((S_80172840_1 *)action)->unk_96 <= 0) {
        ((S_80172840_1 *)action)->unk_96 = 0;
        ((S_80172840_4 *)sprite)->unk_14 &= 0xF7FF;
    }
    if ((((S_80172840_4 *)sprite)->unk_14 & 0xE000) == 0) {
        goto done;
    }
    ((S_80172840_5 *)position)->unk_14 = 0;
    ((S_80172840_5 *)position)->unk_10 = 0;
    ((S_80172840_5 *)position)->unk_0C = 0;
    func_800A2B04(position, ((S_80172840_4 *)sprite)->unk_24, ((S_80172840_4 *)sprite)->unk_25);
    if (((S_80172840_4 *)sprite)->unk_2C != D_80174194) {
        ((S_80172840_4 *)sprite)->unk_2C = D_80174194;
        func_80047784(
            sprite,
            D_80174194[((D_80083228[0] + ((S_80172840_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
            0);
    }
    status = D_80083460;
    if (status->unk_0C != 0) {
        goto done;
    }
    status->unk_0A--;
    ((S_80172840_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172840_1 *)action)->unk_8C = D_80170E68;
    func_800A4ACC(actor);
    if (((S_80172840_0 *)actor)->unk_6D.u > 0) {
        ((S_80172840_0 *)actor)->unk_6D.s--;
    }
    ((S_80172840_0 *)actor)->unk_73.s = 0;
    ((S_80172840_0 *)actor)->unk_72.s = 0;
    ((S_80172840_0 *)actor)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
