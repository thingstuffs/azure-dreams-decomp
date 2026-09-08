#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    void *effect_state = effect_state_in;
    void *motion = motion_in;
#ifdef __mips__
    register void *actor ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *actor_data;
    void *image_base;
    void *resource_base;
#else
    void *actor;
    void *actor_data;
    void *image_base;
    void *resource_base;
#endif
#ifdef __mips__
    register s32 actor_or_corner ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
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

    actor = FIELD(effect_state, void *, 0);
    timer = (u16)FIELD(effect_state, u16, 0x50);
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    timer -= 1;
    phase_or_entry = *(s16 *)((u8 *)effect_state + 0xA);
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    actor_data = FIELD(actor, void *, -0x14);
    FIELD(effect_state, u16, 0x50) = timer;

    if ((u32)phase_or_entry >= 6) {
        goto finish;
    }
    actor_or_corner = (s32)((u8 *)actor - 0x20);
    phase_table = jtbl_80024008;
    ASM_KEEP(phase_table);   /* MATCH pin: retail delay-slot fill depends on it */
    phase_or_entry <<= 2;
    phase_or_entry = (s32)((u8 *)phase_table + phase_or_entry);
    phase_label = *(void **)(u32)phase_or_entry;
    (void)phase_labels;
    goto *phase_label;

case0:
    if ((FIELD(FIELD(effect_state, void *, 4), u16, 0) & 0x80) == 0) {
        goto finish;
    }
    {
        void *target_actor;
        s16 height;

        height = (s16)func_800A3820(0x22);
        target_actor = func_800A05A4(actor,
            FIELD(actor_data, u8, 0x24),
            FIELD(actor_data, u8, 0x25),
            FIELD(actor, s16, 0x2A), height);
        FIELD(actor, void *, 0x60) = target_actor;
        if (target_actor == 0) {
            FIELD(actor, u8, 0x72) = FIELD(actor_data, u8, 0x24);
            FIELD(actor, u8, 0x73) = FIELD(actor_data, u8, 0x25);
            goto update;
        }
        {
#ifdef __mips__
            register void *target_data ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
#else
            void *target_data;
#endif
            target_data = FIELD(target_actor, void *, -0x14);
            FIELD(actor, u8, 0x72) = FIELD(target_data, u8, 0x24);
            FIELD(actor, u8, 0x73) = FIELD(target_data, u8, 0x25);
        }
    }

update:
    FIELD(motion, u16, 2) =
        FIELD(FIELD((void *)actor_or_corner, void *, 8), u16, 2);
    FIELD(motion, u16, 6) =
        FIELD(FIELD((void *)actor_or_corner, void *, 8), u16, 6);
    FIELD(motion, u16, 0xA) =
        FIELD(FIELD((void *)actor_or_corner, void *, 8), u16, 0xA);
    FIELD(effect_state, u16, 0x50) = 8;
    tile_coord = FIELD(actor, s8, 0x72);
    FIELD(motion, s16, 0xE) =
        (tile_coord << 6) - (FIELD(motion, u16, 2) - 0x20);
    FIELD(motion, s32, 0xC) = FIELD(motion, s32, 0xC) /
        FIELD(effect_state, s16, 0x50);
    tile_coord = FIELD(actor, s8, 0x73);
    FIELD(motion, s16, 0x12) =
        (tile_coord << 6) - (FIELD(motion, u16, 6) - 0x20);
    FIELD(motion, s32, 0x10) = FIELD(motion, s32, 0x10) /
        FIELD(effect_state, s16, 0x50);
    FIELD(motion, s16, 0x16) = func_800BCB04(
        FIELD(motion, u16, 2), FIELD(motion, u16, 6),
        (s16)(FIELD(FIELD((void *)actor_or_corner, void *, 8), u16, 0xA) -
              0x30)) - FIELD(motion, s16, 0xA);
    FIELD(motion, s32, 0x14) = FIELD(motion, s32, 0x14) /
        FIELD(effect_state, s16, 0x50);
    func_800A56E0(0x300);
    FIELD(effect_state, u16, 0xA)++;
    goto finish;

