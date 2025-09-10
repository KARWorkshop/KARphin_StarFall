#include <DolphinQt/KAR/WarpRelayAccountInfo.hpp>

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

#include <KARphin/WarpRelay/WarpRelayAccount.hpp>

//#include <Core/KAR/KARBootData.hpp>

//#include <KAR/WarpRelayImageLoader.hpp>

// changes all the GUI to be what we use for a guest account
void KAR::WarpRelay::AccountInfoDialog::OnGUIChange_GuestAccount()
{
 // KAR::WarpRelay::WarpRelayAccount* account = KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount();

  // if it's a guest account, we show the prompt about not having custom icons
 // guestNotfication_Label->setText(tr(
 //     "This is a guest account, you can set your display name, but will be limited to stock "
 //     "Icons.\nTo have custom Icons, you must have a Warp Relay Account. Currently only specific "
 //     "beta testers/donators can have them.\nThis does not mean donating will get you a Warp "
 //     "Relay Account. jas is working to set up a proper and secure system for Accounts."));

  displayName_EditFeild->setText(
     QString::fromStdString(KAR::Account::Account::Instance().displayName));

  //updates the preset icon
  //presetIcon_Dropdown->setVisible(true);
  //presetIcon_Dropdown->setCurrentIndex((int)account->presetIcon);

  //hides the URL input fields
  //customURL_EditFeild->setVisible(false);
  //customURL_Label->setVisible(false);
}

// changes all the GUI to be what we use for a non-guest account
void KAR::WarpRelay::AccountInfoDialog::OnGUIChange_WarpRelayAccount()
{
  KAR::Account::Account& account = KAR::Account::Account::Instance();

  // if it's a guest account, we show the prompt about not having custom icons
 // guestNotfication_Label->setText(tr(
  //    "You can set a custom icon using the input field at the bottom.\nMake sure the image is 40 by 40 px for best result. You can use others but it may not show up as well."));

  displayName_EditFeild->setText(QString::fromStdString(account.displayName));

  //hides the icon presets
  //presetIcon_Dropdown->setVisible(false);

  //shows the url input feild
  //customURL_EditFeild->setVisible(true);
 // customURL_EditFeild->setText(QString::fromStdString(account->customIconURL));
  //customURL_Label->setVisible(true);
}

