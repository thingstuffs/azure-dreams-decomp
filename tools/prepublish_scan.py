#!/usr/bin/env python3
"""Pre-publish scan of the tracked tree: nothing private, nothing retail, nothing oversized.

    python3 tools/prepublish_scan.py                       # scan tracked + new unignored files, exit 1 on any finding
    python3 tools/prepublish_scan.py --root DIR            # scan another checkout (uses its git index, else walks it)
    python3 tools/prepublish_scan.py --allowlist FILE      # default: tools/prepublish_allowlist.txt
    python3 tools/prepublish_scan.py --no-allowlist        # show everything
    python3 tools/prepublish_scan.py --list-allowed        # also print the findings the allowlist hid
    python3 tools/prepublish_scan.py --max-bytes N         # content-scan limit and size-finding threshold (default 1048576)
    python3 tools/prepublish_scan.py --deep                # also read files above --max-bytes (slow, reads the whole tree)
    python3 tools/prepublish_scan.py --json                # machine-readable findings

Rules (the id is what the allowlist and the output use):
  abs-path       home-directory (<user>)/, /Users/<user>/, /mnt/<drive>, /tmp/claude-, Windows C:\\Users\\ paths, and the
                 -home-<user>-<project> directory form used by editor session folders
  private-ip     RFC 1918 addresses (10.x, 172.16-31.x, 192.168.x) and link-local 169.254.x
  token          GitHub (ghp_, gho_, github_pat_), Anthropic (sk-ant-), OpenAI-style (sk-...), AWS (AKIA...),
                 Slack (xox?-), Google (AIza...) keys, and PEM private-key blocks
  email          anything shaped like an address, except the always-fine noreply ones
  name           the personal-name deny list (below), case-insensitive
  retail-blob    a file whose extension is a binary/image/archive/object type (.bin .o .elf .iso .cue .img .exe
                 .rom .a .lib .raw .dat .pak .gz of such), or a .s/.dis whose first lines look like a disassembly
                 (address column, "file format elf32")
  retail-hex     a run of >= 12 consecutive 8-hex-digit words, or >= 96 contiguous hex digits, in a text file:
                 the shape of a dumped code/data region (SHA-256 hashes are 64 digits and do not trip it)
  size           a file larger than --max-bytes (reported by size alone, the content is not read unless --deep)
  secret-file    file names like .env, id_rsa, *.pem, *.key, *.p12

Allowlist file: one entry per line, `#` comments. `<glob> <rule|*>`; the glob is fnmatch on the repo-relative
path (`**` is the same as `*`, a trailing `/` matches a directory prefix). Optionally `<glob> <rule> ~ <regex>`
only hides findings whose matched text matches the regex. Every entry should say why in a comment above it.

Exit status: 0 clean (or only allowlisted), 1 findings, 2 usage/IO error.
"""
import argparse, fnmatch, json, os, re, subprocess, sys

# personal-name deny list, split so this file does not trip its own scan
DENY_WORDS = ("da" + "vid", "thing" + "stuffs")
SKIP_CONTENT_EXT = {".gz", ".xz", ".bz2", ".zip", ".png", ".jpg", ".jpeg", ".gif", ".ico", ".pdf", ".patch_bin"}
BLOB_EXT = {".bin", ".o", ".obj", ".elf", ".iso", ".cue", ".img", ".exe", ".dll", ".so", ".rom", ".a", ".lib",
            ".raw", ".dat", ".pak", ".sav", ".mcr", ".mcd", ".sym", ".exo", ".psx", ".z64", ".sfc"}
SECRET_NAME = re.compile(r"(^|/)(\.env(\..*)?|id_(rsa|dsa|ecdsa|ed25519)(\.pub)?|.*\.(pem|key|p12|pfx|keystore))$")
ALWAYS_OK_EMAIL = re.compile(r"^(noreply|no-reply)@(anthropic\.com|github\.com|users\.noreply\.github\.com)$|@example\.(com|org)$|@users\.noreply\.github\.com$", re.I)

