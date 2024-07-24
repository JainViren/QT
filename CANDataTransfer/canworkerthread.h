// Copyright 2012 CrossControl

#ifndef CANWORKERTHREAD_H
#define CANWORKERTHREAD_H

#include <QThread>
#include <QSemaphore>

#include "canwrapper.h"
#include <linux/types.h>
#include <QElapsedTimer>

//extern  static QSemaphore  can_workerthred_lock;//,sema_start_getting,sema_screen_change_1;

class CanWorkerThread : public QThread
{
    Q_OBJECT
public:



    QElapsedTimer timer_for_measuring_time_taken_to_detect_ball;
    explicit CanWorkerThread(QObject *parent = 0);

    void Init(CanWrapper *wrapper); // Initialize

    void run();         // start thread

    void shutDown();    // Make thread shut down

    bool m_running;     // Set to false to stop thread



signals:
    void msgReceived(int ID, int Data_0, int Data_1, int Data_2, int Data_3, int Data_4, int Data_5, int Data_6, int Data_7);
    void reset_mpc_disconnection(bool temp);

public slots:
    bool sendMsg (int ID, int Data_0, int Data_1, int Data_2, int Data_3, int Data_4, int Data_5, int Data_6, int Data_7);
    void sendNMTStartupMsg (int ID, int Data_0, int Data_1);
private:
    CanWrapper *m_can;  // Pointer to can wrapper class

    //bool m_running;     // Set to false to stop thread

    int ID;
    int Data_0;
    int Data_1;
    int Data_2;
    int Data_3;
    int Data_4;
    int Data_5;
    int Data_6;
    int Data_7;

    long int start_time;

    //int ID_for_cheksumcheck;
    //int Data_0_for_cheksumcheck;
    //int Data_1_for_cheksumcheck;
    //int Data_2_for_cheksumcheck;
    //int Data_3_for_cheksumcheck;
    //int Data_4_for_cheksumcheck;
    //int Data_5_for_cheksumcheck;
    //int Data_6_for_cheksumcheck;
    //int Data_7_for_cheksumcheck;

    unsigned char ID_uchar;
    unsigned char Data_0_uchar;
    unsigned char Data_1_uchar;
    unsigned char Data_2_uchar;
    unsigned char Data_3_uchar;
    unsigned char Data_4_uchar;
    unsigned char Data_5_uchar;
    unsigned char Data_6_uchar;
    unsigned char Data_7_uchar;

};

#endif // CANWORKERTHREAD_H