KAR::WarpRelay::AccountInfoDialog::AccountInfoDialog(QWidget* parent)
    : QDialog(parent)
{
  setWindowTitle(tr("Warp Relay Account"));
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  //loads all accounts
  KAR::Account::Account::Instance() = KAR::Account::LoadDefaultWarpRelayAccount();
  KAR::Account::Account acc = KAR::Account::Account::Instance();

  //creates the layout
  m_main_layout = new QVBoxLayout();

   // the tag about accounts or image dimentions
  // guestNotfication_Label = new QLabel(tr(
  //     "This is a guest account, you can set your display name, but will be limited to stock "
  //     "Icons.\nTo have custom Icons, you must have a Warp Relay Account. Currently only specific "
  //     "beta testers/donators can have them.\nThis does not mean donating will get you a Warp "
  //     "Relay Account. jas is working to set up a proper and secure system for Accounts."));
  //m_main_layout->addWidget(guestNotfication_Label);

   //drop down of Accounts
  // accounts_Dropdown = new QComboBox();
  // for (size_t i = 0; i < KAR::WarpRelay::WarpRelayAccountManager::accounts.size(); ++i)
  //   accounts_Dropdown->addItem(QString::fromStdString(KAR::WarpRelay::WarpRelayAccountManager::accounts[i].username));
  // accounts_Dropdown->setCurrentIndex(KAR::WarpRelay::WarpRelayAccountManager::currentlyLoggedInAccountIndex);
  // accounts_Dropdown->setToolTip(tr("All the Warp Relay Accounts you have in KARphin."));
  // m_main_layout->addWidget(accounts_Dropdown);

   //display name
   displayName_Label = new QLabel(tr("Display Name:"));
   displayName_Label->setToolTip(tr("This is the name you will show to the public."));
   m_main_layout->addWidget(displayName_Label);
   displayName_EditFeild = new QLineEdit;
   displayName_EditFeild->setText(QString::fromStdString(
       acc.displayName));
   displayName_EditFeild->setToolTip(tr("This is the name you will show to the public."));
   displayName_EditFeild->setValidator(
       new UTF8CodePointCountValidator(NetPlay::MAX_NAME_LENGTH, displayName_EditFeild));
   m_main_layout->addWidget(displayName_EditFeild);

   //the icon for this profile
  //icon_Label = new QLabel(tr("Account Icon"));
  //icon_Label->setToolTip(tr("The icon you show to the public"));
  //m_main_layout->addWidget(icon_Label);
  //icon_storage = new QLabel();
  //icon_storage->setPixmap(
  //    IconLoader::GetIcon(
  //        KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount()->customIconURL).pixmap(80));
  //m_main_layout->addWidget(icon_storage);

   //the dropdown for various pre-set icons
  // presetIcon_Dropdown = new QComboBox();
  // presetIcon_Dropdown->setToolTip(tr("The presets for Guest accounts."));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Pink"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Yellow"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Blue"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Green"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Purple"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Red"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Brown"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("White"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Citrus"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Cherry"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Carbon"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Emerald"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Sapphire"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Orange"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Light Blue"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Lavender"));
  // presetIcon_Dropdown->addItem(QString::fromStdString("Ivory"));
  // presetIcon_Dropdown->setCurrentIndex((uint8_t)KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount()->presetIcon);
  // m_main_layout->addWidget(presetIcon_Dropdown);

   //the input feild for a custom URL
  //customURL_Label = new QLabel(tr("Custom URL"));
  //customURL_Label->setToolTip(tr("The custom URL to the image you would like as your icon."));
  //customURL_EditFeild = new QLineEdit(); 
  //QObject::connect(
  //    customURL_EditFeild, &QLineEdit::textChanged,
  //                 [&](const QString& newText) {
  //  KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount()->customIconURL =
  //      newText.toStdString();
  //  UpdateAccountIcon();
  //});
  //m_main_layout->addWidget(customURL_Label);
  //m_main_layout->addWidget(customURL_EditFeild);

   //m_main_layout->addWidget(new QLabel(tr("Region:")), 1, 0);
   
   //m_main_layout->addWidget(new QLabel(tr("Backend:")), 4, 0);
   //m_main_layout->addWidget(new QLabel(tr("Warp Relay Perma Host Code:")), 5, 0);
   //m_main_layout->addWidget(new QLabel(tr("Custom Icon:")), 6, 0);
   //
   //m_main_layout->addWidget(new QLabel(tr("Warp Relay Private Hash:")), 8, 0);
   //m_main_layout->addWidget(new QLabel(tr("Warp Relay Discord Link Hash:")), 9, 0);

   

  // connect(accounts_Dropdown, &QComboBox::currentIndexChanged, this,
  //         &AccountInfoDialog::OnAccountChanged); //when the account drop down changes
  // connect(presetIcon_Dropdown, &QComboBox::currentIndexChanged, this,
        //   &AccountInfoDialog::OnPresetIconChanged); //when the preset dropdown changes

   setLayout(m_main_layout);

   // if we're no longer a guest account
  // if (!KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount()->isGuestAccount)
  //   OnGUIChange_WarpRelayAccount();

   // if we're a guest account
   //else
  //   OnGUIChange_GuestAccount();
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
    KAR::Account::Account::Instance().displayName =
        displayName_EditFeild->text().toStdString();

   // KAR::WarpRelay::WriteWarpRelayAccount(
   //     *KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount());

    // saves the selected Warp Relay Account
  // bool d = false;
  // std::string m = "";
  // KAR::Boot::KARSettings settings = KAR::Boot::LoadKARSettingsFromDisc(d, m);
  // settings.warpRelayAccountIndex =
  //     KAR::WarpRelay::WarpRelayAccountManager::currentlyLoggedInAccountIndex;
  // KAR::Boot::WriteKARSettingsToDisc(settings);

    KAR::Account::Account::Instance().Write(KAR::Account::Account::DefaultFilepath());

  }
  else //if they refuse to change, revert to the previous index
  {
   //index = static_cast<int>(WarpRelayAccountManager::currentlyLoggedInAccountIndex);
   //weRevertedAChangedOfAccount = true;
   //accounts_Dropdown->setCurrentIndex(index);
    return;
  }

  //sets the account
 // KAR::WarpRelay::WarpRelayAccount* account = WarpRelayAccountManager::SetLoggedInAccount(static_cast<uint32_t>(index));

  //if we're no longer a guest account
 // if (!account->isGuestAccount)
 //   OnGUIChange_WarpRelayAccount();
 //
 // // if we're a guest account
 // else
 //   OnGUIChange_GuestAccount();
}

// when the preset icon is changed
void KAR::WarpRelay::AccountInfoDialog::OnPresetIconChanged(int index)
{
  // sets the custom icon url to the preset
 // KAR::WarpRelay::WarpRelayAccount* account =
 //     KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount();
 // account->presetIcon = (KAR::WarpRelay::PresetIcon)index;
 // account->customIconURL = KAR::WarpRelay::GetPresetIconURL(account->presetIcon);

  //updates the image we render
  UpdateAccountIcon();
}

 // updates the image we render
void KAR::WarpRelay::AccountInfoDialog::UpdateAccountIcon()
{
  //icon_storage->setPixmap(
  //    IconLoader::GetIcon(
  //        KAR::WarpRelay::WarpRelayAccountManager::GetLoggedInAccount()->customIconURL)
  //        .pixmap(80));
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
    KAR::Account::Account::Instance().displayName =
        displayName_EditFeild->text().toStdString();
    

    //saves the selected Warp Relay Account
   // bool d = false;
   // std::string m = "";
   // KAR::Boot::KARSettings settings = KAR::Boot::LoadKARSettingsFromDisc(d, m);
   // settings.warpRelayAccountIndex =
   //     KAR::WarpRelay::WarpRelayAccountManager::currentlyLoggedInAccountIndex;
   // KAR::Boot::WriteKARSettingsToDisc(settings);

    KAR::Account::Account::Instance().Write(KAR::Account::Account::DefaultFilepath());

    // Accept the close event
    event->accept();
  }
  else
  {
    // Ignore the close event
    event->ignore();
  }
}
