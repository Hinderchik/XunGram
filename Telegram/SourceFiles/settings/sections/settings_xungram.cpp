/*
This file is part of XunGram,
a Telegram desktop client with an open plugin system.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "settings/sections/settings_xungram.h"

#include "extra/extra.h"
#include "lang/lang_keys.h"
#include "settings/settings_common.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/checkbox.h"
#include "ui/wrap/slide_wrap.h"
#include "ui/wrap/vertical_layout.h"
#include "window/window_session_controller.h"
#include "styles/style_settings.h"

namespace Settings {

void SetupXunGramSection(
		not_null<Ui::VerticalLayout*> container,
		not_null<Window::SessionController*> controller) {

	const auto title = Ui::CreateChild<Ui::SlideWrap<Ui::VerticalLayout>>(
		container.get(),
		object_ptr<Ui::VerticalLayout>(container.get()));

	title->setDuration(0);
	{ // Title
		const auto &st = st::settingsTitle;
		Ui::AddSubsectionTitle(
			title->entity(),
			tr::lng_xungram_title(tr::now));
	}

	{ // Ghost Mode Toggle
		const auto ghostMode = Ui::AddSkip(
			title->entity(),
			st::settingsGhostModePadding);

		const auto checkbox = Ui::CreateChild<Ui::Checkbox>(
			ghostMode,
			u"Ghost Mode"_q,
			false);

		checkbox->setChecked(
			Core::App().settings().xungramGhostMode());

		Ui::Connect(checkbox, &Ui::Checkbox::changed, [=](bool checked) {
			Core::App().settings().setXunGramGhostMode(checked);
			Core::App().saveSettings();
		});

		Ui::AddInfo(
			title->entity(),
			tr::lng_xungram_ghost_mode_desc(tr::now),
			st::settingsGhostModeAbout);
	}

	{ // Plugin Engine Status
		const auto pluginStatus = Ui::AddSkip(
			title->entity(),
			st::settingsPluginStatusPadding);

		Ui::AddSubsectionTitle(
			pluginStatus,
			tr::lng_xungram_plugin_engine(tr::now));

		Ui::AddInfo(
			pluginStatus,
			tr::lng_xungram_plugin_engine_status(tr::now),
			st::settingsPluginStatusAbout);
	}

	container->add(std::move(title));
}

} // namespace Settings
