#include "common.h"

/* S_800799C0: per-voice/channel value table (matches existing convention
 * used by src/w_8005E7E0.c / func_8005DA88's indexed view of the same
 * global). */
typedef struct S_800799C0 {
    s32 value[10];
} S_800799C0;
extern S_800799C0 D_800799C0;

/* S_800799B4: 3-word record - value, flag, pointer (offsets 0/4/8 off
 * D_800799B4/D_800799B8/D_800799BC). Confirmed by sibling func_8005D838,
 * which writes value=a0(size), flag=0, ptr=a1(buffer) through the same
 * three symbols; this function clears all three fields to 0. */
typedef struct S_800799B4 {
    s32 value;
    s32 flag;
    void *ptr;
} S_800799B4;
extern S_800799B4 D_800799B4;

/* S_80079974: playback/queue busy flag (plain scalar). Declared as an
 * incomplete-size array to force hi/lo (not gp_rel) addressing, matching
 * the convention in src/w_8005E7E0.c. */
extern s32 D_80079974[3];

/* Matches existing declaration in src/w_8005E450.c. */
typedef struct S_800794FC {
    s32 v;
    s32 pad[2];
} S_800794FC;
extern S_800794FC D_800794FC;

/* Matches existing declaration in src/w_8005E450.c. */
typedef struct S_80079500 {
    void *ptr;
    s32 pad[2];
} S_80079500;
extern S_80079500 D_80079500;

/* Remaining reset-block scalars: each gets its own independent %hi/%lo
 * materialization in retail (no address reuse across stores), so each is
 * declared as its own >8B symbol to force hi/lo addressing, matching the
 * array[3]/array[8] convention used elsewhere in this TU family. */
extern s32 D_800794F8[3];
extern s32 D_80079508[3];
extern s16 D_8007950C[8];
extern s16 D_8007950E[8];
extern s32 D_80079510[3];
extern s32 D_80079514[3];
extern s32 D_800794F4[3];
extern s32 D_800794F0[3];
extern s32 D_8007951C[3];
extern s32 D_80079518[3];
extern s32 D_80079950[3];

/* 24-entry s16 sentinel table; D_80079520 is element 0, D_8007954E is the
 * last element (base + 23*2). */
extern s16 D_80079520[24];

extern void ResetCallback(s32 a0);
extern void func_8005CC04(s32 a0);
extern void func_8005CB88(void);
extern void func_8005D550(s32 a0, s32 a1, s32 a2);

/* Resets SPU/voice playback state. Calls ResetCallback/func_8005CC04 on the
 * requested channel a0; if a0 is the master channel (0), fills a 24-entry
 * s16 sentinel table with 0xC000. Then calls func_8005CB88, clears a block
 * of playback-state globals, re-primes D_80079500.ptr with the current
 * D_800799C0[0] value and forwards it to func_8005D550(0xD1, value, 0),
 * then clears a second block of state globals (including the
 * D_800799B4/B8/BC record and the D_80079974 busy flag). */
void func_8005CA90(s32 a0)
{
    s32 s0 = a0;
    s32 v1;
    s32 i;

    ResetCallback(a0);
    func_8005CC04(s0);

    if (s0 == 0) {
        u16 val = 0xC000;
        for (i = 23; i >= 0; i--) {
            D_80079520[i] = val;
        }
    }

    func_8005CB88();

    v1 = D_800799C0.value[0];

    D_800794F8[0] = 0;
    D_800794FC.v = 0;
    D_80079508[0] = 0;
    D_8007950C[0] = 0;
    D_8007950E[0] = 0;
    D_80079510[0] = 0;
    D_80079514[0] = 0;
    D_80079500.ptr = (void *)v1;

    func_8005D550(0xD1, v1, 0);

    D_800799B4.value = 0;
    D_800799B4.flag = 0;
    D_800799B4.ptr = 0;
    D_800794F4[0] = 0;
    D_80079974[0] = 0;
    D_800794F0[0] = 0;
    D_8007951C[0] = 0;
    D_80079518[0] = 0;
    D_80079950[0] = 0;
}
