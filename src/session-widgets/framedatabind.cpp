/*
 * Copyright (C) 2018 ~ 2021 Uniontech Technology Co., Ltd.
 *
 * Author:     fanpengcheng <fanpengcheng@uniontech.com.so>
 *
 * Maintainer: fanpengcheng <fanpengcheng@uniontech.com.so>
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
#include "framedatabind.h"

FrameDataBind::FrameDataBind()
    : QObject()
{

}

FrameDataBind::~FrameDataBind()
{

}

FrameDataBind *FrameDataBind::Instance()
{
    static FrameDataBind frameDataBind;
    return &frameDataBind;
}

int FrameDataBind::registerFunction(const QString &flag, std::function<void (QVariant)> function)
{
    for (auto it = m_registerList.begin(); it != m_registerList.end(); ++it) {
        if (it.key() == flag) {
            QList<int> keys = it.value().keys();
            int index = 0;
            while (true) {
                if (!keys.contains(index)) {
                    it.value()[index] = function;
                    return index;
                }

                ++index;
            }
        }
    }

    m_registerList[flag][0] = function;
    return 0;
}

void FrameDataBind::unRegisterFunction(const QString &flag, int index)
{
    for (auto it = m_registerList.begin(); it != m_registerList.end(); ++it) {
        if (it.key() == flag) {
            it.value().remove(index);
        }
    }
}

QVariant FrameDataBind::getValue(const QString &flag) const
{
    if (m_datas.contains(flag)) {
        return m_datas[flag];
    } else {
        return QVariant();
    }
}

void FrameDataBind::updateValue(const QString &flag, const QVariant &value)
{
    m_datas[flag] = value;

    refreshData(flag);
}

void FrameDataBind::clearValue(const QString &flag)
{
    if (m_datas.contains(flag)) {
        m_datas.remove(flag);
    }
}

void FrameDataBind::refreshData(const QString &flag)
{
    QList<std::function<void (QVariant)>> functions = m_registerList[flag].values();

    for (auto it = functions.constBegin(); it != functions.constEnd(); ++it) {
        (*it)(m_datas[flag]);
    }
}
