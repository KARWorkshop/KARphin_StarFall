#pragma once

//defines a custom window for KAR Warp Relay Account info

#include <QDialog>

//#include <Core/KAR/WarpRelay\WarpRelayAccountManager.hpp>

//class QCheckBox;
class QComboBox;
class QDialogButtonBox;
//class QLabel;
class QLineEdit;
class QCloseEvent;
    //class QListWidget;
class QGridLayout;
class QPushButton;
//class QSpinBox;
//class QTabWidget;
class QLabel;
class QVBoxLayout;

namespace KAR::WarpRelay
{
class AccountInfoDialog : public QDialog
{
 // Q_OBJECT
public:
  explicit AccountInfoDialog(QWidget* parent);

  void closeEvent(QCloseEvent* event) override;

//signals:
 // bool Join();
 // bool Host(const UICommon::GameFile& game);

private:

  //when the Account is changed
  void OnAccountChanged(int index);

  //when the preset icon is changed
  void OnPresetIconChanged(int index);

  //changes all the GUI to be what we use for a guest account
  void OnGUIChange_GuestAccount();

  //changes all the GUI to be what we use for a non-guest account
  void OnGUIChange_WarpRelayAccount();

  //updates the image we render
  void UpdateAccountIcon();

  QVBoxLayout* m_main_layout;

  //common
  QComboBox* accounts_Dropdown;

  //notification how guest accounts work or if it's not, the size of the image
  QLabel* guestNotfication_Label;

  QLabel* displayName_Label;
  QLineEdit* displayName_EditFeild;

  //account image preview
  QLabel* icon_Label;
  QLabel* icon_storage; //stores our icon

  //secondary dropdown for guests to change their default icon
  QComboBox* presetIcon_Dropdown;

  //custom url for none-guests
  QLabel* customURL_Label;
  QLineEdit* customURL_EditFeild;

  //network tab

  //linked accounts tab

};

}