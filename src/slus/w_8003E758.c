#include "common.h"
typedef struct S_80083958 {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u8  unk4;
    /* 0x5 */ u8  unk5;
    /* 0x6 */ u16 counter1;
    /* 0x8 */ u16 counter2;
    /* 0xA */ u16 flags;
    /* 0xC */ u8  pad0C[40 - 0xC];   /* >gcc -G32 -> gcc SPLITS the address */
} S_80083958;

typedef struct S_80083968 {
    /* 0x00 */ u8  unk00;
    /* 0x01 */ u8  pad01[3];
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u8  unk08[0xF];
    /* 0x17 */ u8  unk17;
} S_80083968;

typedef struct S_80083164 {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u8  pad2[0xE];
    /* 0x10 */ u8 pad10[40 - 0x10]; /* >gcc -G32 -> gcc SPLITS the address */
} S_80083164;

extern S_80083958 D_80083958;

/* RETAIL jump table for the state==1 dispatch: an ABSOLUTE in
 * config/generated/slus_006.14.undefined_syms.txt (0x8002D5C0, 28 entries,
 * live cases 0/6/9/0x15/0x1B, every other index -> the `tail` block).
 * Dispatching through it means this TU emits NO compiler-generated jump table
 * into .text-referenced .rodata, which is what makes the object LINK. */
extern void *jtbl_8002D5C0[];
extern S_80083968 D_80083968[32];

extern u8  D_800814D0;        /* head index: $gp scalar */
extern u8  D_800814D1[16];    /* tail index: %hi/%lo (size>8) */
    /* driver state byte: %hi/%lo; head via [-3] */
extern u8  D_800814D4;        /* mode byte store: $gp scalar */
extern u32 D_800814CC;        /* $gp word */
extern u8  D_800814D8[16];    /* %hi/%lo CdReadSync buffer */
extern u8  D_80081450;        /* status byte read: $gp scalar */
extern u8  D_80081438[0x20];  /* neighbour: &D_80081438[0x18]==&D_80081450 (%hi/%lo) */
extern u32 D_80081480[8];     /* %hi/%lo */
extern S_80083164 D_80083164; /* %hi/%lo (size>8) */
extern u8  D_80080AD0;        /* $gp */
extern u16 D_80080AD2;        /* $gp */
extern u16 D_80080AD4;        /* $gp */
extern s32 D_80080AD8;        /* $gp */

extern int  CdSync(int mode, u8 *result);
extern int  CdControl(u8 com, u8 *param, u8 *result);
extern int  CdControlF(u8 com, u8 *param);
extern int  CdRead(int count, u32 *buf, int mode);
extern int  CdRead2(int mode);
extern int  CdReadSync(int mode, u8 *result);
extern int  CdReset(int mode);
extern void StUnSetRing(void);

extern void func_8003E70C(void);
extern void func_8003F5EC(void);
extern void func_8003F624(void);
extern int  func_8003F240(void);
extern void CdIntToPos(u32 lba, u8 *loc);
extern u8  D_800814D3[16];
extern u8  D_800814D3_1[16] __asm__("D_800814D3");
extern u8  D_800814D3_2[16] __asm__("D_800814D3");
extern u8  D_800814D3_3[16] __asm__("D_800814D3");
extern u8  D_800814D3_8[16] __asm__("D_800814D3");
extern u8  D_800814D3_9[16] __asm__("D_800814D3");
extern u8  D_800814D3_10[16] __asm__("D_800814D3");
extern u8  D_800814D3_11[16] __asm__("D_800814D3");
extern u8  D_800814D3_12[16] __asm__("D_800814D3");
extern u8  D_800814D3_13[16] __asm__("D_800814D3");
extern u8  D_800814D3_14[16] __asm__("D_800814D3");
extern u8  D_800814D3_15[16] __asm__("D_800814D3");
extern u8  D_800814D3_24[16] __asm__("D_800814D3");
extern u8  D_800814D2[16];
extern u8  D_800814D2_P[16] __asm__("D_800814D2");
extern u8  D_800814D2_R[16] __asm__("D_800814D2");

#define CDBUF (&D_80081438[0x18])   /* == &D_80081450, %hi/%lo addressing */

