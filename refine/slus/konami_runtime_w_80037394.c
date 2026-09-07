#include "common.h"

#include "common.h"

typedef struct S_80037394_0 {
    u8 pad_00[0x44];
    s32 * unk_44;
    u8 pad_48[0x2];
    s16 unk_4A;
    u8 pad_4C[0x18];
    union { u16 s; volatile u16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
} S_80037394_0;   /* arg0 in func_80037394 */

typedef struct S_80037394_1 {
    u8 pad_00[0x4C];
    u8 unk_4C;
} S_80037394_1;   /* temp_v0 + temp_v1 in func_80037394 */

typedef struct S_80037394_2 {
    u8 pad_00[0x8];
    u32 unk_08;
    s32 unk_0C;
} S_80037394_2;   /* arg2 in func_80037394 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80037534(void *arg0, s32 arg1, void *arg2);
extern void func_80036C7C(s32 *arg0, void *arg1, void *arg2);

extern u8 D_8006A988[];
extern u8 D_8006A994[];
extern u8 D_8006A9A0[];
extern u8 D_8006A9AC[];
extern u8 D_8006A9B8[];
extern u8 D_8006A9C4[];
extern u32 D_8006A9D0[];
extern u8 D_80081E90[];
extern u8 D_80081EA0[];
extern u8 D_80082B80[];
extern u8 D_80082B90[];
extern u8 D_80082BA0[];
extern u8 D_80082BB0[];

/* Updates the current entry's output value and applies its blink color. */
void func_80037394(void *state, s32 mode, void *output) {
    u8 entry_flags;
    s8 *entry_data;
    s16 entry_offset;

    if (func_80037534(state, mode, output) != 0) {
        return;
    }

    func_80036C7C(((S_80037394_0 *)state)->unk_44 + 3, D_8006A988, D_80082B80);
    func_80036C7C(((S_80037394_0 *)state)->unk_44 + 3, D_8006A994, D_80082B90);
    func_80036C7C(((S_80037394_0 *)state)->unk_44 + 3, D_8006A9A0, D_80082BA0);
    func_80036C7C(((S_80037394_0 *)state)->unk_44 + 3, D_8006A9AC, D_80082BB0);
    func_80036C7C(((S_80037394_0 *)state)->unk_44 + 3, D_8006A9B8, D_80081E90);
    func_80036C7C(((S_80037394_0 *)state)->unk_44 + 3, D_8006A9C4, D_80081EA0);

    entry_data = (s8 *)((S_80037394_0 *)state)->unk_44;
    entry_offset = ((S_80037394_0 *)state)->unk_4A;
    entry_flags = ((S_80037394_1 *)(entry_data + entry_offset))->unk_4C;
    if (entry_flags & 0x80) {
        ((S_80037394_0 *)state)->unk_64.s = ((S_80037394_0 *)state)->unk_64.s + 1;
        if (((S_80037394_0 *)state)->unk_64.u & 1) {
            ((S_80037394_2 *)output)->unk_0C = 0xC0C0C0;
        } else {
            ((S_80037394_2 *)output)->unk_0C = 0;
        }
    } else {
        ((S_80037394_2 *)output)->unk_0C = 0xC0C0C0;
    }

    ((S_80037394_2 *)output)->unk_08 =
        D_8006A9D0[(entry_flags & 0x7F) + ((S_80037394_0 *)state)->unk_66];
}
