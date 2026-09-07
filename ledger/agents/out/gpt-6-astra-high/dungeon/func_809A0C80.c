#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef NON_MATCHING
#define DGN_TABLE_PAGE(sym, offset) ((unsigned long)(sym) - (offset))
#else
#define DGN_TABLE_PAGE(sym, offset) 0x80170000UL
#endif

extern void func_80047784();
extern u8 D_80083160[];
extern s16 D_80083228[];
extern u16 D_80083460[];
extern u8 *D_800E3D7C[];
extern void *D_80170838[];
extern u8 D_801710EC[];
extern u8 D_80175EB8[];
extern u8 D_80175EC8[];
extern u8 D_80175ED0[];

typedef struct S_80172480_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u16 unk_B0;
    s16 unk_B2;
} S_80172480_0;   /* arg0 in func_80172480 */

typedef struct S_80172480_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
} S_80172480_1;   /* arg3 in func_80172480 */

typedef struct S_80172480_2 {
    u8 pad_00[0x8];
    u16 unk_08;
    u8 pad_0A[0xBE];
    u16 unk_C8;
} S_80172480_2;   /* base_83160 in func_80172480 */

typedef struct S_80172480_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    M2C_UNK * unk_2C;
} S_80172480_3;   /* arg2 in func_80172480 */

typedef struct S_80172480_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80172480_4;   /* D_800E3D7C[0] in func_80172480 */

/* Advances an actor's turn-and-animation sequence and restores its saved heading. */
void func_80172480(S_80172480_0 *actor, s32 unused, S_80172480_3 *animation, S_80172480_1 *transform) {
    s32 heading;
    u8 phase;
    u8 *scene_state = D_80083160;
    unsigned long table_page;
    static void *const phase_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };

    phase = actor->unk_9B;
    if (phase >= 5) {
        return;
    }
    (void)phase_labels;
    goto *D_80170838[(u32)phase];
jt_c0:
        heading = transform->unk_2A & 0xFFF;
        transform->unk_2A = heading;
        if (((0x400 - ((((S_80172480_2 *)scene_state)->unk_C8 + 0x100) & 0xE00)) & 0xE00) != heading) {
            transform->unk_2A = heading + 0x200;
            return;
        }
        goto advance;
jt_c1:
        if (actor->unk_92 == 0) {
            table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
            goto resolve_table;
        }
        table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
        ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
        table_page += 0x5EC8;
        if ((animation->unk_14 & 0x8000) == 0) {
            return;
        }
        goto start_animation;
jt_c2:
        if (animation->unk_14 & 0xE000) {
            table_page = DGN_TABLE_PAGE(D_80175ED0, 0x5ED0);
            ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
            table_page += 0x5ED0;
            goto start_animation;
        }
        goto done;
jt_c3:
        {
            u16 scene_status = ((S_80172480_2 *)scene_state)->unk_08;
            if (scene_status != 0) {
                table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
                goto resolve_table;
            }
            if (((S_80172480_4 *)(D_800E3D7C[0]))->unk_9A != 0x17) {
                table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
                goto resolve_table;
            }
        }
        goto done;
resolve_table:
        table_page += 0x5EC8;
start_animation:
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot contents depend on it */
        {
            u8 *animation_table;
            animation_table = (u8 *)table_page;
            animation->unk_2C = animation_table;
            {
                unsigned long animation_entry = (unsigned long)(((s32) (D_80083228[0] + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                animation_entry += (unsigned long)animation_table;
                func_80047784(animation, *(u8 *)animation_entry, 0);
            }
        }
advance:
        phase = actor->unk_9B + 1;
        actor->unk_9B = phase;
        return;
jt_c4:
        if (animation->unk_14 & 0xE000) {
            transform->unk_1C = (s32) (transform->unk_1C | 0x40000);
            {
                u8 *animation_table = D_80175EB8;
                animation->unk_2C = animation_table;
                func_80047784(animation, animation_table[((s32) (D_80083228[0] + (s16) transform->unk_2A + 0x100) >> 9) & 7], 0);
            }
            actor->unk_8C = D_801710EC;
            transform->unk_2A = (u16) actor->unk_B0;
            actor->unk_B2 = 0;
            D_80083460[5] = (u16) (D_80083460[5] - 1);
        }
done:
        return;
}
