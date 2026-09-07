#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_80174300(void) __attribute__((noreturn));

extern s16 D_80083228;
extern u8 D_80174A7C[];


typedef struct S_801740F8_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_801740F8_0;   /* arg0 in func_801740F8 */

typedef struct S_801740F8_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801740F8_1;   /* arg2 in func_801740F8 */

typedef struct S_801740F8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_801740F8_2;   /* arg3 in func_801740F8 */


void func_801740F8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 timer;
    s16 next_timer;
    s32 state;
    register u8 *page ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *tbl;

    state = ((S_801740F8_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto update;
    }
    if (state < 2) {
        page = (u8 *)0x80170000;
        if (state == 0) {
            goto state_0;
        }
        func_80174300();
    } else {
        if (state == 2) {
            goto test_done;
        }
        if (state == 3) {
            goto state_3;
        }
        func_80174300();
    }

state_0:
    ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
    tbl = page + 0x4A7C;
    if (((S_801740F8_1 *)arg2)->unk_2C != tbl) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = tbl;
        func_80047784(
            arg2,
            *(u8 *)(((((D_80083228 + ((S_801740F8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7)) + (u32)tbl),
            0);
    }
    ((S_801740F8_0 *)arg0)->unk_98 |= 8;
    ((S_801740F8_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
    ((S_801740F8_0 *)arg0)->unk_9E = 5;
    ((S_801740F8_0 *)arg0)->unk_A4 = 0;
    ((S_801740F8_0 *)arg0)->unk_9B++;

update:
    timer = ((S_801740F8_0 *)arg0)->unk_9E;
    ((S_801740F8_0 *)arg0)->unk_90 -= ((S_801740F8_0 *)arg0)->unk_A4;
    if (timer != 0) {
        ((S_801740F8_0 *)arg0)->unk_A4 = -func_800644B8(timer * 0x199) << 10;
    }

    ((S_801740F8_0 *)arg0)->unk_90 += ((S_801740F8_0 *)arg0)->unk_A4;
    next_timer = (u16)((S_801740F8_0 *)arg0)->unk_9E - 1;
    ((S_801740F8_0 *)arg0)->unk_9E = next_timer;
    if (next_timer < 0) {
        ((S_801740F8_0 *)arg0)->unk_90 = 0;
        ((S_801740F8_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801740F8_2 *)arg3)->unk_1C |= 0x08000000;
        ((S_801740F8_0 *)arg0)->unk_9B++;
    }

test_done:
    if (!(((S_801740F8_2 *)arg3)->unk_1C & 0x08000000)) {
        goto end;
    }
    ((S_801740F8_0 *)arg0)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_801740F8_1 *)arg2)->unk_24, ((S_801740F8_1 *)arg2)->unk_25);
    ((S_801740F8_0 *)arg0)->unk_9B++;
    func_80174300();

state_3:
    if (((S_801740F8_1 *)arg2)->unk_2C != D_80174A7C - 0x50) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80174A7C - 0x50;
        func_80047784(
            arg2,
            (D_80174A7C - 0x50)[((D_80083228 + ((S_801740F8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

end:
    return;
}

/* MECHANISM: four natural pointer args keep retail's 0x28 frame and s0/s3/s2/s1
   save order. The dispatcher must be an EXPLICIT if/else tree (==1, <2, ==0 |
   ==2, ==3), never a `switch`: a switch has ONE `default:` label, so both
   non-matching paths `j` a single shared tail and word 18 comes out as
   `j $Ldefault` instead of retail's `j func_80174300`; two separate noreturn
   calls duplicate the maspsx LEAD-18 tail jump at both exits.
   Because the case-0 arm's fall-through is then a CALL, reorg refuses to steal
   the `lui %hi(D_80174A7C)` out of the case-0 block into the beq delay slot
   (word 17), so the case-0 table base is built from a HELD PAGE LITERAL
   (0x80170000) assigned in the `state < 2` block: that single `lui` sits before
   the branch and reorg sinks it into the delay slot. `ASM_REG("$2") + ASM_KEEP`
   is load-bearing twice - it pins the page to retail's $v0 and makes the page
   opaque to CSE, so `page + 0x4A7C` stays an `addiu $a1,$v0,0x4a7c` instead of
   collapsing into `ori`. The final index add is written in INTEGER form
   (`idx + (u32)tbl`) because C pointer arithmetic canonicalises to ptr-first and
   would emit `addu $v0,$a1,$v0`; retail's `addu $v0,$v0,$a1` needs index-first.
   The case-3 arm stays SYMBOLIC (`D_80174A7C - 0x50`): its base is a constant
   expression, so fold already puts it last and its %hi is stolen into the
   delay slot unaided. */
