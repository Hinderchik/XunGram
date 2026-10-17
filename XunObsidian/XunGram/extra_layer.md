---
tags: [xungram, cpp]
---
# Слой Extra

Часть [[Архитектура]] · точка входа `Extra::Initialize()`.

## Файлы
| Файл | Роль |
|---|---|
| `extra/extra.h`, `extra/extra.cpp` | `Extra::Initialize()`, создаёт `static Host::Engine` и запускает `initialize()` |
| `extra/seam/hooks.h/.cpp` | `Extra::Hooks::OnUpdate()` — обработчики швов |
| `extra/host/manifest.h/.cpp` | парсер `manifest.json` (Qt JSON), `kApiVersion = 1` |
| `extra/host/engine.h/.cpp` | `Engine`: поиск плагинов в `QStandardPaths::AppDataLocation + "/plugins"` |
| `extra/features/` | C++ фичи (пусто, позже) |
| `extra/ui/` | UI-менеджер плагинов (пусто, позже) |

## CMake
- Один изолированный блок `nice_target_sources(Telegram ...)` в `tdesktop/Telegram/CMakeLists.txt` (~строки 2359–2371).
- `target_include_directories(Telegram PRIVATE ${src_loc})` — строка ~2592.
- Апстрим-исходники не трогаются, кроме [[Швы|швов]].

## Связанные заметки
- [[Движок плагинов]]
- [[Швы]]
- [[Журнал работ]]
