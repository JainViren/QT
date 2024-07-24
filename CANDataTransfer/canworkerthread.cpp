// Copyright 2012 CrossControl
#include<QDebug>
#include "canworkerthread.h"

#include "canwrapper.h"


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <signal.h>

#include <assert.h>

#include <errno.h>

#include <fcntl.h>

#include <stdio.h>

#include <sys/time.h>

#include <QElapsedTimer>

static volatile int iCounter_canworker_thread,ID_for_cheksumcheck;

CanWorkerThread::CanWorkerThread(QObject *parent) :
    QThread(parent)
{
}

// Setup worker thread
// Parameter:
// wrapper - pointer to CAN wrapper instance
void CanWorkerThread::Init(CanWrapper *wrapper)
{
    m_running = true;
    m_can = wrapper;
    iCounter_canworker_thread=0;


    //qDebug() << "can_workerthred_lock" <<can_workerthred_lock.available();
}

// This function will be excuted in an own thread when start is called from parent thread
// It will wait for data from CAN (blocking) and signal to GUI when data arrives
void CanWorkerThread::run()
{
    struct can_frame msg;
    int ret;
    int i;
    int errorCode;

    bool rtr;
    bool extended;
    bool error;

    struct timeval tv;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    ID_for_cheksumcheck = 0;

    int _ideal_time_counter  = 0;
  //  timer_for_measuring_time_taken_to_detect_ball.start();
    // long int * Total_time_taken = new long int(0);

            while(m_running)
    {
        // This call will block but only for one sec to let us abort if m_running = false
        // errorCode is errors related to socket problems, error is can related problems like bus-off

               ++_ideal_time_counter;
        ret = m_can->GetMsg(msg, extended, rtr, error, errorCode, tv);
        //_Devendra qDebug() << "FROM THREAD CAN:-this is what ret made by"<<ret <<"ID count of thread is"<<iCounter_canworker_thread++;



          //     * Total_time_taken =timer_for_measuring_time_taken_to_detect_ball.elapsed();

         //_Devendra  qDebug() <<"time at thread start "<< * Total_time_taken;
        if(ret)
        {
            QString string;

            if(error)   // Error frame
            {   //qDebug() << "FROM THREAD CAN:Error frame" <<"ID count of thread is"<<iCounter_canworker_thread;
                string = QString("Error frame received, class = " +  QString::number(msg.can_id));
            }
            else
            if(extended)   // Extended frame
            {   //_Devendra qDebug() << "FROM THREAD CAN:Extended frame" <<"ID count of thread is"<<iCounter_canworker_thread;
                if(rtr)
                {
                    string = QString("RTR ID: %1 LENGTH: %2").arg(msg.can_id).arg(msg.can_dlc);
                }
                else
                {
                    string = QString("ID: %1 LENGTH: %2 DATA: ").arg(msg.can_id).arg(msg.can_dlc);

                    ID = msg.can_id;
                    Data_0 = msg.data[0];
                    Data_1 = msg.data[1];
                    Data_2 = msg.data[2];
                    Data_3 = msg.data[3];
                    Data_4 = msg.data[4];
                    Data_5 = msg.data[5];
                    Data_6 = msg.data[6];
                    Data_7 = msg.data[7];

                    for(i = 0; i < msg.can_dlc; ++i)
                    {
                        string.append(QString::number(msg.data[i]) + " ");
                    }
                }
            }
            else    // Standard frame
            {
                //_Devendra qDebug() << "FROM THREAD CAN:standard frame" <<"ID count of thread is"<<iCounter_canworker_thread;
                if(rtr)
                {
                    string = QString("RTR ID: %1 LENGTH: %2").arg(msg.can_id).arg(msg.can_dlc);
                }
                else
                {
                    string = QString("ID: %1 LENGTH: %2 DATA: ").arg(msg.can_id).arg(msg.can_dlc);

                    ID = msg.can_id;
                    Data_0 = msg.data[0];
                    Data_1 = msg.data[1];
                    Data_2 = msg.data[2];
                    Data_3 = msg.data[3];
                    Data_4 = msg.data[4];
                    Data_5 = msg.data[5];
                    Data_6 = msg.data[6];
                    Data_7 = msg.data[7];

                    for(i = 0; i < msg.can_dlc; ++i)
                    {
                        string.append(QString::number(msg.data[i]) + " ");
                    }

                }
             }

            // Send string to GUI
            // Because this is an own thread, we must emit a signal rater than making a direct call
            // Because we are in a different thread than the GUI thread, this will put the data onto a queue
            // And will be processed by the GUI thread


            //_Devendra qDebug() << "FROM THREAD CAN:ID_for_cheksumcheck before if"<<ID_for_cheksumcheck ;
            //if(ID_for_cheksumcheck!=(ID^Data_0^Data_1^Data_2^Data_3^Data_4^Data_5^Data_6^Data_7))
            //{
                //qDebug() << "FROM THREAD CAN:ID_for_cheksumcheck inside if"<<ID_for_cheksumcheck ;
                emit msgReceived(ID, Data_0, Data_1, Data_2, Data_3, Data_4, Data_5, Data_6, Data_7);

                if(_ideal_time_counter>1000){
                    emit reset_mpc_disconnection(true);
                    _ideal_time_counter = 0;
                }
                //qDebug() << "ideal_time_counter"<<_ideal_time_counter ;
                //qDebug() << "msg emitted"<<"ID count of thread is"<<iCounter_canworker_thread ;
                //ID_for_cheksumcheck=ID^Data_0^Data_1^Data_2^Data_3^Data_4^Data_5^Data_6^Data_7;


                //qDebug() << "FROM THREAD CAN:ID_for_cheksumcheck after updation"<<ID_for_cheksumcheck ;
            //}


          //_Devendra   * Total_time_taken =timer_for_measuring_time_taken_to_detect_ball.elapsed();

      //_Devendra  qDebug() <<"time at thread end "<< * Total_time_taken;




//start_time =
           // qDebug() <<"Time_taken_by whole funtion"<<timer_for_measuring_time_taken_to_detect_ball.elapsed()-* Total_time_taken ;//<<std::endl<<std::endl;

        }
        else
        {
            if(errorCode)
            {
                QString string = QString("Error detected, errorcode: " + QString::number(errorCode));

                //emit msgReceived(string);
            }
        }
    }
}

