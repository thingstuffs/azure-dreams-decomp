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

extern SoundTransferRegisters *D_80079958;
extern s32 *D_8007995C;
extern s32 * volatile D_80079960;
extern s32 *D_80079964;
extern void (* volatile D_80079990)(u32);
extern s32 D_800799A8;
extern s32 D_800799AC;
extern s32 D_800799B0;
extern s32 *D_80079968;
extern s32 D_80079974;
extern s32 D_80079978;
extern s32 D_8007997C;
extern s32 D_80079980;
extern s32 D_80079984;
extern s32 D_80079988;
extern s32 D_8007998C;
extern volatile s32 D_80079994;
extern u16 D_80079998[8];
extern u16 D_80086D58[10];
extern char D_80033204[];
extern u16 D_80079970;
extern char D_800331F4[];
extern char D_80033214[];
extern char D_80033228[];
extern s32 printf();

void DeliverEvent(u32 event_class, u32 event_spec);
void func_8005D6D8(void);
void func_8005D704(void);
s32 func_8005CC04(s32 warm);
void func_8005CE98(u16 *src, u32 bytes_left);
void func_8005D064(void);
void func_8005D124(s32 ram_address, s16 spu_address, s32 block_count);
s32 func_8005D1D0(s32 command, ...);
void delayMultiplyLoop(void);

#endif
