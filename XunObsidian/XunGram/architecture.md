---
tags: [xungram, architecture]
---
# Архитектура

Связь: [[XunGram]] · слой кода → [[Слой Extra]] · стыки → [[Швы]] · движок → [[Движок плагинов]].

## Принцип
Форк [[tdesktop]] + **изолированный слой** `extra/`, который регулярно мержится с upstream.
Плагины на Python работают **в процессе** (без песочницы) с максимальной властью.

## Слои
```mermaid
graph TD
  UI[Qt UI / tdesktop] --> HOOKS[Extra::Hooks]
  HOOKS --> ENGINE[Host::Engine]
  ENGINE --> PY[Python плагины]
  PY --> SDK[xungram SDK]
  ENGINE --> MAN[Host::Manifest]
  subgraph Слой Extra
    HOOKS
    ENGINE
    MAN
  end
  subgraph Upstream tdesktop
    UD[api/ core/ ...]
  end
  UD --> HOOKS
```

## Подход C (гибрид)
- Hot-path фичи — на C++ (производительность).
- Кастомизация — Python-плагинами через публичный API v1.

## Раскладка
```
tdesktop/Telegram/SourceFiles/extra/
  extra.h / extra.cpp     # Extra::Initialize()
  seam/                   # швы в upstream (hooks)
  host/                   # манифесты + движок
  features/               # C++ фичи (позже)
  ui/                     # UI-менеджер плагинов (позже)
```

## Связанные заметки
- [[Слой Extra]]
- [[Движок плагинов]]
- [[Швы]]
- [[Вехи]]
