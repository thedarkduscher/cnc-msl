/*
 * Copyright (C) 2009-2015,
 * Intelligent Robotics and Intelligent Systems (IRIS) Lab
 * CAMBADA robotic soccer team – http://robotica.ua.pt/CAMBADA/
 * University of Aveiro, Portugal
 *
 * This file is part of the CAMBADA BASESTATION
 *
 * CAMBADA BASESTATION is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CAMBADA BASESTATION is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this package.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __FULLWINDOW_H
#define __FULLWINDOW_H

#include "ui_FullWindow.h"
#include <QtGui>

class FWind : public QMainWindow , public Ui::FullWindow
{
    Q_OBJECT

public:
    FWind(QMainWindow *parent =0);
    ~FWind();

private:
    bool fullscreenflag;
    QMainWindow *fullwindow;

    //FieldWidget *Fieldwdg;

    QTimer *UpdateTimer;

public slots:
    void WindowFullScreenMode (void);
    void UpdateGameInfo(void);

};


#endif
