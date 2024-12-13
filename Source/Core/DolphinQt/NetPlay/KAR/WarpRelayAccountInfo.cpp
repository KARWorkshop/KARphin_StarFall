#include <KAR/WarpRelayAccountInfo.hpp>

#include <memory>

#include <qevent.h>
#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QTabWidget>

#include "Core/Config/NetplaySettings.h"
#include "Core/NetPlayProto.h"

#include "DolphinQt/QtUtils/ModalMessageBox.h"
#include "DolphinQt/QtUtils/NonDefaultQPushButton.h"
#include "DolphinQt/QtUtils/UTF8CodePointCountValidator.h"
#include "DolphinQt/Settings.h"

#include "UICommon/GameFile.h"
#include "UICommon/NetPlayIndex.h"

#include <Core/KAR/KARBootData.hpp>

KAR::WarpRelay::AccountInfoDialog::AccountInfoDialog(QWidget* parent)
    : QDialog(parent)
{
  setWindowTitle(tr("Warp Relay Account"));
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  //loads all accounts
  KAR::WarpRelay::WarpRelayAccountManager::LoadAllAccounts();

  //creates the layout
  m_main_layout = new QVBoxLayout();

   // the tag about accounts
   guestNotfication_Label = new QLabel(tr(
       "This is a guest account, you can set your display name, but will be limited to stock "
       "Icons.\nTo have custom Icons, you must have a Warp Relay Account. Currently only specific "
       "beta testers/donators can have them.\nThis does not mean donating will get you a Warp "
       "Relay Account. jas is working to set up a proper and secure system for Accounts."));
  m_main_layout->addWidget(guestNotfication_Label);


   //drop down of Accounts
   accounts_Dropdown = new QComboBox();
   for (size_t i = 0; i < KAR::WarpRelay::WarpRelayAccountManager::accounts.size(); ++i)
     accounts_Dropdown->addItem(QString::fromStdString(KAR::WarpRelay::WarpRelayAccountManager::accounts[i].username));
   accounts_Dropdown->setCurrentIndex(KAR::WarpRelay::WarpRelayAccountManager::currentlyLoggedInAccountIndex);
   accounts_Dropdown->setToolTip(tr("All the Warp Relay Accounts you have in KARphin."));
   m_main_layout->addWidget(accounts_Dropdown);

   //display name
   displayName_Label = new QLabel(tr("Display Name:"));
   displayName_Label->setToolTip(tr("This is the name you will show to the public."));
   m_main_layout->addWidget(displayName_Label);
   displayName_EditFeild = new QLineEdit;
   displayName_EditFeild->setText(QString::fromStdString(
       KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount()->displayName));
   displayName_EditFeild->setToolTip(tr("This is the name you will show to the public."));
   displayName_EditFeild->setValidator(
       new UTF8CodePointCountValidator(NetPlay::MAX_NAME_LENGTH, displayName_EditFeild));
   m_main_layout->addWidget(displayName_EditFeild);

   //the icon for this profile
   
   //the size and offset cropping for the image

   //m_main_layout->addWidget(new QLabel(tr("Region:")), 1, 0);
   
   //m_main_layout->addWidget(new QLabel(tr("Backend:")), 4, 0);
   //m_main_layout->addWidget(new QLabel(tr("Warp Relay Perma Host Code:")), 5, 0);
   //m_main_layout->addWidget(new QLabel(tr("Custom Icon:")), 6, 0);
   //
   //m_main_layout->addWidget(new QLabel(tr("Warp Relay Private Hash:")), 8, 0);
   //m_main_layout->addWidget(new QLabel(tr("Warp Relay Discord Link Hash:")), 9, 0);

   setLayout(m_main_layout);

   connect(accounts_Dropdown, &QComboBox::currentIndexChanged, this,
           &AccountInfoDialog::OnAccountChanged);

//  CreateMainLayout();
//
//  bool use_index = Config::Get(Config::NETPLAY_USE_INDEX);
//  std::string index_region = Config::Get(Config::NETPLAY_INDEX_REGION);
//  std::string index_name = Config::Get(Config::NETPLAY_INDEX_NAME);
//  std::string index_password = Config::Get(Config::NETPLAY_INDEX_PASSWORD);
//  std::string nickname = Config::Get(Config::NETPLAY_NICKNAME);
//  std::string traversal_choice = Config::Get(Config::NETPLAY_TRAVERSAL_CHOICE);
//  int connect_port = Config::Get(Config::NETPLAY_CONNECT_PORT);
//  int host_port = Config::Get(Config::NETPLAY_HOST_PORT);
//  int host_listen_port = Config::Get(Config::NETPLAY_LISTEN_PORT);
//  bool enable_chunked_upload_limit = Config::Get(Config::NETPLAY_ENABLE_CHUNKED_UPLOAD_LIMIT);
//  u32 chunked_upload_limit = Config::Get(Config::NETPLAY_CHUNKED_UPLOAD_LIMIT);
//#ifdef USE_UPNP
//  bool use_upnp = Config::Get(Config::NETPLAY_USE_UPNP);
//
//  m_host_upnp->setChecked(use_upnp);
//#endif
//
//  m_nickname_edit->setText(QString::fromStdString(nickname));
//  m_connection_type->setCurrentIndex(traversal_choice == "direct" ? 0 : 1);
//  m_connect_port_box->setValue(connect_port);
//  m_host_port_box->setValue(host_port);
//
//  m_host_force_port_box->setValue(host_listen_port);
//  m_host_force_port_box->setEnabled(false);
//
//  m_host_server_browser->setChecked(use_index);
//
//  m_host_server_region->setEnabled(use_index);
//  m_host_server_region->setCurrentIndex(
//      m_host_server_region->findData(QString::fromStdString(index_region)));
//
//  m_host_server_name->setEnabled(use_index);
//  m_host_server_name->setText(QString::fromStdString(index_name));
//
//  m_host_server_password->setEnabled(use_index);
//  m_host_server_password->setText(QString::fromStdString(index_password));
//
//  m_host_chunked_upload_limit_check->setChecked(enable_chunked_upload_limit);
//  m_host_chunked_upload_limit_box->setValue(chunked_upload_limit);
//  m_host_chunked_upload_limit_box->setEnabled(enable_chunked_upload_limit);
//
//  OnConnectionTypeChanged(m_connection_type->currentIndex());
//
//  ConnectWidgets();
}

