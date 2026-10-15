#include "slus/sound_dma_lifecycle.h"

/* Initialize the SPU, resetting voice settings on a cold start. */
s32 func_8005CC04(s32 warm)
{
    s32 entry_index;
    s32 result;
    u32 status_polls;
    volatile u16 *clear_entry;
    SoundTransferRegisters *spu_regs;

    *D_80079968 |= 0xB0000;
    D_80079974 = 0;
    D_80079978 = 0;
    D_80079970 = 0;
    D_80079958->mvoll = 0;
    D_80079958->mvolr = 0;
    D_80079958->control = 0;
    func_8005D730();
    D_80079958->mvoll = 0;
    D_80079958->mvolr = 0;
    status_polls = 0;
    while (D_80079958->status.ordered & 0x7FF) {
        if (++status_polls >= 0xF01) {
            printf(D_800331F4, D_80033204);
            break;
        }
    }
    D_8007997C = 2;
    D_80079980 = 3;
    D_80079984 = 8;
    D_80079988 = 7;
    D_80079958->transfer_control = 4;
    D_80079958->rvoll = 0;
    D_80079958->rvolr = 0;
    D_80079958->keyoff_lo = 0xFFFF;
    D_80079958->keyoff_hi = 0xFFFF;
    D_80079958->rev_lo = 0;
    D_80079958->rev_hi = 0;
    entry_index = 0;
    clear_entry = D_80086D58;
    for (; entry_index < 10; entry_index++) {
        *clear_entry = 0;
        clear_entry++;
    }
    if (warm == 0) {
        D_80079970 = 0x200;
        D_80079958->fm_lo = 0;
        D_80079958->fm_hi = 0;
        D_80079958->noise_lo = 0;
        D_80079958->noise_hi = 0;
        D_80079958->cdvoll = 0;
        D_80079958->cdvolr = 0;
        D_80079958->extvoll = 0;
        D_80079958->extvolr = 0;
        func_8005CE98(D_80079998, 0x10);
        spu_regs = D_80079958;
        for (entry_index = 0; entry_index < 24; entry_index++) {
            spu_regs->voice[entry_index].voll = 0;
            spu_regs->voice[entry_index].volr = 0;
            spu_regs->voice[entry_index].pitch = 0x3FFF;
            spu_regs->voice[entry_index].addr = 0x200;
            spu_regs->voice[entry_index].adsr1 = 0;
            spu_regs->voice[entry_index].adsr2 = 0;
        }
        D_80079958->keyon_lo = 0xFFFF;
        D_80079958->keyon_hi = 0xFF;
        func_8005D730();
        func_8005D730();
        func_8005D730();
        func_8005D730();
        D_80079958->keyoff_lo = 0xFFFF;
        D_80079958->keyoff_hi = 0xFF;
        func_8005D730();
        func_8005D730();
        func_8005D730();
        func_8005D730();
    }
    result = 0;
    D_8007998C = 1;
    D_80079958->control = 0xC000;
    D_80079990 = 0;
    D_80079994 = 0;
    return result;
}
