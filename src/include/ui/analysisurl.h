/**
 * @copyright 2020-2020 Uniontech Technology Co., Ltd.
 *
 * @file analysisurl.h
 *
 * @brief 管理解析url线程
 *
 * @date 2020-08-28 14:40
 *
 * Author: bulongwei  <bulongwei@uniontech.com>
 *
 * Maintainer: bulongwei  <bulongwei@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ANALYSISURL_H
#define ANALYSISURL_H

#include "urlthread.h"
#include <QObject>
#include <QMap>

struct LinkInfo {
    enum UrlState {
        Start = 1,
        Analysising,
        Finished
    };
    int index; //url序号
    QString url; //url链接
    UrlState state; //url状态
    QString urlName; //url名字
    QString type; //url类型
    QString urlSize; //url大小
    QString urlTrueLink; //url真实链接
    long length;
    LinkInfo()
    {
        index = -1;
        length = 0;
        url.clear();
        state = UrlState::Start;
        urlName.clear();
        urlSize.clear();
        urlTrueLink.clear();
        type.clear();
    }
    LinkInfo &operator=(const LinkInfo &l)
    {
        index = l.index;
        state = l.state;
        url = l.url;
        type = l.type;
        urlSize = l.urlSize;
        urlName = l.urlName;
        urlTrueLink = l.urlTrueLink;
        length = l.length;
        return *this;
    }
};

class AnalysisUrl : public QObject
{
    Q_OBJECT

public:
    explicit AnalysisUrl(QObject *parent = nullptr);
    ~AnalysisUrl();

    void setUrlList(QMap<QString, LinkInfo> list);

public slots:
    void getLinkInfo(LinkInfo);

private:
    void stopWork(int index);

signals:
    void sendFinishedUrl(LinkInfo *);

private:
    QMap<QString, LinkInfo> m_curAllUrl;
    QMap<int, QThread *> m_workThread;
};

#endif // ANALYSISURL_H
