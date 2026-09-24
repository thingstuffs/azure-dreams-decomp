#!/usr/bin/env python3
"""Check source hygiene against the frozen transition's actual compiler output."""
from pathlib import Path
import hashlib
import json
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
PAYLOAD = HERE.parent / "transition/payload"
INCLUDE = HERE.parent / "live_fixture/include"
CCDIR = ROOT / "toolchain/compilers/gcc-2.7.2-cdk"

CHANGES = {
    "w_80041AB0.c": [
        ("/* S_80081480: >8B struct forced to hi/lo addressing (only field0 @ offset 0 accessed here) */", "/* External word holding the current buffer write position. */"),
        ("/* S_8008148C: >8B struct forced to hi/lo addressing (only field0 @ offset 0 accessed here) */", "/* External word holding the buffer base. */"),
    ],
    "w_8004AB7C.c": [
        ("/* Force hi/lo access rather than a small-data scalar load. */", "/* External words used to select item categories. */"),
    ],
    "gp_d92c_owned.c": [
        ("#define FLAGS_PAGE ((u8 *)D_80082E60)\n#define FLAGS_OFFSET 0\n#define BASE_PAGE ((u8 *)&D_80083160)\n#define BASE_OFFSET 0\n", ""),
        ("typedef struct \n", "typedef struct\n"),
        ("    S_8003D92C_80083160 *input_state;", "  S_8003D92C_80083160 *input_state;"),
    ],
    "w_8003FAD4.c": [
        ("    u32 pool_page;\n", ""),
        ("    pool_page = 0x801F0000;\n", ""),
    ],
}

def sha(data):
    return hashlib.sha256(data).hexdigest()

def main():
    (HERE / ".ignore").write_text("*\n")
    records = []
    for name, replacements in CHANGES.items():
        before = (PAYLOAD / "src/slus" / name).read_text()
        after = before
        for old, new in replacements:
            assert after.count(old) == 1, (name, old)
            after = after.replace(old, new)
        streams = {}
        for arm, source in (("before", before), ("after", after)):
            d = HERE / arm
            d.mkdir(exist_ok=True)
            (d / name).write_text(source)
            cmd = [str(CCDIR / "gcc"), "-B" + str(CCDIR) + "/", "-S", "-O2",
                   "-I" + str(INCLUDE), "-w", name, "-o", name + ".s"]
            p = subprocess.run(cmd, cwd=d, capture_output=True, text=True)
            (d / (name + ".log")).write_text(p.stdout + p.stderr)
            assert p.returncode == 0, (name, p.stderr)
            streams[arm] = (d / (name + ".s")).read_bytes()
        same = streams["before"] == streams["after"]
        records.append({"source": "src/slus/" + name,
                        "before_sha256": sha(before.encode()),
                        "after_sha256": sha(after.encode()),
                        "compiler": str(CCDIR / "gcc"), "flags": "-S -O2 -w",
                        "compiler_assembly_identical": same,
                        "before_assembly_sha256": sha(streams["before"]),
                        "after_assembly_sha256": sha(streams["after"])})
    result = {"status": "MATCH" if all(r["compiler_assembly_identical"] for r in records) else "DIFF",
              "production_modified": False, "frozen_fixtures_modified": False,
              "records": records}
    (HERE / "receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
