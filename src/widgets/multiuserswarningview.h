/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
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

#ifndef MULTIUSERSWARNINGVIEW_H
#define MULTIUSERSWARNINGVIEW_H

#include <QFrame>
#include <QKeyEvent>
#include <dimagebutton.h>
#include "warningview.h"
#include "userinfo.h"
#include "sessionbasemodel.h"

class QListWidget;
class QLabel;
class QVBoxLayout;

DWIDGET_USE_NAMESPACE

class QPushButton;
class MultiUsersWarningView : public WarningView
{
    Q_OBJECT
public:
    MultiUsersWarningView(SessionBaseModel::PowerAction inhibitType, QWidget *parent = nullptr);
    ~MultiUsersWarningView() override;

    void setUsers(QList<std::shared_ptr<User>> users);
    SessionBaseModel::PowerAction action() const;
    void toggleButtonState() Q_DECL_OVERRIDE;
    void buttonClickHandle() Q_DECL_OVERRIDE;
    void setAcceptReason(const QString &reason) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event)Q_DECL_OVERRIDE;

protected:
    bool focusNextPrevChild(bool next) Q_DECL_OVERRIDE;
    void setCurrentButton(const ButtonType btntype) Q_DECL_OVERRIDE;

signals:
    void actionInvoked();
    void cancelled();

private:
    QString getUserIcon(const QString &path);
    void updateIcon();

private:
    QVBoxLayout * m_vLayout;
    QListWidget * m_userList;
    QLabel * m_warningTip;
    QPushButton * m_cancelBtn;
    QPushButton * m_actionBtn;
    QPushButton *m_currentBtn;
    SessionBaseModel::PowerAction m_action;
    const int m_buttonIconSize = 28;
    const int m_buttonWidth = 200;
    const int m_buttonHeight = 64;
    SessionBaseModel::PowerAction m_inhibitType;
};

class UserListItem : public QFrame
{
    Q_OBJECT
public:
    UserListItem(const QString &icon, const QString &name);

private:
    QLabel * m_icon;
    QLabel * m_name;

    QPixmap getRoundPixmap(const QString &path);
};

#endif // MULTIUSERSWARNINGVIEW_H
