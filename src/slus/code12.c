/* gcc 2.7.2 -O2 — own TU (func_800438E4: caller-signature conflict) */
typedef unsigned char u8;
typedef signed char s8;
typedef int s32;

typedef struct {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 unk3;
} Struct800438E4;

/*
 * Reads a signed "field2" byte (offset 2) and a 5-bit mask from the low bits
 * of the byte at offset 3. If the mask is zero, returns field2 unchanged;
 * otherwise returns field2 scaled by 10*mask.
 */
s32 func_800438E4(Struct800438E4 *a0) {
    s32 mask = a0->unk3 & 0x1F;
    s32 field2 = a0->unk2;

    if (mask != 0) {
        field2 = field2 * (10 * mask);
    }
    return field2;
}
