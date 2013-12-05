/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "base/command_line.h"
#include "content/public/common/content_switches.h"
#include "ui/base/resource/resource_bundle.h"
#include "type_conversion.h"
#include "web_engine_library_info.h"

#include <QFileInfo>
#include <QStringBuilder>

namespace ui {

void ResourceBundle::LoadCommonResources()
{
    // Loading these resources probably only makes sense for the browser process
    if (CommandLine::ForCurrentProcess()->HasSwitch(switches::kProcessType))
        return;

    // We repacked the resources we need and installed them. now let chromium mmap that file.
    AddDataPackFromPath(base::FilePath(toFilePathString(WebEngineLibraryInfo::location(WebEngineLibraryInfo::DataPath) % QStringLiteral("/qtwebengine_resources.pak"))) , SCALE_FACTOR_100P);
}

// As GetLocaleFilePath is excluded for Mac in resource_bundle.cc,
// we have to add a replacement for it using the inverted logic.
#if defined(OS_MACOSX)
base::FilePath ResourceBundle::GetLocaleFilePath(const std::string& /*app_locale*/, bool /*test_file_exists*/)
{
    return base::FilePath();
}
#endif

gfx::Image& ResourceBundle::GetNativeImageNamed(int resource_id, ImageRTL rtl)
{
    LOG(WARNING) << "Unable to load image with id " << resource_id;
    NOTREACHED();  // Want to assert in debug mode.
    return GetEmptyImage();
}

}  // namespace ui
