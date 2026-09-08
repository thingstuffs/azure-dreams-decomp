#include "common.h"

extern u8 D_800160B8[9];
extern u8 D_80016E3C[9];
extern void func_8001670C(void *, void *, void *, void *);

/*
 * The retail symbol starts with a 0x4B4-byte data bank.  The executable body
 * follows it at 0x806D2858.  Keep the bank out of non-MIPS ports, where the
 * public symbol is the ordinary C function below.
 */
#ifdef __mips__
static const u32 data_bank[301] __asm__("func_806D23A4")
    __attribute__((section(".text.func_806D23A4"), aligned(4))) = {
    [0] = 0x08a908a8,
    [4] = 0x0000000b,
    [5] = 0x8001746c,
    [6] = 0x800160f8,
    [7] = 0x800160c0,
    [8] = 0x80017724,
    [10] = 0x1d800000,
    [14] = 0x800176ac,
    [17] = 0x1d800000,
    [19] = 0x80017434,
    [20] = 0x800176b0,
    [21] = 0x800173bc,
    [22] = 0x800173ac,
    [23] = 0x000108aa,
    [31] = 0x001d000b,
    [32] = 0x03200180,
    [33] = 0x80017478,
    [35] = 0x00000001,
    [37] = 0x000018d4,
    [38] = 0x00008000,
    [44] = 0x00000001,
    [45] = 0x00008000,
    [50] = 0x00000101,
    [51] = 0x000003ea,
    [53] = 0x09816000,
    [54] = 0x0000115c,
    [58] = 0x00008c42,
    [193] = 0x00000007,
    [194] = 0x00014000,
    [195] = 0x00000001,
    [196] = 0x80017420,
    [197] = 0x00000050,
    [198] = 0x024001e0,
    [199] = 0x00014000,
    [200] = 0x0000ff00,
    [202] = 0x000000a4,
    [203] = 0x01600260,
    [204] = 0x00014000,
    [205] = 0x0000ff00,
    [207] = 0x00000053,
    [208] = 0x00600360,
    [209] = 0x00014000,
    [210] = 0x0000ff00,
    [212] = 0x00000055,
    [213] = 0x006001e0,
    [214] = 0x00014000,
    [215] = 0x0000ff00,
    [217] = 0x0000005a,
    [218] = 0x00600220,
    [219] = 0x00008000,
    [224] = 0x00008000,
    [229] = 0x00008000,
    [280] = 0x4c070707,
    [281] = 0x80016c34,
    [282] = 0x00000001,
    [283] = 0x4c070707,
    [284] = 0x80016bd4,
    [285] = 0x00010f48,
    [286] = 0x3078765c,
    [287] = 0x645c3533,
    [288] = 0x5c617461,
    [289] = 0x6e776f74,
    [290] = 0x3462735c,
    [291] = 0x30307333,
    [292] = 0x69622e30,
    [293] = 0x0000006e,
    [294] = 0x3078765c,
    [295] = 0x645c3533,
    [296] = 0x5c617461,
    [297] = 0x6e776f74,
    [298] = 0x3062735c,
    [299] = 0x69622e36,
    [300] = 0x0000006e,
};
__asm__(".globl func_806D23A4\n"
        ".size func_806D23A4, 1260");
#define BODY_NAME func_806D2858
#else
#define BODY_NAME func_806D23A4
#endif

/* Apply the selected record from the fixed tables to the context. */
void BODY_NAME(void *context, s32 unused, void *selector)
{
    func_8001670C(D_800160B8, D_80016E3C, context, selector);
}
