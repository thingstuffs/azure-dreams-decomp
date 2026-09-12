#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017360C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_8017360C_0;   /* arg0 in func_8017360C */


typedef struct S_8017360C_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8017360C_2;   /* arg3 in func_8017360C */

typedef struct S_8017360C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8017360C_3;   /* global in func_8017360C */

typedef struct S_8017360C_4 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8017360C_4;   /* owner in func_8017360C */

typedef struct S_8017360C_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_8017360C_5;   /* room_base in func_8017360C */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30();
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173E00(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern void *D_801708D0[];
extern u8 D_801714D4[];
extern u8 D_801740F0[];
extern u8 D_801740F8[];
extern u8 D_80174150[];
extern u8 D_80174158[];
extern u8 D_80174160[];


/* Advances the actor state sequence and selects effects for its facing direction. */
void func_8017360C(void *action, void *context, void *entity, void *actor)
{
    static void *const state_labels[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4, &&state_5
    };
    u8 *effect_table;
    s32 effect_entry;
    s32 next_state;
    u8 state;

    state = ((S_8017360C_0 *)action)->unk_9B;
    if (state >= 6) {
        return;
    }
    (void)state_labels;
    goto *D_801708D0[state];

state_0:
    {
        u8 *dungeon_state;
        u8 *effect_page;
        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        effect_page = (u8 *)0x80170000;
        ASM_KEEP(effect_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        effect_table = effect_page + 0x40F8;
        (*(void * *)((u8 *)entity + 0x2C)) = effect_table;
        effect_entry = (D_80083228 + ((S_8017360C_2 *)actor)->unk_2A + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)effect_table;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        dungeon_state = (u8 *)&D_80083460;
        ((S_8017360C_3 *)dungeon_state)->unk_0A--;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
        goto store_state;
    }

state_1:
        if (((S_8017360C_0 *)action)->unk_92.s != 0) {
            return;
        }
        {
            u8 *effect_page;
            effect_page = (u8 *)0x80170000;
            ASM_KEEP(effect_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            effect_table = effect_page + 0x4150;
        }
        goto effect_common;

state_2:
        if ((s16)((S_8017360C_0 *)action)->unk_96++ < 2) {
            return;
        }
        {
            u8 *effect_page;
            effect_page = (u8 *)0x80170000;
            ASM_KEEP(effect_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            effect_table = effect_page + 0x4158;
        }
        goto effect_common;

state_3:
        if ((func_80042900(actor, 1) << 16) != 0) {
            u8 *dungeon_state = (u8 *)&D_80083460;
            s32 actor_flags;

            if ((((S_8017360C_3 *)dungeon_state)->unk_02 & 0x1000) != 0) {
                return;
            }

            if ((((S_8017360C_2 *)actor)->unk_64 != 0) &&
                func_800AA6B4(action, context, entity, 0)) {
                return;
            }

            if (((S_8017360C_2 *)actor)->unk_25 == 0) {
                if ((((S_8017360C_3 *)dungeon_state)->unk_02 & 0x2008) != 0) {
                    return;
                }
                func_800AA79C(action, context, entity, actor);
                goto done;
            }

            if ((s16)func_800A2C34(actor) != 0) {
                return;
            }

            actor_flags = ((S_8017360C_2 *)actor)->unk_1C.s;
            if ((actor_flags & 0x100) != 0) {
                func_800AA258(action, context, entity, actor);
                goto done;
            }

            {
            u32 adjustment_flag = 0x80000;
            if ((actor_flags & adjustment_flag) != 0) {
                u16 remaining_amount;

                func_800AA888(action, context, entity, actor);
                remaining_amount = ((S_8017360C_0 *)action)->unk_92.u;
                remaining_amount -= ((S_8017360C_0 *)action)->unk_A2;
                ((S_8017360C_0 *)action)->unk_A2 = 0;
                ((S_8017360C_0 *)action)->unk_9E = 0;
                ((S_8017360C_0 *)action)->unk_92.u = remaining_amount;
                func_80173E00(action, context, entity, actor);
                goto done;
            }
            }

            if (((S_8017360C_2 *)actor)->unk_6D == 0) {
                return;
            }

            if ((s16)func_800A2C34(actor) != 0) {
                void *owner = D_800814A8;

                if ((s16)func_8009A180(actor,
                        (u8 *)((S_8017360C_4 *)owner)->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            func_800A9A0C(actor);
            func_800A9A04(actor);
            if ((func_80042900(actor, 1) << 16) != 0) {
                u8 *room_base = D_80082E80;
                s8 room_id = ((Rec_D_80082E80 *)entity)->unk_26.as_s8;

                if ((room_id != ((S_8017360C_5 *)room_base)->unk_26) || (room_id < 0)) {
                    if ((s16)func_8009FD40(room_base, entity) >= 2) {
                        goto final_check;
                    }
                }

                if ((func_800A6D30() & 7) != 0) {
                    goto final_check;
                }
                func_80042B68(actor, 1);
            }
final_check:
            if ((func_80042900(actor, 1) << 16) != 0) {
                return;
            }
        }

        {
            u8 *effect_page;
            effect_page = (u8 *)0x80170000;
            ASM_KEEP(effect_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            effect_table = effect_page + 0x4160;
        }
        (*(void * *)((u8 *)entity + 0x2C)) = effect_table;
        effect_entry = (D_80083228 + ((S_8017360C_2 *)actor)->unk_2A + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)effect_table;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000) != 0) {
            goto finished;
        }
        ((S_8017360C_0 *)action)->unk_9B++;
        {
            u8 *dungeon_state = (u8 *)&D_80083460;
            ((S_8017360C_3 *)dungeon_state)->unk_0A++;
        }
        goto done;

state_4:
        {
        u32 phase_flag = 0x40000;
        u8 *effect_page;
        u32 phase_flags;

        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        ASM_KEEP(phase_flag);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        effect_page = (u8 *)0x80170000;
        ASM_KEEP(effect_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        phase_flags = ((S_8017360C_2 *)actor)->unk_1C.u;
        effect_table = effect_page + 0x40F8;
        phase_flags |= phase_flag;
        ((S_8017360C_2 *)actor)->unk_1C.u = phase_flags;
effect_common:
        (*(void * *)((u8 *)entity + 0x2C)) = effect_table;
        effect_entry = (D_80083228 + ((S_8017360C_2 *)actor)->unk_2A + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)effect_table;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        ((S_8017360C_0 *)action)->unk_96 = 0;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
store_state:
        ((S_8017360C_0 *)action)->unk_9B = next_state;
        goto done;
        }

state_5:
        if ((s16)((S_8017360C_0 *)action)->unk_96++ < 4) {
            return;
        }

        {
            register u8 *effect_page ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            effect_page = (u8 *)0x80170000;
            ASM_KEEP(effect_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            effect_table = effect_page + 0x40F0;
        }
        (*(void * *)((u8 *)entity + 0x2C)) = effect_table;
        effect_entry = (D_80083228 + ((S_8017360C_2 *)actor)->unk_2A + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)effect_table;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        {
            u8 *dungeon_state = (u8 *)&D_80083460;
            ((S_8017360C_3 *)dungeon_state)->unk_0A--;
        }

finished:
        ((S_8017360C_0 *)action)->unk_8C = D_801714D4;
done:
        return;
}

/* MECHANISM: retail sets no $a0 for the func_800A6D30 call — on the `bgez` fast path
   $a0 still holds &D_80082E80 (the func_8009FD40 arg base), and the jal delay slot is a
   real nop, so the retail source called it ARG-LESS (K&R decl, zero-arg call). Passing
   arg3 made gcc emit a redundant `move $a0,$s0` into that delay slot (the whole 1-word
   residue two prior runs plateaued on). Rest of the shape: $5-pinned 0x80170000 page base
   per effect table, extern jtbl_D_801708D0 computed-goto dispatch, &D_80083460 held base
   for the 0xA counter RMW. */
