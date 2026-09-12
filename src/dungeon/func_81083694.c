#include "common.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct TileEntry {
    u8 pad[12];
    u16 flags;
    u8 tail[6];
} TileEntry;

extern u16 D_80083462;
extern s16 D_80083228;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern TileEntry D_800E2970[];
extern void *D_80170808[];
extern u8 D_80175F10[];
extern u8 D_80175F20;
extern u8 D_80175F28;
extern u8 D_80175F38[];
extern u8 D_80175F50;
extern u8 D_80175F60;

extern s32 func_80042900();
extern s32 func_80047784(void *, s32, s32);
extern s32 func_8009A180();
extern s32 func_8009FB34();
extern s32 func_8009FD7C();
extern s32 func_800A0818();
extern s32 func_800A1C58();
extern s32 func_800A6D30();
extern s32 func_800A9A0C();
extern s32 func_800AA258();
extern s32 func_800AA6B4();
extern s32 func_800AA79C();
extern s32 func_800AA888();
extern s32 func_800AA924();
extern s32 func_800AAB10();
extern s32 func_800AAF00();
extern s32 func_801716B4();
extern s32 func_801718F8();
extern s32 func_80172050();
extern s32 func_80172218();
extern s32 func_80172334();
extern s32 func_801723D8();
extern s32 func_80172504();
extern s32 func_801727D8();
extern s32 func_80174698();
extern s32 func_80174EB4();
extern s32 func_80175ED4();

