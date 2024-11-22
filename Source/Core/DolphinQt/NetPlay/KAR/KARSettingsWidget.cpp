#include <KAR/KARSettingsWidget.hpp>

#include "DolphinQt/QtUtils/WrapInScrollArea.h"

#include <algorithm>
#include <utility>

#include <QCursor>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include <qcheckbox.h>

#include "Common/FileUtil.h"
#include "Common/IniFile.h"

#include "Core/ActionReplay.h"
#include "Core/ConfigManager.h"

#include "DolphinQt/Config/CheatCodeEditor.h"
#include "DolphinQt/Config/CheatWarningWidget.h"
#include "DolphinQt/Config/HardcoreWarningWidget.h"
#include "DolphinQt/QtUtils/NonDefaultQPushButton.h"
#include "DolphinQt/QtUtils/SetWindowDecorations.h"

#include "UICommon/GameFile.h"

KAR::Core::KARSettingsWidget::KARSettingsWidget(std::string game_id)
    : m_game_id(std::move(game_id))
{
  CreateWidgets();
  ConnectWidgets();

  if (!m_game_id.empty())
  {
    //Common::IniFile game_ini_local;

    //// We don't use LoadLocalGameIni() here because user cheat codes that are installed via the UI
    //// will always be stored in GS/${GAMEID}.ini
    //game_ini_local.Load(File::GetUserPath(D_GAMESETTINGS_IDX) + m_game_id + ".ini");

    //const Common::IniFile game_ini_default =
    //    SConfig::LoadDefaultGameIni(m_game_id, m_game_revision);
    //m_ar_codes = ActionReplay::LoadCodes(game_ini_default, game_ini_local);
  }

 // UpdateList();
 // OnSelectionChanged();
}

KAR::Core::KARSettingsWidget::~KARSettingsWidget() = default;

void KAR::Core::KARSettingsWidget::CreateWidgets()
{
  QGridLayout* layout = new QGridLayout();

  //the FS screen code to use
  m_FS_type = new QComboBox();

  //m_FS_type->addItem(tr("Auto")); //expermental
  m_FS_type->addItem(tr("None")); //sets no screen code

  //core single person screen
  m_FS_type->addItem(tr("Single: Port 1"));
  m_FS_type->addItem(tr("Single: Port 2"));
  m_FS_type->addItem(tr("Single: Port 3"));
  m_FS_type->addItem(tr("Single: Port 4"));

  //shows multiable screens screen
  m_FS_type->addItem(tr("Multi-Screen: Port 1 and 2"));
  m_FS_type->addItem(tr("Multi-Screen: Port 3 and 4"));
  m_FS_type->addItem(tr("Multi-Screen: Port 1, 2, and 3"));
  m_FS_type->addItem(tr("Multi-Screen: Port 2, 3, and 4"));


  m_FS_type->setToolTip(tr("Sets the Fullscreen code\n\nPort 1-4 are for seeing one perspective for the full screen. "
                           "This must match the port you are set as in Netplay. You can check this under your GC Mapping or have your port manually set via the "
                           "Assign Controller Ports. If for example you are set to Port 4, you would select Port 4 in the drop down. That way you only see yourself and none of the split screen.\n\n"
                           "The Multi-Screen codes show several ports at once. Theses are mainly used for local play or netplay, while having two or more of thoses 3+ players on the same machine.\n\n"
                           "None tells KARphin to not use any screen codes. This will result in a normal split screen.\n\n"));
  
  layout->addWidget(new QLabel(tr("Screen Code")), 0, 0);
  layout->addWidget(m_FS_type, 0, 1);

  //sets the default boot screen
  m_defaultBootScreen_type = new QComboBox();
  m_defaultBootScreen_type->addItem(tr("Debug/Settings Menu"));
  m_defaultBootScreen_type->addItem(tr("Main Menu"));
  m_defaultBootScreen_type->setToolTip(
      tr("Sets which screen to boot into, uses a modified version of the Skip To Main Menu code."));

  layout->addWidget(new QLabel(tr("Default Boot Screen")), 1, 0);
  layout->addWidget(m_defaultBootScreen_type, 1, 1);

  /*m_shouldMemCardAutoChange_checkbox = new QCheckBox(tr("should memory cards auto-change to match game"));
  m_shouldMemCardAutoChange_checkbox->setChecked(true);
  m_shouldMemCardAutoChange_checkbox->setToolTip(tr(
      "If set to true, KARphin will auto-change the memory card in use to one matching the game. "
      "This can cause desyncs when users have inconsistant memory card data. So KARphin defaults "
      "Memory cards to be off. But if memory card reading and writing is enabled. "
      "And this option is enabled, KARphin will auto-create memory cards.\n\n(Memory Card Writing "
      "must be set to enable)"));
  layout->addWidget(m_shouldMemCardAutoChange_checkbox, 2, 0);*/

  WrapInScrollArea(this, layout);
}

