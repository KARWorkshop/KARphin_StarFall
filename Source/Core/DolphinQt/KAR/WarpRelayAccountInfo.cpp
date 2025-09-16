#include <DolphinQt/KAR/WarpRelayAccountInfo.hpp>

#include <memory>

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
#include <qevent.h>
#include <qicon.h>

#include "Core/Config/NetplaySettings.h"
#include "Core/NetPlayProto.h"

#include "DolphinQt/QtUtils/ModalMessageBox.h"
#include "DolphinQt/QtUtils/NonDefaultQPushButton.h"
#include "DolphinQt/QtUtils/UTF8CodePointCountValidator.h"
#include "DolphinQt/Settings.h"

#include "UICommon/GameFile.h"
#include "UICommon/NetPlayIndex.h"

#include <KARphin/WarpRelay/Accounts/WarpRelayAccount.hpp>

static const char* GUEST_ACCOUNT_TEXT =
    "You can set your display name.";

static const char* WARP_RELAY_ACCOUNT_TEXT =
    "You can set a custom icon using the input field at the bottom.\nMake sure the image is "
         "40 by 40 px for best result. You can use others but it may not show up as well.";

KAR::WarpRelay::AccountInfoDialog::AccountInfoDialog(QWidget* parent) : QDialog(parent)
{
  setWindowTitle(tr("Warp Relay Account"));
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  // loads all accounts
 // KAR::WarpRelay::WarpRelayAccountManager::LoadAllAccounts();
  KAR::Account::Account& account = KAR::Account::Account::Instance();

  // creates the layout
  m_main_layout = new QVBoxLayout();

  // the tag about accounts or image dimentions
  guestNotfication_Label = new QLabel(tr(
      GUEST_ACCOUNT_TEXT));
  m_main_layout->addWidget(guestNotfication_Label);

  // display name
  displayName_Label = new QLabel(tr("Display Name:"));
  displayName_Label->setToolTip(tr("This is the name you will show to the public."));
  m_main_layout->addWidget(displayName_Label);
  displayName_EditFeild = new QLineEdit;
  displayName_EditFeild->setText(QString::fromStdString(
      account.displayName));
  displayName_EditFeild->setToolTip(tr("This is the name you will show to the public."));
  displayName_EditFeild->setValidator(
      new UTF8CodePointCountValidator(NetPlay::MAX_NAME_LENGTH, displayName_EditFeild));
  m_main_layout->addWidget(displayName_EditFeild);

  setLayout(m_main_layout);
}

void KAR::WarpRelay::AccountInfoDialog::closeEvent(QCloseEvent* event)
{
  // Add your callback or custom handling here
  QMessageBox::StandardButton res = QMessageBox::question(
      this, tr("Confirm Account Data"), tr("Are you content with these Account settings?"),
      QMessageBox::Yes | QMessageBox::No);

  if (res == QMessageBox::Yes)
  {
    // saves the data to the file
    KAR::Account::Account::Instance().displayName = displayName_EditFeild->text().toStdString();
    KAR::Account::Account::Instance().Write(
        KAR::IO::GetDirectory_Account() + KAR::Account::Account::Instance().displayName + ".wrv2");

    // Accept the close event
    event->accept();
  }
  else
  {
    // Ignore the close event
    event->ignore();
  }
}
