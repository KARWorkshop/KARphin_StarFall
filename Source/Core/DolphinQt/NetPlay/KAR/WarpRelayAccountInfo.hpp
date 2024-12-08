#pragma once

//defines a custom window for KAR Warp Relay Account info

#include <QDialog>

#include <Core/KAR/WarpRelay\WarpRelayAccountManager.hpp>

//class QCheckBox;
//class QComboBox;
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

  //void CreateMainLayout();
  //void ConnectWidgets();
  //void PopulateGameList();
  //void ResetTraversalHost();
  //
  //void SaveSettings();
  //
  //void OnConnectionTypeChanged(int index);
  //
  //// Main Widget
  //QDialogButtonBox* m_close_button;
  //QComboBox* m_connection_type;
  //QLineEdit* m_nickname_edit;

  QVBoxLayout* m_main_layout;

  //common
  QComboBox* accounts_Dropdown;

  //info
  QLabel* displayName_Label;
  QLineEdit* displayName_EditFeild;
  QLabel* guestNotfication_Label;

  //network tab

  //linked accounts tab

  //QTabWidget* m_tab_widget;
  //QPushButton* m_reset_traversal_button;
  //
  //// Connection Widget
  //QLabel* m_ip_label;
  //QLineEdit* m_ip_edit;
  //QLabel* m_connect_port_label;
  //QSpinBox* m_connect_port_box;
  //QPushButton* m_connect_button;
  //
  //// Host Widget
  //QLabel* m_host_port_label;
  //QSpinBox* m_host_port_box;
  //QListWidget* m_host_games;
  //QPushButton* m_host_button;
  //QCheckBox* m_host_force_port_check;
  //QSpinBox* m_host_force_port_box;
  //QCheckBox* m_host_chunked_upload_limit_check;
  //QSpinBox* m_host_chunked_upload_limit_box;
  //QCheckBox* m_host_server_browser;
  //QLineEdit* m_host_server_name;
  //QLineEdit* m_host_server_password;
  //QComboBox* m_host_server_region;

};

}