/* Processes queued CD commands and advances pending reads and drive operations. */
void func_8003E758(void)
{
    S_80083958 *driver;
    S_80083968 *queue, *command, *active_queue, *active_command;
    int state;
    int sync_result, retries;
    u8  status;
    int head_index;
    int head_stride;
    u8  location[8];
    u8  sync_status[8];

process_queue:
    driver = &D_80083958;
    driver->flags &= 0xFFFE;

    if (D_800814D0 == D_800814D1[0])
        goto queue_empty;

    driver->flags |= 1;
    state = D_800814D3_1[0];

    if (state == 0xFF) {
        queue = D_80083968;
        head_index = D_800814D0;
        /* head_index*24 SPLIT into two carriers (head_index*3, then <<3): one 4-ref temp for
         * the whole chain outranks the address %hi in local-alloc
         * (floor_log2(4)*4/5 vs floor_log2(2)*2/4) and steals $v0; two 2-ref
         * carriers do not, so the %hi keeps retail's $v0.  Same 3 insns. */
        head_stride = head_index * 3;
        switch (*((u8 *)queue + head_stride * 8)) {
        case 0:
            D_800814D3_2[0] = 0xFF;
            driver->unk4 = 0;
            D_800814D2[0] = 0;
            D_800814D0 = (head_index + 1) & 0x1F;
            goto process_queue;

        case 1:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 2;
            driver->unk4 = 2;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 2:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            command = &queue[D_800814D0];
            CdIntToPos(command->unk04, location);
            if (CdControl(2, location, CDBUF) == 0) goto finish;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 6: {
            u32 *read_info;
            u32 read_word, read_addr, sector_count;
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            command = &queue[D_800814D0];
            read_info = (u32 *)command->unk04;
            read_word = read_info[0];
            read_addr = read_word & 0x7FFFFF;
            if (read_addr == 0)
                read_addr = D_80081480[0];
            else
                read_addr = read_addr | 0x80000000;
            sector_count = read_info[0] >> 23;
            if (sector_count == 0) {
                u8 *state_ptr = &D_800814D3_3[0];
                D_800814D3[0] = 0xFF;
                state_ptr[-3] += 1;
                goto finish;
            }
            D_800814CC = (read_addr + (sector_count << 11)) - 4;
            D_800814D4 = 0x80;
            if (CdControl(0xE, &D_800814D3[1], 0) == 0) return;
            sync_result = CdSync(1, sync_status);
            if (sync_result != 0) {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) {
                    func_8003E70C();
                    return;
                }
            }
            CdIntToPos(read_info[1], location);
            if (CdControl(2, location, 0) == 0) return;
            sync_result = CdSync(1, sync_status);
            if (sync_result != 0) {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) {
                    func_8003E70C();
                    return;
                }
            }
            if (CdRead(sector_count, (u32 *)read_addr, 0x80) == 0) return;
            goto mark_pending;
        }

        case 9:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            if (CdControl(9, 0, CDBUF) == 0) goto finish;
            goto mark_pending;

        case 0xD:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            {
                int command_offset = D_800814D0 * 24;
                u8 *params = queue->unk08;
                if (CdControl(0xD, command_offset + params, CDBUF) == 0) goto finish;
            }
            D_800814D3_8[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0xE:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            {
                int command_offset = D_800814D0 * 24;
                u8 *params = queue->unk08;
                if (CdControl(0xE, command_offset + params, CDBUF) == 0) goto finish;
            }
            D_800814D3_9[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0x15:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            command = &queue[D_800814D0];
            CdIntToPos(command->unk04, location);
            if (CdControlF(0x15, location) == 0) goto finish;
            goto mark_pending;

        case 0x1B:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            command = &queue[D_800814D0];
            CdIntToPos(command->unk04, location);
            retries = 0x10;
            if (CdControl(2, location, 0) == 0) return;
            {
                int disk_error = 5;
                for (;;) {
                    sync_result = CdSync(1, sync_status);
                    retries--;
                    if (sync_result == 0) goto wait_stream_seek;
                    retries = 0x10;
                    if (sync_result != disk_error) goto start_stream;
                stream_error:
                    func_8003E70C();
                    return;
                wait_stream_seek:
                    if (retries != 0) continue;
                    goto stream_error;
                start_stream:
                    for (;;) {
                        if (CdRead2(0xC8) != 0) break;
                        if (--retries == 0) goto stream_error;
                    }
                    D_80083958.unk4 = 0;
                mark_pending:
                    D_800814D3_11[0] = 1;
                    goto finish;
                }
            }

        case 0xA:
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            retries = 0x10;
            for (;;) {
                if (CdReset(0) != 0) break;
                if (--retries == 0) goto stream_error;
            }
            D_800814D3[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0xFF:
            (*(void (*)(u32))queue[head_index].unk04)(*(u32 *)D_80083968[D_800814D0].unk08);
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0xFC:
            StUnSetRing();
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0x4:
        case 0x8:
        case 0xB:
        case 0xC:
        case 0x10:
        case 0x16:
        default:
            goto finish;
        }
    } else if (state == 1) {
        /* `dispatch_labels` exists only to stop gcc deleting the case labels; it lands
         * in .rodata but is unreferenced from .text, so the linker discards it.
         * Idiom from src/w_800595C0.c / w_8004CECC.c / w_80042BDC.c. */
        static void *const dispatch_labels[] = {
            &&complete_noop, &&complete_read, &&complete_pause, &&complete_seek, &&complete_stream
        };
        u32 opcode;
        (void)dispatch_labels;
        active_queue = D_80083968;
        head_index = D_800814D0;
        active_command = &active_queue[head_index];
        opcode = active_command->unk00;
        if (opcode >= 0x1C) goto finish;
        goto *jtbl_8002D5C0[opcode];
        {
            complete_noop: {
                register u8 *state_ptr ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                register int idle_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                int old_head;
                idle_state = 0xFF;
                D_800814D3_14[0] = idle_state;
                state_ptr = &D_800814D3_13[0];
                old_head = state_ptr[-3];
                D_80083958.unk4 = 0;
                D_800814D2[0] = 0;
                state_ptr[-3] = (old_head + 1) & 0x1F;
                goto process_queue;
            }

            complete_read:
                sync_result = CdSync(1, CDBUF);
                if (sync_result == 0) goto finish;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error) goto command_failed;
                }
                D_80080AD8 = CdReadSync(1, D_800814D8);
                if (D_80080AD8 > 0) goto finish;
                if (D_80080AD8 != 0) goto read_failed;
                if (D_80080AD0 == 0) goto read_complete;
                if ((*(u32 *)D_800814CC & 0xFFFF0000) == 0x10120000) goto finish;
                func_8003E70C();
                D_800814D2[0] = 0;
                D_80080AD2 = D_80080AD2 + 1;
                if ((D_80080AD2 & 3) == 3) {
                    CdReset(0);
                    func_8003F5EC();
                }
                D_800814D3[0] = 0xFF;
                goto finish;
            read_complete:
                {
                    u8 *state_ptr = &D_800814D3_15[0];
                    S_80083958 *read_driver = &D_80083958;
                    D_800814D3[0] = 0xFF;
                    read_driver->unk4 = 2;
                    state_ptr[-3] += 1;
                    D_800814D2[0] = D_800814D2_R[0] | 1;
                    read_driver->unk5 = read_driver->unk5 + 1;
                    goto finish;
                }
            read_failed:
                if (D_80080AD8 >= 0) goto finish;
                goto command_failed;

            complete_pause:
                sync_result = CdSync(1, CDBUF);
                if (sync_result == 0) goto finish;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error) goto command_failed;
                }
                goto check_drive_status;

            complete_seek:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0) goto finish;
                if (sync_result != 5) goto check_drive_status;
                goto command_failed;

            command_failed:
                func_8003E70C();
                D_800814D3[0] = 0xFF;
                D_80083958.unk4 = 0;
                D_800814D2[0] = 0;
                goto finish;

            check_drive_status:
                if (CdControl(1, 0, CDBUF) == 0) goto finish;
                if ((D_80081450 & 0xFD) != 0) goto finish;
                D_80083958.unk4 = 2;
                D_800814D3[0] = 0xFF;
                D_800814D0 = D_800814D0 + 1;
                goto finish;

            complete_stream:
                if (CdSync(1, CDBUF) == 5) {
                    D_800814D3[0] = 0xFF;
                    goto finish;
                }
                retries = 0x10;
                for (;;) {
                    if (CdControl(1, 0, CDBUF) != 0) break;
                    if (--retries == 0) {
                        func_8003E70C();
                        D_800814D3[0] = 0xFF;
                        return;
                    }
                }
                status = D_80081450;
                if (status & 0x40) goto finish;
                if (status & 0x20) {
                    u8 *status_ptr = &D_800814D2_P[0];
                    register S_80083968 *stream_queue ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    register int idle_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    S_80083968 *stream_command;
                    int stream_head;
                    idle_state = 0xFF;
                    stream_queue = D_80083968;
                    ASM_KEEP_NV(status_ptr);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    D_800814D2[0] = 0;
                    D_800814D3[0] = idle_state;
                    stream_head = status_ptr[-2];
                    stream_command = &stream_queue[stream_head];
                    ASM_SET(stream_queue);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    if (stream_command->unk17 != 0xFF) {
                        D_80083958.unk4 = 4;
                        D_80080AD4 = 1;
                    }
                    status_ptr[-2] += 1;
                    goto finish;
                }
                if (status & 0x80) D_800814D3[0] = 0xFF;
                goto finish;

        }
    }

    goto finish;

queue_empty:
    if (CdSync(1, 0) == 5) {
        if ((func_8003F240() & 0xFF) == 0x1B) {
            D_800814D3_24[0] = 0xFF;
            if (D_800814D0 != 0)
                D_800814D0 = D_800814D0 - 1;
            else
                D_800814D0 = 0x1F;
            func_8003F624();
        } else {
            CdControl(1, 0, 0);
        }
    }

finish:
    if ((D_80083164.unk0 & 0x7FFF) == 0)
        D_80083958.counter1 = 0;
    D_800814D0 = D_800814D0 & 0x1F;
}