/* Update an actor's dungeon actions, status, facing, and animation. */
void func_80170E94(void *actor, void *context, void *sprite, void *stats) {
    s16 heading_flags;
    s32 tile_index;
    u32 action_index;
    u32 state;
    u32 active_state;
    u32 idle_state;
    u8 *active_anims;
    register u8 *next_anims ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *anim_entry;
    u8 *leader_sprite;
    static void *const action_labels[] = {
        &&case_1, &&case_1, &&case_1, &&case_default,
        &&case_5, &&case_5, &&case_5, &&case_8,
        &&case_9, &&case_default, &&case_11, &&case_12,
    };

    if ((F(actor, u8, 0xAE) == 0) && (D_80083462 & 0x1000)) {
        F(actor, u8, 0x9A) = 14;
        func_801716B4(actor, context, sprite, stats);
        goto done;
    }

    if (F(stats, u8, 0x25) == 0) {
        func_80175ED4(actor, stats);
        func_800AA79C(actor, context, sprite, stats);
        if (F(sprite, void *, 0x2C) == &D_80175F28) {
            goto done;
        }
        next_anims = &D_80175F20;
        goto set_anims;
    }

    if (F(stats, u32, 0x1C) & 0x200) {
        if (F(sprite, void *, 0x2C) == &D_80175F28) {
            F(actor, u8, 0x9A) = 13;
            F(actor, u8, 0x9B) = 1;
            F(actor, u32, 0x8C) = 0;
            F(stats, u32, 0x1C) &= ~0x40000;
            goto done;
        }
        func_80175ED4(actor, stats);
        if (func_800AA924(actor, context, sprite, &D_80175F20)) {
            goto done;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (F(stats, u32, 0x1C) & 0x100) {
            func_800AA258(actor, context, sprite, stats);
            goto done;
        }

        state = F(actor, u8, 0x9A);
        active_state = 25;
        idle_state = 14;
        if (state == active_state) {
            goto state_check_14;
        }
        if (F(actor, u8, 0xAE) != 0) {
            u8 *active_table = D_80175F38;
            if (F(sprite, void *, 0x2C) != active_table) {
                func_80174EB4(actor, context, sprite);
                F(sprite, void *, 0x2C) = active_table;
                func_80047784(sprite,
                    active_table[((D_80083228 + F(stats, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            F(actor, u8, 0x9A) = active_state;
            goto state_done;
        }
state_check_14:
        state = F(actor, u8, 0x9A);
        idle_state = 14;
        if (state != idle_state) {
            if (F(actor, u8, 0xAE) == 0) {
                u8 *idle_table = D_80175F10;
                if (F(sprite, void *, 0x2C) != idle_table) {
                    F(sprite, void *, 0x2C) = idle_table;
                    func_80047784(sprite,
                        idle_table[((D_80083228 + F(stats, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
                F(actor, u8, 0x9A) = idle_state;
            }
        }

state_done:
        F(actor, u16, 0x98) &= 0xFFF3;
        if (F(stats, s16, 0x64) != 0) {
            if (func_800AA6B4(actor, context, sprite, &D_80175F50)) {
                goto done;
            }
        }
        if (F(stats, u32, 0x1C) & 0x80000) {
            func_800AA888(actor, context, sprite, stats);
            func_80174698(actor, context, sprite, stats);
            goto done;
        }
        if ((s16)func_800A1C58(stats) != 0) {
            func_800AAB10(actor, context, sprite, stats);
        }
    }

    tile_index = func_8009FB34(F(sprite, u8, 0x24), F(sprite, u8, 0x25));
    F(sprite, u8, 0x26) = tile_index;
    if (F(stats, s8, 0x6D) <= 0) {
        goto health_zero;
    }
    if (F(stats, u32, 0x1C) & 0x20) {
        goto kill;
    }
    if ((F(sprite, u16, 0x24) == *(u16 *)&D_80082EA4) &&
        (F(actor, u8, 0xAE) == 0)) {
        func_80175ED4(actor, stats);
        func_801718F8(actor, context, sprite, stats);
        goto done;
    }

    if (!(F(stats, u16, 0x46) & 0x8000)) {
        if (D_80083462 & 0x2000) {
            if ((s16)func_8009A180(stats,
                    (u8 *)F(D_800814A8, void *, 0x58) + 0x20) != 0) {
                goto done;
            }
        }
        if (F(actor, u8, 0xAE) == 0) {
            if ((s16)func_801727D8(actor, context, sprite, 0) == 0) {
                goto done;
            }
        }
        F(stats, u16, 0x46) |= 0x4000;
        if (!(F(stats, u16, 0x46) & 0x8000)) {
            goto case_default;
        }
    }

    action_index = (F(stats, u16, 0x46) & 0x3FFF) - 1;
    if (action_index >= 12) {
        goto case_default;
    }
    (void)action_labels;
    goto *D_80170808[action_index];

case_12:
    if (func_80175ED4(actor, stats) == 0) {
        goto kill;
    }
    next_anims = D_80175F10;
    F(sprite, void *, 0x2C) = next_anims;
    func_80047784(sprite,
        next_anims[((D_80083228 + F(stats, s16, 0x2A) + 0x100) >> 9) & 7], 0);
    goto kill;

case_11:
    func_801718F8(actor, context, sprite, stats);
    goto final_cleanup;

case_8:
    func_80175ED4(actor, stats);
    if ((s16)func_80172050(actor, context, sprite, stats) != 0) {
        goto done;
    }
    func_80172218(actor, context, sprite, stats);
    goto done;

case_9:
    {
    register void *anim_sprite;

    if (F(actor, u8, 0xAE) != 0) {
        if (F(stats, u32, 0x1C) & 0x400) {
            register s32 turn_flags ASM_REG("$2") = F(stats, s32, 0x14);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if (turn_flags >= 0) {
                void *random_actor = actor;
                void *random_context = context;
                F(stats, u32, 0x14) = (u32)turn_flags | 0x80000000;
                F(stats, u16, 0x2A) +=
                    (func_800A6D30(random_actor, random_context) & 7) << 9;
            }
        }
        func_80172504(actor, context, sprite, stats);
        goto done;
    }
    func_801723D8(actor, context, sprite, stats);
    goto done;

case_5: {
        s16 heading;
        void *leader;

        heading = func_800A0818(
            F(sprite, u8, 0x24), F(sprite, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &heading_flags);
        leader = D_800814A8;
        F(stats, s16, 0x2A) = heading;
        if (F(leader, u8, 0x9A) == 17) {
            goto case_1;
        }
    }

kill:
    func_800A9A0C(stats);
    goto done;

case_1:
    func_80175ED4(actor, stats);
    func_800AAF00(actor, context, sprite, &D_80175F60, func_80170E94);
    goto done;

case_default:
    func_801718F8(actor, context, sprite, stats);
    if (F(actor, u8, 0xAE) == 0) {
        goto done;
    }

final_cleanup:
    func_80175ED4(actor, stats);
    goto done;

health_zero:
    if (F(actor, u8, 0xAE) == 0) {
        u32 flags = F(stats, u32, 0x1C);
        if (flags & 0x2000) {
            goto flag_2000;
        }
        if ((s8)tile_index >= 0) {
            if (D_800E2970[(s8)tile_index].flags & 2) {
                goto final_checks;
            }
        }
        if (flags & 0x430) {
            goto final_checks;
        }
        leader_sprite = D_80082E80;
        if ((s16)func_8009FD7C(F(sprite, u8, 0x24), F(sprite, u8, 0x25),
                leader_sprite[0x24], leader_sprite[0x25]) != 0) {
            F(stats, s16, 0x2A) = func_800A0818(
                F(sprite, u8, 0x24), F(sprite, u8, 0x25),
                leader_sprite[0x24], leader_sprite[0x25], &heading_flags);
        }
        goto final_checks;

flag_2000:
        if ((s16)func_80042900(stats, 4) != 0) {
            goto final_checks;
        }
        if (F(D_800814A8, u8, 0x9A) == 23) {
            func_80172334(actor, context, sprite, stats);
        }
    }

final_checks:
    if (D_80083462 & 0x2000) {
        goto done;
    }
    if (F(sprite, u16, 0x14) & 0x40) {
        goto done;
    }
    if (F(actor, u8, 0xAE) != 0) {
        active_anims = D_80175F38;
        if (F(sprite, void *, 0x2C) == active_anims) {
            goto done;
        }
        func_80174EB4(actor, context, sprite);
        F(sprite, void *, 0x2C) = active_anims;
        anim_sprite = sprite;
        anim_entry = active_anims + (((D_80083228 + F(stats, s16, 0x2A) + 0x100) >> 9) & 7);
    } else {
        void *current_anims;
        u8 *idle_anims;

        current_anims = F(sprite, void *, 0x2C);
        idle_anims = D_80175F10;
        if (current_anims == idle_anims) {
            goto done;
        }
        next_anims = idle_anims;

set_anims:
        F(sprite, void *, 0x2C) = next_anims;
        anim_sprite = sprite;
        anim_entry = (u8 *)((unsigned long)
            (((D_80083228 + F(stats, s16, 0x2A) + 0x100) >> 9) & 7) +
            (unsigned long)next_anims);
    }

    func_80047784(anim_sprite, *anim_entry, 0);
    }

done:
    return;
}
