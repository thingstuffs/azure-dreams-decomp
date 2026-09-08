#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80173280_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
} S_80173280_0;   /* arg0 in func_80173280 */

typedef struct S_80173280_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80173280_1;   /* arg3 in func_80173280 */

typedef struct S_80173280_2 {
    u8 * unk_00;
} S_80173280_2;   /* (u8 *)obj - 0x14 in func_80173280 */

typedef struct S_80173280_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80173280_3;   /* tile in func_80173280 */


typedef struct S_80173280_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80173280_5;   /* D_80083460 in func_80173280 */

typedef struct S_80173280_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80173280_6;   /* global in func_80173280 */

typedef struct S_80173280_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173280_7;   /* kindp in func_80173280 */



extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void D_80170CF8(void *, s32, s32, s32, s32, s32, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern u8 D_80170838[16];
extern u8 D_801717F4[];
extern u8 D_80175988[];

/* Advances action setup, target effects, animation timing, and cleanup. */
void func_80173280(void *actor, void *motion, void *tile_arg, void *action)
{
    s16 particle_index;
    register void *tile ASM_REG("$20") = tile_arg;   /* MATCH pin: retail address form (%hi/%lo vs kind_table+offset) depends on it */
    s32 offset_y;
    s32 offset_x;
    void *target_obj;
    u8 *kind_data;
    s32 state;
    s32 effect_flags;
    register s32 action_dep ASM_REG("$18");   /* MATCH pin: retail schedule: same instructions, different order without it */
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };

#ifdef NON_MATCHING
    action_dep = 0;
#endif
    ASM_KEEP_DEP_NV(action_dep, action);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_USE(action_dep);   /* MATCH pin: retail schedule: same instructions, different order without it */
    state = ((S_80173280_0 *)actor)->unk_9B;
    ASM_KEEP(tile);   /* MATCH pin: retail schedule: same instructions, different order without it */
    effect_flags = 0;
    if (state != 1) {
        if ((s32)state < 2) {
            if (state == 0) {
                goto state_0;
            }
            return;
        }
        if (state == 2) {
            goto state_2;
        }
        if (state == 3) {
            goto state_3;
        }
        return;
    }
    goto state_1;

state_0:
    if (((S_80173280_1 *)action)->unk_1C & 0x2000) {
        u32 kind = (((S_80173280_1 *)action)->unk_46 & 0x3FFF) - 1;

        if (kind >= 7) {
            goto kind_default;
        }
        goto *(((void **)D_80170838)[kind]);

kind_5:
        effect_flags = 1;
        goto kind_3;
kind_6:
        effect_flags = 1;
        goto kind_2;
kind_7:
        effect_flags = 1;
        goto kind_1;
    } else {
        u32 kind = ((S_80173280_1 *)action)->unk_46 & 0x3FFF;

        if (kind == 2) {
            goto kind_2;
        }
        if ((s32)kind < 3) {
            if (kind == 1) {
                goto kind_1;
            }
            kind_data = 0;
            goto use_kind;
        }
        if (kind == 3) {
            goto kind_3;
        }
        kind_data = 0;
        goto use_kind;
    }

kind_3:
    kind_data = (u8 *)action + 0xE;
    goto use_kind;
kind_2:
    kind_data = (u8 *)action + 0xB;
    goto use_kind;
kind_1:
    kind_data = (u8 *)action + 8;
    goto use_kind;
kind_default:
    kind_data = 0;

use_kind:
    if (*kind_data != 0) {
        *(volatile u16 *)((u8 *)actor + 0x98) =
            ((S_80173280_0 *)actor)->unk_98 & 0xFF7F;
        {
            s32 reuse_target = effect_flags;
            ASM_KEEP(reuse_target);   /* MATCH pin: retail delay-slot fill depends on it */
            if (reuse_target) {
                target_obj = D_800814A8;
                ((S_80173280_1 *)action)->unk_60 = target_obj;
                goto copy_existing;
            }
        }
        {
            u8 *kind_table;
            u8 kind;
            u8 *kind_entry;

            kind_table = (u8 *)0x80070000;
            ASM_KEEP(kind_table);   /* MATCH pin: keeps a statement from moving across a call/branch */
            kind = *kind_data;
            kind_table -= 0x21DC;
            kind_entry = (u8 *)((u32)(kind * 20) + (u32)kind_table);
            ASM_KEEP(kind_entry);   /* MATCH pin: load-bearing for the whole function shape */

            if (kind_entry[0x12] == 2) {
                target_obj = ((S_80173280_1 *)action)->unk_60;

                if (target_obj != 0) {
copy_existing:
                    {
                        register u8 *target_tile ASM_REG("$3") =
                            ((S_80173280_2 *)((u8 *)target_obj - 0x14))->unk_00;
                        ((S_80173280_1 *)action)->unk_72.s = target_tile[0x24];
                        ((S_80173280_1 *)action)->unk_73.s = target_tile[0x25];
                    }
                    goto invoke_move;
                }
                goto call_move;
            }
        }

        *(void * volatile *)((u8 *)action + 0x60) =
            func_800A05A4(action, ((S_80173280_3 *)tile)->unk_24, ((S_80173280_3 *)tile)->unk_25,
                          ((S_80173280_1 *)action)->unk_2A, 0x10);
        ASM_KEEP(effect_flags);   /* MATCH pin: keeps a statement from moving across a call/branch */
        {
            s32 x = ((S_80173280_1 *)action)->unk_72.u;
            s32 y = ((S_80173280_1 *)action)->unk_73.u;

            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            ((S_80173280_1 *)action)->unk_72.s = x;
            ((S_80173280_1 *)action)->unk_73.s = y;
        }

call_move:
        (void)0;
invoke_move:
        if (func_800A94A0(action, kind_data, effect_flags, (u8 *)actor + 0x98)) {
            ((S_80173280_0 *)actor)->unk_96.s = 0x18;
            ((S_80173280_0 *)actor)->unk_9E = 4;
            ((S_80173280_0 *)actor)->unk_9B++;
            return;
        }
        goto done;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_80173280_3 *)tile)->unk_24, ((S_80173280_3 *)tile)->unk_25);
    {
        u8 *active_actor = D_800814A8;
        ((S_80173280_5 *)D_80083460)->unk_0C = 0;
        ((S_80173280_6 *)active_actor)->unk_A6--;
    }
    func_800A4ACC(action);
    ((S_80173280_1 *)action)->unk_6D--;
    ((S_80173280_0 *)actor)->unk_8C = D_801717F4;
    ((S_80173280_1 *)action)->unk_73.s = 0;
    ((S_80173280_1 *)action)->unk_72.s = 0;
    ((S_80173280_1 *)action)->unk_46 &= 0x7FFF;
    return;

