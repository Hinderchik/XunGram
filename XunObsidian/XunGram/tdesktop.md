---
tags: [xungram, base]
---
# tdesktop

База проекта [[XunGram]] — форк Telegram Desktop.

## Факты
- Версия: **7.3.1** (`AppVersionStr`)
- Стек: C++20, Qt6
- Лицензия: GPLv3
- Официальная поддержка сборки: **только Docker** (`docs/building-linux.md`).
- Нативный путь = дистро-мейнтейнерский (`DESKTOP_APP_USE_PACKAGED`) — см. [[Сборка нативный Arch]].

## Важные файлы
- `tdesktop/Telegram/CMakeLists.txt` — блок источников [[Слой Extra|extra/*]]
- `tdesktop/Telegram/SourceFiles/core/application.cpp` — [[Швы|seam.app-startup]]
- `tdesktop/Telegram/SourceFiles/api/api_updates.cpp` — [[Швы|seam.update-dispatch]]
- `tdesktop/Telegram/build/docker/centos_env/Dockerfile` — рецепты всех [[Внешние зависимости|зависимостей]]

## Связанные заметки
- [[Архитектура]]
- [[Сборка нативный Arch]]
