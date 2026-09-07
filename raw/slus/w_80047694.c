#include "common.h"

/* D_80082E6A: standalone byte global (siblings in this wave access it directly
 * via hi/lo, distinct symbol from D_80082E60 even though numerically adjacent).
 * Declared >8B to force %hi/%lo addressing (matches target's lui/lbu form). */
struct S_80082E6A {
    u8 field_0;
    u8 pad[11];
};
extern struct S_80082E6A D_80082E6A;

/* Entry-array element type shared with func_8004761C/func_800482C8 (stride 0xC,
 * only flags byte at offset 0 read by those callees). */
struct S_8004761C_Entry {
    u8 flags;
    u8 pad[0xB];
};
struct S_800482C8_Entry {
    u8 flags;
    u8 pad[0xB];
};

extern void func_8004761C(struct S_8004761C_Entry *arg0, s32 *arg1);
extern void func_800482C8(struct S_800482C8_Entry *arg0, s32 *arg1);
extern void func_800475A4(struct S_8004761C_Entry *arg0, s32 *arg1);

/* S_80047694: caller-side view of an entity/state struct.
 *   field_8  (0x08): pointer to the 0xC-byte entry array (passed on to callees)
 *   field_14 (0x14): u16 flags; bit 0x400 selects the func_800482C8 path
 *   field_28 (0x28): pointer to an s32 cursor/arg passed on to callees
 */
struct S_80047694 {
    u8 pad_0[0x8];
    struct S_8004761C_Entry *field_8;
    u8 pad_C[0x8];
    u16 field_14;
    u8 pad_16[0x28 - 0x16];
    s32 *field_28;
};

/* summary: dispatch on arg0's flags/global state to one of three handlers,
 * passing through the entry-array pointer and the s32* cursor unchanged. */
void func_80047694(struct S_80047694 *arg0)
{
    if (arg0->field_14 & 0x400) {
        func_800482C8((struct S_800482C8_Entry *)arg0->field_8, arg0->field_28);
    } else if (D_80082E6A.field_0 == 1) {
        func_8004761C(arg0->field_8, arg0->field_28);
    } else {
        func_800475A4(arg0->field_8, arg0->field_28);
    }
}
