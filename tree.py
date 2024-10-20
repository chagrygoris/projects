import dataclasses
import os
import sys
from argparse import ArgumentParser, Namespace
from pathlib import Path
from typing import List


def check_empty_dir(path:Path) -> bool:
    res = True
    def iterate(path:Path):
        nonlocal res
        if path.is_symlink(): return
        if path.is_file() and not path.is_symlink():
            res = False
            return
        for p in path.iterdir():
            iterate(p)
    iterate(path)
    return res

def contains_empty_ext(path:Path):
    res = False
    def iterate(path:Path):
        nonlocal res
        if path.is_symlink(): return
        if path.is_file() and not path.is_symlink() and not path.suffixes:
            res = True
            return
        for p in path.iterdir():
            iterate(p)
    iterate(path)
    return res

def contains_usual_ext(path:Path, extensions:List[str]) -> bool:
    res = False
    def iterate(path:Path):
        nonlocal res
        if path.is_symlink(): return
        if path.is_file() and not path.is_symlink() and any(str(path).endswith(e) for e in extensions):
            res = True
            return
        if path.is_dir():
            for p in path.iterdir():
                iterate(p)
    iterate(path)
    return res

def check_extension(path:Path, extension:List[str]):
    if '' in extension and len(extension) == 1:
        return contains_empty_ext(path)
    elif '' in extension:
        return contains_empty_ext(path) or contains_usual_ext(path, extension[1:])
    else:
        return contains_usual_ext(path, extension)


@dataclasses.dataclass
class RecursionSettings:
    """Настройки рекурсии."""
    path:Path = Path('.')
    depth:int = 1000000000
    prune:bool = False
    indent:int = 4
    output:Path = Path()
    extension:list[str] = dataclasses.field(default_factory=list)
    def __init__(self, **kwargs):
        for ka, kv in kwargs.items():
            self.__setattr__(ka, kv)
        if self.extension: self.prune = True
        if not self.indent: self.indent = 4
        if self.extension:
            self.extension = sorted(list(map(lambda x : '.' + x if x and x[0] != '.' else x, self.extension)))
        self.path = Path(os.path.normpath(str(Path(self.path))))
        if self.output: self.output = Path(self.output)


def get_parser() -> ArgumentParser:
    """Получить парсер аргументов командной строки."""
    ap = ArgumentParser(
        prog='tree',
        description='tree. Выводит представление файловой системы в виде дерева'
    )
    ap.add_argument('path', type=str, default='.', nargs='?')
    ap.add_argument('-p', '--prune', action='store_true', default=False)
    ap.add_argument('-d', '--depth', action='store', type=int, default=1e9)
    ap.add_argument('-i', '--indent', type=int, metavar='N', default=4)
    ap.add_argument('-o', '--output', type=str, metavar='FILE')
    ap.add_argument('-e', '--extension', action='append', type=str)
    return ap


def has_valid_args(args: Namespace) -> tuple[bool, str | None]:
    """Проверить, что аргументы валидны."""
    try:
        args.path = os.path.normpath(args.path)
        Path(args.path)
    except Exception:
        raise ArgumentParser.error(self=get_parser(), message='invalid path')
    if not args.path or not Path(args.path).exists() or not Path(args.path).is_dir():
        raise ArgumentParser.error(self=get_parser(), message='invalid path -- not exists')
    if args.depth and (args.depth < 0):
        raise SystemExit(2)
    if args.indent is not None and (args.indent <= 0):
        sys.stderr.write(get_parser().format_help() + '\n' + 'tree: error: indent should be positive')
        raise SystemExit(2)
    if args.output is not None and (Path(args.output).is_dir() or Path(args.output).is_symlink()):
        sys.stderr.write(get_parser().format_help() + '\n' + 'tree: error: output file should be a file, not a directory nor symlink')
        raise SystemExit(2)
    return (True, None)


def get_extension(path: Path) -> str:
    """Получить расширение файла (возможно, пустое)."""
    if not path.suffixes:
        return ''
    return ''.join(path.suffixes)

def tree(path: Path, settings: RecursionSettings) -> None:
    """Вывести файловое древо."""
    if settings.output:
        settings.output.touch(exist_ok=True)
    res = f'''{str(path.absolute())}/\n'''
    def iterate(path:Path, depth:int) -> None:
        nonlocal res
        for p in sorted(list(path.iterdir()), key=lambda x : (not x.is_dir(), str(x))):
            if not p.is_dir() and not p.is_file() or p.is_symlink():
                continue
            if settings.prune and p.is_dir() and check_empty_dir(p):
                continue
            elif settings.extension and p.is_dir() and not check_extension(p, settings.extension):
                continue
            elif settings.extension and p.is_file() and get_extension(p) not in settings.extension:
                continue
            res += f"{' ' * settings.indent * depth}{str(p.relative_to(path))}"
            if p.is_dir():
                res += '/'
            res += '\n'
            if p.is_dir() and depth < settings.depth:
                iterate(p, depth + 1)
    if settings.depth > 0:
        iterate(path, 1)
    res = res.strip()
    if settings.output:
        with open(settings.output, 'w') as f:
            f.write(res + '\n')
    else:
        print(res)

def main(argv: list[str] | None = None) -> None:
    """Запустить консольную утилиту."""
    nsps = get_parser().parse_args(argv)
    if nsps.path == None:
        nsps.path = Path('./')
    has_valid_args(nsps)
    settings = RecursionSettings(**get_parser().parse_args(argv).__dict__)
    tree(settings.path, settings)

if __name__ == "__main__":
    main(sys.argv[1:])