
#include "common.h"
typedef struct S_80084960
{
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s8 f30;
    u8 pad31[7];
    s16 f38;
    s16 f3a;
    u8 pad3c[4];
    s16 f40;
    u8 pad42[2];
    s32 f44;
    s32 f48;
    s8 f4c;
    u8 f4d;
    s8 f4e;
    u8 pad4f[1];
    s16 f50;
    u8 pad52[11];
    s8 f5d;
    u8 pad5e[1];
    s8 f5f;
    s8 f60;
    s8 f61;
    u8 pad62[2];
    s32 f64;
    s32 f68;
    s8 f6c;
    s8 f6d;
    s8 f6e;
    u8 pad6f[1];
    s32 f70;
    u8 pad74[4];
    s8 f78;
    u8 pad79[1];
    s8 f7a;
    s8 f7b;
    s8 f7c;
    u8 pad7d[3];
    s32 f80;
    s32 f84;
    s8 f88;
    s8 f89;
    s8 f8a;
    u8 pad8b[1];
    s32 f8c;
    u8 pad90[4];
    s32 f94;
    s8 f98;
    u8 pad99[3];
}
S_80084960;
typedef struct S_80085458
{
    s16 f00;
    s16 f02;
    s16 f04;
    u16 f06;
    u8 pad08[8];
    u16 f10;
    u16 f12;
    u8 pad14[4];
    s16 f18;
    u16 f1a;
    u8 f1c;
    u8 f1d;
    u8 pad1e[0x5A];
}
S_80085458;
typedef struct S_80073738
{
    s16 f0;
    s16 pad[7];
}
S_80073738;
extern s32 D_80073734; /* scalar: MEM_IN_STRUCT_P == 0, needs -G0 */
extern S_80073738 D_80073738;
extern s32 D_80073740[64];
extern S_80084960 D_80084960[16];
extern S_80085458 D_80085458[64];
extern void func_80055E7C();
extern void func_800564A8();
extern void func_80056654(S_80085458 *e, s32 value);
extern void func_80057A94(S_80084960 *e);
extern void func_800561D8(S_80085458 *e, S_80084960 *rec);
extern s32 func_800563B0(s32 a0, u16 a1, u16 a2);
extern void func_80056A08(void);
extern void func_8005E97C(s32 a0, s32 a1);
extern s32 func_8005EB78(s32 a0);
/* Applies a channel control change and updates affected voices. */
void func_80057D20(u8 channel, u8 control, u32 value)
{
    S_80084960 *settings = &D_80084960[channel];
    s32 refresh_notes = 0;
    s32 stopped_voices = 0;
    s32 voice_idx;
    u32 control_value;
    s32 entry_idx;
    s32 voice_status;
    s32 pending_voices;
    control_value = value;
    switch (control) {
    case 1:
        if (((u32) settings->f48) < 0x40) {
            settings->f08 = control_value & 0xFF;
            settings->f40 = ((u8) control_value) << 1;
            if ((settings->f44 != 0) && (settings->f40 != 0)) {
                settings->f38 = ((u32) settings->f40 << 2) / settings->f44;
            }
            else {
                settings->f3a = 0;
                for (voice_idx = 0; voice_idx < D_80073734; voice_idx++) {
                    if (D_80085458[voice_idx].f06 == channel) {
                        func_80056654(&D_80085458[voice_idx], 1);
                    }
                }
            }
            if (((control_value & 0xFF) == 0) || (settings->f38 == 0)) {
                settings->f3a = 0;
                for (voice_idx = 0; voice_idx < D_80073734; voice_idx++) {
                    if (D_80085458[voice_idx].f06 == channel) {
                        func_80056654(&D_80085458[voice_idx], 1);
                    }
                }
            }
        }
        else {
            settings->f08 = control_value & 0xFF;
            settings->f44 = control_value & 0xFF;
            if (((control_value & 0xFF) != 0) && (settings->f40 != 0)) {
                settings->f38 = (settings->f40 / (control_value & 0xFF)) << 1;
            }
            else {
                settings->f3a = 0;
                for (voice_idx = 0; voice_idx < D_80073734; voice_idx++) {
                    if (D_80085458[voice_idx].f06 == channel) {
                        func_80056654(&D_80085458[voice_idx], 1);
                    }
                }
            }
            if (((control_value & 0xFF) == 0) || (settings->f38 == 0)) {
                settings->f3a = 0;
                for (voice_idx = 0; voice_idx < D_80073734; voice_idx++) {
                    if (D_80085458[voice_idx].f06 == channel) {
                        func_80056654(&D_80085458[voice_idx], 1);
                    }
                }
            }
        }
        func_80055E7C(4, channel, settings->f08);
        break;

    case 2:
        if (((u32) settings->f48) < 0x40) {
            settings->f44 = (u8) control_value;
        }
        else {
            settings->f40 = (control_value & 0xFF) << 1;
        }
        break;

    case 3:
        settings->f48 = control_value & 0xFF;
        break;

    case 4:
        settings->f28 = control_value & 0xFF;
        break;

    case 5:
        settings->f50 = control_value & 0xFF;
        break;

    case 7:
        {
            settings->f0c = control_value & 0xFF;
            pending_voices = 1;
            refresh_notes = pending_voices;
            func_80055E7C(3, channel, control_value & 0xFF);
            break;
        }

    case 10:
        {
            settings->f04 = ((control_value & 0xFF) == 0) ? (1) : (control_value & 0xFF);
            pending_voices = 1;
            refresh_notes = pending_voices;
            func_80055E7C(2, channel, settings->f04);
            break;
        }

    case 11:
        {
            settings->f14 = control_value & 0xFF;
            pending_voices = 1;
            refresh_notes = pending_voices;
            func_80055E7C(5, channel, control_value & 0xFF);
            break;
        }

    case 12:
        {
            settings->f2c = control_value & 0xFF;
            pending_voices = 1;
            refresh_notes = pending_voices;
            break;
        }

    case 20:
        settings->f6c = control_value << 1;
        break;

    case 21:
        settings->f6e = control_value;
        break;

    case 22:
        settings->f68 = (control_value & 0xFF) << 4;
        settings->f64 = (control_value & 0xFF) << 4;
        settings->f6d = 0;
        settings->f5d = 1;
        break;

    case 23:
        settings->f6d = control_value;
        if (((control_value & 0xFF) != 0) && (settings->f68 != 0)) {
            settings->f70 = settings->f68 / (control_value & 0xFF);
            if (settings->f70 == 0) {
                settings->f70 = 1;
            }
        }
        break;

    case 25:
        settings->f88 = control_value << 1;
        break;

    case 26:
        settings->f8a = control_value;
        break;

    case 27:
        settings->f84 = (control_value & 0xFF) << 7;
        settings->f80 = (control_value & 0xFF) << 7;
        settings->f89 = 0;
        settings->f78 = 1;
        break;

    case 28:
        settings->f89 = control_value;
        if (((control_value & 0xFF) != 0) && (settings->f84 != 0)) {
            settings->f8c = settings->f84 / (control_value & 0xFF);
            if (settings->f8c == 0) {
                settings->f8c = 1;
            }
        }
        break;

    case 30:
        D_80073738.f0 = control_value & 0xFF;
        func_800564A8();
        break;

    case 64:
        for (entry_idx = 0; entry_idx < D_80073734; entry_idx++) {
            if (channel == D_80085458[entry_idx].f06) {
                if (((u32) (control_value & 0xFF)) < 0x40) {
                    for (voice_idx = 0; voice_idx < D_80073734; voice_idx++) {
                        if (((D_80085458[voice_idx].f06 == channel) && (D_80085458[voice_idx].f1d != 0))
                            && (D_80085458[voice_idx].f1c & 0x80)) {
                            {
                                voice_status = D_80073740[voice_idx];
                                pending_voices = stopped_voices;
                                pending_voices |= voice_status;
                                stopped_voices = pending_voices;
                            }
                            do {
                                func_8005E97C(0, D_80073740[voice_idx]);
                                voice_status = func_8005EB78(D_80073740[voice_idx]);
                            }
                            while ((voice_status != 2) && (voice_status != 0));
                            D_80085458[voice_idx].f1d = 0;
                            D_80085458[voice_idx].f1a = 0;
                        }
                    }

                    D_80085458[entry_idx].f1d = 0;
                }
                else {
                    D_80085458[entry_idx].f1d = 1;
                }
            }
        }

        if (((u32) (control_value & 0xFF)) < 0x40) {
            D_80084960[channel].f18 = 0;
        }
        else {
            D_80084960[channel].f18 = 1;
        }
        break;

    case 91:
        settings->f30 = control_value & 0x7F;
        break;

    case 6:
        settings->f4e = control_value;
        if ((settings->f4d != 0x14) && (settings->f4d != 0x1E)) {
            func_80057A94(settings);
        }
        break;

    case 98:
        settings->f4c = control_value;
        break;

    case 99:
        settings->f4d = control_value;
        break;

    case 120:

    case 121:

    case 123:
        func_80056A08();
        break;

    case 126:
        settings->f98 = control_value;
        break;

    default:
        break;
    }

    {
        s32 stop_mask = stopped_voices;
        if (stop_mask) {
            func_8005E97C(0, stop_mask);
        }
    }
    {
        s32 needs_refresh = refresh_notes;
        if (needs_refresh) {
            for (entry_idx = 0; entry_idx < D_80073734; entry_idx++) {
                if ((channel == D_80085458[entry_idx].f06) && (D_80085458[entry_idx].f1a != 0)) {
                    func_800561D8(&D_80085458[entry_idx], &D_80084960[channel]);
                    func_800563B0(entry_idx, D_80085458[entry_idx].f10, D_80085458[entry_idx].f12);
                }
            }
        }
    }
}
