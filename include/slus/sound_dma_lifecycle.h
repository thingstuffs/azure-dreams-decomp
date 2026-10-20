#ifndef SLUS_SOUND_DMA_LIFECYCLE_H
#define SLUS_SOUND_DMA_LIFECYCLE_H

#include "common.h"

typedef volatile u16 SoundTransferRegister16;
typedef union SoundHalfwordCell {
    u16 value;
    SoundTransferRegister16 ordered;
} SoundHalfwordCell;

typedef struct SoundVoiceRegisters {
    SoundTransferRegister16 voll;
    SoundTransferRegister16 volr;
    SoundTransferRegister16 pitch;
    SoundTransferRegister16 addr;
    SoundTransferRegister16 adsr1;
    SoundTransferRegister16 adsr2;
    SoundTransferRegister16 curvol;
    SoundTransferRegister16 repaddr;
} SoundVoiceRegisters;
typedef struct SoundTransferRegisters {
    SoundVoiceRegisters voice[24];
    SoundTransferRegister16 mvoll;
    SoundTransferRegister16 mvolr;
    u16 rvoll;
    u16 rvolr;
    u16 keyon_lo;
    SoundTransferRegister16 keyon_hi;
    u16 keyoff_lo;
    SoundTransferRegister16 keyoff_hi;
    u16 fm_lo;
    u16 fm_hi;
    u16 noise_lo;
    u16 noise_hi;
    u16 rev_lo;
    u16 rev_hi;
    u8 pad19C[0x1A6 - 0x19C];
    SoundHalfwordCell transfer_address;
    SoundTransferRegister16 transfer_fifo;
    SoundTransferRegister16 control;
    u16 transfer_control;
    SoundHalfwordCell status;
    u16 cdvoll;
    u16 cdvolr;
    u16 extvoll;
    SoundTransferRegister16 extvolr;
    u8 pad1B8[0x1C0 - 0x1B8];
    u16 reverb[32];
} SoundTransferRegisters;

extern SoundTransferRegisters *spu_registers;
extern s32 *spu_dma_ram_address_register;
extern s32 * volatile spu_dma_block_control_register;
extern s32 *spu_dma_channel_control_register;
extern void (* volatile spu_transfer_callback)(u32);
extern s32 spu_dma_read_direction;
extern s32 spu_dma_ram_address;
extern s32 spu_dma_block_count;
extern s32 *spu_dma_priority_register;
extern s32 spu_transfer_uses_fifo;
extern s32 D_80079978;
extern s32 spu_address_alignment_enabled;
extern s32 spu_address_unit_shift;
extern s32 spu_address_alignment;
extern s32 spu_address_alignment_mask;
extern s32 spu_transfer_complete;
extern volatile s32 D_80079994;
extern u16 spu_cold_start_sample[8];
extern u16 spu_keyon_shadow[10];
extern char spu_init_timeout_label[];
extern u16 spu_transfer_address_units;
extern char spu_timeout_format[];
extern char spu_fifo_busy_timeout_label[];
extern char spu_fifo_status_timeout_label[];
extern s32 printf();

void DeliverEvent(u32 event_class, u32 event_spec);
void select_spu_dma_write_channel_flags(void);
void select_spu_dma_read_channel_flags(void);
s32 initialize_spu_registers_and_voices(s32 warm);
void write_spu_transfer_fifo_in_chunks(u16 *src, u32 bytes_left);
void complete_spu_dma_and_signal_event(void);
void submit_spu_dma_read_blocks(s32 ram_address, s16 spu_address, s32 block_count);
s32 dispatch_spu_dma_transfer_command(s32 command, ...);
void delay_multiply_loop(void);

#endif
