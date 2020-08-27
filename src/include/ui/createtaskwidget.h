﻿/**
 * @copyright 2020-2020 Uniontech Technology Co., Ltd.
 *
 * @file newtaskwidget.h
 *
 * @brief 新建任务类
 *
 * @date 2020-06-09 10:52
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

#ifndef NEWTASKWIDGET_H
#define NEWTASKWIDGET_H

#include "settings.h"
#include <dfilechooseredit.h>
#include <DMainWindow>
#include <DPushButton>
#include <DDialog>
#include <DLabel>
#include <DTextEdit>
#include <DSuggestButton>
#include <DFileDialog>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCloseEvent>

class LinkInfo;
class BtInfoDialog;
class MessageBox;
class BtInfoDelegate;
class BtInfoTableView;
class AnalysisUrl;
class TaskDelegate;
class QStandardItemModel;

DWIDGET_USE_NAMESPACE

class  CreateTaskWidget :public DDialog
{
    Q_OBJECT
public:
    explicit CreateTaskWidget(DDialog *parent=0);
    ~CreateTaskWidget();

    void setUrl(QString url);

    void showNetErrorMsg();

    /**
     * @brief updateSelectedInfo 更新文件列表选中后的信息（Delegate内部调用）
     */
    void updateSelectedInfo();

    void setUrlName(int index, QString name);
private:
    /**
     * @brief 初始化ui
     */
    void initUi();

    /**
     * @brief 是否为磁力链接
     * @param url 路径
     * @return  true 为磁力链接  false 为不是磁力链接
    */
    bool isMagnet(QString url);

    /**
     * @brief 是否为http链接
     * @param url 路径
     * @return  true 为http链接  false 为不是http链接
    */
    bool isHttp(QString url);

    /**
     * @brief 根据重定向url 获取真是url地址,并发送到主界面
     * @param 重定向地址
     * @return  返回真是url地址
    */
    void getTruetUrl(QString redirecUrl);

    void getUrlToName(QString url,QString &name, QString &type);

    void setData(int index, QString name,QString type, QString size, QString url, long length, QString trueUrl);

    void hideTableWidget();

    void showTableWidget();

    bool isVideo(QString ext);//判断扩展名是否是常见视频格式
    bool isAudio(QString ext);//判断扩展名是否是常见音频格式
    bool isPicture(QString ext);//判断扩展名是否是常见图片格式
    bool isZip(QString ext);
    bool isDoc(QString ext);

private slots:
    /**
     * @brief 打开选择文件窗口按钮
     */
    void onFileDialogOpen();
    /**
     * @brief 关闭窗口按钮
     */
    void onCancelBtnClicked();
    /**
     * @brief 确定下载按钮
     */
    void onSureBtnClicked();
    /**
     * @brief url文本框变化
     */
    void onTextChanged();

    /**
     * @brief 选择下载路径
     */
    void onFilechoosed(const QString &);

    /**
     * @brief 更新解析列表
     */
    void updataTabel(LinkInfo*);

    //void changeUrlName(const QModelIndex &index);

    /**
     * @brief 全选按钮
     */
    void onAllCheck();       //全选按钮
    /**
     * @brief 视频按钮
     */
    void onVideoCheck();     //视频按钮
    /**
     * @brief 视频按钮
     */
    void onAudioCheck();     //音频按钮
    /**
     * @brief 视频按钮
     */
    void onPictureCheck();   //图片按钮
    /**
     * @brief 视频按钮
     */
    void onZipCheck();     //其他按钮
    /**
     * @brief 视频按钮
     */
    void onDocCheck();     //其他按钮
    /**
     * @brief 视频按钮
     */
    void onOtherCheck();     //其他按钮

protected:
    /**
     * @brief 拖拽处理函数
     * @param event 拖拽事件
    */
    void dragEnterEvent(QDragEnterEvent *event);
    /**
     * @brief 拖拽释放处理函数
     * @param event 拖拽事件
    */
    void dropEvent(QDropEvent *event);

    /**
     * @brief 关闭事件
     * @param event 关闭事件
    */
    void closeEvent(QCloseEvent *event);


signals:
    /**
     * @brief 新建http下载任务
     * @param url 信息
     * @param save_path 保存路径
     * @param path_name 文件名字
    */
    void downloadWidgetCreate(QVector<LinkInfo *> urlList,QString savePath);
    /**
     * @brief 新建bt下载任务
     * @param btPath bt下载地址
     * @param opt 选项
     * @param infoName bt文件名字
     * @param infoHash bt文件hash值
    */
    void downLoadTorrentCreate(QString btPath,QMap<QString,QVariant> &opt,QString infoName, QString infoHash);

private:
    DTextEdit *m_texturl;               //url文本框
    DSuggestButton *m_sureButton;      //确认按钮
    DFileChooserEdit *m_editDir;    //选择下载路径窗口
    QString m_defaultDownloadDir;   //默认文件路径

    QStandardItemModel *m_model;    //tableview中的模型，数据交流
    TaskDelegate *m_delegate;     //tableview中选中表格item
    BtInfoTableView *m_tableView;//列表
    DWidget *m_widget;      //包裹view

    DCheckBox *m_checkAll;          //文件类型全选
    DCheckBox *m_checkVideo;        //视频文件类型
    DCheckBox *m_checkAudio;        //音频文件类型
    DCheckBox *m_checkPicture;      //图片文件类型
    DCheckBox *m_checkDoc;          //文档文件类型
    DCheckBox *m_checkZip;          //压缩包文件类型
    DCheckBox *m_checkOther;        //其他文件类型
    DLabel *m_labelSelectedFileNum; //选中文件数
    DLabel *m_labelFileSize;         //总大小标签
    QWidget *m_checkWidget;

    AnalysisUrl *m_analysisUrl;
};


#endif // NEWTASKWIDGET_H
