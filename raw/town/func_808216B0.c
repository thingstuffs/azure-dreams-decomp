#include "common.h"

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern void *D_80020284[5];
extern u8 D_80024334[16];
extern u16 D_80024500[8];
extern u8 D_80045340[];
extern u8 D_800F8E9C[16];

void func_80023EB0(void *arg0)
{
    static void *const sw_keep[] = {
        &&sw_0, &&sw_1, &&sw_2, &&sw_3, &&sw_4
    };
    register u8 *state ASM_REG("$18") = arg0;
    register void *obj ASM_REG("$16");
    void *part;
    register u8 *work ASM_REG("$2");
    u8 *object_data;
    u8 *part_data;
    s32 scale;
    s32 kind;
    s32 store_value;
    s32 mask_index;
    s32 color;
    register s32 index ASM_REG("$17");
    u16 counter;

    switch (S16_AT(state, 0x18)) {
    case 0:
        S16_AT(state, 0xC) = 0x410;
        S16_AT(state, 4) = 0x340;
        S16_AT(state, 0xE) = 0x348;
        S16_AT(state, 6) = 0x348;
        S16_AT(state, 0x10) = -0x60;
        S16_AT(state, 8) = -0x60;

        kind = S16_AT(state, 0x22);
        if ((u32)kind >= 5) {
            goto init_done;
        }
        (void)sw_keep;
        goto *D_80020284[kind];

sw_0:
        store_value = -0x60;
        goto store_both;
sw_1:
        store_value = -0x98;
        goto store_both;
sw_2:
        store_value = -0x30;
store_both:
        S16_AT(state, 0x1E) = store_value;
        S16_AT(state, 0x1C) = store_value;
        goto init_done;
sw_3:
        store_value = -0xB0;
        S16_AT(state, 0x1C) = store_value;
        store_value = -0x10;
        goto store_second;
sw_4:
        store_value = -0x10;
        S16_AT(state, 0x1C) = store_value;
        store_value = -0xB0;
store_second:
        S16_AT(state, 0x1E) = store_value;

init_done:
        index = 1;
        object_data = D_80024334;
        scale = 0x800;
        part_data = D_800F8E9C;
alloc_loop:
        obj = func_8003FC64(0x136);
        if (obj != 0) {
            PTR_AT(obj, 0x10) = object_data;
            func_8004491C(obj, D_80045340);
            part = PTR_AT(obj, 0xC);
            S16_AT(part, 0x14) = 0xC;
            color = 0x00808080;
            ASM_SCHED_BARRIER();
            work = (u8 *)obj + 0x20;
            ASM_KEEP(work);
            S16_AT(part, 0x1E) = scale;
            S16_AT(part, 0x1C) = scale;
            PTR_AT(part, 8) = part_data;
            U8_AT(part, 4) = 0;
            U8_AT(part, 5) = 0;
            S32_AT(part, 0xC) = color;
            PTR_AT(obj, 0x20) = state;
            S16_AT(work, 8) = index;
        }
        ASM_KEEP(obj);
        index--;
        if (index >= 0) {
            goto alloc_loop;
        }
        S16_AT(state, 0x18) = 1;
        break;

    case 1:
        break;

    default:
        goto done;
    }

    counter = U16_AT(state, 0x1A) + 1;
    U16_AT(state, 0x1A) = counter;
    if (((counter >> 2) & 1) != 0) {
        mask_index = S16_AT(state, 0x22);
        if ((U16_AT(PTR_AT(state, 0), 0x62) & D_80024500[mask_index]) != 0) {
            S32_AT(state, 0x14) = 0;
            goto color_done;
        }
    }
    S32_AT(state, 0x14) = 0x00FFFFFF;

color_done:
    if (U16_AT(PTR_AT(state, 0), 0x64) >= U16_AT(state, 0x20)) {
        s32 dx = (S16_AT(state, 0x1C) - S16_AT(state, 8)) >> 1;
        s32 dy = (S16_AT(state, 0x1E) - S16_AT(state, 0x10)) >> 1;

        S16_AT(state, 8) = U16_AT(state, 8) + dx;
        S16_AT(state, 0x10) = U16_AT(state, 0x10) + dy;
        U16_AT(state, 0x24) &= ~1;
        goto done;
    }

    {
        s32 dx = (-0x60 - S16_AT(state, 8)) >> 1;
        s32 dy = (-0x60 - S16_AT(state, 0x10)) >> 1;
        s32 other;
        s32 value;

        S16_AT(state, 8) = U16_AT(state, 8) + dx;
        other = U16_AT(state, 0x10) + dy;
        S16_AT(state, 0x10) = other;
        ASM_SCHED_BARRIER();
        value = (s16)other + 0x60;
        if (value < 0) {
            value = -value;
        }
        if (value < 2) {
            U16_AT(state, 0x24) |= 1;
        }
    }

done:
    ASM_KEEP(state);
    return;
}

/* MECHANISM: closed by SCOPE-SPLIT + two portable SCHED FENCES, no new pins.
   (1) `value`/`other` were function-scope names shared by BOTH tail arms, fusing
   their live ranges and rotating path A's coloring; block-scoping dx/dy per arm
   made path A byte-exact unchanged.  (2) Both tail arms are the SAME shape
   (deltas-first, then the two stores); path B only differs by the trailing
   abs() test, whose sll/sra/addiu chain hangs off the 0x10 store value and so
   out-prioritises the whole 8-coord group in sched1 (it also let dbr steal the
   store into the bgez delay slot).  ASM_SCHED_BARRIER() between the 0x10 store
   and the sign-extend cuts that dependence out of the region: retail's order and
   its bgez nop return exactly.  ASM_KEEP is WRONG here -- its "=r" def puts the
   held value back on the critical chain and reorders the arm.  (3) In the alloc
   loop the same fence pair restores the frame: `color = 0x00808080;` before an
   ASM_SCHED_BARRIER() keeps the lui/ori in the pre-fence region (retail words
   1-2), and `work = obj+0x20; ASM_KEEP(work);` after it defeats gcc's fold of
   obj+0x20+8 into 40(obj) while pinning the addu to retail's word 6; the
   $2 pin then hands part=$3 / twelve=$2 / work=$2 exactly as retail colours it.
   DEPIN note: the inherited ASM_KEEP(index) was itself the residue -- it blocked
   dbr from filling the loop's bgez delay slot with `li $2,1`. */
