/* XiVO Client
 * Copyright (C) 2007-2015 Avencall
 *
 * This file is part of XiVO Client.
 *
 * XiVO Client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version, with a Section 7 Additional
 * Permission as follows:
 *   This notice constitutes a grant of such permission as is necessary
 *   to combine or link this software, or a modified version of it, with
 *   the OpenSSL project's "OpenSSL" library, or a derivative work of it,
 *   and to copy, modify, and distribute the resulting work. This is an
 *   extension of the special permission given by Trolltech to link the
 *   Qt code with the OpenSSL library (see
 *   <http://doc.trolltech.com/4.4/gpl.html>). The OpenSSL library is
 *   licensed under a dual license: the OpenSSL License and the original
 *   SSLeay license.
 *
 * XiVO Client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XiVO Client.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <baseengine.h>
#include <phonenumber.h>

#include "history.h"
#include "history_model.h"
#include "history_view.h"

History::History(QWidget *parent)
    : XLet(parent, tr("History"), ":/images/tab-history.svg"),
      m_model(NULL),
      m_proxy_model(NULL)
{
    this->ui.setupUi(this);

    QFile qssFile(QString(":/default.qss"));
    if(qssFile.open(QIODevice::ReadOnly)) {
        this->setStyleSheet(qssFile.readAll());
    }

    m_model = new HistoryModel(this);
    this->ui.history_table->setModel(m_model);

    m_proxy_model = new HistorySortFilterProxyModel(this);
    m_proxy_model->setSourceModel(m_model);
    this->ui.history_table->setModel(m_proxy_model);
    this->ui.history_table->sortByColumn(0, Qt::AscendingOrder);

    QAction *sent_call_action = this->ui.menu->addAction(tr("Sent calls"));
    QAction *received_call_action = this->ui.menu->addAction(tr("Received calls"));
    QAction *missed_call_action = this->ui.menu->addAction(tr("Missed calls"));

    connect(sent_call_action, SIGNAL(triggered()),
            m_model, SLOT(sentCallMode()));
    connect(received_call_action, SIGNAL(triggered()),
            m_model, SLOT(receivedCallMode()));
    connect(missed_call_action, SIGNAL(triggered()),
            m_model, SLOT(missedCallMode()));

    this->ui.menu->setSelectedAction(0);
}

XLet* XLetHistoryPlugin::newXLetInstance(QWidget *parent)
{
    b_engine->registerTranslation(":/obj/history_%1");
    return new History(parent);
}
