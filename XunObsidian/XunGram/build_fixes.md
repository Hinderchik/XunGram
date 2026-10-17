---
tags: [xungram, build, fixes]
---
# Исправления сборки

Ошибки нативной сборки на Arch и как починены. Связь: [[Сборка нативный Arch]].

```mermaid
graph LR
  B[Boost missing] --> F1[install boost] --> N[nasm/perl-xml-parser] --> F2[install] --> T[tde2e missing] --> F3[build tdlib/td E2E] --> W[wallet_engine missing] --> F4[build Rust crate] --> O[tg_owt missing] --> F5[build tg_owt] --> G[gdbus-codegen missing] --> F6[из исходников GNOME/glib] --> S[пробел в пути] --> F7[rename в telegram-client]
```

| # | Ошибка | Причина | Фикс |
|---|---|---|---|
| 1 | `Found Boost` upstream / `Could not find Boost` | нет `boost` | `pacman -S boost nasm perl-xml-parser vulkan-headers xorg-util-macros` |
| 2 | `Could not find tde2e` | нет Telegram-компонента | собрать из `tdlib/td` `TD_E2E_ONLY=ON` → [[tde2e]] |
| 3 | `Could not find DESKTOP_APP_WALLET_ENGINE_LIBRARY` | нет Rust-сборки | [[tdesktop_rust]] (rustup 1.96.1 + bindgen) |
| 4 | `Could not find tg_owt` | нет WebRTC | сборка [[tg_owt]] |
| 5 | `Could not find DESKTOP_APP_GDBUSCODEGEN` | в GLib 2.90 `gdbus-codegen` вынесен из пакета (нет в Arch и AUR) | взять чистый Python-кодогенератор из исходников `GNOME/glib` (тег 2.82.2) → `.deps/gdbus-codegen` |
| 6 | `gcc: fatal error: input file '/home/xunkal1/telegram' is the same as output file` (шаг GIR) | пробел в пути; `os.getcwd()` канонизирует symlink, `libtool`/`gcc` рвут путь | переименовать папку в `/home/xunkal1/telegram-client`, старое имя — symlink |

## Пакеты, которые реально нужны были
```
boost nasm perl-xml-parser vulkan-headers xorg-util-macros
cmake ninja ccache gperf
```
Остальное (Qt6, ffmpeg, openssl, …) уже стояло — из-за установленного `telegram-desktop`.

## Приёмы
- Всё кладём в `.deps/<name>` и передаём через `CMAKE_PREFIX_PATH` (без sudo).
- `libselinux` в Arch нет → tg_owt собирается без SELinux (не критично).
- `gdbus-codegen` в GLib 2.90 больше не поставляется. Собран вручную из исходников
  `GNOME/glib@2.82.2` (`gio/gdbus-2.0/codegen`), разложен в стандартную схему
  `bin/gdbus-codegen` + `share/glib-2.0/codegen/` и передан через
  `-D DESKTOP_APP_GDBUSCODEGEN=/home/xunkal1/telegram-client/.deps/gdbus-codegen/bin/gdbus-codegen`.
- Сборка должна идти из пути **без пробелов** (`/home/xunkal1/telegram-client`).
  Symlink не помогает: `os.getcwd()` резолвит его в физический путь, и пробел
  снова ломает `g-ir-scanner`. Подробнее — [[Сборка нативный Arch]].

## Связанные заметки
- [[Внешние зависимости]]
- [[Журнал работ]]
