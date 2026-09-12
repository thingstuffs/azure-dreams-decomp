#include "common.h"

typedef struct S_func_818DA800_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[2];
    union { s16 as_s16; u16 as_u16; } unk_0A;
    u8 pad_0C[0x44];
    union { s16 as_s16; u16 as_u16; } unk_50;
    union { s16 as_s16; u16 as_u16; } unk_52;
} S_func_818DA800_1;

typedef struct S_func_818DA800_2 {
    union {
        s32 as_s32;
        struct {
            u8 pad_00[2];
            union { s16 as_s16; u16 as_u16; } unk_02;
        } half;
    } unk_00;
    union {
        s32 as_s32;
        struct {
            u8 pad_04[2];
            union { s16 as_s16; u16 as_u16; } unk_06;
        } half;
    } unk_04;
    union {
        s32 as_s32;
        struct {
            u8 pad_08[2];
            union { s16 as_s16; u16 as_u16; } unk_0A;
        } half;
    } unk_08;
    union {
        s32 as_s32;
        struct {
            u8 pad_0C[2];
            s16 unk_0E;
        } half;
    } unk_0C;
    union {
        s32 as_s32;
        struct {
            u8 pad_10[2];
            s16 unk_12;
        } half;
    } unk_10;
    union {
        s32 as_s32;
        struct {
            u8 pad_14[2];
            s16 unk_16;
        } half;
    } unk_14;
} S_func_818DA800_2;

typedef struct S_func_818DA800_3 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xE];
    union { s8 as_s8; u8 as_u8; } unk_72;
    union { s8 as_s8; u8 as_u8; } unk_73;
} S_func_818DA800_3;

typedef struct S_func_818DA800_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_818DA800_4;

typedef struct S_func_818DA800_5 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_818DA800_5;

typedef struct S_func_818DA800_6 {
    u16 unk_00;
} S_func_818DA800_6;

