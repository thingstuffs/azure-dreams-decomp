/* delta: genuine extern symbol for the format page (regime B) + one pointer
   variable PER SITE that is re-assigned (dead store) after each use, so cse's
   equivalence class for the symbolic constant holds no valid register at
   sites 2/3 and each site must re-emit its own (lo_sum (high S) S). */
#include "common.h"
typedef struct Vec3s { s16 x; s16 y; s16 z; s16 pad; } Vec3s;
typedef void (*ReportValue)(const char *, const char *, s32);
typedef struct TownDispatch { u8 pad_000[0x168]; ReportValue report_value; } TownDispatch;
typedef struct TownRoot { u8 pad_00[0x1C]; s32 *result_values; TownDispatch *dispatch; } TownRoot;
extern void func_8001A854(Vec3s *, s32);
extern s32 func_8001A8DC(Vec3s *, Vec3s *, s32, s32, Vec3s *);
extern TownRoot *D_80016000[];
extern char D_8001610C[8];
extern char D_80016118[8];
extern char D_80016120[8];
extern char D_80016128[8];
void func_8001A9B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    Vec3s first;
    Vec3s second;
    Vec3s result;
    TownRoot *root;
    const char *fmt1;
    const char *fmt2;
    const char *fmt3;
    func_8001A854(&first, arg0);
    {
        ReportValue report;
        report = D_80016000[0]->dispatch->report_value;
        fmt1 = D_8001610C;
        report(fmt1, D_80016118, first.x);
    }
    fmt1 = 0;
    func_8001A854(&second, arg1);
    {
        ReportValue report;
        report = D_80016000[0]->dispatch->report_value;
        fmt2 = D_8001610C;
        report(fmt2, D_80016120, second.x);
    }
    fmt2 = 0;
    func_8001A8DC(&first, &second, arg2, arg3, &result);
    {
        ReportValue report;
        report = D_80016000[0]->dispatch->report_value;
        fmt3 = D_8001610C;
        report(fmt3, D_80016128, result.x);
    }
    root = D_80016000[0];
    root->result_values[1] = result.x;
    root->result_values[2] = result.y;
}
