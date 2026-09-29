#include "common.h"

extern void DrawSync(s32);
extern void Control_CD(s32, void *, void *);
extern void func_8003F320(void);
extern void func_80041344(void *, s32);
extern void func_80046E38(u8, void *);
extern void func_8003E140(void);

extern u8 D_800136B8;
extern u8 D_80080BB4[8];
extern u8 D_80080BBC[8];
extern u8 D_80080BC4[8];
extern u8 D_80080BCC[8];
extern u8 D_80080BD4[8];
extern u8 D_80080BDC[8];
extern u8 D_80080BE4[8];
extern u8 D_80080BEC[8];
extern u8 D_80080BF4[8];
extern u8 D_80080BFC[8];
extern u8 D_80080C04[8];
extern u8 D_80080C0C[8];
extern u8 D_80080C14[8];
extern s32 D_80081480;
extern u8 D_800D2FB4[][32];
extern u8 D_800D381A;
extern u8 D_8012F004[];

/* Loads shared and variant-specific resources, then processes the selected table entry. */
void func_80051228(void)
{
    u8 load_status;
    u8 *resource;
    s32 command;

    load_status = 0;
    Control_CD(6, D_80080BB4, 0);
    Control_CD(0xFF, func_8003E140, &load_status);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480);
    DrawSync(0);
    load_status = 0;
    Control_CD(6, D_80080BBC, 0);
    Control_CD(0xFF, func_8003E140, &load_status);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480);
    DrawSync(0);
    load_status = 0;
    Control_CD(6, D_80080BC4, 0);
    Control_CD(0xFF, func_8003E140, &load_status);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480);
    DrawSync(0);
    load_status = 0;
    Control_CD(6, D_80080BCC, 0);
    Control_CD(0xFF, func_8003E140, &load_status);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480);
    DrawSync(0);
    load_status = 0;

    switch (D_800D381A) {
    case 0:
    case 1:
    default:
        switch (D_800136B8) {
        default:
            command = 6;
            resource = D_80080BD4;
            break;
        case 11:
            command = 6;
            resource = D_80080BDC;
            break;
        case 12:
            command = 6;
            resource = D_80080BE4;
            break;
        case 13:
            command = 6;
            resource = D_80080BEC;
            break;
        }
        break;
    case 2:
        command = 6;
        resource = D_80080BF4;
        break;
    case 3:
        switch (D_800136B8) {
        default:
            command = 6;
            resource = D_80080BFC;
            break;
        case 11:
            command = 6;
            resource = D_80080C04;
            break;
        case 12:
            command = 6;
            resource = D_80080C0C;
            break;
        case 13:
            command = 6;
            resource = D_80080C14;
            break;
        }
        break;
    }

    Control_CD(command, resource, 0);
    Control_CD(0xFF, func_8003E140, &load_status);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480);
    DrawSync(0);
    func_80046E38(D_800D2FB4[D_800D381A][0], D_8012F004);
}
