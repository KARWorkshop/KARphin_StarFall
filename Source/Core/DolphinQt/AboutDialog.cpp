// Copyright 2016 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DolphinQt/AboutDialog.h"

#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QtGlobal>

#include "Common/Version.h"

#include "DolphinQt/Resources.h"

#include <KARphin/Version.hpp>

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent)
{
  setWindowTitle(tr("About KARphin"));
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  const QString text =
      QStringLiteral(R"(
<p style='font-size:38pt; font-weight:400;'>KARphin</p>

<p style='font-size:18pt;'>%VERSION_STRING%</p>

<p style='font-size: small;'>
%CHNAGE_LOG%<br>
</p>

<p>
KARphin is a free and open-source Kirby Air Ride emulator.
</p>

<p>
This software should not be used to play Kirby Air Ride ROMs you do not legally own.
</p>
)")
          .replace(QStringLiteral("%VERSION_STRING%"),
                   QString::fromStdString(KAR::Version::GetVersionString_Full()))
          .replace(QStringLiteral("%CHNAGE_LOG%"),
                   // i18n: "Branch" means the version control term, not a literal tree branch.
                   tr("%1").arg(QString::fromStdString(KARPHIN_CHANGE_LOG)));

  QLabel* text_label = new QLabel(text);
  text_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
  text_label->setOpenExternalLinks(true);

  QLabel* copyright = new QLabel(
      QStringLiteral("<small>%1</small>")
          .arg(
              // i18n: This message uses curly quotes in English. If you want to use curly quotes
              // in your translation, please use the type of curly quotes that's appropriate for
              // your language. If you aren't sure which type is appropriate, see
              // https://en.wikipedia.org/wiki/Quotation_mark#Specific_language_features
              tr("\u00A9 2025+ Jas. \u201cGameCube\u201d and \u201cWii\u201d and \u201cKirby Air Ride\u201d are "
                 "trademarks of Nintendo. KARphin is not affiliated with Nintendo in any way.")));

  QLabel* logo = new QLabel();
  logo->setPixmap(Resources::GetAppIcon().pixmap(200, 200));
  logo->setContentsMargins(30, 0, 30, 0);

  QVBoxLayout* main_layout = new QVBoxLayout;
  QHBoxLayout* h_layout = new QHBoxLayout;

  setLayout(main_layout);
  main_layout->addLayout(h_layout);
  main_layout->addWidget(copyright);
  copyright->setAlignment(Qt::AlignCenter);
  copyright->setContentsMargins(0, 15, 0, 0);

  h_layout->setAlignment(Qt::AlignLeft);
  h_layout->addWidget(logo);
  h_layout->addWidget(text_label);
}
