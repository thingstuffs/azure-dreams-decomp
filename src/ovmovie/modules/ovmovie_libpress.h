#ifndef OVMOVIE_LIBPRESS_H
#define OVMOVIE_LIBPRESS_H
#include "common.h"
#include "m2c_compat.h"
extern u8 D_8017823C;
extern u8 D_80178240[];
extern u8 D_80178280[];
extern u8 D_801782C0;
extern u8 D_801782C4;
extern u8 D_80180000[];
extern s32 D_80176800;
extern s32 D_8017681C;
extern s32 D_8017682C;
extern u32 D_8017683C;
extern u32 D_80176864;
extern u32 D_8017689C;
static s32 *D_8017834C;
static s32 *D_80178350;
static s32 *D_80178354;
static s32 *D_80178358;
static s32 *D_8017835C;
static s32 *D_80178360;
static s32 *D_8017837C;
static u32 *D_80178380;
static s32 *D_80178384;
extern s32 func_8005FFFC(void);
extern s32 func_8006005C(s32, void (*)(void));
extern s32 printf();
void set_movie_decode_mode(s32);
s32 *copy_decoder_tables_to_buffer(s8 *);
s8 *copy_decoder_blocks_to_globals(s8 *);
s32 func_80177838(u16 *);
void configure_decoder_command_flags(s32 *, s32);
void request_decoder_output_dma(s32, u32);
s32 read_decoder_input_dma_status(s32);
s32 read_decoder_output_dma_status(s32);
s32 register_mode_zero_callback(void (*)(void));
s32 register_mode_one_callback(void (*)(void));
static void reset_decoder_and_load_tables(s32);
static void start_decoder_input_dma(s32 *, u32);
static void start_decoder_output_dma(s32, u32);
static s32 wait_for_decoder_input_dma(void);
static s32 wait_for_decoder_output_dma(void);
static u32 read_decoder_status_register(void);
static s32 report_decoder_error_and_reset(const char *);
#endif
