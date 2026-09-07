#include "common.h"

#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_Entry {
    u8 flags;
    u8 pad[0xB];
} S_Entry;

/* Walk arg0's table (*unk28) from base+(index*4) to end in 8-byte steps.
 * For each outer slot with type==2, walk its 0xC-byte entry list and store
 * arg1 into every active (flags&0x20) entry whose id (halfword at +6) matches
 * arg2. Stops after the entry with flags&0x80. */
void func_800478E8(void *arg0, s32 arg1, s32 arg2) {
    u32 var_a0;
    S_Entry *var_v1;
    void *temp_v0;
    void *var_a3;
    void *var_t0;
    s32 two;

    temp_v0 = *M2C_FIELD(arg0, void ***, 0x28);
    var_a0 = M2C_FIELD(temp_v0, s32 *, 0) + (M2C_FIELD(temp_v0, s32 *, 4) * 4);
    if (var_a0 < (u32)M2C_FIELD(temp_v0, u32 *, 8)) {
        two = 2;
        var_t0 = (void *)(var_a0 + 4);
    loop:
        if (M2C_FIELD(var_t0, s16 *, -2) == two) {
            var_v1 = M2C_FIELD(var_t0, S_Entry **, 0);
            var_a3 = (s8 *)var_v1 + 8;
            do {
                if ((var_v1->flags & 0x20) && (M2C_FIELD(var_a3, s16 *, -2) == arg2)) {
                    M2C_FIELD(var_a3, s32 *, 0) = arg1;
                }
                var_a3 = (s8 *)var_a3 + 0xC;
            } while (!((var_v1++)->flags & 0x80));
        }
        {
            void *p = *M2C_FIELD(arg0, void ***, 0x28);
            u32 lim = (u32)M2C_FIELD(p, u32 *, 8);
            var_t0 = (s8 *)var_t0 + 8;
            var_a0 += 8;
            if (var_a0 < lim) {
                goto loop;
            }
        }
    }
}
