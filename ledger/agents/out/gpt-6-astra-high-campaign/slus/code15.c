/* gcc 2.7.2 -O2 — own TU (func_8005E7B0: caller-extern + D_80079958 multi-view conflict) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct {
    u8 pad[0x1AA];
    u16 field_1AA;
} TargetStruct;

typedef struct {
    TargetStruct *ptr;
    u32 pad2[2]; /* keep total size > 8 bytes so hi/lo addressing (not gp_rel) is used */
} D_80079958_t;

extern D_80079958_t D_80079958;

/* Packs one table entry into the low halfword and another entry's low byte into bits 16-23. */
s32 func_8005E7B0(s32 low_index, s32 high_index)
{
    volatile u16 *table = (volatile u16 *)D_80079958.ptr;
    return ((table[high_index] & 0xFF) << 16) | table[low_index];
}
