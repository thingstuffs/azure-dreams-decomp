#!/usr/bin/env python3
"""Polish type_flow_apply header edits: in the lines a batch changed, a header that includes the defining header of
a shared type spells its typedef (`ObjectPosition *`, no new forward `struct ObjectPosition;`); a header that does
not keeps the forward-declaration style the applier wrote.

    type_flow_polish_headers.py HEADER...      (run from the root; compares each header with git HEAD)
"""
import difflib, re, subprocess, sys
from pathlib import Path
DEFS = {'ObjectPosition': 'shared/entity.h', 'SpriteFrameState': 'shared/sprite_frame_state.h',
        'MovingPosition': 'shared/dungeon_moving_views.h', 'ObjectNodeHeader': 'shared/object_node.h',
        'ActorRecord': 'shared/entity.h', 'TownObjectRecord': 'shared/town_object.h'}
for path in sys.argv[1:]:
    old = subprocess.run(['git', 'show', 'HEAD:' + path], capture_output=True, text=True).stdout.splitlines(True)
    new = Path(path).read_text().splitlines(True)
    included = {m.group(1) for m in re.finditer(r'#include "([^"]+)"', ''.join(new))}
    ok = {n for n, h in DEFS.items() if h in included}
    out = []
    sm = difflib.SequenceMatcher(a=old, b=new, autojunk=False)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            out.extend(new[j1:j2]); continue
        for line in new[j1:j2]:
            m = re.match(r'^struct (\w+);\s*$', line)
            if m and m.group(1) in ok:
                continue                        # forward declaration of a type the header already sees
            for n in ok:
                line = re.sub(r'\bstruct %s \*' % n, n + ' *', line)
            out.append(line)
    Path(path).write_text(''.join(out))
    print(path, sorted(ok))
