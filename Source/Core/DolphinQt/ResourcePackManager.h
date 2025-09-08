// Copyright 2018 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QDialog>

#include <KARphin/KWQI/KWQI_Game.hpp>

class QPushButton;
class QTableWidget;
class QTableWidgetItem;

class ResourcePackManager : public QDialog
{
public:
  explicit ResourcePackManager(QWidget* parent = nullptr);

private:

  //creates the general widgets

  //creates the menu tab for Full Game ISO Mods

  //creates the menu tab for Mixtapes (Songs)

  //creates the menu tab for Machine Packs

  //creates the menu tab for City Packs

  //creates the menu tab for extended Kiry Skins

  void CreateWidgets();
  void ConnectWidgets();


  void OpenResourcePackDir();
  void RepopulateTable();
  void Change();
  void Install();
  void Uninstall();
  void Remove();
  void PriorityUp();
  void PriorityDown();
  void Refresh();

  void SelectionChanged();
  void ItemDoubleClicked(QTableWidgetItem* item);

  int GetResourcePackIndex(QTableWidgetItem* item) const;

  QPushButton* m_open_directory_button;
  QPushButton* m_change_button;
  QPushButton* m_remove_button;
  QPushButton* m_refresh_button;
  QPushButton* m_priority_up_button;
  QPushButton* m_priority_down_button;

  QTableWidget* m_table_widget;

  std::vector<KWQI::Game::KWQIData_Game> games;
};
