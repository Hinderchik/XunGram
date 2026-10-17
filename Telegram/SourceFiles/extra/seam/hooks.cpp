/*
This file is part of XunGram,
a Telegram desktop client with an open plugin system.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "extra/seam/hooks.h"

#include "base/debug_log.h"

namespace Extra::Hooks {

void OnUpdate() {
	static bool logged = false;
	if (!logged) {
		logged = true;
		LOG(("XunGram: update hook active"));
	}
}

} // namespace Extra::Hooks
