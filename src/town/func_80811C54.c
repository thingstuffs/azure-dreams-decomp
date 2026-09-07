#include "common.h"

#define FIELD(p, type, off) (*(type)((u8 *)(p) + (off)))
#define COUNT_VALUE (D_80012BCC)
#define COUNT_STORE(x) (D_80012BCC = (x))
#define COUNT_RELOAD (D_80012BCC)
#define DIGIT0 (D_80530590[0])
#define DIGIT1 (D_80530590[1])
#define DIGIT2 (D_80530590[2])

extern void func_8003BC18(void *, void *);
extern void *func_800373DC(s32);
extern void func_80232A08(void *);
extern void *func_80232868(s32, s32, s32);
extern void func_802441A4(void *);
extern void func_80244588(void);
extern void *func_80252550(void *, void *);
extern void func_8023FA58(void *, void *, void *);
extern u8 D_8003C558[];
extern u32 D_80012BCC;
extern u32 D_80077C68[4];
extern u8 D_80077C64[];
extern u8 D_8012F130[0x20];
extern u16 D_801328F8[];
extern u8 D_80526704[];
extern u8 D_80530154[];
extern u8 D_8053016C[];
extern u8 D_8053019C[][12];
extern s16 D_805301CC[];
extern s16 D_80530590[];
extern void *D_80530598[];
extern u8 D_8052DC78[];
extern u8 D_8052D770[];

