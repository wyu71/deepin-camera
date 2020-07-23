/*
* Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     hujianbo <hujianbo@uniontech.com>
*
* Maintainer: hujianbo <hujianbo@uniontech.com>
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

#ifndef THUMBNAILSBAR_H
#define THUMBNAILSBAR_H
#include <DWidget>
#include <QDateTime>
#include <QObject>
#include <QDebug>
#include <QDirIterator>
#include <QReadWriteLock>
#include <QListWidget>
#include <QHBoxLayout>
#include <QFileSystemWatcher>
#include <QPushButton>
#include <DButtonBox>
#include <DFloatingWidget>
#include <DIconButton>
#include <QTimer>
#include <DLabel>
#include <DSpinner>
#include "imageitem.h"
DWIDGET_USE_NAMESPACE
#define IMAGE_HEIGHT_DEFAULT 40
#define LAST_BUTTON_WIDTH 64
#define LAST_BUTTON_HEIGHT 50
#define LAST_BUTTON_SPACE 14//按钮与窗体的间隔
#define ITEM_SPACE 2//控件间距

enum ActType {ActTakePic, ActTakeVideo}; // 定义枚举类型ActType
enum CamStatus {STATNULL, STATPicIng, STATVdIng}; // 定义枚举类型CamStatus

class ThumbnailsBar : public DFloatingWidget
{
    Q_OBJECT
public:

    explicit ThumbnailsBar(DWidget *parent = nullptr);
    int getItemCount()
    {
        return m_nItemCount;
    }
    void setBtntooltip();
    void ChangeActType(int nType);
    void addPath(QString strPath);
    void addFile(QString strFile);
    void delFile(QString strFile);

    QHBoxLayout *m_mainLayout;
    DWidget *m_wgt;
    QHBoxLayout *m_hBOx;
    int m_nMaxItem;
    int m_nStatus; //当前状态
private:
    int m_nItemCount;
    volatile bool m_bFlag;
    int m_current = 0;

    int m_nActTpye;//拍照或者视频模式，默认拍照

    QStringList m_strlstFolders;

    DPushButton *m_lastButton {nullptr};

    QTime m_lastDelTime;

    int m_lastItemCount;

    QFileInfoList m_fileInfoLst;//所有文件信息

    int m_curFileIndex;//当前读取到的文件位置

private:
    void mousePressEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) override;//用于取消鼠标拖拽，避免拖拽时窗口移动
signals:
    void fitToolBar();//调整工具栏
    void enableTitleBar(int nType);//1、禁用标题栏视频；2、禁用标题栏拍照；3、恢复标题栏视频；4、恢复标题栏拍照
    void takePic();
    void takeVd();
    void enableSettings(bool bTrue);
public slots:
    void onFoldersChanged(const QString &strDirectory);
    void onFileChanged(const QString &strDirectory);
    void onBtnClick();
    void onShortcutCopy();
    void onShortcutDel();
    void onTrashFile();
};

#endif // THUMBNAILSBAR_H