case1:
    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    FIELD(motion, s32, 8) += FIELD(motion, s32, 0x14);
    if (FIELD(effect_state, s16, 0x50) > 0) {
        goto finish;
    }
    {
        u8 *base_page;
        actor_or_corner = 3;
#ifdef __mips__
        base_page = (u8 *)0x80020000;
        ASM_KEEP(base_page);   /* MATCH pin: load-bearing for the whole function shape */
        image_base = base_page + 0x4538;
        base_page = (u8 *)0x800E0000;
        ASM_KEEP(base_page);   /* MATCH pin: load-bearing for the whole function shape */
        resource_base = base_page - 0x1520;
#else
        image_base = D_80024538;
        resource_base = D_800DEAE0;
#endif
        do {
            void *burst_obj;
#ifdef __mips__
            register void *prim ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
#else
            void *prim;
#endif
            void *child_state;
            void *resource_cursor;
#ifdef __mips__
            s32 center_coord;
            s32 corner_coord;
            s32 position_or_z_offset;
            register s32 prim_color ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
#else
            s32 center_coord;
            s32 corner_coord;
            s32 position_or_z_offset;
            s32 prim_color;
#endif

            burst_obj = func_8003FD64(0x312, D_80083498);
            if (burst_obj != 0) {
                func_8004491C(burst_obj, D_80045340);
                prim = FIELD(burst_obj, void *, 0xC);
                position_or_z_offset = (s32)FIELD(burst_obj, void *, 8);
                FIELD(burst_obj, void *, 0x10) = image_base;
                center_coord = FIELD(motion, s16, 2);
                child_state = (u8 *)burst_obj + 0x20;
                if (actor_or_corner >> 1) {
                    corner_coord = center_coord - 16;
                } else {
                    corner_coord = center_coord + 16;
                }
                FIELD((void *)position_or_z_offset, s16, 2) = corner_coord;
                position_or_z_offset = (s32)FIELD(burst_obj, void *, 8);
                center_coord = FIELD(motion, s16, 6);
                if ((actor_or_corner & 1) == 0) {
                    corner_coord = center_coord + 16;
                } else {
                    corner_coord = center_coord - 16;
                }
                FIELD((void *)position_or_z_offset, s16, 6) = corner_coord;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                prim_color = 0xC00000;
                ASM_KEEP(prim_color);   /* MATCH pin: retail schedule: same instructions, different order without it */
                position_or_z_offset = -0x100000;
                FIELD(FIELD(burst_obj, void *, 8), s32, 8) =
                    FIELD(motion, s32, 8) + position_or_z_offset;
                FIELD(prim, s16, 0x1E) = 0xC00;
                FIELD(prim, s16, 0x10) = 0x60;
                {
                    u16 prim_flags;

                    prim_flags = FIELD(prim, u16, 0x14);
                    prim_color |= 0xC0C0;
                    FIELD(prim, void *, 0) = resource_base;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    resource_cursor = resource_base;
                    ASM_KEEP(resource_cursor);   /* MATCH pin: retail delay-slot fill depends on it */
                    FIELD(prim, s16, 0x1C) = 0;
                    FIELD(prim, s32, 0xC) = prim_color;
                    prim_flags |= 0xC;
                    FIELD(prim, u16, 0x14) = prim_flags;
                }
                FIELD(prim, void *, 8) = FIELD(resource_cursor, void *, 4);
                FIELD(prim, u8, 4) = 0;
                FIELD(prim, u8, 5) = 0;
                FIELD(child_state, void *, 0) = effect_state;
                FIELD(child_state, u16, 0x48) =
                    FIELD(actor, void *, 0x60) ? 0x20 : 0xA;
                FIELD(child_state, u16, 0x4C) = 0;
            }
            actor_or_corner--;
        } while (actor_or_corner >= 0);
    }
    if (FIELD(actor, void *, 0x60) != 0) {
        void *impact_obj;
        impact_obj = func_8003FD64(0x201, D_80083498);
        if (impact_obj != 0) {
#ifdef __mips__
            register void *child_state ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
            u16 effect_y;
#else
            void *child_state;
            u16 effect_y;
#endif
            u16 effect_z;
            s32 duration;
            func_8004491C(impact_obj, D_80024714);
            FIELD(impact_obj, void *, 0x10) = D_80024684;
            child_state = (u8 *)impact_obj + 0x20;
            FIELD(child_state, u16, 4) = FIELD(motion, u16, 2);
            effect_y = FIELD(motion, u16, 6);
            FIELD(child_state, u16, 6) = effect_y;
            effect_z = FIELD(motion, u16, 0xA);
            FIELD(child_state, u16, 0x12) = 1;
            FIELD(child_state, s32, 0xC) = -64;
            duration = 40;
            FIELD(child_state, u16, 8) = effect_z;
            FIELD(impact_obj, void *, 0x20) = effect_state;
            FIELD(child_state, u16, 0x10) = duration;
        }
    }
    FIELD(effect_state, u16, 0x50) = 10;
    FIELD(effect_state, u16, 0xA)++;
    goto finish;

case2:
    if (FIELD(effect_state, s16, 0x50) > 0) {
        goto finish;
    }
    if (FIELD(actor, void *, 0x60) == 0) {
        FIELD(effect_state, u16, 0x50) = 8;
        FIELD(effect_state, u16, 0xA) = 5;
        goto finish;
    }
    FIELD(effect_state, u16, 0x50) = 20;
    FIELD(effect_state, u16, 0xA)++;
    goto finish;

case3:
    if (FIELD(effect_state, s16, 0x50) > 0) {
        goto finish;
    }
    if (FIELD(actor, void *, 0x60) != 0 &&
        func_8009D218(FIELD(actor, void *, 0x60), 1, actor) == 0 &&
        (FIELD(FIELD(actor, void *, 0x60), u32, 0x14) & 4) != 0) {
        func_800C8900(
            FIELD(actor, void *, 0x60),
            FIELD(D_800E3D68, u8, 0) == 0xFF ? 0xFF : 0x10,
            2);
    }
    FIELD(effect_state, u16, 0x50) = 10;
    FIELD(effect_state, u16, 0xA)++;
    goto finish;

case4:
    if (FIELD(effect_state, s16, 0x50) > 0) {
        goto finish;
    }
    FIELD(effect_state, u16, 0x50) = 4;
    FIELD(effect_state, u16, 0xA)++;
    goto finish;

case5:
    if (FIELD(effect_state, s16, 0x52) & (u16)0x8000) {
        FIELD(effect_state, u16, 0x52) &= 0x7FFF;
        goto finish;
    }
    if (FIELD(effect_state, s16, 0x50) > 0) {
        goto finish;
    }
    D_8008346C[0] = 0;
    FIELD(effect_state, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto finish;

finish:
    ;
}
