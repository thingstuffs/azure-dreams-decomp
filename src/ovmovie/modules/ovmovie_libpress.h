#ifndef OVMOVIE_LIBPRESS_H
#define OVMOVIE_LIBPRESS_H
#include "common.h"
#include "m2c_compat.h"
extern u8 movie_iq_table_header;
extern u8 movie_iq_luma_bytes[];
extern u8 movie_iq_chroma_bytes[];
extern u8 movie_coefficient_table_header;
extern u8 movie_coefficient_table_bytes;
extern u8 D_80180000[];
extern s32 movie_decoder_option_format;
extern s32 movie_decoder_input_sync_label;
extern s32 movie_decoder_output_sync_label;
extern u32 movie_decoder_dma_format;
extern u32 movie_decoder_fifo_format;
extern u32 movie_decoder_timeout_format;
static s32 *movie_mdec_input_dma_address;
static s32 *movie_mdec_input_dma_blocks;
static s32 *movie_mdec_input_dma_control;
static s32 *movie_mdec_output_dma_address;
static s32 *movie_mdec_output_dma_blocks;
static s32 *movie_mdec_output_dma_control;
static s32 *movie_mdec_data_register;
static u32 *movie_mdec_status_register;
static s32 *movie_dma_priority_register;
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
