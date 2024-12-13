#pragma once

//defines a general tab for all KAR Settings

#include <QDialog>

#include <Core/KAR/KARBootData.hpp>

class QCheckBox;
 class QComboBox;
class QDialogButtonBox;
 class QLabel;
class QLineEdit;
class QCloseEvent;
// class QListWidget;
class QGridLayout;
class QPushButton;
// class QSpinBox;
// class QTabWidget;
class QLabel;

namespace KAR::Core
{

class KARSettingsWidget : public QWidget
{

public:
  explicit KARSettingsWidget(std::string game_id);
  ~KARSettingsWidget() override;

//  void AddCode(ActionReplay::ARCode code);
//
signals:
  void OpenGeneralSettings();
//#ifdef USE_RETRO_ACHIEVEMENTS
//  void OpenAchievementSettings();
//#endif  // USE_RETRO_ACHIEVEMENTS
//
//private:
//  void OnSelectionChanged();
//  void OnItemChanged(QListWidgetItem* item);
//  void OnContextMenuRequested();
//
  void CreateWidgets();
  void ConnectWidgets();
//  void UpdateList();
//  void SaveCodes();
//  void SortAlphabetically();
//  void SortEnabledCodesFirst();
//  void SortDisabledCodesFirst();
//
//  void OnCodeAddClicked();
//  void OnCodeEditClicked();
//  void OnCodeRemoveClicked();
//
//  void OnListReordered();\
//

  //when one of the custom drop down changes
  void OnDropDownChanged();

  KAR::Boot::KARSettings settings;

  std::string m_game_id;
  //QComboBox* m_FS_type;
  QComboBox* m_defaultBootScreen_type;
  //QCheckBox* m_shouldMemCardAutoChange_checkbox;
  //  u16 m_game_revision;
//
//  CheatWarningWidget* m_warning;
//#ifdef USE_RETRO_ACHIEVEMENTS
//  HardcoreWarningWidget* m_hc_warning;
//#endif  // USE_RETRO_ACHIEVEMENTS
//  QListWidget* m_code_list;
//  QPushButton* m_code_add;
//  QPushButton* m_code_edit;
//  QPushButton* m_code_remove;
//
//  std::vector<ActionReplay::ARCode> m_ar_codes;
//  bool m_restart_required;
};
}