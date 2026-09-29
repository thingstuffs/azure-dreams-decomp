#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct TileEntry {
    u8 pad[12];
    u16 flags;
    u8 tail[6];
} TileEntry;

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
    register void *anim_sprite;

    if ((F(actor, u8, 0xAE) == 0) && (dungeonStatus.flags & 0x1000)) {
        F(actor, u8, 0x9A) = 14;
        func_801716B4(actor, context, sprite, stats);
        return;
    }

    if (F(stats, u8, 0x25) == 0) {
        func_80175ED4(actor, stats);
        func_800AA79C(actor, context, sprite, stats);
        if (F(sprite, void *, 0x2C) == &D_80175F28) {
            return;
        }
        next_anims = &D_80175F20;
        F(sprite, void *, 0x2C) = next_anims;
        func_80047784(sprite,
            next_anims[((gameWork.view.viewAngle + F(stats, s16, 0x2A) + 0x100) >> 9) & 7], 0);
        return;
    }

    if (F(stats, u32, 0x1C) & 0x200) {
        if (F(sprite, void *, 0x2C) == &D_80175F28) {
            F(actor, u8, 0x9A) = 13;
            F(actor, u8, 0x9B) = 1;
            F(actor, u32, 0x8C) = 0;
            F(stats, u32, 0x1C) &= ~0x40000;
            return;
        }
        func_80175ED4(actor, stats);
        if (func_800AA924(actor, context, sprite, &D_80175F20)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (F(stats, u32, 0x1C) & 0x100) {
            func_800AA258(actor, context, sprite, stats);
            return;
        }

        state = F(actor, u8, 0x9A);
        active_state = 25;
        idle_state = 14;
        if (state != active_state && F(actor, u8, 0xAE) != 0) {
            u8 *active_table = D_80175F38;
            if (F(sprite, void *, 0x2C) != active_table) {
                func_80174EB4(actor, context, sprite);
                F(sprite, void *, 0x2C) = active_table;
                func_80047784(sprite,
                    active_table[((gameWork.view.viewAngle + F(stats, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            F(actor, u8, 0x9A) = active_state;
        } else {
            state = F(actor, u8, 0x9A);
            idle_state = 14;
            if (state != idle_state) {
                if (F(actor, u8, 0xAE) == 0) {
                    u8 *idle_table = D_80175F10;
                    if (F(sprite, void *, 0x2C) != idle_table) {
                        F(sprite, void *, 0x2C) = idle_table;
                        func_80047784(sprite,
                            idle_table[((gameWork.view.viewAngle + F(stats, s16, 0x2A) + 0x100) >> 9) & 7],
                            0);
                    }
                    F(actor, u8, 0x9A) = idle_state;
                }
            }
        }

        F(actor, u16, 0x98) &= 0xFFF3;
        if (F(stats, s16, 0x64) != 0) {
            if (func_800AA6B4(actor, context, sprite, &D_80175F50)) {
                return;
            }
        }
        if (F(stats, u32, 0x1C) & 0x80000) {
            func_800AA888(actor, context, sprite, stats);
            func_80174698(actor, context, sprite, stats);
            return;
        }
        if ((s16)func_800A1C58(stats) != 0) {
            func_800AAB10(actor, context, sprite, stats);
        }
    }

    tile_index = func_8009FB34(F(sprite, u8, 0x24), F(sprite, u8, 0x25));
    F(sprite, u8, 0x26) = tile_index;
    if (F(stats, s8, 0x6D) > 0) {
        if (F(stats, u32, 0x1C) & 0x20) {
            func_800A9A0C(stats);
            return;
        }
        if ((F(sprite, u16, 0x24) == *(u16 *)(&D_80082E80.tileX)) &&
            (F(actor, u8, 0xAE) == 0)) {
            func_80175ED4(actor, stats);
            func_801718F8(actor, context, sprite, stats);
            return;
        }

        if (!(F(stats, u16, 0x46) & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(stats,
                        (u8 *)F(D_800814A8, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }
            if (F(actor, u8, 0xAE) == 0) {
                if ((s16)func_801727D8(actor, context, sprite, 0) == 0) {
                    return;
                }
            }
            F(stats, u16, 0x46) |= 0x4000;
            if (!(F(stats, u16, 0x46) & 0x8000)) {
                func_801718F8(actor, context, sprite, stats);
                if (F(actor, u8, 0xAE) != 0) {
                    func_80175ED4(actor, stats);
                }
                return;
            }
        }

        action_index = (F(stats, u16, 0x46) & 0x3FFF) - 1;
        switch (action_index) {
        case 11:
        if (func_80175ED4(actor, stats) == 0) {
            func_800A9A0C(stats);
            return;
        }
        next_anims = D_80175F10;
        F(sprite, void *, 0x2C) = next_anims;
        func_80047784(sprite,
            next_anims[((gameWork.view.viewAngle + F(stats, s16, 0x2A) + 0x100) >> 9) & 7], 0);
        func_800A9A0C(stats);
        return;

        case 10:
        func_801718F8(actor, context, sprite, stats);
        func_80175ED4(actor, stats);
        return;

        case 7:
        func_80175ED4(actor, stats);
        if ((s16)func_80172050(actor, context, sprite, stats) != 0) {
            return;
        }
        func_80172218(actor, context, sprite, stats);
        return;

        case 8:
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
            return;
        }
        func_801723D8(actor, context, sprite, stats);
        return;

        case 4:
        case 5:
        case 6: {
            s16 heading;
            void *leader;

            heading = func_800A0818(
                F(sprite, u8, 0x24), F(sprite, u8, 0x25),
                D_80082E80.tileX, D_80082E80.tileY, &heading_flags);
            leader = D_800814A8;
            F(stats, s16, 0x2A) = heading;
            if (F(leader, u8, 0x9A) != 17) {
                func_800A9A0C(stats);
                return;
            }
        }

        case 0:
        case 1:
        case 2:
        func_80175ED4(actor, stats);
        func_800AAF00(actor, context, sprite, &D_80175F60, func_80170E94);
        return;

        default:
        func_801718F8(actor, context, sprite, stats);
        if (F(actor, u8, 0xAE) != 0) {
            func_80175ED4(actor, stats);
        }
        return;
        }
    } else {
        if (F(actor, u8, 0xAE) == 0) {
            u32 flags = F(stats, u32, 0x1C);
            if (!(flags & 0x2000)) {
                if (!((s8)tile_index >= 0 && (D_800E2970[(s8)tile_index].flags & 2)) && !(flags & 0x430)) {
                    if ((s16)func_8009FD7C(F(sprite, u8, 0x24), F(sprite, u8, 0x25),
                            D_80082E80.tileX, D_80082E80.tileY) != 0) {
                        F(stats, s16, 0x2A) = func_800A0818(
                            F(sprite, u8, 0x24), F(sprite, u8, 0x25),
                            D_80082E80.tileX, D_80082E80.tileY, &heading_flags);
                    }
                }
            } else if ((s16)func_80042900(stats, 4) == 0) {
                if (F(D_800814A8, u8, 0x9A) == 23) {
                    func_80172334(actor, context, sprite, stats);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (F(sprite, u16, 0x14) & 0x40) {
        return;
    }
    if (F(actor, u8, 0xAE) != 0) {
        active_anims = D_80175F38;
        if (F(sprite, void *, 0x2C) == active_anims) {
            return;
        }
        func_80174EB4(actor, context, sprite);
        F(sprite, void *, 0x2C) = active_anims;
        anim_sprite = sprite;
        anim_entry = active_anims + (((gameWork.view.viewAngle + F(stats, s16, 0x2A) + 0x100) >> 9) & 7);
    } else {
        void *current_anims;
        u8 *idle_anims;

        current_anims = F(sprite, void *, 0x2C);
        idle_anims = D_80175F10;
        if (current_anims == idle_anims) {
            return;
        }
        next_anims = idle_anims;

        F(sprite, void *, 0x2C) = next_anims;
        anim_sprite = sprite;
        anim_entry = (u8 *)((unsigned long)
            (((gameWork.view.viewAngle + F(stats, s16, 0x2A) + 0x100) >> 9) & 7) +
            (unsigned long)next_anims);
    }

    func_80047784(anim_sprite, *anim_entry, 0);
}