void KAR::Core::KARSettingsWidget::ConnectWidgets()
{
 // connect(m_FS_type, &QComboBox::currentIndexChanged, this,
 //         &NetPlaySetupDialog::OnConnectionTypeChanged);

//  connect(m_warning, &CheatWarningWidget::OpenCheatEnableSettings, this,
//          &ARCodeWidget::OpenGeneralSettings);
//#ifdef USE_RETRO_ACHIEVEMENTS
//  connect(m_hc_warning, &HardcoreWarningWidget::OpenAchievementSettings, this,
//          &ARCodeWidget::OpenAchievementSettings);
//#endif  // USE_RETRO_ACHIEVEMENTS
//
//  connect(m_code_list, &QListWidget::itemChanged, this, &ARCodeWidget::OnItemChanged);
//  connect(m_code_list, &QListWidget::itemSelectionChanged, this, &ARCodeWidget::OnSelectionChanged);
//  connect(m_code_list->model(), &QAbstractItemModel::rowsMoved, this,
//          &ARCodeWidget::OnListReordered);
//  connect(m_code_list, &QListWidget::customContextMenuRequested, this,
//          &ARCodeWidget::OnContextMenuRequested);
//
//  connect(m_code_add, &QPushButton::clicked, this, &ARCodeWidget::OnCodeAddClicked);
//  connect(m_code_edit, &QPushButton::clicked, this, &ARCodeWidget::OnCodeEditClicked);
//  connect(m_code_remove, &QPushButton::clicked, this, &ARCodeWidget::OnCodeRemoveClicked);
}
//
//void ARCodeWidget::OnItemChanged(QListWidgetItem* item)
//{
//  m_ar_codes[m_code_list->row(item)].enabled = (item->checkState() == Qt::Checked);
//
//  if (!m_restart_required)
//    ActionReplay::ApplyCodes(m_ar_codes);
//
//  UpdateList();
//  SaveCodes();
//}
//
//void ARCodeWidget::OnContextMenuRequested()
//{
//  QMenu menu;
//
//  menu.addAction(tr("Sort Alphabetically"), this, &ARCodeWidget::SortAlphabetically);
//  menu.addAction(tr("Show Enabled Codes First"), this, &ARCodeWidget::SortEnabledCodesFirst);
//  menu.addAction(tr("Show Disabled Codes First"), this, &ARCodeWidget::SortDisabledCodesFirst);
//
//  menu.exec(QCursor::pos());
//}
//
//void ARCodeWidget::SortAlphabetically()
//{
//  m_code_list->sortItems();
//  OnListReordered();
//}
//
//void ARCodeWidget::SortEnabledCodesFirst()
//{
//  std::stable_sort(m_ar_codes.begin(), m_ar_codes.end(), [](const auto& a, const auto& b) {
//    return a.enabled && a.enabled != b.enabled;
//  });
//
//  UpdateList();
//  SaveCodes();
//}
//
//void ARCodeWidget::SortDisabledCodesFirst()
//{
//  std::stable_sort(m_ar_codes.begin(), m_ar_codes.end(), [](const auto& a, const auto& b) {
//    return !a.enabled && a.enabled != b.enabled;
//  });
//
//  UpdateList();
//  SaveCodes();
//}
//
//void ARCodeWidget::OnListReordered()
//{
//  // Reorder codes based on the indices of table item
//  std::vector<ActionReplay::ARCode> codes;
//  codes.reserve(m_ar_codes.size());
//
//  for (int i = 0; i < m_code_list->count(); i++)
//  {
//    const int index = m_code_list->item(i)->data(Qt::UserRole).toInt();
//
//    codes.push_back(std::move(m_ar_codes[index]));
//  }
//
//  m_ar_codes = std::move(codes);
//
//  SaveCodes();
//}
//
//void ARCodeWidget::OnSelectionChanged()
//{
//  auto items = m_code_list->selectedItems();
//
//  if (items.empty())
//    return;
//
//  const auto* selected = items[0];
//
//  bool user_defined = m_ar_codes[m_code_list->row(selected)].user_defined;
//
//  m_code_remove->setEnabled(user_defined);
//  m_code_edit->setText(user_defined ? tr("&Edit Code...") : tr("Clone and &Edit Code..."));
//}
//
//void ARCodeWidget::UpdateList()
//{
//  m_code_list->clear();
//
//  for (size_t i = 0; i < m_ar_codes.size(); i++)
//  {
//    const auto& ar = m_ar_codes[i];
//    auto* item = new QListWidgetItem(QString::fromStdString(ar.name)
//                                         .replace(QStringLiteral("&lt;"), QChar::fromLatin1('<'))
//                                         .replace(QStringLiteral("&gt;"), QChar::fromLatin1('>')));
//
//    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
//                   Qt::ItemIsDragEnabled);
//    item->setCheckState(ar.enabled ? Qt::Checked : Qt::Unchecked);
//    item->setData(Qt::UserRole, static_cast<int>(i));
//
//    m_code_list->addItem(item);
//  }
//
//  m_code_list->setDragDropMode(QAbstractItemView::InternalMove);
//}
//
//void ARCodeWidget::SaveCodes()
//{
//  if (m_game_id.empty())
//    return;
//
//  const auto ini_path =
//      std::string(File::GetUserPath(D_GAMESETTINGS_IDX)).append(m_game_id).append(".ini");
//
//  Common::IniFile game_ini_local;
//  game_ini_local.Load(ini_path);
//  ActionReplay::SaveCodes(&game_ini_local, m_ar_codes);
//  game_ini_local.Save(ini_path);
//}
//
//void ARCodeWidget::AddCode(ActionReplay::ARCode code)
//{
//  m_ar_codes.push_back(std::move(code));
//
//  UpdateList();
//  SaveCodes();
//}
//
//void ARCodeWidget::OnCodeAddClicked()
//{
//  ActionReplay::ARCode ar;
//  ar.enabled = true;
//
//  CheatCodeEditor ed(this);
//  ed.SetARCode(&ar);
//  SetQWidgetWindowDecorations(&ed);
//  if (ed.exec() == QDialog::Rejected)
//    return;
//
//  m_ar_codes.push_back(std::move(ar));
//
//  UpdateList();
//  SaveCodes();
//}
//
//void ARCodeWidget::OnCodeEditClicked()
//{
//  const auto items = m_code_list->selectedItems();
//  if (items.empty())
//    return;
//
//  const auto* const selected = items[0];
//  auto& current_ar = m_ar_codes[m_code_list->row(selected)];
//
//  CheatCodeEditor ed(this);
//  if (current_ar.user_defined)
//  {
//    ed.SetARCode(&current_ar);
//
//    SetQWidgetWindowDecorations(&ed);
//    if (ed.exec() == QDialog::Rejected)
//      return;
//  }
//  else
//  {
//    ActionReplay::ARCode ar = current_ar;
//    ed.SetARCode(&ar);
//
//    SetQWidgetWindowDecorations(&ed);
//    if (ed.exec() == QDialog::Rejected)
//      return;
//
//    m_ar_codes.push_back(std::move(ar));
//  }
//
//  SaveCodes();
//  UpdateList();
//}
//
//void ARCodeWidget::OnCodeRemoveClicked()
//{
//  auto items = m_code_list->selectedItems();
//
//  if (items.empty())
//    return;
//
//  const auto* selected = items[0];
//
//  m_ar_codes.erase(m_ar_codes.begin() + m_code_list->row(selected));
//
//  SaveCodes();
//  UpdateList();
//
//  m_code_remove->setEnabled(false);
//}