R_ABS = re.compile(r"(?:/ho" r"me/[A-Za-z0-9_.-]+/|/Users/[A-Za-z0-9_.-]+/|/mnt/[a-z]/|/tmp/claude-|[A-Za-z]:\\Users\\|"
                   r"(?<![A-Za-z0-9])-home-[A-Za-z0-9_.]+-[A-Za-z0-9_.-]+)")
R_IP = re.compile(r"(?<![0-9.])(?:10\.\d{1,3}\.\d{1,3}\.\d{1,3}|192\.168\.\d{1,3}\.\d{1,3}|172\.(?:1[6-9]|2\d|3[01])\.\d{1,3}\.\d{1,3}|169\.254\.\d{1,3}\.\d{1,3})(?![0-9])")
R_TOKEN = re.compile(r"(?:gh[pousr]_[A-Za-z0-9]{30,}|github_pat_[A-Za-z0-9_]{30,}|sk-ant-[A-Za-z0-9_-]{16,}|sk-[A-Za-z0-9]{32,}|"
                     r"AKIA[0-9A-Z]{16}|xox[abprs]-[A-Za-z0-9-]{10,}|AIza[0-9A-Za-z_-]{35}|-----BEGIN [A-Z ]*PRIVATE KEY-----)")
R_EMAIL = re.compile(r"[A-Za-z0-9._%+-]+@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)*\.[A-Za-z]{2,}")
R_NAME = re.compile("|".join(re.escape(w) for w in DENY_WORDS), re.I)
R_HEXWORDS = re.compile(r"(?:(?<![0-9A-Fa-f])[0-9A-Fa-f]{8}(?![0-9A-Fa-f])[ ,\t\"':;\[\]\n\r]{1,4}){12,}")
R_HEXRUN = re.compile(r"(?<![0-9A-Fa-f])[0-9A-Fa-f]{96,}(?![0-9A-Fa-f])")
R_DISASM_LINE = re.compile(r"^\s*(?:0x)?[0-9a-f]{8}:?\s+(?:[0-9a-f]{8}\s+)?[a-z.][a-z0-9.]*\s", re.I)


def tracked_files(root):
    try:
        # tracked files plus new, not-ignored files (so a change is scanned before it is `git add`ed); paths that
        # are in the index but already deleted from the work tree are skipped
        out = subprocess.run(["git", "-C", root, "ls-files", "-z", "--cached", "--others", "--exclude-standard"],
                             capture_output=True, check=True).stdout
        names = sorted({p for p in out.decode("utf-8", "surrogateescape").split("\0") if p})
        return [p for p in names if os.path.lexists(os.path.join(root, p))]
    except (subprocess.CalledProcessError, FileNotFoundError):
        res = []
        for d, dirs, fs in os.walk(root):
            dirs[:] = [x for x in dirs if x != ".git"]
            res += [os.path.relpath(os.path.join(d, f), root) for f in fs]
        return sorted(res)


def load_allowlist(path):
    ents = []
    if not path or not os.path.exists(path):
        return ents
    for n, line in enumerate(open(path, encoding="utf-8"), 1):
        line = line.rstrip("\n")
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        text_rx = None
        if " ~ " in line:
            line, rx = line.split(" ~ ", 1)
            text_rx = re.compile(rx.strip())
        parts = line.split()
        if len(parts) != 2:
            raise SystemExit(f"{path}:{n}: want `<glob> <rule|*>`")
        glob = parts[0].replace("**", "*")
        ents.append((glob, parts[1], text_rx))
    return ents


def allowed(ents, rule, path, text):
    for glob, r, rx in ents:
        if r not in ("*", rule):
            continue
        if glob.endswith("/"):
            ok = path.startswith(glob)
        else:
            ok = fnmatch.fnmatchcase(path, glob)
        if ok and (rx is None or rx.search(text or "")):
            return True
    return False


