/*
 * Copyright (C) 2015 ~ 2018 Deepin Technology Co., Ltd.
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

#ifndef USERAVATAR_H
#define USERAVATAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QPropertyAnimation>

#include <dimagebutton.h>

//class AvatarDeleteButton : public DImageButton
//{
//    Q_OBJECT
//public:
//    AvatarDeleteButton(QWidget *parent = 0);
//};

class UserAvatar : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor borderSelectedColor READ borderSelectedColor WRITE setBorderSelectedColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)

public:
    enum AvatarSize {
        AvatarSmallSize = 80,
        AvatarNormalSize = 90,
        AvatarLargeSize = 100
    };
    Q_ENUM(AvatarSize)

    explicit UserAvatar(QWidget *parent = nullptr, bool deleteable = false);
    void setIcon(const QString &iconPath);
    void setAvatarSize(const int size);
    void setDisabled(bool disable);

    QColor borderSelectedColor() const;
    void setBorderSelectedColor(const QColor &borderSelectedColor);

    QColor borderColor() const;
    void setBorderColor(const QColor &borderColor);

    int borderWidth() const;
    void setBorderWidth(int borderWidth);

    void setSelected(bool selected);

    bool deleteable() const;
    void setDeleteable(bool deleteable);

    void showButton();
    void hideButton();
    void setColor(QColor color);

signals:
    void mousePress();
    void requestDelete();
    void userAvatarClicked();
    void alphaChanged();

    void showFinished();
    void hideFinished();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QImage imageToGray(const QImage &image);
    void initDeleteButton();

//    AvatarDeleteButton *m_deleteButton = NULL;
    QLabel *m_iconLabel = nullptr;
    QString m_iconPath = "";
    QColor m_borderColor;
    QColor m_borderSelectedColor;
    int m_avatarSize = 90;
    int m_borderWidth = 0;
    bool m_selected = false;
    bool m_deleteable = false;

    const int SMALL_ICON_SIZE = 80;
    const int NORMAL_ICON_SIZE = 90;
    const int LARGE_ICON_SIZE = 100;
    const int AVATAR_ROUND_RADIUS = 18;

    QPalette m_palette;
    QPropertyAnimation *m_showAnimation;
    QPropertyAnimation *m_hideAnimation;
};


#endif // USERAVATAR_H
