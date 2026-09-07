#include "common.h"

/* D_80080B54: >8-byte global accessed via %hi/%lo (siblings initSubRecordPair /
 * func_8004CD28 pass &D_80080B54 as a pointer arg, so the real struct is
 * larger than what this function touches). This function only reads the
 * first 4 bytes as a packed CVECTOR-style color word (r,g,b,cd). */
typedef struct S_80080B54 {
    s32 color; /* offset 0x0: packed r,g,b,cd read/written as one word */
    u8 pad[8]; /* real struct is bigger; not accessed here */
} S_80080B54;

extern S_80080B54 D_80080B54;

/* Local (non-global) color struct pointed to by Struct800497F4.unk4. */
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} Color800497F4;

typedef struct {
    s32 unk0;         /* flag/counter; function is a no-op when 0 */
    Color800497F4 *unk4; /* pointer to the object's color */
} Struct800497F4;

/* Fades an object's color toward neutral gray (0x808080) by -0x10 per call
 * on each of r/g/b; once neutral, either resets the color to the template
 * D_80080B54 or (if a1 is set) clears unk0 to stop further fading. */
void fadeColorToGray(Struct800497F4 *a0, s32 a1)
{
    Color800497F4 *v1;

    if (a0->unk0 == 0) {
        return;
    }

    v1 = a0->unk4;
    if ((*(u32 *)v1 << 8) != 0x80808000) {
        a0->unk4->r -= 0x10;
        a0->unk4->g -= 0x10;
        a0->unk4->b -= 0x10;

        if ((*(u32 *)a0->unk4 << 8) == 0x80808000) {
            *(u32 *)a0->unk4 = D_80080B54.color;
        }
        return;
    }

    if (a1 != 0) {
        a0->unk0 = 0;
    }
}
