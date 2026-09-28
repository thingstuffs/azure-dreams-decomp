"""hand8.py: the S_80083178 rows onto GameView (applied on top of respell8's draft8/ text; writes draft8/).
   VARIANT=b also folds func_800B2614's `((S_800B7D74_4 *)game_state)->unk_B0` into game_state->viewAngle."""
import os, re, sys
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
sys.path.insert(0, str(LANE / "tools"))
from respell8 import respell
def base(rid):
    return respell((REPO / "src" / (rid + ".c")).read_text())[0]
def vec(expr):   # state_94.v[i].c on a GameView pointer/object -> the flat field
    def f(m):
        i, c = int(m.group(1)), m.group(2); off = 0x94 + 8 * i + {"x": 0, "y": 2, "z": 4}[c]
        return "viewAngle" if off == 0xB0 else "unk_%03X" % off
    return re.sub(r"state_94\.v\[(\d)\]\.([xyz])\b", f, expr)
def rep(t, a, b, count=None):
    assert a in t, a
    return t.replace(a, b) if count is None else t.replace(a, b, count)
E = {}
t = base("dungeon/func_800C6654")
t = rep(t, "struct S_80083178 *state = ((void *)&gameWork.view);", "GameView *state = &gameWork.view;")
E["dungeon/func_800C6654"] = vec(t)
t = base("dungeon/func_800C1E70")
E["dungeon/func_800C1E70"] = rep(t, "struct S_80083178 *state = ((void *)&gameWork.view);", "GameView *state = &gameWork.view;")
t = base("dungeon/func_800B2614")
t = rep(t, "struct S_80083178 *game_state = ((void *)&gameWork.view);", "GameView *game_state = &gameWork.view;")
if os.environ.get("VARIANT") == "b":
    t = t.replace("((S_800B7D74_4 *)game_state)->unk_B0", "game_state->viewAngle")
    if "S_800B7D74_4 *" not in t and len(re.findall(r"\bS_800B7D74_4\b", t)) == 2:
        t = re.sub(r"typedef struct S_800B7D74_4 \{\n    u8 pad_00\[0xB0\];\n    s16 unk_B0;\n\} S_800B7D74_4;   /\* global in func_800B7D74 \*/\n\n", "", t)
E["dungeon/func_800B2614"] = t
for rid in ("dungeon/func_8191696C", "dungeon/func_81984E94"):
    t = base(rid)
    t = rep(t, "struct S_80083178 *state = ((void *)&gameWork.view);", "GameView *state = &gameWork.view;")
    t = t.replace("&state->field_B8", "&state->slot[0].unk_04").replace("state->callback", "state->slot[0].callback")
    E[rid] = t
t = base("slus/w_80044724")
t = rep(t, "    struct S_80083178 *source;", "    GameView *source;")
t = rep(t, "source = ((void *)&gameWork.view);", "source = &gameWork.view;")
t = re.sub(r"= source->state_94\.v\[(\d)\];", lambda m: "= *(struct S_80083178Vector *)&source->unk_%03X;" % (0x94 + 8 * int(m.group(1))), t)
E["slus/w_80044724"] = vec(t)
t = (REPO / "src/slus/w_8004D5D0.c").read_text()
t = rep(t, '#include "shared/entity_objects.h"\n', '#include "shared/entity_objects.h"\n#include "shared/game_work.h"\n\n'
        '/* gameWork.view declared on its own: retail forms this TU\'s base at 0x80083178 itself (not gameWork + 0x18). */\n'
        'extern GameView D_80083178;\n')
t = rep(t, "into D_80083178 and", "into D_80083178 (gameWork.view's position vector) and")
E["slus/w_8004D5D0"] = vec(t)
t = (REPO / "src/dungeon/func_800AFA68.c").read_text()
t = rep(t, '#include "shared/game_work.h"\n', '#include "shared/game_work.h"\n\n'
        '/* gameWork.view declared on its own: this row forms its camera base as D_80083178 - 0x18 (as gameWork it misses). */\n'
        'extern GameView D_80083178;\n', 1)
E["dungeon/func_800AFA68"] = t
t = (REPO / "src/slus/code2.c").read_text()
t = rep(t, '#include "common.h"\n', '#include "common.h"\n#include "shared/game_work.h"\n\n'
        '/* gameWork.view declared on its own: func_8004D0C8 / func_8004D110 form their base at 0x80083178 (as gameWork the\n'
        ' * offsets and the schedule change: cc1 listing differs). */\n'
        'extern GameView D_80083178;\n', 1)
t = rep(t, "D_80083178.ptr = state;", "D_80083178.slot[0].unk_24 = state;")
t = rep(t, "D_80083178.field_B8 = state;", "D_80083178.slot[0].unk_04 = state;")
t = rep(t, "D_80083178.callback = ", "D_80083178.slot[0].callback = ")
E["slus/code2"] = t
for rid, t in E.items():
    assert "S_80083178 " not in t.replace("S_80083178Vector", "") or rid == "", rid
    d = LANE / "draft8" / (rid + ".c"); d.parent.mkdir(parents=True, exist_ok=True); d.write_text(t); print("wrote", rid)
