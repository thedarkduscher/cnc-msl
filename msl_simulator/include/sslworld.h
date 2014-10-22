/*
grSim - RoboCup Small Size Soccer Robots Simulator
Copyright (C) 2011, Parsian Robotic Center (eew.aut.ac.ir/~parsian/grsim)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SSLWORLD_H
#define SSLWORLD_H


#include <QGLWidget>
#include <QObject>
#include <QUdpSocket>
#include <QList>


#include "graphics.h"
#include "physics/pworld.h"
#include "physics/pball.h"
#include "physics/pground.h"
#include "physics/pfixedbox.h"
#include "physics/pray.h"

#include "net/robocup_ssl_server.h"
#include "net/MSLSimulatorROSCommunication.h"
#include "msl_simulator/messages_robocup_ssl_wrapper.h"

#include "robot.h"
#include "configwidget.h"

#include "config.h"

#define WALL_COUNT 10

class RobotsFomation;
class SendingPacket {
    public:
    SendingPacket(msl_simulator::messages_robocup_ssl_wrapperPtr _packet,int _t);
    msl_simulator::messages_robocup_ssl_wrapperPtr packet;
    int t;
};

class SSLWorld : public QObject
{
    Q_OBJECT
private:
    QGLWidget* m_parent;
    int framenum;
    dReal last_dt;
    QList<SendingPacket*> sendQueue;
    char packet[200];
    char *in_buffer;    
public:    
    dReal customDT;
    bool isGLEnabled;
    SSLWorld(QGLWidget* parent,ConfigWidget* _cfg,RobotsFomation *form1,RobotsFomation *form2);
    virtual ~SSLWorld();
    void glinit();
    void step(dReal dt=-1);
    msl_simulator::messages_robocup_ssl_wrapperPtr generatePacket();
    void sendVisionBuffer();
    ConfigWidget* cfg;
    CGraphics* g;
    PWorld* p;
    PBall* ball;
    PGround* ground;
    PRay* ray;
    PFixedBox* walls[WALL_COUNT];
    int selected;
    bool show3DCursor;
    dReal cursor_x,cursor_y,cursor_z;
    dReal cursor_radius;
    RoboCupSSLServer *visionServer;
    msl_simulator::MSLSimulatorROSCommunication *rosCommunicator;
    QTimer *recvTimer;
    QUdpSocket *blueStatusSocket,*yellowStatusSocket;
    bool updatedCursor;
    Robot* robots[ROBOT_COUNT*2];
    QTime *timer;
    int sendGeomCount;
public slots:
    void recvActions();
signals:
    void fpsChanged(int newFPS);
};

class RobotsFomation {
    public:
        dReal x[ROBOT_COUNT];
        dReal y[ROBOT_COUNT];
        RobotsFomation(int type);
        void setAll(dReal *xx,dReal *yy);
        void loadFromFile(const QString& filename);
        void resetRobots(Robot** r,int team);
};

dReal fric(dReal f);
int robotIndex(int robot,int team);

#endif // SSLWORLD_H
