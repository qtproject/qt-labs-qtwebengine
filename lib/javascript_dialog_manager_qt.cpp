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

#include "javascript_dialog_manager_qt.h"

#include "base/memory/singleton.h"

#include "web_contents_adapter_client.h"
#include "web_contents_view_qt.h"
#include "type_conversion.h"

using base::string16;

Q_STATIC_ASSERT_X((int)content::JAVASCRIPT_MESSAGE_TYPE_PROMPT == (int)WebContentsAdapterClient::PromptDialog, "These enums should be in sync.");

JavaScriptDialogManagerQt *JavaScriptDialogManagerQt::GetInstance()
{
    return Singleton<JavaScriptDialogManagerQt>::get();
}

void JavaScriptDialogManagerQt::RunJavaScriptDialog(content::WebContents *webContents, const GURL &origin_url, const std::string &accept_lang, content::JavaScriptMessageType javascript_message_type, const string16 &message_text, const string16 &default_prompt_text, const content::JavaScriptDialogManager::DialogClosedCallback &callback, bool *did_suppress_message)
{
    WebContentsAdapterClient* client = WebContentsViewQt::from(webContents->GetView())->client();
    bool res = false;
    QString promptInput;
    if (client) {
        WebContentsAdapterClient::JavascriptDialogType dialogType = (WebContentsAdapterClient::JavascriptDialogType)javascript_message_type;
        res = client->javascriptDialog(dialogType, toQt(message_text).toHtmlEscaped(), toQt(default_prompt_text).toHtmlEscaped(), &promptInput);
    }
    callback.Run(res, toString16(promptInput));
}

bool JavaScriptDialogManagerQt::HandleJavaScriptDialog(content::WebContents *web_contents, bool accept, const string16 *prompt_override)
{
    // FIXME: We might need to keep a queue of modal dialogs in there and unqueue them...
    return false;
}
