#include "common.h"

/* --- gcc 2.7.2-cdk (cygnus SN32.3.7.0004) translation unit: zero-frame shared-tail
   epilogue that the -psx builds don't reproduce. See tools/compiler_notes.md. --- */

extern unsigned short D_80084778[5];

/* Append a value to the counted array; return -1 if its 32 slots are full, otherwise 0. */
short func_80055778(int value)
{
    unsigned short count = D_80084778[0];
    if (count >= 0x20) return -1;
    D_80084778[0] = count + 1;
    D_80084778[*(volatile unsigned short *)D_80084778] = value;
    return 0;
}


/* shared D_80084960 table (0x9C stride) */
typedef struct {
    int unk00; int unk04; char pad08[4]; int unk0C;
    char pad10[0xC]; int unk1C; char pad20[0x9C-0x20];
} Entry80084960;
extern Entry80084960 D_80084960[];

/* Clamp a 16-bit signed value to the range [0, 0x7F]. */
s32 func_80055750(s16 value) {
    if (value < 0) {
        return 0;
    }
    if (value >= 0x80) {
        return 0x7F;
    }
    return value;
}

typedef struct {
    u8 pad00[0x11];
    u8 unk11;
} Struct1;

extern s32 D_800835E8[];

/* Look up a signed table value using the entry byte field plus an index offset. */
s32 func_8004383C(Struct1 *entry, s16 index_offset) {
    return D_800835E8[entry->unk11 + index_offset];
}

extern u8 D_800712AC[16];
extern s32 D_8007361C[256];

/* Look up a word through the byte index table D_800712AC. */
s32 func_800498EC(s32 index) {
    return D_8007361C[D_800712AC[index]];
}

extern u8 D_800712B0[256];
extern s32 D_8007361C[256];

/* Look up a word through the byte index table D_800712B0. */
s32 func_80049918(s32 index) {
    return D_8007361C[D_800712B0[index]];
}

/* extern decls */
extern void *D_8006ADC0[4];
extern int D_800812D0[4];
extern void func_80053C6C(void);

/* Set the list tail to D_800812D0 and process the list. */
void func_80053CD0(void)
{
    D_8006ADC0[0] = (void *)D_800812D0;
    func_80053C6C();
}

/* size >8B to force %hi/%lo (not gp_rel) codegen for all three globals */
extern u32 D_80081478[3];
extern void *D_80083160[3];
extern u8 D_801C9E40[16];

/* Return whether the state-selected table value is below the unsigned limit. */
s32 func_80045310(u32 limit)
{
    u32 *values = &D_80081478[0];
    u32 *selected_value = values;

    if (D_80083160[0] != (void *)D_801C9E40) {
        selected_value = values + 1;
    }
    return *selected_value < limit;
}

typedef struct {
    /* 0x00 */ int unk00;
    unsigned char pad[0x98];
} Struct_80084960; /* size 0x9C (156) */

/* Store a byte value in the selected entry's first word. */
void func_8005845C(unsigned char entry_index, unsigned char value) {
    D_80084960[entry_index].unk00 = value;
}

extern int func_8004AA34(int *a0, int *a1);
extern void func_8004AFC8(void *base, int count, int size, int (*compar)(int *, int *));

/* Sort the array of four-byte elements using func_8004AA34. */
void func_8004AA44(int count, void *base)
{
    func_8004AFC8(base, count, 4, func_8004AA34);
}

/* Return the word at offset 0xC in the selected table entry. */
int func_8005C858(int unused_0, short entry_index, int unused_2)
{
    return D_80084960[entry_index].unk0C;
}
