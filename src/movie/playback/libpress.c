/* Movie decoder table setup, DMA transfers, completion waits, callbacks and timeout recovery. */
#include "../../ovmovie/modules/ovmovie_libpress.h"
#include "../../ovmovie/modules/ovmovie_libpress.h"
/* Distinct SDK table objects preserve their independent C addresses. */
static u32 ovm_press_iq[33] = { 0x40000001, 0x13101002, 0x16161310, 0x16161616, 0x1B1A181A, 0x1A1A1B1B, 0x1B1B1A1A, 0x1D1D1D1B, 0x1D222222, 0x1B1B1D1D, 0x20201D1D, 0x26252222, 0x22232325, 0x28262623, 0x30302828, 0x38382E2E, 0x5345453A, 0x13101002, 0x16161310, 0x16161616, 0x1B1A181A, 0x1A1A1B1B, 0x1B1B1A1A, 0x1D1D1D1B, 0x1D222222, 0x1B1B1D1D, 0x20201D1D, 0x26252222, 0x22232325, 0x28262623, 0x30302828, 0x38382E2E, 0x5345453A };
static u32 ovm_press_coefficient[33] = { 0x60000000, 0x5A825A82, 0x5A825A82, 0x5A825A82, 0x5A825A82, 0x6A6D7D8A, 0x18F8471C, 0xB8E3E707, 0x82759592, 0x30FB7641, 0x89BECF04, 0xCF0489BE, 0x764130FB, 0xE7076A6D, 0xB8E38275, 0x7D8A471C, 0x959218F8, 0xA57D5A82, 0x5A82A57D, 0xA57D5A82, 0x5A82A57D, 0x8275471C, 0x6A6D18F8, 0xE7079592, 0xB8E37D8A, 0x89BE30FB, 0xCF047641, 0x7641CF04, 0x30FB89BE, 0xB8E318F8, 0x82756A6D, 0x95927D8A, 0xE707471C };
struct OvmPressIdentification { u32 signature; u32 release; };
static struct OvmPressIdentification ovm_press_identification = { 0x150E7350, 0x0040AE9C };
static s32 *movie_mdec_input_dma_address = (s32 *)0x1F801080;
static s32 *movie_mdec_input_dma_blocks = (s32 *)0x1F801084;
static s32 *movie_mdec_input_dma_control = (s32 *)0x1F801088;
static s32 *movie_mdec_output_dma_address = (s32 *)0x1F801090;
static s32 *movie_mdec_output_dma_blocks = (s32 *)0x1F801094;
static s32 *movie_mdec_output_dma_control = (s32 *)0x1F801098;
static s32 *movie_gpu_dma_address = (s32 *)0x1F8010A0;
static s32 *movie_gpu_dma_blocks = (s32 *)0x1F8010A4;
static s32 *movie_gpu_dma_control = (s32 *)0x1F8010A8;
static s32 *movie_cd_dma_address = (s32 *)0x1F8010B0;
static s32 *movie_cd_dma_blocks = (s32 *)0x1F8010B4;
static s32 *movie_cd_dma_control = (s32 *)0x1F8010B8;
static s32 *movie_mdec_data_register = (s32 *)0x1F801820;
static u32 *movie_mdec_status_register = (u32 *)0x1F801824;
static s32 *movie_dma_priority_register = (s32 *)0x1F8010F0;
static const char ovm_press_option[] = "MDEC_rest:bad option(%d)\n";
static const char ovm_press_input[] = "MDEC_in_sync";
static const char ovm_press_output[] = "MDEC_out_sync";
static const char ovm_press_dma[] = "\t DMA=(%d,%d), ADDR=(0x%08x->0x%08x)\n";
static const char ovm_press_fifo[] = "\t FIFO=(%d,%d),BUSY=%d,DREQ=(%d,%d),RGB24=%d,STP=%d\n";
static const char ovm_press_timeout[] = "%s timeout:\n";
#define movie_iq_table_header (*(u8 *)&ovm_press_iq[0])
#define movie_iq_luma_bytes ((u8 *)&ovm_press_iq[1])
#define movie_iq_chroma_bytes ((u8 *)&ovm_press_iq[17])
#define movie_coefficient_table_header (*(u8 *)&ovm_press_coefficient[0])
#define movie_coefficient_table_bytes (*(u8 *)&ovm_press_coefficient[1])
#define movie_decoder_option_format ovm_press_option[0]
#define movie_decoder_input_sync_label ovm_press_input[0]
#define movie_decoder_output_sync_label ovm_press_output[0]
#define movie_decoder_dma_format ovm_press_dma[0]
#define movie_decoder_fifo_format ovm_press_fifo[0]
#define movie_decoder_timeout_format ovm_press_timeout[0]
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Apply the requested mode, performing setup when it is zero. */
void set_movie_decode_mode(s32 mode) {
    if (mode == 0) {
        func_8005FFFC();
    }
    reset_decoder_and_load_tables(mode);
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


typedef struct S_80040F10_0 {
    s32 unk_00;
} S_80040F10_0;

typedef struct S_80040F10_1 {
    s32 unk_00;
} S_80040F10_1;

typedef struct S_80040F10_2 {
    s32 unk_00;
} S_80040F10_2;

typedef struct S_80040F10_3 {
    s32 unk_00;
} S_80040F10_3;

typedef struct S_80040F10_4 {
    s32 unk_00;
} S_80040F10_4;

typedef struct S_80040F10_5 {
    s32 unk_00;
} S_80040F10_5;

/* Copy three global data blocks into a contiguous 256-byte buffer. */
s32 *copy_decoder_tables_to_buffer(s8 *buffer) {
    s8 *first_src;
    s8 *second_src;
    s8 *third_src;
    s8 *first_dst;
    s8 *second_dst;
    s8 *third_dst;
    s32 first_word;
    s32 second_word;
    s32 third_word;
    s32 first_countdown;
    s32 second_countdown;
    s32 third_countdown;

    first_dst = buffer;
    first_src = movie_iq_luma_bytes;
    first_countdown = 0xF;
    do {
        first_word = ((S_80040F10_0 *)first_src)->unk_00;
        first_src += 4;
        first_countdown -= 1;
        ((S_80040F10_1 *)first_dst)->unk_00 = first_word;
        first_dst += 4;
    } while (first_countdown != -1);
    second_dst = buffer + 0x40;
    second_src = movie_iq_chroma_bytes;
    second_countdown = 0xF;
    do {
        second_word = ((S_80040F10_2 *)second_src)->unk_00;
        second_src += 4;
        second_countdown -= 1;
        ((S_80040F10_3 *)second_dst)->unk_00 = second_word;
        second_dst += 4;
    } while (second_countdown != -1);
    third_dst = buffer + 0x80;
    third_src = &movie_coefficient_table_bytes;
    third_countdown = 0x1F;
    do {
        third_word = ((S_80040F10_4 *)third_src)->unk_00;
        third_src += 4;
        third_countdown -= 1;
        ((S_80040F10_5 *)third_dst)->unk_00 = third_word;
        third_dst += 4;
    } while (third_countdown != -1);
    return buffer;
}
#include "../../ovmovie/modules/ovmovie_libpress.h"





typedef struct S_80040F9C_0 {
    s32 unk_00;
} S_80040F9C_0;   /* src in copy_decoder_blocks_to_globals */

typedef struct S_80040F9C_1 {
    s32 unk_00;
} S_80040F9C_1;   /* dst in copy_decoder_blocks_to_globals */

/* Copies two 64-byte blocks into global buffers and processes two global regions. */
s8 *copy_decoder_blocks_to_globals(s8 *data) {
    s8 *data_start;
    s8 *src;
    s8 *dst;
    s32 word;
    s32 word_index;

    data_start = data;
    src = data;
    dst = movie_iq_luma_bytes;
    word_index = 0xF;
    do {
        word = ((S_80040F9C_0 *)src)->unk_00;
        src += 4;
        word_index -= 1;
        ((S_80040F9C_1 *)dst)->unk_00 = word;
        dst += 4;
    } while (word_index != -1);

    dst = movie_iq_chroma_bytes;
    src = data_start + 0x40;
    word_index = 0xF;
    do {
        word = ((S_80040F9C_0 *)src)->unk_00;
        src += 4;
        word_index -= 1;
        ((S_80040F9C_1 *)dst)->unk_00 = word;
        dst += 4;
    } while (word_index != -1);

    start_decoder_input_dma((s32 *)&movie_iq_table_header, 0x20);
    start_decoder_input_dma((s32 *)&movie_coefficient_table_header, 0x20);
    return data_start;
}
#include "../../ovmovie/modules/ovmovie_libpress.h"

/* Returns the unsigned 16-bit value at the given pointer. */
s32 read_decoder_word_count(u16 *command) {
    return *command;
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Apply option flags to a command word and dispatch its update. */
void configure_decoder_command_flags(s32 *command, s32 flags)
{
    if (flags & 1) {
        *command &= ~0x08000000;
    } else {
        *command |= 0x08000000;
    }

    if (flags & 2) {
        *command |= 0x02000000;
    } else {
        *command &= ~0x02000000;
    }

    start_decoder_input_dma(command, *(u16 *)command);
}
#include "../../ovmovie/modules/ovmovie_libpress.h"
/* Calls start_decoder_output_dma with destination, words. */
void request_decoder_output_dma(s32 destination, u32 words) { start_decoder_output_dma(destination, words); }
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Read status bit 29, or refresh and hand back the refresher's status. */
s32 read_decoder_input_dma_status(s32 read_status_bit) {
    if (read_status_bit != 0) {
        return (read_decoder_status_register() >> 0x1D) & 1;
    }
    return wait_for_decoder_input_dma();
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Read status bit 24, or refresh and hand back the refresher's status. */
s32 read_decoder_output_dma_status(s32 read_status_bit) {
    if (read_status_bit != 0) {
        return (read_decoder_status_register() >> 0x18) & 1;
    }
    return wait_for_decoder_output_dma();
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Forwards the value to func_8006005C with a zero first argument. */
s32 register_mode_zero_callback(void (*callback)(void)) {
    return func_8006005C(0, callback);
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Passes 1 and the supplied value to func_8006005C. */
s32 register_mode_one_callback(void (*callback)(void)) {
    return func_8006005C(1, callback);
}
#include "../../ovmovie/modules/ovmovie_libpress.h"
/* Reset the decoder and optionally upload its quantization and coefficient tables. */
static void reset_decoder_and_load_tables(s32 mode) {
    switch (mode) {
    case 0:
        *(volatile u32 *)movie_mdec_status_register = 0x80000000;
        *(volatile u32 *)movie_mdec_input_dma_control = 0;
        *(volatile u32 *)movie_mdec_output_dma_control = 0;
        *(volatile u32 *)movie_mdec_status_register = 0x60000000;
        start_decoder_input_dma((s32 *)&movie_iq_table_header, 0x20);
        start_decoder_input_dma((s32 *)&movie_coefficient_table_header, 0x20);
        return;
    case 1:
        *(volatile u32 *)movie_mdec_status_register = 0x80000000;
        *(volatile u32 *)movie_mdec_input_dma_control = 0;
        *(volatile u32 *)movie_mdec_output_dma_control = 0;
        (void)*(volatile s32 *)movie_mdec_output_dma_control;
        *(volatile u32 *)movie_mdec_status_register = 0x60000000;
        return;
    default:
        printf(&movie_decoder_option_format, mode);
        return;
    }
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Writes the command word and starts a transfer of the remaining input data. */
static void start_decoder_input_dma(s32 *input_data, u32 word_count) {
    wait_for_decoder_input_dma();
    *movie_dma_priority_register |= 0x88;
    *movie_mdec_input_dma_address = input_data + 1;
    *movie_mdec_input_dma_blocks = ((word_count >> 5) << 0x10) | 0x20;
    *movie_mdec_data_register = *input_data;
    *movie_mdec_input_dma_control = 0x01000201;
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Starts a DMA transfer to memory in 32-word blocks. */
static void start_decoder_output_dma(s32 dest_addr, u32 word_count) {
    wait_for_decoder_output_dma();
    *movie_dma_priority_register |= 0x88;
    *movie_mdec_output_dma_control = 0;
    *movie_mdec_output_dma_address = dest_addr;
    *movie_mdec_output_dma_blocks = ((word_count >> 5) << 0x10) | 0x20;
    *movie_mdec_output_dma_control = 0x01000200;
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Waits for decoder status bit 0x20000000 to clear; reports and resets the decoder on timeout. */
static s32 wait_for_decoder_input_dma(void) {
    volatile s32 polls_left = 0x100000;
    if (*movie_mdec_status_register & 0x20000000) {
        do {
            if (--polls_left == -1) {
                report_decoder_error_and_reset((const char *)&movie_decoder_input_sync_label);
                return -1;
            }
        } while (*movie_mdec_status_register & 0x20000000);
    }
    return 0;
}
#include "../../ovmovie/modules/ovmovie_libpress.h"
/* Wait for output DMA completion, resetting the decoder on timeout. */
static s32 wait_for_decoder_output_dma(void) {
    volatile s32 polls_left = 0x100000;
    if (*movie_mdec_output_dma_control & 0x01000000) {
        do {
            if (--polls_left == -1) {
                report_decoder_error_and_reset((const char *)&movie_decoder_output_sync_label);
                return -1;
            }
        } while (*movie_mdec_output_dma_control & 0x01000000);
    }
    return 0;
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Reads the MDEC status word through movie_mdec_status_register. */
static u32 read_decoder_status_register(void) {
    return *(s32 *)movie_mdec_status_register;
}
#include "../../ovmovie/modules/ovmovie_libpress.h"


/* Prints decoder diagnostics and resets the decoder and its DMA channels. */
static s32 report_decoder_error_and_reset(const char *diagnostic_value) {
    u32 decoder_status;
    u32 input_dma_busy;
    u32 output_dma_busy;
    s32 result;

    printf(&movie_decoder_timeout_format, diagnostic_value);
    decoder_status = *(volatile u32 *) movie_mdec_status_register;
    input_dma_busy = (*(volatile u32 *)movie_mdec_input_dma_control >> 0x18) & 1;
    output_dma_busy = (*(volatile u32 *) movie_mdec_output_dma_control >> 0x18) & 1;
    printf(&movie_decoder_dma_format, input_dma_busy, output_dma_busy, *movie_mdec_input_dma_address, *movie_mdec_output_dma_address);
    printf(&movie_decoder_fifo_format, (u32) ~decoder_status >> 0x1F, (decoder_status >> 0x1E) & 1, (decoder_status >> 0x1D) & 1,
           (decoder_status >> 0x1C) & 1, (decoder_status >> 0x1B) & 1, (decoder_status >> 0x19) & 1,
           (decoder_status >> 0x17) & 1);
    *movie_mdec_status_register = 0x80000000;
    *movie_mdec_input_dma_control = 0;
    *movie_mdec_output_dma_control = 0;
    result = 0;
    (void) *(volatile u32 *) movie_mdec_output_dma_control;
    *movie_mdec_status_register = 0x60000000;
    return result;
}