typedef struct S_func_818DA800_7 {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
    void *unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_818DA800_7;

typedef struct S_func_818DA800_8 {
    void *unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[2];
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u8 pad_14[0x34];
    u16 unk_48;
    u8 pad_4A[2];
    u16 unk_4C;
} S_func_818DA800_8;

typedef struct S_func_818DA800_9 {
    u8 pad_00[4];
    void *unk_04;
} S_func_818DA800_9;

typedef struct S_func_818DA800_10 {
    u8 unk_00;
} S_func_818DA800_10;

typedef struct S_func_818DA800_11 {
    u8 pad_00[2];
    u16 unk_02;
} S_func_818DA800_11;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A3820(s32);
extern void *func_800A05A4(void *, u8, u8, s16, s16);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_800A56E0(s32);
extern s32 func_8009D218(void *, s32, void *);
extern void func_800C8900(void *, s32, s32);

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80024538[];
extern u8 D_800DEAE0[];
extern u8 D_80024684[];
extern u8 D_80024714[];
extern u8 D_800E3D68[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];
extern void *jtbl_80024008[];

__asm__(".set jtbl_80024008, 0x80024008");

#ifdef __mips__
static const u32 func_80024000_prefix[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
        0x80024020,
        0,
        0x80024090,
        0x8002421C,
        0x800243E8,
        0x80024424,
        0x80024498,
        0x800244BC,
    };
__asm__(".globl func_80024000\n"
        ".size func_80024000, 1336");
#define FUNC_818DA800_BODY func_80024020
#else
#define FUNC_818DA800_BODY func_80024000
#endif

/* Advances a targeted effect through movement, particle spawning, target interaction, and cleanup. */
void FUNC_818DA800_BODY(void *effect_state_in, void *motion_in)
{
    S_func_818DA800_1 *effect_state = effect_state_in;
    S_func_818DA800_2 *motion = motion_in;
#ifdef __mips__
    register S_func_818DA800_3 *actor ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_func_818DA800_4 *actor_data;
    void *image_base;
    void *resource_base;
#else
    S_func_818DA800_3 *actor;
    S_func_818DA800_4 *actor_data;
    void *image_base;
    void *resource_base;
#endif
#ifdef __mips__
    register s32 actor_or_corner ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#else
    s32 actor_or_corner;
#endif
    s16 timer;
    s32 phase_or_entry;
    s32 tile_coord;
    void **phase_table;
    void *phase_label;
    static void *const phase_labels[] = {
        &&finish,
        &&case0,
        &&case1,
        &&case2,
        &&case3,
        &&case4,
        &&case5,
    };

    actor = effect_state->unk_00;
    timer = (u16)effect_state->unk_50.as_u16;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    timer -= 1;
    phase_or_entry = effect_state->unk_0A.as_s16;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    actor_data = ((S_func_818DA800_5 *)((u8 *)actor - 0x20))->unk_0C;
    effect_state->unk_50.as_u16 = timer;

    if ((u32)phase_or_entry >= 6) {
        goto finish;
    }
    actor_or_corner = (s32)((u8 *)actor - 0x20);
    phase_table = jtbl_80024008;
    ASM_KEEP(phase_table);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    phase_or_entry <<= 2;
    phase_or_entry = (s32)((u8 *)phase_table + phase_or_entry);
    phase_label = *(void **)(u32)phase_or_entry;
    (void)phase_labels;
    goto *phase_label;

case0:
    if ((((S_func_818DA800_6 *)effect_state->unk_04)->unk_00 & 0x80) == 0) {
        goto finish;
    }
    {
        S_func_818DA800_3 *target_actor;
        s16 height;

        height = (s16)func_800A3820(0x22);
        target_actor = func_800A05A4(actor,
            actor_data->unk_24,
            actor_data->unk_25,
            actor->unk_2A, height);
        actor->unk_60 = target_actor;
        if (target_actor == 0) {
            actor->unk_72.as_u8 = actor_data->unk_24;
            actor->unk_73.as_u8 = actor_data->unk_25;
            goto update;
        }
        {
#ifdef __mips__
            register S_func_818DA800_4 *target_data ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#else
            S_func_818DA800_4 *target_data;
#endif
            target_data = ((S_func_818DA800_5 *)((u8 *)target_actor - 0x20))->unk_0C;
            actor->unk_72.as_u8 = target_data->unk_24;
            actor->unk_73.as_u8 = target_data->unk_25;
        }
    }

update:
    motion->unk_00.half.unk_02.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_or_corner)->unk_08)->unk_00.half.unk_02.as_u16;
    motion->unk_04.half.unk_06.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_or_corner)->unk_08)->unk_04.half.unk_06.as_u16;
    motion->unk_08.half.unk_0A.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_or_corner)->unk_08)->unk_08.half.unk_0A.as_u16;
    effect_state->unk_50.as_u16 = 8;
    tile_coord = actor->unk_72.as_s8;
    motion->unk_0C.half.unk_0E =
        (tile_coord << 6) - (motion->unk_00.half.unk_02.as_u16 - 0x20);
    motion->unk_0C.as_s32 = motion->unk_0C.as_s32 /
        effect_state->unk_50.as_s16;
    tile_coord = actor->unk_73.as_s8;
    motion->unk_10.half.unk_12 =
        (tile_coord << 6) - (motion->unk_04.half.unk_06.as_u16 - 0x20);
    motion->unk_10.as_s32 = motion->unk_10.as_s32 /
        effect_state->unk_50.as_s16;
    motion->unk_14.half.unk_16 = func_800BCB04(
        motion->unk_00.half.unk_02.as_u16, motion->unk_04.half.unk_06.as_u16,
        (s16)(((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_or_corner)->unk_08)->unk_08.half.unk_0A.as_u16 -
              0x30)) - motion->unk_08.half.unk_0A.as_s16;
    motion->unk_14.as_s32 = motion->unk_14.as_s32 /
        effect_state->unk_50.as_s16;
    func_800A56E0(0x300);
    effect_state->unk_0A.as_u16++;
    goto finish;