// Make thread to stop. Because the thread might be waiting on a blocking call, the call must be unblocked first to actually make the
// thread stop
void CanWorkerThread::shutDown()
{
    m_running = false;
}

bool CanWorkerThread::sendMsg(int ID, int Data_0, int Data_1, int Data_2, int Data_3, int Data_4, int Data_5, int Data_6, int Data_7)
{
    bool temp_return;
    struct can_frame send_can_msg;
    //ID_uchar = ID;
    send_can_msg.can_id = ID;
    send_can_msg.can_dlc = 8;

    //Data_0_uchar = Data_0;
    send_can_msg.data[0] = Data_0;
    send_can_msg.data[1] = Data_1;
    send_can_msg.data[2] = Data_2;
    send_can_msg.data[3] = Data_3;
    send_can_msg.data[4] = Data_4;
    send_can_msg.data[5] = Data_5;
    send_can_msg.data[6] = Data_6;
    send_can_msg.data[7] = Data_7;
    int test;

    //  bool message_sent = m_can->SendMsg(send_can_msg, true, false, test);   // FOR EXTENDED CAN
       bool message_sent = temp_return = m_can->SendMsg(send_can_msg, false, false, test);  // FOR STANDARD CAN


       return temp_return;

    //qDebug() << "Standard CAN Message Sent is True" << message_sent;

}
void CanWorkerThread::sendNMTStartupMsg(int ID, int Data_0, int Data_1)
{
    struct can_frame send_can_msg;
    //ID_uchar = ID;
    send_can_msg.can_id = ID;
    send_can_msg.can_dlc = 2;

    //Data_0_uchar = Data_0;
    send_can_msg.data[0] = Data_0;
    send_can_msg.data[1] = Data_1;
    send_can_msg.data[2] = Data_2;
    send_can_msg.data[3] = Data_3;
    send_can_msg.data[4] = Data_4;
    send_can_msg.data[5] = Data_5;
    send_can_msg.data[6] = Data_6;
    send_can_msg.data[7] = Data_7;
    int test;
    bool message_sent = m_can->SendMsg(send_can_msg, false, false, test);
}
