#!/usr/bin/env python3
"""Check local Markdown links without reading the disc, build tree or network.

Defaults to the public entry points and reader guides. Pass specific files or
documentation directories to widen the scope; historical evidence is opt-in.
"""
from __future__ import annotations

import argparse
from dataclasses import dataclass
from html import unescape
from pathlib import Path
import re
from urllib.parse import unquote, urlsplit

MAX_BYTES = 4 * 1024 * 1024
INLINE = re.compile(
    r'!?\[[^\]\n]*\]\(\s*(?:<([^>\n]*)>|((?:\\.|[^()\s]|\([^()\n]*\))+))'
    r'(?:\s+[\'\"][^\n]*?[\'\"])?\s*\)'
)
DEFINITION = re.compile(
    r'^ {0,3}\[([^\]\n]+)\]:\s*(?:<([^>\n]+)>|(\S+))', re.M
)
REFERENCE = re.compile(r'!?\[([^\]\n]+)\](?:\[([^\]\n]*)\])?')
HTML_LINK = re.compile(r'<(?:a|img)\b[^>]*?\b(?:href|src)=[\'\"]([^\'\"]+)[\'\"]', re.I)


def prose(text: str) -> str:
    """Mask code and comments, retaining newlines for diagnostics."""
    lines = []
    fence = None
    for line in text.splitlines(keepends=True):
        marker = re.match(r'^ {0,3}(`{3,}|~{3,})(.*)', line)
        if fence:
            if marker and marker[1][0] == fence[0] and len(marker[1]) >= len(fence) and not marker[2].strip():
                fence = None
            lines.append('\n' if line.endswith('\n') else '')
        elif marker:
            fence = marker[1]
            lines.append('\n' if line.endswith('\n') else '')
        elif line.startswith(('    ', '\t')):
            lines.append('\n' if line.endswith('\n') else '')
        else:
            lines.append(line)
    result = ''.join(lines)
    result = re.sub(r'<!--.*?-->', lambda m: '\n' * m[0].count('\n'), result, flags=re.S)
    return re.sub(r'(`+)(?!`)(.*?)\1(?!`)', lambda m: ' ' * len(m[0]), result)


def links(text: str):
    """Yield (line, destination), including reference and HTML links."""
    visible = prose(text)
    definitions = {}
    for match in DEFINITION.finditer(visible):
        target = match[2] if match[2] is not None else match[3]
        definitions[' '.join(match[1].lower().split())] = target
        yield visible.count('\n', 0, match.start()) + 1, target
    for pattern in (INLINE, HTML_LINK):
        for match in pattern.finditer(visible):
            target = next(v for v in match.groups() if v is not None)
            yield visible.count('\n', 0, match.start()) + 1, target
    # Preserve offsets while removing inline links and reference definitions.
    residual = visible
    for pattern in (INLINE, DEFINITION, HTML_LINK):
        residual = pattern.sub(lambda m: re.sub(r'[^\n]', ' ', m[0]), residual)
    for match in REFERENCE.finditer(residual):
        key = ' '.join((match[2] or match[1]).lower().split())
        if key in definitions:
            yield residual.count('\n', 0, match.start()) + 1, definitions[key]
        elif match[2] is not None:
            # An unresolved explicit reference is a broken link too.
            yield residual.count('\n', 0, match.start()) + 1, 'unresolved-reference:' + key


def anchors(text: str) -> set[str]:
    """GitHub-style heading slugs, duplicate suffixes, and explicit HTML IDs."""
    result = set(re.findall(r'\b(?:id|name)=[\'\"]([^\'\"]+)[\'\"]', prose(text)))
    used = set()
    # Headings retain inline code text, unlike ordinary link extraction.
    lines = text.splitlines()
    fence = None
    for index, line in enumerate(lines):
        marker = re.match(r'^ {0,3}(`{3,}|~{3,})(.*)', line)
        if marker:
            if fence is None:
                fence = marker[1]
            elif marker[1][0] == fence[0] and len(marker[1]) >= len(fence) and not marker[2].strip():
                fence = None
            continue
        if fence:
            continue
        heading = re.match(r'^ {0,3}#{1,6}\s+(.+?)(?:\s+#+)?\s*$', line)
        setext = index + 1 < len(lines) and re.fullmatch(r' {0,3}(?:=+|-+)\s*', lines[index + 1])
        if not heading and (not setext or not line.strip()):
            continue
        title = heading[1] if heading else line.strip()
        title = re.sub(r'!?\[([^\]]+)\]\([^)]*\)', r'\1', title)
        title = unescape(re.sub(r'<[^>]+>', '', title)).lower()
        slug = re.sub(r'[^\w\- ]', '', title).replace(' ', '-')
        candidate, suffix = slug, 0
        while candidate in used:
            suffix += 1
            candidate = f'{slug}-{suffix}'
        used.add(candidate)
        result.add(candidate)
    return result


@dataclass(frozen=True)
class Problem:
    path: str
    line: int
    target: str
    reason: str


def check(root: Path, paths: list[Path]) -> tuple[int, list[Problem]]:
    root = root.resolve()
    problems = []
    checked = 0
    cache = {}
    for path in sorted(set(paths)):
        path = path.resolve()
        label = path.relative_to(root).as_posix() if path.is_relative_to(root) else path.name
        if not path.is_relative_to(root) or not path.is_file() or path.stat().st_size > MAX_BYTES:
            problems.append(Problem(label, 1, '', 'input missing, outside root, or over 4 MiB'))
            continue
        for line, target in links(path.read_text(encoding='utf-8')):
            target = unescape(re.sub(r'\\([() ])', r'\1', target))
            if target.startswith('unresolved-reference:'):
                problems.append(Problem(label, line, target, 'undefined reference'))
                continue
            parts = urlsplit(target)
            if parts.scheme or parts.netloc:
                continue
            checked += 1
            destination = (path.parent / unquote(parts.path)).resolve() if parts.path else path
            if not destination.is_relative_to(root):
                reason = 'target escapes repository'
            elif not destination.exists():
                reason = 'missing target'
            elif parts.fragment:
                fragment = unquote(parts.fragment)
                if not destination.is_file() or destination.stat().st_size > MAX_BYTES:
                    reason = 'fragment target is not a file under 4 MiB'
                else:
                    if destination not in cache:
                        contents = destination.read_text(encoding='utf-8')
                        cache[destination] = (len(contents.splitlines()), anchors(contents))
                    line_count, ids = cache[destination]
                    source_line = re.fullmatch(r'L([1-9]\d*)(?:-L([1-9]\d*))?', fragment)
                    if source_line:
                        start, end = int(source_line[1]), int(source_line[2] or source_line[1])
                        reason = '' if 1 <= start <= end <= line_count else 'source line out of range'
                    else:
                        reason = '' if fragment in ids else 'missing anchor'
            else:
                reason = ''
            if reason:
                problems.append(Problem(label, line, target, reason))
    return checked, problems


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('paths', nargs='*', help='repository-relative files or documentation directories')
    args = parser.parse_args(argv)
    root = args.root.resolve()
    inputs = args.paths or ['README.md', 'docs/README.md', 'docs/guide']
    paths = []
    for item in inputs:
        path = root / item
        if path.is_dir():
            paths.extend(path.rglob('*.md'))
        else:
            paths.append(path)
    checked, problems = check(root, paths)
    for problem in problems:
        print(f'{problem.path}:{problem.line}: {problem.reason}: {problem.target}')
    print(f'{len(set(paths))} Markdown files; {checked} local links; {len(problems)} errors')
    return int(bool(problems))


if __name__ == '__main__':
    raise SystemExit(main())
