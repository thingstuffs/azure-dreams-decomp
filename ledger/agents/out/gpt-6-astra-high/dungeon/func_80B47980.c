#include "common.h"

typedef struct S_80175180_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
} S_80175180_0;   /* state in func_80175180 */

typedef struct S_80175180_1 {
    u8 pad_00[0x96];
    u16 unk_96;
} S_80175180_1;   /* arg0 in func_80175180 */

typedef struct S_80175180_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80175180_2;   /* obj in func_80175180 */

typedef struct S_80175180_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_80175180_3;   /* part in func_80175180 */

typedef struct S_80175180_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80175180_4;   /* pos in func_80175180 */

typedef struct S_80175180_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80175180_5;   /* arg1 in func_80175180 */


#define VFIELD(p, type, off) (*(volatile type *)((u8 *)(p) + (off)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80045340[];
extern u8 D_801749EC[];

/* Creates and initializes an effect at an offset from the supplied position. */
void func_80175180(void *source_arg, void *spawn_pos_arg)
{
    register void *source ASM_REG("$17") = source_arg;   /* MATCH pin: retail immediate-load split depends on it */
    register void *spawn_pos ASM_REG("$18") = spawn_pos_arg;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u16 render_flags;
    void *effect;
    S_80175180_3 *render_part;
    S_80175180_4 *position;
    u8 *state;

    effect = func_8003FC64(0x12);
    ASM_KEEP(source);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(spawn_pos);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    state = (u8 *)effect + 0x20;
    if (effect != 0) {
        ((S_80175180_0 *)state)->unk_08 = 0x4A;
        ((S_80175180_0 *)state)->unk_0A = ((S_80175180_1 *)source)->unk_96;
        ((S_80175180_0 *)state)->unk_0C = 0;
        ((S_80175180_2 *)effect)->unk_10 = D_801749EC;
        func_8004491C(effect, D_80045340);
        render_part = ((S_80175180_2 *)effect)->unk_0C;
        render_part->unk_10 = 0x20;
        render_flags = VFIELD(render_part, u16, 0x14);
        render_flags |= 0xC;
        VFIELD(render_part, u16, 0x14) = render_flags;
        render_flags |= 0x80;
        VFIELD(render_part, u16, 0x14) = render_flags;
        position = ((S_80175180_2 *)effect)->unk_08;
        position->unk_00 = ((S_80175180_5 *)spawn_pos)->unk_00;
        position->unk_04 = ((S_80175180_5 *)spawn_pos)->unk_04;
        position->unk_08 = ((S_80175180_5 *)spawn_pos)->unk_08 + 0xFFE80000;
        render_part = ((S_80175180_2 *)effect)->unk_0C;
        render_part->unk_1E = 0x1000;
        render_part->unk_1C = 0x1000;
        render_part->unk_0E = 0x80;
        render_part->unk_0C = 0x80;
        render_part->unk_0D = 0x80;
    }
}

/* MECHANISM: Pin source/spawn_pos to s1/s2 and keep them just after the allocator call,
   preserving the 0x20 frame/save order without blocking retail call setup.
   A volatile u16 RMW retains both flag stores; source order and u8 fields close the residue. */
