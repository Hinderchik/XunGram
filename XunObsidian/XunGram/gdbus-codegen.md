---
tags: [xungram, build, deps]
---
# gdbus-codegen

Часть [[Внешние зависимости]]. Кодогенератор D-Bus C-обвязки из GObject
Introspection. Нужен tdesktop на Linux: `generate_dbus()` в
`cmake/external/glib/generate_dbus.cmake` вызывает его для порталов, a11y,
MPRIS и т.п. (см. [[Исправления сборки]]).

## Проблема
В GLib 2.90 `gdbus-codegen` больше не поставляется: его нет ни в Arch
(`glib2`, `glib2-devel`), ни в AUR. Поэтому CMake падал с
`Could not find DESKTOP_APP_GDBUSCODEGEN`.

## Решение
Инструмент — чистый Python. Взят из исходников GLib (тег 2.82.2) и разложен
в стандартную схему в `.deps/gdbus-codegen`:

```
.deps/gdbus-codegen/
  bin/gdbus-codegen              # launcher (из gdbus-codegen.in)
  share/glib-2.0/codegen/        # python-пакет codegen
```

Версия в `codegen/config.py`: 2.82.2. Подключается через
`-D DESKTOP_APP_GDBUSCODEGEN=/home/xunkal1/telegram-client/.deps/gdbus-codegen/bin/gdbus-codegen`.

Источник файлов: `github.com/GNOME/glib` →
`gio/gdbus-2.0/codegen/` (`gdbus-codegen.in`, `codegen_main.py`, `codegen.py`,
`dbustypes.py`, `parser.py`, `utils.py`, `__init__.py`, `config.py.in`).

## Связанные заметки
- [[Внешние зависимости]]
- [[Сборка нативный Arch]]
- [[Исправления сборки]]
