#!/usr/bin/env python3
"""Turn a built pack into a KIT pack (round 68): the v2 brief, the lane kit, a prompt that says work from the lane.

    python3 tools/lanes/kit_pack.py <lane> [<lane> ...] [--paragraphs big_rows,new_findings] [--question FILE]
                                    [--tier astra|opus|sonnet|sol6|luna6|sol|luna [--repack]]

--tier (round 76) is the served guard: a lane holding a row that a launched lane of the SAME tier served at the
SAME text (tools/lanes/served.py mode `tier`) is not kitted (printed and skipped); --repack kits it anyway.

Run AFTER tools/lanes/build_class_pack.py ... --rows ... --duck (which writes rows.md with the ducks, exemplars.md,
base/, out/).  This replaces BRIEF.md with tools/lanes/duck_pack_brief_v2.md (its <REPO>/<KIT> placeholders written
out as absolute paths, the lane named at the top), appends the named tools/lanes/brief_paragraphs/*.md and an optional
question file (the class question of a family pack), rewrites PROMPT.txt, and runs lanekit/install.py (TOOLS.md).
It refuses a lane that already ran (last_message.txt).  log mining 2026-09-21: every lane rebuilt its own harness, tool
paths were guessed wrong ~15 times, lanes stopped after 13-29 minutes; the v2 brief and the kit answer those.
"""
import sys, subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]

def main(argv):
    paras = argv[argv.index('--paragraphs') + 1].split(',') if '--paragraphs' in argv else []
    qfile = argv[argv.index('--question') + 1] if '--question' in argv else None
    tier = argv[argv.index('--tier') + 1] if '--tier' in argv else None
    skip = set()
    for flag in ('--paragraphs', '--question', '--tier'):
        if flag in argv: skip |= {argv.index(flag), argv.index(flag) + 1}
    lanes = [a for i, a in enumerate(argv) if i not in skip and a != '--repack']
    v2 = (ROOT / 'tools/lanes/duck_pack_brief_v2.md').read_text()
    for lane in lanes:
        D = ROOT / 'work/native_lane' / Path(lane).name
        if not (D / 'rows.md').is_file(): print('no rows.md:', D); continue
        if (D / 'last_message.txt').exists(): print('already ran:', D.name); continue
        if tier:
            sys.path.insert(0, str(ROOT / 'tools/lanes'))
            import served
            ids = sorted(f.parent.name + '/' + f.stem for f in (D / 'base').glob('*/*.c'))
            try:
                served.assert_unserved(ids, repack='--repack' in argv, mode='tier', tier=tier, skip_lane=D.name,
                                       scopes=served.lane_scopes(D))
            except SystemExit as e:
                print('served guard, not kitted:', D.name, '\n' + str(e)); continue
        n = sum(1 for l in (D / 'rows.md').read_text().splitlines() if l.startswith('## ') and '/' in l[3:].split()[0:1][0] if l[3:].split())
        head = (f"# Lane `{D.name}` - {n} rows, each with a rubber-duck brief in `rows.md`\n\n"
                f"Repository root: `{ROOT}`. Your lane directory is `{D}`: WORK FROM IT (cd there first; every file you "
                f"write, every compiler dump, stays inside it). Never edit `src/`, never run git, gates, sweeps or "
                f"landings. Byte-exact candidates go to `out/<container>/<name>.c` with the `.base_sha` the kit's "
                f"`lab.py` writes. `TOOLS.md` in this directory lists every tool with its absolute path.\n\n")
        body = v2.replace('<REPO>', str(ROOT)).replace('<KIT>', str(ROOT / 'tools/lanes/lanekit'))
        extra = ''
        for p in paras:
            f = ROOT / 'tools/lanes/brief_paragraphs' / (p if p.endswith('.md') else p + '.md')
            if f.is_file(): extra += '\n\n' + f.read_text().strip() + '\n'
        if qfile: extra += '\n\n' + Path(qfile).read_text().strip() + '\n'
        (D / 'BRIEF.md').write_text(head + body + extra)
        (D / 'PROMPT.txt').write_text(
            f"cd {D} && source {ROOT}/tools/lanes/lanekit/env.sh - work ONLY inside that directory.\n"
            f"Read BRIEF.md and TOOLS.md there and follow them exactly: restate each row's duck under the fixed heading before "
            f"its first compile, use the kit (lab.py, erase.py, why.py) instead of writing your own harness, give every row its "
            f"first measurements before going deep, and KEEP GOING while any row sits at listing distance <= 4 or a pass "
            f"decision is unexplained - do not stop early. Write REPORT.md in the format the brief gives. End with one line per "
            f"row: row, result, the change, the mechanism, the generator rule, what did not work.\n")
        r = subprocess.run([sys.executable, str(ROOT / 'tools/lanes/lanekit/install.py'), str(D)], capture_output=True, text=True)
        print('kit pack:', D.name, n, 'rows;', (r.stdout.strip().splitlines() or [r.stderr.strip()[-120:]])[-1])

if __name__ == '__main__':
    main(sys.argv[1:])