def scan_file(root, rel, max_bytes, deep=False):
    """yield (rule, line, text) for one file."""
    full = os.path.join(root, rel)
    if SECRET_NAME.search(rel):
        yield "secret-file", 0, rel
    ext = os.path.splitext(rel)[1].lower()
    try:
        size = os.lstat(full).st_size
    except OSError:
        return
    if os.path.islink(full):
        return
    if ext in BLOB_EXT:
        yield "retail-blob", 0, f"binary/object file type ({size} bytes)"
    if size > max_bytes:
        yield "size", 0, f"{size} bytes"
        if not deep:
            return                               # do not read big files: this keeps the scan IO-light
    if ext in SKIP_CONTENT_EXT or ext in BLOB_EXT:
        return
    try:
        with open(full, "rb") as fh:
            raw = fh.read()
    except OSError:
        return
    if b"\0" in raw[:4096]:
        yield "retail-blob", 0, f"binary content in a non-binary extension ({size} bytes)"
        return
    text = raw.decode("utf-8", "replace")
    if ext in (".s", ".dis"):
        head = text.splitlines()[:40]
        if sum(1 for l in head if R_DISASM_LINE.match(l)) >= 3 or "file format elf32" in text[:400]:
            yield "retail-blob", 1, "disassembly listing (address column)"
    for rule, rx in (("abs-path", R_ABS), ("private-ip", R_IP), ("token", R_TOKEN), ("name", R_NAME)):
        for m in rx.finditer(text):
            yield rule, text.count("\n", 0, m.start()) + 1, m.group(0)
    for m in R_EMAIL.finditer(text):
        if not ALWAYS_OK_EMAIL.search(m.group(0)):
            yield "email", text.count("\n", 0, m.start()) + 1, m.group(0)
    for rx in (R_HEXWORDS, R_HEXRUN):
        m = rx.search(text)
        if m:
            yield "retail-hex", text.count("\n", 0, m.start()) + 1, m.group(0).strip()[:60]
            break


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
    ap.add_argument("--allowlist", default=None)
    ap.add_argument("--no-allowlist", action="store_true")
    ap.add_argument("--list-allowed", action="store_true")
    ap.add_argument("--max-bytes", type=int, default=1 << 20)
    ap.add_argument("--deep", action="store_true")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args(argv)
    root = os.path.abspath(a.root)
    if not os.path.isdir(root):
        print(f"no such directory: {root}", file=sys.stderr)
        return 2
    al_path = None if a.no_allowlist else (a.allowlist or os.path.join(root, "tools", "prepublish_allowlist.txt"))
    ents = load_allowlist(al_path)
    findings, hidden, per_rule = [], [], {}
    files = tracked_files(root)
    for rel in files:
        seen = set()
        for rule, line, text in scan_file(root, rel, a.max_bytes, a.deep):
            key = (rule, text)
            if key in seen:
                continue
            seen.add(key)
            rec = {"rule": rule, "path": rel, "line": line, "text": text[:100]}
            if allowed(ents, rule, rel, text):
                hidden.append(rec)
            else:
                findings.append(rec)
                per_rule[rule] = per_rule.get(rule, 0) + 1
    if a.json:
        json.dump({"files": len(files), "findings": findings, "allowlisted": len(hidden)}, sys.stdout, indent=1)
        print()
    else:
        for r in findings:
            print(f"{r['rule']:<11} {r['path']}:{r['line']}: {r['text']}")
        if a.list_allowed:
            for r in hidden:
                print(f"(allowed) {r['rule']:<11} {r['path']}:{r['line']}: {r['text']}")
        print(f"prepublish_scan: {len(files)} files, {len(findings)} finding(s)"
              + (" [" + ", ".join(f"{k}={v}" for k, v in sorted(per_rule.items())) + "]" if per_rule else "")
              + f", {len(hidden)} allowlisted", file=sys.stderr)
    return 1 if findings else 0


if __name__ == "__main__":
    sys.exit(main())