static bool weRevertedAChangedOfAccount = false; //this is a flag so we can not show the same text over and over again

// when the Account is changed
void KAR::WarpRelay::AccountInfoDialog::OnAccountChanged(int index)
{
  //we are reverting, don't update anything
  if (weRevertedAChangedOfAccount)
  {
    weRevertedAChangedOfAccount = false;
    return;
  }

  //saves settings between changes
  QMessageBox::StandardButton res = QMessageBox::question(
      this, tr("Confirm Account Data"), tr("Are you content with these Account settings?"),
      QMessageBox::Yes | QMessageBox::No);

  if (res == QMessageBox::Yes) //if they choose to change we save the old settings
  {
    // saves the data to the file
    KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount()->displayName =
        displayName_EditFeild->text().toStdString();
    KAR::WarpRelay::WriteWarpRelayAccount(
        *KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount());

    // saves the selected Warp Relay Account
    bool d = false;
    std::string m = "";
    KAR::Boot::KARSettings settings = KAR::Boot::LoadKARSettingsFromDisc(d, m);
    settings.warpRelayAccountIndex =
        KAR::WarpRelay::WarpRelayAccountManager::currentlyLoggedInAccountIndex;
    KAR::Boot::WriteKARSettingsToDisc(settings);

  }
  else //if they refuse to change, revert to the previous index
  {
    index = static_cast<int>(WarpRelayAccountManager::currentlyLoggedInAccountIndex);
    weRevertedAChangedOfAccount = true;
    accounts_Dropdown->setCurrentIndex(index);
    return;
  }

  //sets the account
  KAR::WarpRelay::WarpRelayAccount* account = WarpRelayAccountManager::SetLoggedInAccount(static_cast<uint32_t>(index));

  //if it's a guest account, we show the prompt about not having custom icons
  guestNotfication_Label->setDisabled(!account->isGuestAccount);

  displayName_EditFeild->setText(QString::fromStdString(account->displayName));
}

void KAR::WarpRelay::AccountInfoDialog::closeEvent(QCloseEvent* event)
{
  // Add your callback or custom handling here
  QMessageBox::StandardButton res =
      QMessageBox::question(this, tr("Confirm Account Data"), tr("Are you content with these Account settings?"),
                            QMessageBox::Yes | QMessageBox::No);

  if (res == QMessageBox::Yes)
  {
    //saves the data to the file
    KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount()->displayName =
        displayName_EditFeild->text().toStdString();
    KAR::WarpRelay::WriteWarpRelayAccount(
        *KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount());

    //saves the selected Warp Relay Account
    bool d = false;
    std::string m = "";
    KAR::Boot::KARSettings settings = KAR::Boot::LoadKARSettingsFromDisc(d, m);
    settings.warpRelayAccountIndex =
        KAR::WarpRelay::WarpRelayAccountManager::currentlyLoggedInAccountIndex;
    KAR::Boot::WriteKARSettingsToDisc(settings);

    // Accept the close event
    event->accept();
  }
  else
  {
    // Ignore the close event
    event->ignore();
  }
}

//void KAR::WarpRelay::AccountInfoDialog::accept()
//{
//  /*SaveSettings();
//  if (m_tab_widget->currentIndex() == 0)
//  {
//    emit Join();
//  }
//  else
//  {
//    auto items = m_host_games->selectedItems();
//    if (items.empty())
//    {
//      ModalMessageBox::critical(this, tr("Error"), tr("You must select a game to host!"));
//      return;
//    }
//
//    if (m_host_server_browser->isChecked() && m_host_server_name->text().isEmpty())
//    {
//      ModalMessageBox::critical(this, tr("Error"), tr("You must provide a name for your session!"));
//      return;
//    }
//
//    if (m_host_server_browser->isChecked() &&
//        m_host_server_region->currentData().toString().isEmpty())
//    {
//      ModalMessageBox::critical(this, tr("Error"),
//                                tr("You must provide a region for your session!"));
//      return;
//    }
//
//    emit Host(*items[0]->data(Qt::UserRole).value<std::shared_ptr<const UICommon::GameFile>>());
//  }*/
//}
