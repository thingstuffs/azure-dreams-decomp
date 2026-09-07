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

/* Read two u16 entries from the table pointed to by D_80079958.ptr:
 * the low byte of table[a1] shifted into bits 16-23, ORed with the
 * zero-extended table[a0] in the low 16 bits. `volatile` on the table
 * pointer's pointee stops gcc from folding the "& 0xFF" mask into a
 * narrower `lbu` load (retail keeps the full `lhu` + `andi`). */
s32 func_8005E7B0(s32 a0, s32 a1)
{
    volatile u16 *table = (volatile u16 *)D_80079958.ptr;
    return ((table[a1] & 0xFF) << 16) | table[a0];
}
