#include "common.h"

/* --- gcc 2.7.2-cdk (cygnus SN32.3.7.0004) translation unit: zero-frame shared-tail
   epilogue that the -psx builds don't reproduce. See tools/compiler_notes.md. --- */

extern unsigned short D_80084778[5];

/* Appends a0 to the D_80084778[0]-counted array (cap 0x20); returns 0, or -1 if full.
   The volatile read forces a reload of the count for the index (defeats CSE). */
short func_80055778(int a0)
{
    unsigned short count = D_80084778[0];
    if (count >= 0x20) return -1;
    D_80084778[0] = count + 1;
    D_80084778[*(volatile unsigned short *)D_80084778] = a0;
    return 0;
}


/* shared D_80084960 table (0x9C stride) */
typedef struct {
    int unk00; int unk04; char pad08[4]; int unk0C;
    char pad10[0xC]; int unk1C; char pad20[0x9C-0x20];
} Entry80084960;
extern Entry80084960 D_80084960[];

/* Clamp a 16-bit signed value to the range [0, 0x7F]. */
s32 func_80055750(s16 arg0) {
    if (arg0 < 0) {
        return 0;
    }
    if (arg0 >= 0x80) {
        return 0x7F;
    }
    return arg0;
}

typedef struct {
    u8 pad00[0x11];
    u8 unk11;
} Struct1;

extern s32 D_800835E8[];

/* Look up a signed table value indexed by (unsigned byte field + signed 16-bit arg), scaled by 4 */
s32 func_8004383C(Struct1 *arg0, s16 arg1) {
    return D_800835E8[arg0->unk11 + arg1];
}

/* Chained byte->word table lookup: return D_8007361C[ D_800712AC[a0] ];
 * a0 is used directly as a byte offset into D_800712AC (no additional scaling). */
extern u8 D_800712AC[16];
extern s32 D_8007361C[256];

s32 func_800498EC(s32 a0) {
    return D_8007361C[D_800712AC[a0]];
}

extern u8 D_800712B0[256];
extern s32 D_8007361C[256];

/* Two-level table lookup: use arg0 as a byte index into D_800712B0 to obtain
 * a secondary index, then use that to index the 4-byte-wide table
 * D_8007361C and return the resulting word. */
s32 func_80049918(s32 arg0) {
    return D_8007361C[D_800712B0[arg0]];
}

/* extern decls */
extern void *D_8006ADC0[4];
extern int D_800812D0[4];
extern void func_80053C6C(void);

/* Stores the address of D_800812D0 into the list-tail slot D_8006ADC0[0],
 * then invokes the list-processing routine func_80053C6C (no args). */
void func_80053CD0(void)
{
    D_8006ADC0[0] = (void *)D_800812D0;
    func_80053C6C();
}

/* size >8B to force %hi/%lo (not gp_rel) codegen for all three globals */
extern u32 D_80081478[3];
extern void *D_80083160[3];
extern u8 D_801C9E40[16];

/* Pick one of two pointer-table entries depending on whether the current-state
 * pointer D_80083160 still points at the default sentinel D_801C9E40, then
 * return whether that value is < a0 (unsigned compare). */
s32 func_80045310(u32 a0)
{
    u32 *v0 = &D_80081478[0];
    u32 *v1 = v0;

    if (D_80083160[0] != (void *)D_801C9E40) {
        v1 = v0 + 1;
    }
    return *v1 < a0;
}

/* Stores a value into the 32-bit field at offset 0 of the a0-th element
 * of the D_80084960 struct array (element size 0x9C = 156 bytes). */
typedef struct {
    /* 0x00 */ int unk00;
    unsigned char pad[0x98];
} Struct_80084960; /* size 0x9C (156) */

void func_8005845C(unsigned char a0, unsigned char a1) {
    D_80084960[a0].unk00 = a1;
}

/* Wrapper: reorders (count, array) into the (array, count, elemsize, comparator)
 * calling convention expected by func_8004AFC8 (a qsort-style sort routine),
 * passing func_8004AA34 (an int-difference comparator) as the callback. */

extern int func_8004AA34(int *a0, int *a1);
extern void func_8004AFC8(void *base, int count, int size, int (*compar)(int *, int *));

void func_8004AA44(int count, void *base)
{
    func_8004AFC8(base, count, 4, func_8004AA34);
}

/* Element of the D_80084960 stat/entity table (stride 0x9C bytes). This
 * accessor returns the field at offset 0xC for entry a1 (a0/a2 unused,
 * matching the sibling getter/setter family at 0x8005C858-0x8005C94C). */
int func_8005C858(int a0, short a1, int a2)
{
    return D_80084960[a1].unk0C;
}