void func_8052C854(void *arg0, void *arg1)
{
    u8 *self = (u8 *)arg0;
    u8 *input;
    u8 *common_value;
    register u8 *arg1_bytes;
    s32 state;
    s32 i;
    s32 j;
    s32 inner;
    s16 *digit_base;
    s32 state_one;
    u8 *obj;

    input = D_8012F130;
    state = FIELD(self, s16 *, 0x5C);
    arg1_bytes = (u8 *)arg1;
    common_value = D_80526704;
    if ((u32)state >= 8U) {
        goto done;
    }
    switch (state) {
    case 0: goto state_0;
    case 1: goto state_1;
    case 2: goto state_2;
    case 3: goto state_3;
    case 4: goto state_4;
    case 5: goto state_5;
    case 6: goto state_6;
    case 7: goto state_7;
    }

state_0:
    FIELD(self, u16 *, 0x62) = 0;
    FIELD(self, u16 *, 0x64) = 0;
    func_802441A4(input);
    state_one = 1;
    FIELD(self, s16 *, 0x5C) = state_one;
    if (COUNT_VALUE < 1000U) {
        goto done;
    }
    if (func_80252550(D_80530154, arg1_bytes) == 0) {
        goto done;
    }
    D_80530598[0] = func_80232868(0, -80, 64);
    D_801328F8[0] = 0;
    func_80244588();
    COUNT_STORE(COUNT_VALUE - 1000);
    FIELD(self, u16 *, 0x64) = 1;
    FIELD(self, u16 *, 0x5E) = 5;
    FIELD(self, s16 *, 0x5C) = 2;
    goto done;

state_1:
    if (FIELD(input, u32 *, 8) & 0x5000) {
        u16 value = FIELD(self, u16 *, 0x5E);
        FIELD(self, u16 *, 0x5E) = value - 1;
        if ((s16)value < 0) {
            FIELD(self, u16 *, 0x5E) = 0;
            goto label_C984;
        }
    } else {
        FIELD(self, u16 *, 0x5E) = 5;
    }

label_C984:
    if ((FIELD(input, u32 *, 0x10) & 0x1000) ||
        ((FIELD(input, u32 *, 8) & 0x1000) &&
         (FIELD(self, s16 *, 0x5E) <= 0))) {
        if (FIELD(self, u16 *, 0x64) < 3U) {
            if (COUNT_VALUE < 1000U) {
                goto done;
            }
            ++FIELD(self, u16 *, 0x64);
            {
                u32 *count = &D_80012BCC;
                COUNT_STORE(*count - 1000);
            }
            goto done;
        }
    }

    if ((FIELD(input, u32 *, 0x10) & 0x4000) ||
        ((FIELD(input, u32 *, 8) & 0x4000) &&
         (FIELD(self, s16 *, 0x5E) <= 0))) {
        if (FIELD(self, u16 *, 0x64) >= 2U) {
            COUNT_STORE(COUNT_VALUE + 1000);
            FIELD(self, u16 *, 0x64)--;
            goto done;
        }
    }

    {
        state = FIELD(input, u32 *, 0x10);
        if (state & 0x40) {
            FIELD(self, u16 *, 0x5E) = 10;
            FIELD(self, s16 *, 0x5C) = 3;
            goto done;
        }
        if (!(state & 0x20) || FIELD(self, u16 *, 0x64) == 0) {
            goto done;
        }
        FIELD(self, u16 *, 0x5E) = 20;
        FIELD(self, s16 *, 0x5C) = 4;
        goto done;
    }

state_2:
    {
        s32 value = FIELD(self, u16 *, 0x5E) - 1;
        FIELD(self, u16 *, 0x5E) = value;
        if ((s16)value > 0) {
            goto done;
        }
        COUNT_STORE(COUNT_VALUE + (s32)FIELD(self, u16 *, 0x64) * 1000);
        func_80232A08(D_80530598[0]);
        FIELD(self, s16 *, 0x5C) = 0;
        goto done;
    }

state_3:
    {
        s32 value = FIELD(self, u16 *, 0x5E) - 1;
        FIELD(self, u16 *, 0x5E) = value;
        if ((s16)value > 0) {
            goto done;
        }
        {
            u8 *slot;
            j = 2;
            i = 2;
            slot = self + 8;
            do {
                u8 *child = FIELD(slot, u8 **, 0x4C);
                FIELD(child, s16 *, 0x24) = i;
                slot -= 4;
                j--;
            } while (j >= 0);
        }
        FIELD(self, s16 *, 0x5C) = 5;
        goto done;
    }

state_4:
    {
        s16 index = FIELD(self, s16 *, 0x5E);
        u8 *child = FIELD(
            self + (s32)index * 4,
            u8 **, 0x4C);
        if (FIELD(child, s16 *, 0x24) != 3) {
            goto done;
        }
        FIELD(self, s16 *, 0x5C) = 6;
        FIELD(self, u16 *, 0x60) = 0;
        goto done;
    }

state_5:
    {
        u16 value = FIELD(self, u16 *, 0x60);
        FIELD(self, u16 *, 0x60) = value - 1;
        if ((s16)value <= 0) {
            FIELD(self, u16 *, 0x60) = 0;
        }
    }

    if ((FIELD(input, u32 *, 0x10) & 0x20) &&
        FIELD(self, s16 *, 0x60) == 0) {
        s16 index = FIELD(self, s16 *, 0x5E);
        u8 *child = FIELD(
            self + (s32)index * 4,
            u8 **, 0x4C);
        FIELD(child, s16 *, 0x24) = 4;
        FIELD(self, u16 *, 0x60) = 10;
        FIELD(self, u16 *, 0x5E) = FIELD(self, u16 *, 0x5E) + 1;
    }

    if (FIELD(self, s16 *, 0x5E) != 3) {
        goto done;
    }
    FIELD(self, s32 *, 0x58) = 0;
    {
        /* pad/tailpad reproduce retail's 160-byte locals area.  tailpad is
           one word short of the natural [2]: the missing word is taken by
           the dead spill slot reload allocates for the (slot - self) seed
           of the j-gadget below (gcc 2.6.3 reload1.c:2309 alter_reg gives a
           stack slot to every pseudo with reg_renumber < 0 and stale
           reg_n_refs > 0, even when combine already deleted its insns).  */
        struct MatrixFrame {
            s32 pad[22];
            s32 values[9];
            s32 tailpad[1];
        } matrix_frame;
        u8 *slot_base;
        u8 *table_base;
        u8 *scratch;
        u8 *slot;
        s16 *map;
        s32 matrix_count;

        j = 2;
        slot_base = self + 8;
        table_base = D_8053019C[2];
        scratch = (u8 *)matrix_frame.pad + 24;
        inner = 2;

matrix_outer:
        {
            u8 *table;
            s32 *dst;
            u8 *child;
            inner = 2;
            table = table_base;
            slot = slot_base;
            dst = (s32 *)(scratch + 96);
            do {
            {
                child = *(u8 **)(slot + 0x4C);
                i = FIELD(child, s16 *, 0x2A);
                /* Runtime no-ops (i*3 - i - i == i); combine folds all nine
                   away before allocation, so they emit nothing.  They are
                   load-bearing twice at the earlier passes:
                   1) loop.c keeps the %12 magic constant (lui/ori) INSIDE
                      this loop, as retail has it, only while the body holds
                      > threshold real insns at loop time: move_movables'
                      (threshold*savings*lifetime) >= insn_count test
                      (gcc 2.6.3 loop.c:1622, threshold = 2*(1+n_non_fixed_regs),
                      loop.c:525).  Measured on this row: 56 insns rejected,
                      52 hoisted (+2 words) -- eight copies are NOT enough.
                   2) flow.c counts the folded statements into i's
                      reg_n_refs (flow.c:1977, loop-depth weighted), keeping
                      the function-scope i top-priority in global.c's
                      allocno_compare (global.c:594) so it owns $a0 across
                      this loop exactly as retail's words 260-271 need.  */
                i = i * 3 - i - i;
                i = i * 3 - i - i;
                i = i * 3 - i - i;
                i = i * 3 - i - i;
                i = i * 3 - i - i;
                i = i * 3 - i - i;
                i = i * 3 - i - i;
                i = i * 3 - i - i;
                i = i * 3 - i - i;
                /* Single-expression form owns retail's words 272-273: the
                   sum, remainder and address temporaries are fresh locals
                   that each die exactly once, so local-alloc chains them
                   into one quantity (combine_regs; a tie to i itself is
                   impossible -- local-alloc.c:1762 refuses when the dying
                   reg is a global) and the ascending scan lands it in $a0
                   because the div-magic subexpression quantities hold
                   $v0/$v1 first (qty_compare, local-alloc.c:1576).  */
                *dst = table[(inner + i) % 12];
                dst--;
                inner--;
            }
            } while (inner >= 0);
            slot_base -= 4;
            table_base -= 12;
            scratch -= 4;
            j--;
            scratch -= 8;
        }
        if (j >= 0) {
            goto matrix_outer;
        }

        matrix_count = FIELD(self, u16 *, 0x64);
        {
            /* j == 0 here: after three outer iterations slot == self, so
               t == 0 and t*3 - t - t - t == 0; combine folds the whole pair
               to `j = 0` (retail's move $a3,$zero).  The (slot - self) seed
               is load-bearing: it is slot's 4th weighted reference at flow
               time, and with matrix_count read from self (retail word 283,
               lhu base $s0) slot needs exactly 4 refs to keep the five loop
               pointers in retail's $t0-$t4 fill order under global.c's
               floor_log2(n_refs)-quantised allocno_compare (global.c:594).
               Cost: one dead 4-byte spill slot, absorbed by tailpad[].  */
            s32 t = slot - self;
            j = t * 3 - t - t - t;
            if (matrix_count > 0) {
                map = D_805301CC;
                do {
                switch (j) {
                case 0: {
                    u16 flags;
                    if (matrix_frame.values[1] != matrix_frame.values[4] ||
                        matrix_frame.values[1] != matrix_frame.values[7]) {
                        break;
                    }
                    {
                        s32 value = matrix_frame.values[1];
                        s32 offset = (s32)map[value] * 1000;
                        flags = FIELD(self, u16 *, 0x62);
                        FIELD(self, u16 *, 0x62) = flags | 4;
                        {
                            register s32 delta =
                                (s32)FIELD(self, u16 *, 0x64) * offset;
                            FIELD(self, s32 *, 0x58) =
                                delta + FIELD(self, s32 *, 0x58);
                        }
                    }
                    if (matrix_frame.values[4] == 0) {
                        u16 next_flags = flags | 5;
                        FIELD(self, u16 *, 0x62) = next_flags;
                    }
                    break;
                }
                case 1:
                    if (matrix_frame.values[0] == matrix_frame.values[3] &&
                        matrix_frame.values[0] == matrix_frame.values[6]) {
                        FIELD(self, u16 *, 0x62) |= 0x10;
                        {
                            s32 value = matrix_frame.values[0];
                            s32 offset = (s32)map[value] * 1000;
                            s32 delta =
                                (s32)FIELD(self, u16 *, 0x64) * offset;
                            FIELD(self, s32 *, 0x58) =
                                delta + FIELD(self, s32 *, 0x58);
                        }
                        if (matrix_frame.values[0] == 0) {
                            FIELD(self, u16 *, 0x62) |= 1;
                        }
                    }
                    if (matrix_frame.values[2] != matrix_frame.values[5] ||
                        matrix_frame.values[2] != matrix_frame.values[8]) {
                        break;
                    }
                    FIELD(self, u16 *, 0x62) |= 8;
                    {
                        s32 value = matrix_frame.values[8];
                        s32 offset = (s32)map[value] * 1000;
                        s32 delta =
                            (s32)FIELD(self, u16 *, 0x64) * offset;
                        FIELD(self, s32 *, 0x58) =
                                delta + FIELD(self, s32 *, 0x58);
                    }
                    if (matrix_frame.values[8] == 0) {
                        FIELD(self, u16 *, 0x62) |= 1;
                    }
                    break;
                case 2:
                    if (matrix_frame.values[0] == matrix_frame.values[4] &&
                        matrix_frame.values[8] == matrix_frame.values[0]) {
                        FIELD(self, u16 *, 0x62) |= 0x40;
                        {
                            s32 value = matrix_frame.values[4];
                            s32 offset = (s32)map[value] * 1000;
                            s32 delta =
                                (s32)FIELD(self, u16 *, 0x64) * offset;
                            FIELD(self, s32 *, 0x58) =
                                delta + FIELD(self, s32 *, 0x58);
                        }
                        if (matrix_frame.values[4] == 0) {
                            FIELD(self, u16 *, 0x62) |= 1;
                        }
                    }
                    if (matrix_frame.values[2] != matrix_frame.values[4] ||
                        matrix_frame.values[6] != matrix_frame.values[2]) {
                        break;
                    }
                    FIELD(self, u16 *, 0x62) |= 0x20;
                    {
                        s32 value = matrix_frame.values[4];
                        s32 offset = (s32)map[value] * 1000;
                        s32 delta =
                            (s32)FIELD(self, u16 *, 0x64) * offset;
                        FIELD(self, s32 *, 0x58) =
                            delta + FIELD(self, s32 *, 0x58);
                    }
                    if (matrix_frame.values[4] == 0) {
                        FIELD(self, u16 *, 0x62) |= 1;
                    }
                    break;
                }
                    j++;
                } while (j < FIELD(self, u16 *, 0x64));
            }
        }
    }

state_6:
    if (FIELD(self, s32 *, 0x58) == 0) {
        FIELD(self, u16 *, 0x5E) = 10;
        FIELD(self, u16 *, 0x64) = 0;
        FIELD(self, s16 *, 0x5C) = 3;
        goto done;
    }

    if (FIELD(self, u16 *, 0x62) & 1) {
        obj = (u8 *)func_800373DC(0x100);
        if (obj != 0) {
            FIELD(obj, u8 **, 0x10) = D_8052DC78;
        }
    }

    {
        s32 amount = FIELD(self, s32 *, 0x58);
        s32 quotient10 = (j = amount / 1000) / 10;
        s32 hundreds = quotient10 / 10;
        s32 ones = j - quotient10 * 10;
        s32 tens = quotient10;
        s32 ext = (tens -= hundreds * 10, ones << 16);
        s16 narrow_tens = (inner = ext >> 16, (s16)tens);
        s32 signed_tens = narrow_tens;
        s32 signed_hundreds;
        s32 hundreds_ext;
        s16 *decimal_base = D_80530590;
        inner += signed_tens;
        hundreds = hundreds % 10;
        hundreds_ext = hundreds << 16;
        amount = hundreds_ext >> 16;
        signed_hundreds = amount;
        inner += signed_hundreds;

    decimal_base[0] = ones;
    DIGIT1 = narrow_tens;
    DIGIT2 = hundreds;
        ext = (inner < 10);
        if (ext) {
            if (signed_hundreds > 0) {
                s32 dec2 = hundreds - 1;
                inner += 9;
                DIGIT2 = dec2;
                DIGIT1 = narrow_tens + 10;
                goto label_D164;
            }
            if (narrow_tens > 0) {
                inner += 9;
                DIGIT1 = narrow_tens - 1;
                decimal_base[0] = ones + 10;
            }
        }
label_D164:
        FIELD(self, u16 *, 0x5E) = 0;
        FIELD(self, s16 *, 0x5C) = 7;
        goto done;
    }

state_7:
    {
        FIELD(self, u16 *, 0x5E)++;
        if ((s16)FIELD(self, u16 *, 0x5E) == 9) {
            func_802441A4(input);
        }
        if (FIELD(self, u16 *, 0x5E) & 3) {
            goto done;
        }
    }

    digit_base = (s16 *)D_80530590;
    {
        s32 digit2 = DIGIT2;
    if ((s32)digit_base[0] + DIGIT1 + digit2 == 0) {
        if (!(FIELD(self, u16 *, 0x62) & 2)) {
            void *effect = D_80530598[0];
            FIELD(self, u16 *, 0x64) = 0;
            func_80232A08(effect);
            FIELD(self, u16 *, 0x5E) = 10;
            FIELD(self, s16 *, 0x5C) = 3;
        }
        FIELD(self, u16 *, 0x62) &= 0xFFFD;
        goto done;
    }
    }

    {
        u8 *state_data;
        u8 *object_data;
        s32 color;
        s32 half;

        obj = (u8 *)func_800373DC(0x136);

        if (obj == 0) {
            goto done;
        }
        FIELD(obj, u8 **, 0x10) = D_8052D770;
        FIELD(FIELD(obj, u8 **, 8), s32 *, 0) =
            FIELD(arg1_bytes, s32 *, 0) + (s32)0xFEC00000;
        FIELD(FIELD(obj, u8 **, 8), s32 *, 4) =
            FIELD(arg1_bytes, s32 *, 4) + (s32)0xFFC00000;
        FIELD(FIELD(obj, u8 **, 8), s32 *, 8) =
            FIELD(arg1_bytes, s32 *, 8) + (s32)0xFFC00000;
        state_data = FIELD(obj, u8 **, 8);
        FIELD(state_data, s32 *, 0x10) = 0;
        FIELD(state_data, s32 *, 0xC) = 0;
        FIELD(FIELD(obj, u8 **, 8), s32 *, 0x14) = 0x40000;
        func_8003BC18(obj, D_8003C558);
        object_data = FIELD(obj, u8 **, 0xC);
        FIELD(object_data, u16 *, 0x1E) = 0x1000;
        FIELD(object_data, u16 *, 0x1C) = 0x1000;
        arg1_bytes = obj + 0x20;

        if (DIGIT2 != 0) {
            DIGIT2--;
            FIELD(obj, s16 *, 0x74) = 2;
            goto label_D338;
        }
        if (DIGIT1 != 0) {
            DIGIT1--;
            FIELD(obj, s16 *, 0x74) = 1;
            half = FIELD(object_data, u16 *, 0x12) - 5;
            goto label_D334;
        }
        if (DIGIT0 != 0) {
            DIGIT0--;
            FIELD(obj, s16 *, 0x74) = 0;
            half = FIELD(object_data, u16 *, 0x12) + 5;
label_D334:
            FIELD(object_data, u16 *, 0x12) = half;
        }

label_D338:
        color = 0x00808080;
        FIELD(object_data, void **, 0) = (void *)D_80077C64;
        FIELD(object_data, s32 *, 8) = D_80077C68[0];
        FIELD(object_data, u8 *, 4) = 0;
        FIELD(object_data, u8 *, 5) = 0;
        FIELD(object_data, s32 *, 0xC) = color;
        FIELD(arg1_bytes, void **, 0) = self;
        FIELD(arg1_bytes, void **, 0x50) = common_value;
        func_8023FA58(arg1_bytes + 8, FIELD(obj, void **, 8), D_8053016C);
    }

done:
    return;
}