state_1:
    if (func_8003F270()) {
        ((S_80173280_3 *)tile)->unk_14 |= 0x800;
        return;
    }
    ((S_80173280_3 *)tile)->unk_14 &= 0xF7FF;
    ((S_80173280_0 *)actor)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    particle_index = 0;
    do {
        effect_flags = func_80069EF8() & 0xFF;
        effect_flags |= 0x80;
        offset_x = (s16)((func_80069EF8() & 0x7F) - 0x40);
        offset_y = (s16)((func_80069EF8() & 0x7F) - 0x40);
        D_80170CF8((u8 *)actor - 0x20, 0, 0x00808080, effect_flags, offset_x, offset_y,
                   (s16)((func_80069EF8() & 0x7F) - 0x40));
        particle_index++;
    } while (particle_index < 5);

    ((S_80173280_0 *)actor)->unk_9E--;
    if ((s16)((S_80173280_0 *)actor)->unk_9E == 1) {
        ((S_80173280_3 *)tile)->unk_14 |= 0x800;
    }
    if (((S_80173280_0 *)actor)->unk_96.u == 5) {
        ((S_80173280_3 *)tile)->unk_14 &= 0xF7FF;
    }
    ((S_80173280_0 *)actor)->unk_96.s--;
    if ((s16)((S_80173280_0 *)actor)->unk_96.s > 0 &&
        !(((S_80173280_3 *)tile)->unk_14 & 0xE000)) {
        goto done;
    }
    ((S_80173280_0 *)actor)->unk_98 |= 0x80;
    ((S_80173280_0 *)actor)->unk_9B++;
    ((S_80173280_3 *)tile)->unk_14 |= 0x800;
    ((S_80173280_0 *)actor)->unk_96.s = 0x14;
    return;

state_3:
    kind_data = D_80083460;
    if (((S_80173280_7 *)kind_data)->unk_0C == 0) {
        ((S_80173280_0 *)actor)->unk_96.s = 0;
    }
    ((S_80173280_0 *)actor)->unk_96.s--;
    if ((s16)((S_80173280_0 *)actor)->unk_96.s <= 0) {
        *(volatile u16 *)((u8 *)actor + 0x96) = 0;
        ((S_80173280_3 *)tile)->unk_14 &= 0xF7FF;
    }
    if (!(((S_80173280_3 *)tile)->unk_14 & 0xE000)) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_80173280_3 *)tile)->unk_24, ((S_80173280_3 *)tile)->unk_25);
    if (((S_80173280_3 *)tile)->unk_2C != D_80175988) {
        u8 *frame_table = D_80175988;
        (*(u8 * *)((u8 *)tile + 0x2C)) = frame_table;
        func_80047784(tile,
            frame_table[((D_80083228 + ((S_80173280_1 *)action)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80173280_3 *)tile)->unk_14 &= 0xF7FF;
    }
    if (((S_80173280_7 *)kind_data)->unk_0C != 0) {
        goto done;
    }
    ((S_80173280_7 *)kind_data)->unk_0A--;
    ((S_80173280_0 *)actor)->unk_8C = D_801717F4;
    func_800A4ACC(action);
    ((S_80173280_1 *)action)->unk_73.s = 0;
    ((S_80173280_1 *)action)->unk_72.s = 0;
    ((S_80173280_1 *)action)->unk_6D--;
    ((S_80173280_1 *)action)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
