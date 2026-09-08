#include "common.h"

typedef struct S_801750F8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801750F8_0;   /* arg0 in func_801750F8 */

typedef struct S_801750F8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801750F8_1;   /* arg3 in func_801750F8 */

typedef struct S_801750F8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_801750F8_2;   /* arg2 in func_801750F8 */

typedef struct S_801750F8_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801750F8_3;   /* counter in func_801750F8 */



extern s32 func_801744E0(void *);
extern void func_80047784(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174D98(void *, void *, void *, void *);

extern s16 D_80083228;
extern s32 D_80083460;
extern void *D_80170888[];
extern u8 D_801716F4[];
extern u8 D_8017555C[];
extern u8 D_801755BC[];
extern u8 D_801755C4[];
extern u8 D_801755CC[];

/* Advances a timed action animation, deforming the sprite and restoring it on completion. */
void func_801750F8(void *action_in, void *direction_data_in, void *sprite_in, void *actor_in)
{
    void *action = action_in;
    void *direction_data = direction_data_in;
    register void *sprite ASM_REG("$17") = sprite_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *actor = actor_in;
    u8 state;
    static void *const state_labels[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };

    state = ((S_801750F8_0 *)action)->unk_9B;
    if ((u32)state >= 6) {
        goto end;
    }
    (void)state_labels;
    goto *D_80170888[state];

L0:
    {
        s32 facing_angle;
        s16 timer;
        u32 actor_flags;

        facing_angle = func_801744E0(direction_data);
        facing_angle = (facing_angle << 16) >> 7;
        ((S_801750F8_1 *)actor)->unk_2A = facing_angle;

        timer = ++((S_801750F8_0 *)action)->unk_96.s;
        if (timer >= 0x78) {
            ((S_801750F8_0 *)action)->unk_9B = 5;
            ((S_801750F8_0 *)action)->unk_96.s = 0;
            goto end;
        }

        actor_flags = ((S_801750F8_1 *)actor)->unk_14;
        if (!(actor_flags & 0x00800000)) {
            goto end;
        }
        ((S_801750F8_1 *)actor)->unk_14 = actor_flags & 0xFF7FFFFF;
        ((S_801750F8_0 *)action)->unk_96.s = 0;
        ((S_801750F8_0 *)action)->unk_9B++;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801755BC;
        func_80047784(sprite,
            D_801755BC[((D_80083228 + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_800A56E0(0x51E);
        goto end;
    }

L1:
    if (!(((S_801750F8_2 *)sprite)->unk_14 & 0x6000)) {
        goto end;
    }
    ((S_801750F8_0 *)action)->unk_96.s = 0;
    ((S_801750F8_0 *)action)->unk_9B++;
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801755CC;
    func_80047784(sprite,
        D_801755CC[((D_80083228 + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801750F8_2 *)sprite)->unk_14 |= 0x0800;
    goto end;

L2:
    {
        s16 timer;

        timer = ++((S_801750F8_0 *)action)->unk_96.s;
        if (timer < 0xF) {
            goto end;
        }
        ((S_801750F8_0 *)action)->unk_96.s = 0;
        ((S_801750F8_0 *)action)->unk_9B++;
        ((S_801750F8_2 *)sprite)->unk_14 &= 0xF7FF;
        goto end;
    }

L3:
    {
        s32 scale_x;
        s32 scale_y;
        s16 timer;

        timer = ++((S_801750F8_0 *)action)->unk_96.s;
        if (timer < 3) {
            goto opposite_sound;
        }
        if (timer >= 7) {
            goto check_11;
        }
        scale_x = ((S_801750F8_2 *)sprite)->unk_1C;
        scale_y = ((S_801750F8_2 *)sprite)->unk_1E;
        scale_x += 0x258;
        scale_y -= 0x258;
        goto store_xy;

check_11:
        if (timer >= 0xB) {
            goto timer_ge_11;
        }

opposite_sound:
        scale_x = ((S_801750F8_2 *)sprite)->unk_1C - 0x258;
        scale_y = ((S_801750F8_2 *)sprite)->unk_1E + 0x258;
        ((S_801750F8_2 *)sprite)->unk_1C = scale_x;
        ((S_801750F8_2 *)sprite)->unk_1E = scale_y;
        func_800A56E0(0x51F);
        goto after_xy;

timer_ge_11:
        if (timer >= 0xF) {
            goto check_17;
        }
        scale_x = ((S_801750F8_2 *)sprite)->unk_1C;
        scale_y = ((S_801750F8_2 *)sprite)->unk_1E;
        scale_x += 0x258;
        ASM_KEEP(scale_x);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        scale_y -= 0x258;
        goto store_xy;

check_17:
        if (timer >= 0x11) {
            goto after_xy;
        }
        scale_x = ((S_801750F8_2 *)sprite)->unk_1C - 0x258;
        scale_y = ((S_801750F8_2 *)sprite)->unk_1E + 0x258;

store_xy:
        ((S_801750F8_2 *)sprite)->unk_1C = scale_x;
        ((S_801750F8_2 *)sprite)->unk_1E = scale_y;

after_xy:
        if (((S_801750F8_0 *)action)->unk_96.u < 0x14) {
            goto end;
        }
        ((S_801750F8_0 *)action)->unk_96.s = 0;
        ((S_801750F8_0 *)action)->unk_9B++;
        ((S_801750F8_2 *)sprite)->unk_1E = 0x1000;
        ((S_801750F8_2 *)sprite)->unk_1C = 0x1000;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801755C4;
        func_80047784(sprite,
            D_801755C4[((D_80083228 + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_800A56E0(0x509);
        func_80174D98(action, direction_data, sprite, actor);
        goto end;
    }

L4:
    {
        s16 timer;

        timer = ++((S_801750F8_0 *)action)->unk_96.s;
        if (timer < 9) {
            goto end;
        }
        ((S_801750F8_0 *)action)->unk_96.s = 0;
        ((S_801750F8_0 *)action)->unk_9B++;
        goto end;
    }

L5:
    {
        u8 *action_counters = (u8 *)&D_80083460;

        ((S_801750F8_3 *)action_counters)->unk_0A--;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8017555C;
        func_80047784(sprite,
            D_8017555C[((D_80083228 + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_800AD594(actor, 0x1000);
        ((S_801750F8_0 *)action)->unk_8C = D_801716F4;
        ((S_801750F8_3 *)action_counters)->unk_0C = 0;
        ((S_801750F8_1 *)actor)->unk_46 &= 0x7FFF;
    }

end:
    return;
}

/* MECHANISM: frame is 4 param->callee-saved copies; all four MUST be declared as
   ASM_REG register locals in parameter order ($18,$16,$17,$19) so the copies emit
   a0,a1,a2,a3 and each sw pairs with its move (unpinned params emit via assign_parms
   and reorder to a1,a3,a0,a2).  L3's two identical "+0x258" arms are cross-jumped
   into one block unless each carries an ASM_KEEP at a DIFFERENT depth (after both
   lhu in arm A, after the first addiu in arm C): the volatile asm stops
   find_cross_jump's backward match while leaving the trailing addiu free to fill the
   `j` delay slot.  Config: 2.7.2-cdk-G0 -- 2.8.1-G0's dbr refuses a split-address
   %hi (HIGH) insn in a branch delay slot and steals `move a0,s1` instead (+1 word
   at each of the two table sites); cdk fills both slots with `lui a1,%hi(tbl)`. */
