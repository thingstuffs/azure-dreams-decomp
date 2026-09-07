#include "common.h"

/* Sparse view of the shared global state struct D_80083160: only the two
 * fields this function reads (offsets 0x8 and 0x10). Declared >8 bytes so
 * codegen uses %hi/%lo addressing, matching sibling functions elsewhere
 * that touch other fields of the same global. */
typedef struct {
    u8 pad00[0x8];
    s32 unk08;
    u8 pad0C[0x4];
    s32 unk10;
} S_80050308_D80083160;

extern S_80050308_D80083160 D_80083160;

/* Object struct for this function's argument. The object is embedded 0x20
 * bytes into a larger allocation (base = (char*)obj - 0x20, passed to the
 * sibling init/reset routines func_80050DA8/func_80050EA8), and has a
 * "next state" callback pointer at offset -0x10. */
typedef struct S_80050308 {
    u8 pad00[0x4];
    s32 unk04;        /* saved previous state-fn value */
    u8 pad08[0x4];
    s32 unk0C;         /* counter */
    s32 unk10;         /* mode value (2 or 3) */
    s32 unk14;
    s32 unk18;
    s32 unk1C;         /* wrapped index */
    s32 unk20;         /* result of func_800502E0 */
    u8 pad24[0x4];
    void *unk28;       /* arg passed to func_800502E0 */
    u8 pad2C[0x68 - 0x2C];
    s32 unk68;         /* arg0 for func_800500B4 */
} S_80050308;

typedef void (*StateFn_80050308)(void *);

extern s16 func_80053DA8(s32 a0);
extern void func_80050DA8(void *a0);
extern void func_80050EA8(void *a0);
extern s32 func_800502E0(void *a0);
extern s32 func_8004FF20(void *a0);
extern void func_8004FFA8(void *a0);
extern s32 func_80049DE8(s32 a0, s32 a1, s32 a2);
extern void func_800500B4(s32 a0, void *a1);

/* summary: State-machine driver for an object embedded 0x20 bytes into a
 * larger allocation. Reacts to global flag bits in D_80083160 (offsets
 * 0x8/0x10): bit 0x20 -> tear down and reset to the outer base object; bit
 * 0x40 -> fully reset via func_800502E0/func_8004FF20, either swapping in
 * the func_8004FFA8 state callback or handing off to func_80050EA8; bit
 * 0x5000 (of the flag-8 field) -> adjust a ramp counter/mode toward a
 * target direction implied by flag-0x10's 0x4000/0x1000 bits, and once a
 * nonzero direction is established, re-wrap the index field via
 * func_80049DE8. Always finishes by forwarding to func_800500B4. */
void func_80050308(void *a0)
{
    S_80050308 *s0 = (S_80050308 *)a0;
    S_80050308_D80083160 *g = &D_80083160;
    s32 v1;
    s32 s1;

    if (g->unk08 != 0) {
        v1 = g->unk10;
        if (v1 & 0x20) {
            func_80053DA8(0x515);
            func_80050DA8((char *)s0 - 0x20);
        } else if (v1 & 0x40) {
            func_80053DA8(0x514);
            s0->unk20 = func_800502E0(s0->unk28);
            if (func_8004FF20(s0) == 0) {
                s32 old = *(s32 *)((char *)s0 - 0x10);

                *(StateFn_80050308 *)((char *)s0 - 0x10) = func_8004FFA8;
                s0->unk04 = old;
            } else {
                func_80050EA8((char *)s0 - 0x20);
            }
        } else if (g->unk08 & 0x5000) {
            s1 = 0;
            if (v1 & 0x4000) {
                s1 = 1;
                goto set_mode3;
            }
            if (v1 & 0x1000) {
                s1 = -1;
                goto set_mode3;
            }
            goto check_counter;

        set_mode3:
            s0->unk0C = 0;
            s0->unk10 = 3;
            goto merge;

        check_counter:
            if (s0->unk0C >= 3) {
                s32 v1b;

                s0->unk0C = s0->unk0C - 1;
                v1b = g->unk08;
                if (v1b & 0x4000) {
                    s1 = 1;
                } else if (v1b & 0x1000) {
                    s1 = -1;
                } else {
                    goto merge;
                }
                s0->unk10 = 2;
            } else {
                s0->unk0C = s0->unk0C + 1;
            }

        merge:
            if (s1 != 0) {
                func_80053DA8(0x502);
                s0->unk18 = s0->unk1C;
                s0->unk14 = 0;
                s0->unk1C = func_80049DE8(s0->unk1C, s1, 6);
            }
        }
    }
    func_800500B4(s0->unk68, s0);
}
