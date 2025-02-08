#pragma once

//manages executing the bootloader

#include <QProcess>
#include <Common/FileUtil.h>

namespace KAR::Bootloader
{
	//forces a update of KARphin
	static inline void InvokeBootloader_UpdateKARphin()
	{
    const std::string KWRoot = File::GetExeDirectory() + "/..";
    QProcess::startDetached(QString::fromStdString(KWRoot + "/Tools/Bootloader.exe"),
                            {QString::fromStdString("--headless"),
                             QString::fromStdString("--silent"),
                             QString::fromStdString("-installDir"), QString::fromStdString(KWRoot),
                             QString::fromStdString("-KARphin"), QString::fromStdString("-boot")},
                            QString::fromStdString(KWRoot + "/Tools"));
  }
}