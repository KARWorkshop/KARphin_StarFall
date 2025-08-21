// Copyright 2018 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DolphinQt/Updater.h"

#include <cstdlib>
#include <utility>

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <QVBoxLayout>

#include "Common/Version.h"

#include "DolphinQt/QtUtils/RunOnObject.h"
#include "DolphinQt/QtUtils/SetWindowDecorations.h"
#include "DolphinQt/Settings.h"

#include <KARphin/Version.hpp>

// Refer to docs/autoupdate_overview.md for a detailed overview of the autoupdate process

Updater::Updater(QWidget* parent, std::string update_track, std::string hash_override)
    : m_parent(parent), m_update_track(std::move(update_track)),
      m_hash_override(std::move(hash_override))
{
  connect(this, &QThread::finished, this, &QObject::deleteLater);
}

void Updater::run()
{
  AutoUpdateChecker::CheckForUpdate(m_update_track, m_hash_override,
                                    AutoUpdateChecker::CheckType::Automatic);
}

void Updater::CheckForUpdate()
{
  AutoUpdateChecker::CheckForUpdate(m_update_track, m_hash_override,
                                    AutoUpdateChecker::CheckType::Manual);
}

void Updater::OnUpdateAvailable(const NewVersionInformation& info)
{
  if (std::getenv("DOLPHIN_UPDATE_SERVER_URL"))
  {
    TriggerUpdate(info, AutoUpdateChecker::RestartMode::RESTART_AFTER_UPDATE);
    RunOnObject(m_parent, [this] {
      m_parent->close();
      return 0;
    });
    return;
  }

  bool updateDeps = false;

  std::optional<int> choice = RunOnObject(m_parent, [&] {
    QDialog* dialog = new QDialog(m_parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
    dialog->setWindowTitle(tr("Update available"));
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    auto* label = new QLabel(
        tr("<h2>A new version of KARphin is available!</h2>KARphin %1 is available for "
           "download. "
           "You are running %2.<br> Would you like to update?<br><h4>Release Notes:</h4>")
            .arg(QString::fromStdString(info.new_shortrev))
            .arg(QString::fromStdString(KAR::Version::GetVersionString_Full())));
    label->setTextFormat(Qt::RichText);

    auto* changelog = new QTextBrowser;

    changelog->setHtml(QString::fromStdString(info.changelog_html));
    changelog->setOpenExternalLinks(true);
    changelog->setMinimumWidth(400);

    auto* updateDepsCheck = new QCheckBox(tr("Also update KARphin dependicies?"));

    connect(updateDepsCheck, &QCheckBox::toggled, [&](bool checked) { updateDeps = checked; });

    auto* buttons = new QDialogButtonBox;

    buttons->addButton(tr("Install Update"), QDialogButtonBox::AcceptRole);

    auto* layout = new QVBoxLayout;
    dialog->setLayout(layout);

    layout->addWidget(label);
    layout->addWidget(changelog);
    layout->addWidget(updateDepsCheck);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

    SetQWidgetWindowDecorations(dialog);
    return dialog->exec();
  });

  if (choice && *choice == QDialog::Accepted)
  {
    TriggerUpdate(info, AutoUpdateChecker::RestartMode::RESTART_AFTER_UPDATE);

   RunOnObject(m_parent, [this] {
      m_parent->close();
      return 0;
    });
  }
}
