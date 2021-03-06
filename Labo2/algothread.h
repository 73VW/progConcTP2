/*               Programmation Concurrente
 *                  Labo2
 *                 Laurent Gander et Maël Pedretti
 *               HE-Arc 2017
 */


#ifndef ALGOTHREAD_H
#define ALGOTHREAD_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <windows.h>
#include <QWaitCondition>

#include "mainwindow.h"
#include "paramlist.h"

using namespace std;

class AlgoThread : public QThread
{
    Q_OBJECT
public:
    AlgoThread(MainWindow* mainWindow,int nbSite,int nbHabitants,int nbBorne,int nbVelo);

    friend void* runHabitants(void*);
    friend void* runMaintenance(void*);

protected:
     void run();

signals:
     void initSite(int siteId,int nbVelo);
     void initHabitant(int habId,int initSiteId);
     void initCamion();

     void setHabitantState(int habId,int param);
     void setSiteVelo(int idSite,int nbVelo);
     void startDeplacement(int habId,int initSite,int destSite,int parcourTime);

     void setDepotVelo(int nbVeloDep);
     void setCamVelo(int nbVeloCam);
     void startCamionDeplacement(int initSite,int destSite,int parcourTime);

private:
     int nbSite;
     int nbHabitants;
     int nbBorne;
     int nbVelo;
     QMutex **mutex;
     QWaitCondition **conditionsArr;
};

struct initHab {
    AlgoThread* algoThread;
    int posDep;
    int posArr;
    bool enRoute;
    int tempsAttente;
    int id;
    int tempsTrajet;
    int* nbVeloSite;
    QMutex** mutex;
    int nbSite;
    int nbBorne;
    QWaitCondition **conditionsArr;
};

struct initDep {
    AlgoThread* algoThread;
    int nbVelo;
    int nbSite;
    int* nbVeloSite;
    int nbBorne;
    QMutex** mutex;
    QWaitCondition **conditionsArr;
    //MORE THINGS HERE
};


#endif // ALGOTHREAD_H
