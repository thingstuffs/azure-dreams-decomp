# Psy-Q requirement for complete overlay proof

Most build tools are free: `tools/setup.sh` provisions the stock gcc drops,
vendored `maspsx`, splat and mkpsxiso; your system supplies GNU `as` and the host
build tools. Complete native-overlay
proof additionally uses the proprietary SN Systems / Sony **ASPSX** assembler
from the PlayStation Psy-Q SDK. The repository does not supply or download it.
If you own the SDK, setup can copy the pinned file from your installation.
The retail disc is a separate required input for retail-byte gates.

## What needs it

The **overlay-module windows** need it: the windows that contain a whole-translation-unit module listed in
`config/overlays/modules.json`, including affected complete-module placements.
The current manifest and its affected windows determine the scope; it is not a
fixed count that can be carried forward from an old snapshot.
For these windows the gate assembles the module once with maspsx + GNU `as` and once with genuine ASPSX,
and it requires both results to equal the retail bytes (`tools/gate/overlay_module_gate.py`,
`overlay_native_allocations.py`).

These do **not** need it:

* the SLUS executable (`tools/build/build_slus.sh`, SHA-1 gate);
* overlay windows without a native module/placement requiring genuine comparison;
* ordinary per-function scoring (a requested module/window proof may additionally need it);
* the census (`tools/census/regenerate.py`);
* `tools/row_db.py`.

Without the pinned assembler/loader, module-window proof fails with a missing
toolchain input. Successful free-tool windows do not discharge that requirement.

The window input hash (`inputs_sha`) includes these tool identities. Missing or
changed tools can invalidate cached receipts; a cached journal entry is not a
substitute for a reproducible proof.

To list current home modules and their physical sources (no disc or SDK needed):

```sh
python3 - <<'EOF'
import json
from pathlib import Path
manifest = json.loads(Path('config/overlays/modules.json').read_text())
for module in manifest['modules']:
    print(module['key'], module['source'])
EOF
```

The gate computes affected windows, including destinations listed in
`config/overlays/module_placements.json`; listing home sources alone is not that
complete dependency calculation.

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

**Requires your disc for setup and your own Psy-Q SDK for the genuine assembler.**
Replace the example SDK/loader paths with files you own:

```sh
tools/setup.sh --psyq /path/to/your/psyq            # searches the directory (5 levels) for ASPSX.EXE with the pinned sha256
tools/setup.sh --psyq /path/to/psyq --wibo /path/to/wibo   # use a local wibo instead of downloading it
AZURE_CLEAN_PSYQ=/path/to/psyq tools/setup.sh        # same, via the environment (like AZURE_CLEAN_DISC)
tools/setup.sh --check                               # verifies the two files when present; an absent optional SDK is allowed, but other setup gaps still fail
```

How setup handles the files:

* It **copies** the file into `toolchain/genuine/`. It never symlinks, and it refuses to write through a
  `toolchain/genuine` that is itself a symlink.
* It checks the sha256 of the copy, and of anything already there, on every run.
* A file with any other hash is refused. Install the one from the SDK listed above.

After disc extraction and provisioning, build the executable first so that its
assembly/assets exist for overlay consumers, then create the overlay view and
run the windows. **This full sequence requires the disc and the pinned Psy-Q
assembler/loader for module windows.**

```sh
bash tools/build/build_slus.sh -j 4
bash tools/build/mk_ovl_root.sh
python3 tools/build/gate_all.py --workers 4
```

Inspect the individual failures if any window refuses; the existence of a
generated view or an old receipt is not a successful gate.
