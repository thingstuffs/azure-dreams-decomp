#include "common.h"

/* S_8006E61C: 12-byte record array indexed by a signed 16-bit id.
 * field0 (u16) is a counter/state value; field4 and field8 are pointers
 * forwarded to func_8003E4FC (callback registration). */
typedef struct {
    u16 field0;
    s16 pad2;
    void *field4;
    void *field8;
} S_8006E61C;
extern S_8006E61C D_8006E61C[];

/* Per-id "last processed" byte counter, indexed by field0-1. */
extern u8 D_80080AF0[];

/* S_80081480 / S_8008148C: >8B structs forced to hi/lo addressing (only
 * field_0 at offset 0 is accessed here); pattern shared with
 * src/w_80043CD0.c and src/w_80041AB0.c. */
typedef struct {
    s32 field_0;
    s32 pad4;
    s32 pad8;
} S_80081480;
extern S_80081480 D_80081480;

typedef struct {
    s32 field_0;
    s32 pad4;
    s32 pad8;
} S_8008148C;
extern S_8008148C D_8008148C;

/* switch dispatcher on pad events; takes no arguments (matched, gcc 2.7.2, code.c) */
extern void func_800542BC(void);

extern void DrawSync(s32 a0);

/* registers a callback (kind, callback-ptr, arg) (matched, code.c) */
extern s32 func_8003E4FC(s32 a0, void *a1, void *a2);

/* runs one step of the main loop while a condition holds (matched, code.c) */
extern void func_8003F320(void);

/* setter for D_800814C8 (matched, gcc 2.7.2, code.c) */
extern void func_8003F5E0(s32 a0);

/* masks a0 to 16 bits and forwards to func_80055778, sign-extends result (matched, code.c) */
extern short func_80053DA8(s32 a0);

/* tests availability bit n of D_800847D0 (matched, gcc 2.8.1, w_8005405C.c) */
extern s32 func_8005405C(s16 n);

/* Activates an unprocessed record, registers its callbacks, and waits for availability. */
void func_8004425C(s16 record_id)
{
    S_8006E61C *record;
    s16 slot;
    u8 *processed_id;
    s32 ready_value;
    s32 available;

    {
        register s32 record_offset ASM_REG("$3") = (s32)record_id * sizeof(S_8006E61C);
        record = (S_8006E61C *)((char *)D_8006E61C + record_offset);
    }
    slot = (s16)((u16)record->field0 - 1);
    processed_id = &D_80080AF0[slot];
    if (*processed_id != record_id + 1) {
        func_800542BC();
        *processed_id = (u8)(record_id + 1);
        DrawSync(0);
        {
            void *callback = record->field8;
            D_80081480.field_0 = D_8008148C.field_0;
            func_8003E4FC(6, callback, 0);
        }
        func_8003E4FC(6, record->field4, 0);
        func_8003F320();
        ready_value = 1;
        /* == D_8008148C.field_0, but reached via the D_80081480 neighbour symbol
         * (offset +12) so gcc treats it as a genuinely different SYMBOL_REF from
         * the EARLIER D_8008148C.field_0 read above and can't CSE the two %hi/%lo
         * address computations into one cached base register (retail recomputes
         * both independently; see decomp_learnings.md's "dual-access global"
         * neighbour-symbol technique). */
        func_8003F5E0(((s32 *)&D_80081480)[3]);
        func_80053DA8(((2 << slot) | 0x10) & 0xFFFF);
        func_800542BC();
        do {
            available = (s16)func_8005405C(record->field0);
        } while (available != ready_value);
    }
}
