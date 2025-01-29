#pragma once

//defines the input widget for syncing shock collars in the controller menu

#include <QWidget>

#include <array>

class QCheckBox;
class QComboBox;
class QHBoxLayout;
class QGridLayout;
class QGroupBox;
class QLabel;
class QPushButton;
class QRadioButton;

namespace Core
{
enum class State;
}

class ShockCollarControllerWidget final : public QWidget
{

public:
  explicit ShockCollarControllerWidget(QWidget* parent);

  void UpdateBluetoothAvailableStatus();

private:
  void SaveSettings();
  void OnBluetoothPassthroughSyncPressed();
  void OnBluetoothPassthroughResetPressed();
  void OnWiimoteRefreshPressed();
  void OnWiimoteConfigure(size_t index);

  void CreateLayout();
  void ConnectWidgets();
  void LoadSettings(Core::State state);

  QGroupBox* m_shockCollar_box;
  QGridLayout* m_shockCollar_layout;
  std::array<QLabel*, 4> m_wiimote_labels;
  std::array<QComboBox*, 4> m_wiimote_boxes;
  std::array<QPushButton*, 4> m_wiimote_buttons;
  std::array<QHBoxLayout*, 4> m_wiimote_groups;
  std::array<QLabel*, 2> m_wiimote_pt_labels;

  //QRadioButton* m_wiimote_emu;
  //QRadioButton* m_wiimote_passthrough;
  QPushButton* m_wiimote_sync;
  QPushButton* m_wiimote_reset;
  QCheckBox* m_wiimote_continuous_scanning;
  //QCheckBox* m_wiimote_real_balance_board;
  //QCheckBox* m_wiimote_speaker_data;
  //QCheckBox* m_wiimote_ciface;
  QPushButton* m_wiimote_refresh;
  QLabel* m_bluetooth_unavailable;
};