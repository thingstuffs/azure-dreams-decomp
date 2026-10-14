#include "ovmovie_libpress.h"
/* Distinct SDK table objects preserve their independent C addresses. */
static u32 ovm_press_iq[33] = { 0x40000001, 0x13101002, 0x16161310, 0x16161616, 0x1B1A181A, 0x1A1A1B1B, 0x1B1B1A1A, 0x1D1D1D1B, 0x1D222222, 0x1B1B1D1D, 0x20201D1D, 0x26252222, 0x22232325, 0x28262623, 0x30302828, 0x38382E2E, 0x5345453A, 0x13101002, 0x16161310, 0x16161616, 0x1B1A181A, 0x1A1A1B1B, 0x1B1B1A1A, 0x1D1D1D1B, 0x1D222222, 0x1B1B1D1D, 0x20201D1D, 0x26252222, 0x22232325, 0x28262623, 0x30302828, 0x38382E2E, 0x5345453A };
static u32 ovm_press_coefficient[33] = { 0x60000000, 0x5A825A82, 0x5A825A82, 0x5A825A82, 0x5A825A82, 0x6A6D7D8A, 0x18F8471C, 0xB8E3E707, 0x82759592, 0x30FB7641, 0x89BECF04, 0xCF0489BE, 0x764130FB, 0xE7076A6D, 0xB8E38275, 0x7D8A471C, 0x959218F8, 0xA57D5A82, 0x5A82A57D, 0xA57D5A82, 0x5A82A57D, 0x8275471C, 0x6A6D18F8, 0xE7079592, 0xB8E37D8A, 0x89BE30FB, 0xCF047641, 0x7641CF04, 0x30FB89BE, 0xB8E318F8, 0x82756A6D, 0x95927D8A, 0xE707471C };
struct OvmPressIdentification { u32 signature; u32 release; };
static struct OvmPressIdentification ovm_press_identification = { 0x150E7350, 0x0040AE9C };
static s32 *D_8017834C = (s32 *)0x1F801080;
static s32 *D_80178350 = (s32 *)0x1F801084;
static s32 *D_80178354 = (s32 *)0x1F801088;
static s32 *D_80178358 = (s32 *)0x1F801090;
static s32 *D_8017835C = (s32 *)0x1F801094;
static s32 *D_80178360 = (s32 *)0x1F801098;
static s32 *D_80178364 = (s32 *)0x1F8010A0;
static s32 *D_80178368 = (s32 *)0x1F8010A4;
static s32 *D_8017836C = (s32 *)0x1F8010A8;
static s32 *D_80178370 = (s32 *)0x1F8010B0;
static s32 *D_80178374 = (s32 *)0x1F8010B4;
static s32 *D_80178378 = (s32 *)0x1F8010B8;
static s32 *D_8017837C = (s32 *)0x1F801820;
static u32 *D_80178380 = (u32 *)0x1F801824;
static s32 *D_80178384 = (s32 *)0x1F8010F0;
static const char ovm_press_option[] = "MDEC_rest:bad option(%d)\n";
static const char ovm_press_input[] = "MDEC_in_sync";
static const char ovm_press_output[] = "MDEC_out_sync";
static const char ovm_press_dma[] = "\t DMA=(%d,%d), ADDR=(0x%08x->0x%08x)\n";
static const char ovm_press_fifo[] = "\t FIFO=(%d,%d),BUSY=%d,DREQ=(%d,%d),RGB24=%d,STP=%d\n";
static const char ovm_press_timeout[] = "%s timeout:\n";
#define D_8017823C (*(u8 *)&ovm_press_iq[0])
#define D_80178240 ((u8 *)&ovm_press_iq[1])
#define D_80178280 ((u8 *)&ovm_press_iq[17])
#define D_801782C0 (*(u8 *)&ovm_press_coefficient[0])
#define D_801782C4 (*(u8 *)&ovm_press_coefficient[1])
#define D_80176800 ovm_press_option[0]
#define D_8017681C ovm_press_input[0]
#define D_8017682C ovm_press_output[0]
#define D_8017683C ovm_press_dma[0]
#define D_80176864 ovm_press_fifo[0]
#define D_8017689C ovm_press_timeout[0]
