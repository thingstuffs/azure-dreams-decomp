/* v06: v04 + case-16's two `return 0` exits are merged into ONE join point
   (`if (page_b1[0x33E6] == value_b) { ... } return 0;`).  The join CODE_LABEL
   then carries TWO incoming edges, so jump.c's "x = a; if (...) goto l; x = b;"
   hoist (jump.c:926-1017) decrements LABEL_NUSES 2 -> 1 instead of 0 and the
   label survives (jump.c:1014).  next_nonnote_insn(condjump) is therefore a
   CODE_LABEL, not an INSN, so the emit_store_flag fold (jump.c:1181) never
   applies -- while the hoist itself still supplies retail's `li v0,1` ahead of
   an inverted `bne` to the epilogue.  BYTE-EXACT. */
/* v04: v03 + case-1 `first`/`second` are u32 locals declared ahead of `i` -- the loop-resident li 48 lengthens `first`'s live range, tying its allocno priority with `i`'s, and allocno_compare breaks that tie by pseudo number. */
/* v03: v02 + dial (c) two-set `k` keeps the 0x30 constant inside the case-1 loop (loop.c move_movables needs n_times_set==1) + dial (b) case-16 tail falls through to the switch's shared `return 0`. */
/* v02: dial (a) -- case 4/8 and case 16 each get their OWN single-set block-scoped D_800D2644 base pointer AND masked-index local (was one function-scope `records`/`arg` pair set in every arm). */
#include "common.h"

typedef struct S_800B83DC_0 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
    u8 unk_33A5;
} S_800B83DC_0;   /* pair_a in func_800B83DC */

typedef struct S_800B83DC_1 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
    u8 unk_33A5;
} S_800B83DC_1;   /* pair_c in func_800B83DC */



typedef struct {
    u8 pad0[3];
    u8 kind;
    u8 byte4;
    u8 byte5;
    u8 byte6;
    u8 pad7;
    s16 field8;
    u8 padA[22];
} Record;

extern s32 func_80033B2C(s32);
extern Record D_800D2644[];
extern u8 D_800D2EA4[];

s32 func_800B83DC(s32 arg0) {
    s32 input;
    Record *record;
    s32 result;
    u32 first;
    u32 second;
    s32 i;
    s32 arg;
    u8 value_a;
    s32 index_c;
    u8 *pair_a;
    u8 *pair_c;
    u8 *entry;
    Record *case_record;
    Record *case_base;
    u8 *page_a;
    u8 value_b;

    input = arg0;
    {
        Record *base = D_800D2644;
        record = base + (input & 0xFF);
    }
    result = 0;
    if (func_80033B2C(record->field8) == 0) return 0;
    switch (record->kind) {
    case 4:
    case 8: {
        Record *base_a = D_800D2644;
        s32 arg_a = input & 0xFF;
        value_a = base_a[arg_a].byte6;
        if (value_a == 0) return 0;
        i = 0;
        page_a = (u8 *)0x80010000;
        do {
            pair_a = (u8 *)((u8)i * 2 + (u32)page_a);
            if (((S_800B83DC_0 *)pair_a)->unk_33A4 == value_a &&
                ((S_800B83DC_0 *)pair_a)->unk_33A5 != arg_a) return 1;
            i++;
        } while ((u8)i < 0x21);
        return 0;
    }
    case 16: {
        u8 *page_b1;
        u8 *page_b2;
        Record *base_b = D_800D2644;
        s32 arg_b = input & 0xFF;
        value_b = base_b[arg_b].byte6;
        if (value_b == 0) return 0;
        page_b1 = (u8 *)0x80010000;
        if (page_b1[0x33E6] == value_b) {
            page_b2 = page_b1;
            if (page_b2[0x33E7] != arg_b) return 1;
        }
        return 0;
    }
    case 1: {
        u8 *entries;
        u8 *page_c;
        s32 k = 0;
        i = 0;
        page_c = (u8 *)0x80010000;
        entries = &D_800D2EA4[0];
        arg = input & 0xFF;
        case_base = D_800D2644;
        case_record = case_base + arg;
        do {
            index_c = i & 0xFF;
            pair_c = (u8 *)(index_c * 2 + (u32)page_c);
            first = ((S_800B83DC_1 *)pair_c)->unk_33A4;
            if (first == arg) return 0;
            second = ((S_800B83DC_1 *)pair_c)->unk_33A5;
            if (second == arg) return 0;
            entry = (u8 *)(index_c * 8 + (u32)entries);
            if (entry[2] == case_record->byte4 &&
                entry[3] == case_record->byte5 &&
                first >= 0x2D) {
                k = 0x30;
                if (first != k && second == 0) result = 1;
            }
            i++;
        } while ((u8)i < 0x21);
        return result;
    }
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    default:
        break;
    }
    return 0;
}
