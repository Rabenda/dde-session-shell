/*
* Copyright (C) 2021 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     Zhang Qipeng <zhangqipeng@uniontech.com>
*
* Maintainer: Zhang Qipeng <zhangqipeng@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "login_module.h"

#include <QBoxLayout>
#include <QWidget>

#include <QtWebEngineWidgets/QWebEngineView>

#include <QtWebChannel/QWebChannel>

namespace dss {
namespace module {

LoginModule::LoginModule(QObject *parent)
    : QObject(parent)
    , m_callbackFun(nullptr)
    , m_loginWidget(nullptr)
{
    setObjectName(QStringLiteral("LoginModule"));
}

LoginModule::~LoginModule()
{
    if (m_loginWidget) {
        delete m_loginWidget;
    }
}

void LoginModule::init()
{
    initUI();
}

void LoginModule::initUI()
{
    if (m_loginWidget) {
        return;
    }
    m_loginWidget = new QWidget;
    m_loginWidget->setAccessibleName(QStringLiteral("LoginWidget"));
    m_loginWidget->setFixedSize(200, 100);
    QVBoxLayout *loginLayout = new QVBoxLayout(m_loginWidget);

    QWebEngineView *webView = new QWebEngineView(m_loginWidget);
    QWebEnginePage *webPage = new QWebEnginePage(m_loginWidget);
    QWebChannel *webChannel = new QWebChannel(m_loginWidget);
    webView->setPage(webPage);
    webPage->setWebChannel(webChannel);
    webView->setContextMenuPolicy(Qt::NoContextMenu);

    loginLayout->addWidget(webView);

    webView->load(QUrl("https://www.baidu.com"));

    connect(webView, &QWebEngineView::loadFinished, this, [this]{
        QTimer::singleShot(1000, this, [this]{
            AuthCallbackData data;
            data.account = "uos";
            data.token = "1";
            data.result = true;
            m_callbackFun(&data, m_callback->ContainerPtr);
        });

    });
}

void LoginModule::setAuthFinishedCallback(AuthCallback *callback)
{
    m_callback = callback;
    m_callbackFun = callback->callbackFun;
}

} // namespace module
} // namespace dss
