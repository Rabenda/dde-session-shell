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

#ifndef ROUNDITEMBUTTON
#define ROUNDITEMBUTTON

#include <QObject>
#include <QFrame>
#include <QAbstractButton>
#include <QLabel>
#include <QtWidgets>
#include <QFocusEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>

/* The RoundItemButton is used by shutdownButton, restartButton, and so on... */

class RoundItemButton: public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QString normalIcon MEMBER m_normalIcon DESIGNABLE true NOTIFY iconChanged)
    Q_PROPERTY(QString hoverIcon MEMBER m_hoverIcon DESIGNABLE true NOTIFY iconChanged)
    Q_PROPERTY(QString pressedIcon MEMBER m_pressedIcon DESIGNABLE true NOTIFY iconChanged)
    Q_PROPERTY(bool disabled READ isDisabled WRITE setDisabled NOTIFY stateChanged)

public:
    RoundItemButton(QWidget* parent = nullptr);
    RoundItemButton(const QString &text, QWidget* parent = nullptr);
    ~RoundItemButton() override;

    enum State {Default, Normal, Hover, Checked, Pressed, Disabled};

    void setDisabled(bool disabled);
    inline bool isDisabled() const {return m_state == Disabled;}
    void setChecked(bool checked);
    inline bool isChecked() const {return m_state == Checked;}
    inline State state() const {return m_state;}
    inline const QString text() const {return m_text;}
    void setText(const QString &text);
    void updateState(const State state);

    void setNormalPic(const QString &path);
    void setHoverPic(const QString &path);
    void setPressPic(const QString &path);

signals:
    void stateChanged(const State state);
    void clicked();
    void iconChanged();

private slots:
    void updateIcon();
    inline void setState(const State state) {updateState(state);}

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent* event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* e) Q_DECL_OVERRIDE;

private:
    void initUI();
    void initConnect();

private:
    State m_state = Normal;
    int m_penWidth = 1;
    int m_rectRadius = 8;

    QString m_text;
    QString m_normalIcon;
    QString m_hoverIcon;
    QString m_pressedIcon;
    QString m_currentIcon;
};
#endif // ROUNDITEMBUTTON