case1:
    motion->unk_00.as_s32 += motion->unk_0C.as_s32;
    motion->unk_04.as_s32 += motion->unk_10.as_s32;
    motion->unk_08.as_s32 += motion->unk_14.as_s32;
    if (effect_state->unk_50.as_s16 > 0) {
        goto finish;
    }
    {
        actor_or_corner = 3;
#ifdef __mips__
        image_base = D_80024538;
        resource_base = D_800DEAE0;
#else
        image_base = D_80024538;
        resource_base = D_800DEAE0;
#endif
        do {
            S_func_818DA800_5 *burst_obj;
#ifdef __mips__
            register S_func_818DA800_7 *prim ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#else
            S_func_818DA800_7 *prim;
#endif
            S_func_818DA800_8 *child_state;
            S_func_818DA800_9 *resource_cursor;
#ifdef __mips__
            s32 center_coord;
            s32 corner_coord;
            s32 position_or_z_offset;
            register s32 prim_color ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#else
            s32 center_coord;
            s32 corner_coord;
            s32 position_or_z_offset;
            s32 prim_color;
#endif

            burst_obj = func_8003FD64(0x312, D_80083498);
            if (burst_obj != 0) {
                func_8004491C(burst_obj, D_80045340);
                prim = burst_obj->unk_0C;
                position_or_z_offset = (s32)burst_obj->unk_08;
                burst_obj->unk_10 = image_base;
                center_coord = motion->unk_00.half.unk_02.as_s16;
                child_state = (S_func_818DA800_8 *)((u8 *)burst_obj + 0x20);
                if (actor_or_corner >> 1) {
                    corner_coord = center_coord - 16;
                } else {
                    corner_coord = center_coord + 16;
                }
                ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_00.half.unk_02.as_s16 = corner_coord;
                position_or_z_offset = (s32)burst_obj->unk_08;
                center_coord = motion->unk_04.half.unk_06.as_s16;
                if ((actor_or_corner & 1) == 0) {
                    ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_04.half.unk_06.as_s16 = center_coord + 16;
                } else {
                    ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_04.half.unk_06.as_s16 = center_coord - 16;
                }
                prim_color = 0xC00000;
                ASM_KEEP(prim_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                position_or_z_offset = -0x100000;
                ((S_func_818DA800_2 *)burst_obj->unk_08)->unk_08.as_s32 =
                    motion->unk_08.as_s32 + position_or_z_offset;
                prim->unk_1E = 0xC00;
                prim->unk_10 = 0x60;
                {
                    u16 prim_flags;

                    prim_flags = prim->unk_14;
                    prim_color |= 0xC0C0;
                    prim->unk_00 = resource_base;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    resource_cursor = resource_base;
                    ASM_KEEP(resource_cursor);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    prim->unk_1C = 0;
                    prim->unk_0C = prim_color;
                    prim_flags |= 0xC;
                    prim->unk_14 = prim_flags;
                }
                prim->unk_08 = resource_cursor->unk_04;
                prim->unk_04 = 0;
                prim->unk_05 = 0;
                child_state->unk_00 = effect_state;
                child_state->unk_48 =
                    actor->unk_60 ? 0x20 : 0xA;
                child_state->unk_4C = 0;
            }
            actor_or_corner--;
        } while (actor_or_corner >= 0);
    }
    if (actor->unk_60 != 0) {
        S_func_818DA800_5 *impact_obj;
        impact_obj = func_8003FD64(0x201, D_80083498);
        if (impact_obj != 0) {
#ifdef __mips__
            register S_func_818DA800_8 *child_state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u16 effect_y;
#else
            S_func_818DA800_8 *child_state;
            u16 effect_y;
#endif
            u16 effect_z;
            s32 duration;
            func_8004491C(impact_obj, D_80024714);
            impact_obj->unk_10 = D_80024684;
            child_state = (S_func_818DA800_8 *)((u8 *)impact_obj + 0x20);
            child_state->unk_04 = motion->unk_00.half.unk_02.as_u16;
            effect_y = motion->unk_04.half.unk_06.as_u16;
            child_state->unk_06 = effect_y;
            effect_z = motion->unk_08.half.unk_0A.as_u16;
            child_state->unk_12 = 1;
            child_state->unk_0C = -64;
            duration = 40;
            child_state->unk_08 = effect_z;
            impact_obj->unk_20 = effect_state;
            child_state->unk_10 = duration;
        }
    }
    effect_state->unk_50.as_u16 = 10;
    effect_state->unk_0A.as_u16++;
    goto finish;

case2:
    if (effect_state->unk_50.as_s16 > 0) {
        goto finish;
    }
    if (actor->unk_60 == 0) {
        effect_state->unk_50.as_u16 = 8;
        effect_state->unk_0A.as_u16 = 5;
        goto finish;
    }
    effect_state->unk_50.as_u16 = 20;
    effect_state->unk_0A.as_u16++;
    goto finish;

case3:
    if (effect_state->unk_50.as_s16 > 0) {
        goto finish;
    }
    if (actor->unk_60 != 0 &&
        func_8009D218(actor->unk_60, 1, actor) == 0 &&
        (((S_func_818DA800_3 *)actor->unk_60)->unk_14 & 4) != 0) {
        func_800C8900(
            actor->unk_60,
            ((S_func_818DA800_10 *)D_800E3D68)->unk_00 == 0xFF ? 0xFF : 0x10,
            2);
    }
    effect_state->unk_50.as_u16 = 10;
    effect_state->unk_0A.as_u16++;
    goto finish;

case4:
    if (effect_state->unk_50.as_s16 > 0) {
        goto finish;
    }
    effect_state->unk_50.as_u16 = 4;
    effect_state->unk_0A.as_u16++;
    goto finish;

case5:
    if (effect_state->unk_52.as_s16 & (u16)0x8000) {
        effect_state->unk_52.as_u16 &= 0x7FFF;
        goto finish;
    }
    if (effect_state->unk_50.as_s16 > 0) {
        goto finish;
    }
    D_8008346C[0] = 0;
    ((S_func_818DA800_11 *)((u8 *)effect_state - 4))->unk_02 |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto finish;

finish:
    ;
}
