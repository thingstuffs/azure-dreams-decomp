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

/* Returns the signed byte scaled by ten times the mask, or unchanged if the mask is zero. */
s32 func_800438E4(Struct800438E4 *record) {
    s32 mask = record->unk3 & 0x1F;
    s32 value = record->unk2;

    if (mask != 0) {
        value = value * (10 * mask);
    }
    return value;
}
