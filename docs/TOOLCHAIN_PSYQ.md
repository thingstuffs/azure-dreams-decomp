# The genuine Psy-Q assembler (optional)

Everything in this repository builds with free tools: the stock gcc drops, the vendored `maspsx`, GNU `as`,
splat and mkpsxiso, all provisioned by `tools/setup.sh`. One part of the proof also needs a proprietary
file that cannot be redistributed: the SN Systems / Sony **ASPSX** assembler from the PlayStation Psy-Q SDK.
It is never downloaded or committed here. If you own the SDK, `tools/setup.sh` copies the one file it
needs from your copy.

## What needs it

The **overlay-module windows** need it: the windows that contain a whole-translation-unit module listed in
`config/overlays/modules.json`. At this snapshot that is 244 modules (dungeon 193, town 45, main 5,
ovmovie 1) touching 677 of the 3,207 window configs (dungeon 611, town 64, plus `main_boot` and `ovmovie`).
For these windows the gate assembles the module once with maspsx + GNU `as` and once with genuine ASPSX,
and it requires both results to equal the retail bytes (`tools/gate/overlay_module_gate.py`,
`overlay_native_allocations.py`).

These do **not** need it:

* the SLUS executable (`tools/build/build_slus.sh`, SHA-1 gate);
* every other overlay window (2,530 configs);
* the per-function scorer (`tools/verify.py`);
* the census (`tools/census/regenerate.py`);
* `tools/row_db.py`.

Without the assembler, `gate_all.py` reports the module windows as `ERROR ... toolchain/genuine/bin/wibo`
missing. All other windows rebuild and match.

The window input hash (`inputs_sha`) covers the identity of these two files, so without them no window's hash
equals the committed `ledger/gate.jsonl` record. The gate then rebuilds every window instead of reusing it.

To list the module windows:

```sh
python3 - <<'EOF'
import sys; from pathlib import Path; sys.path[:0] = ['tools', 'tools/gate']
from gate.overlay_module_gate import load_modules
from gate.overlay_module_placements import affected_windows
for m in load_modules(Path('.')):
    for w in sorted(affected_windows(m, Path('.'))): print(m['key'], w)
EOF
```

## Exactly which files

Both are pinned in `tools/toolchain.lock.json` under `genuine`, and both are installed under `toolchain/genuine/`.
That directory is not committed (`/toolchain/` is in `.gitignore`).

| installed as | what | size | sha256 |
|---|---|---:|---|
| `toolchain/genuine/psyq/psyq4.4/ASPSX.EXE` | `SDevTC ASPSX version 2.79`, from the **PlayStation Programmer Tool Runtime Library 4.4** (Psy-Q SDK 4.4, DTL-S2350), file `PSYQ\BIN\ASPSX.EXE`. The Psy-Q 4.5 SDK ships the byte-identical file. Proprietary: bring your own. | 89,600 | `fcb987495ba18f9d8b5dc29696f7e6650091d3d86471c60b2a8aa00396888992` |
| `toolchain/genuine/bin/wibo` | **wibo 1.1.0** (Linux x86_64), a small Win32 loader that runs `ASPSX.EXE` (MIT, github.com/decompals/wibo, release asset `wibo-x86_64`). Open source: setup downloads it. | 6,985,552 | `b9ab9f2c5eb014bc79a97f1a2bee9a7ab177d905a7d2f637da5735820021c40c` |

These two files are all the gate uses. It runs `wibo ASPSX.EXE -q -G0 [-0] -o OUT.OBJ IN.S`.

The gate does **not** use:

* `CC1PSX.EXE`, `CCPSX.EXE` or `CPPPSX.EXE` (compiles use the stock gcc drops);
* `PSYLINK.EXE` (linking uses GNU `ld`);
* `ASMPSX.EXE` or `PSYLIB.EXE`;
* any SDK libraries or headers.

ASPSX builds from other SDK releases have different hashes and are refused:

| SDK | ASPSX.EXE sha256 (prefix) |
|---|---|
| 4.0 | `7f928fa89e14…` |
| 4.1 | `44103a7e6443…` |
| 4.3 | `60a72cc29aa5…` |
| 4.6 | `d79cd4c9c973…` |

## Installing it

```sh
tools/setup.sh --psyq /path/to/your/psyq            # searches the directory (5 levels) for ASPSX.EXE with the pinned sha256
tools/setup.sh --psyq /path/to/psyq --wibo /path/to/wibo   # use a local wibo instead of downloading it
AZURE_CLEAN_PSYQ=/path/to/psyq tools/setup.sh        # same, via the environment (like AZURE_CLEAN_DISC)
tools/setup.sh --check                               # verifies the two files when present; their absence is not a gap
```

How setup handles the files:

* It **copies** the file into `toolchain/genuine/`. It never symlinks, and it refuses to write through a
  `toolchain/genuine` that is itself a symlink.
* It checks the sha256 of the copy, and of anything already there, on every run.
* A file with any other hash is refused. Install the one from the SDK listed above.

Once the files are installed, `bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py` gates every window,
module windows included.
