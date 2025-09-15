#pragma once

// defines a custom window for KAR Warp Relay Account info

#include <QDialog>

class QDialogButtonBox;
class QLineEdit;
class QCloseEvent;
class QGridLayout;
class QPushButton;
class QLabel;

namespace KAR::WarpRelay
{
class AccountInfoDialog : public QDialog
{
public:
  explicit AccountInfoDialog(QWidget* parent);

  void closeEvent(QCloseEvent* event) override;

private:

  QVBoxLayout* m_main_layout;

  // notification how guest accounts work or if it's not, the size of the image
  QLabel* guestNotfication_Label;

  QLabel* displayName_Label;
  QLineEdit* displayName_EditFeild;
};

}  // namespace KAR::WarpRelay