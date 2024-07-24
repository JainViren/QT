#include "can_handler3.h"

#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <qmath.h>

int can_send_increment;

CAN_Handler3 * CAN_Handler3::CAN_Handler_instance = 0;
CAN_Handler3 * CAN_Handler3::CAN_Current_instance()
{
    if(!CAN_Handler3::CAN_Handler_instance)
    {
        CAN_Handler3::CAN_Handler_instance = new CAN_Handler3;
    }
    return CAN_Handler3::CAN_Handler_instance;
}

CAN_Handler3::CAN_Handler3(QObject *parent) : QObject(parent)
{

    //Set baud rate of Can0
    pCanSetting = CrossControl::GetCanSetting();
    CrossControl::CanSetting_setBaudrate(pCanSetting, 1, 250);

    //Command line to start Can0.  This can also be done through CCAux
    QProcess CANProcess;
    CANProcess.start("ifconfig can0 up");
    CANProcess.waitForFinished();
    CANProcess.close();

    //-------------------CAN Set Up ----------------------------------
    // Create class to handle CAN communication.  This class is created from the canwrapper classes inluded
    can = new CanWrapper();

    // Create a worker thread that listens to CAN messages and sends data to GUI with signal/slot mecanism
    m_workerThread = new CanWorkerThread();

    // connect signal from worker thread to slot in this class
    connect(m_workerThread, SIGNAL(msgReceived(int,int,int,int,int,int,int,int,int)), this, SLOT(msgReceived(int,int,int,int,int,int,int,int,int)));

    // Init new connection
    QString str = "can0";
    int errorCode;
    int ret = can->Init(str.toUtf8(), errorCode);
    if(!ret)
    {
        QMessageBox msgBox;
        msgBox.setText("Could not initialize CAN net. Error code: " + QString::number(errorCode));
        msgBox.exec();

        return;
    }

    // Enable error messages to be reported
    can->EnableErrorMessages();

    // initialize worker thread
    m_workerThread->Init(can);

    // Start thread
    m_workerThread->start();

    // ----------------Init CAN Signals ----------------------------------------------

    i200_Data0=i200_Data1=i200_Data2=i200_Data3=i200_Data4=i200_Data5=0;
    i201_Data0=i201_Data1=i201_Data2=i201_Data3=0;
    iHeartBit_MPC_A=iHeartBit_MPC_B=0;
    i202_Data1=i202_Data2=0;
    i205_Data0=0;
    i206_Data0=i206_Data1=i206_Data2=i206_Data3=0;
    i207_Data0=i207_Data1=i207_Data2=i207_Data3=0;
    i208_Data0=i208_Data1=i208_Data2=i208_Data3=0;
    i209_Data0=0;
    i210_Data0=i210_Data1=i210_Data2=i210_Data3=0;
    i211_Data0=0;
    i212_Data0=i212_Data1=i212_Data2=i212_Data3=0;
    i213_Data0=i213_Data1=0;
    i218_Data0=i218_Data1=i218_Data2=i218_Data3=0;
    i219_Data0=i219_Data1=0;
    d214_Data0=d214_Data1=0;
    d215_Data0=d215_Data1=0;
    i702_Data0=i702_Data2=i702_Data3=0;
    i705_Data0=i705_Data1=i705_Data2=i705_Data3=0;
    i706_Data0=0;
    i707_Data0=i707_Data1=i707_Data2=i707_Data3=0;
    i708_Data0=0;
    iECan_Heartbit=0;
    i416_Data0=i416_Data1=i416_Data2=i416_Data3=0;
    iAlarm_1=iAlarm_2=0;
    iJoystick_X_pos=iJoystick_X_nag=iJoystick_Y_pos=iJoystick_Y_nag=0;
    bJoystick_Trigger=bJoystick_LH_Button=bJoystick_RH_Button=0;
    iMPCA_Project_Version=iMPCB_Project_Version=0;
    iMPIO_HeartBit=0;
    i301_Data0=i301_Data1=0;
    i305_Data0=i305_Data1=i305_Data2=i305_Data3=i305_Data4=i305_Data5=i305_Data6=i305_Data7=0;
    iLh_Auger_Set_spd=iRh_Auger_Set_spd=iMixe_Set_spd=0;
}



CAN_Handler3::~CAN_Handler3()
{

}

void CAN_Handler3::msgReceived(int ID, int Data_0, int Data_1, int Data_2, int Data_3, int Data_4, int Data_5, int Data_6, int Data_7)
{
    //When a new message is received by the worker thread this slot is called.  The worker thread will pass the ID of the new message as well as the 8 bytes of data
    //Take the ID and find the CAN message ID
    QByteArray c = QByteArray::number(ID, 16);
    if (c.length() == 2)
    {
        ID = c.mid(0, 2).toInt(0, 16);
    }
    else if (c.length() == 7)
    {
        ID = c.mid(1,4).toInt(0,16);
    }
    else if (c.length() == 8)
    {
        ID = c.mid(2, 4).toInt(0, 16);
    }

    //Now that we have the CAN message ID, look for the CAN PGN you want and pull out the correct data for the necissary signal in that PGN
    switch(ID)
    {
//****************************MPC330 A *******************************
    case 10:
        qDebug()<<QString::number(Data_0);
    case 200: //MPC330
    {
        iHeartBit_MPC_A = Data_0;
        i200_Data1 = Data_2; // MPC A DI
        i200_Data2 = Data_3; // MPC A DO
        i200_Data3 = Data_4; // MPC A DO PWM
        i200_Data5 = Data_5; // MPC A DO Voltage PWM
        i200_Data4 = Data_6; // Keypad disconnection
        if(i200_Data4 >> 0 & 1)
        {    iLeft_keypad_Heartbit = 0;    }
        else
        {    iLeft_keypad_Heartbit = 5;     }
        if(i200_Data4 >> 1 & 1)
        {    iRight_keypad_Heartbit = 0;    }
        else
        {    iRight_keypad_Heartbit = 5;     }

    }
    break;

    case 201: //Keypad Inputs
    {
        i201_Data1 = (Data_3 <<8|Data_2); // Left keyboard inputs
        i201_Data2 = (Data_5 <<8|Data_4); // Right Keyboard inputs
    }
    break;

    case 202: //Keypad Outputs
    {
        i202_Data0 = (Data_1 <<8|Data_0); // Left keyboard Outputs
        i202_Data1 = (Data_3 <<8|Data_2); // Left keyboard Outputs
        i202_Data2 = (Data_5 <<8|Data_4); // Right Keyboard Outputs
        i202_Data3 = (Data_7 <<8|Data_6); // Right Keyboard Outputs
    }
    break;

    case 205: //Eng Hr
    {
        i205_Data0 = (Data_1 <<8|Data_0);

    }
    case 206: //MPC 330 FRQ Inputs
    {
        i206_Data0 = (Data_1 <<8|Data_0);
        i206_Data1 = (Data_3 <<8|Data_2);
        i206_Data2 = (Data_5 <<8|Data_4);
        i206_Data3 = (Data_7 <<8|Data_6);
    }
    break;

    case 207: //Act RPM
    {
        i207_Data0 = (Data_1 <<8|Data_0); // Cement
        i207_Data1 = (Data_3 <<8|Data_2); // Engine RPM
        i207_Data2 = (Data_5 <<8|Data_4); // Agg Conveyor
        i207_Data3 = (Data_7 <<8|Data_6); // Mixer
    }
    break;

    case 208: //MPC A AI RAW Count
    {
        i208_Data0 = (Data_1 <<8|Data_0);
        i208_Data1 = (Data_3 <<8|Data_2);
        i208_Data2 = (Data_5 <<8|Data_4);
        i208_Data3 = (Data_7 <<8|Data_6);
    }
    break;

    case 209: //MPC A AI RAW Count
    {
        i209_Data0 = (Data_1 <<8|Data_0);

    }
    break;
    case 210: //MPC A AI Scaled value
    {
        i210_Data0 = (Data_1 <<8|Data_0);
        i210_Data1 = (Data_3 <<8|Data_2);
        i210_Data2 = (Data_5 <<8|Data_4);
        i210_Data3 = (Data_7 <<8|Data_6);
    }
    break;
    case 211: //MPC A AI Scaled value
    {
        i211_Data0 = (Data_1 <<8|Data_0);
    }
    break;
    case 212: //MPC A set current value
    {
        i212_Data0 = (Data_1 <<8|Data_0);
        i212_Data1 = (Data_3 <<8|Data_2);
        i212_Data2 = (Data_5 <<8|Data_4);
        i212_Data3 = (Data_7 <<8|Data_6);
    }
    break;
    case 213: //MPC A set current value
    {
        i213_Data0 = (Data_1 <<8|Data_0);
        i213_Data1 = (Data_3 <<8|Data_2);
    }
    break;
    case 214: //MPC A PWM Voltage Dutycycle
    {
        d214_Data0 = (Data_3 <<16|Data_2 <<12|Data_1 <<8|Data_0);
        d214_Data1 = (Data_7 <<16|Data_6 <<12|Data_5 <<8|Data_4);
    }
    break;
    case 215: //MPC A PWM Voltage Dutycycle
    {
        d215_Data0 = (Data_3 <<16|Data_2 <<12|Data_1 <<8|Data_0);
        d215_Data1 = (Data_7 <<16|Data_6 <<12|Data_5 <<8|Data_4);
    }
    break;
    case 218: //MPC A Act current value
    {
        i218_Data0 = (Data_1 <<8|Data_0);
        i218_Data1 = (Data_3 <<8|Data_2);
        i218_Data2 = (Data_5 <<8|Data_4);
        i218_Data3 = (Data_7 <<8|Data_6);
    }
    break;
    case 219: //MPC A Act current value
    {
        i219_Data0 = (Data_1 <<8|Data_0);
        i219_Data1 = (Data_3 <<8|Data_2);
    }
    break;

    case 220: //MPC A Software version
    {
        iMPCA_Project_Version = (Data_1 <<8|Data_0);
    }
    break;

    case 221: //Alarm
    {
        iAlarm_1 = (Data_1 <<8|Data_0);
        iAlarm_2 = (Data_3 <<8|Data_2);
    }
    break;

    case 222: //Auger & Mixer Set mA
    {
        iLh_Auger_Set_spd   = (Data_1 <<8|Data_0);
        iRh_Auger_Set_spd   = (Data_3 <<8|Data_2);
        iMixe_Set_spd       = (Data_5 <<8|Data_4);
    }
    break;

    case 300: //MPIO HeartBit
    {
        iMPIO_HeartBit = Data_0;
    }
    break;

    case 301: //MPIO DI
    {
        i301_Data0 = Data_0;
        i301_Data1 = Data_1;
    }
    break;

    case 305: //MPIO DO
    {
        i305_Data0 = Data_0;
        i305_Data1 = Data_1;
        i305_Data2 = Data_2;
        i305_Data3 = Data_3;
        i305_Data4 = Data_4;
        i305_Data5 = Data_5;
        i305_Data6 = Data_6;
        i305_Data7 = Data_7;

    }
    break;
    case 400: //ETU HeartBit
    {
        iETU_Heartbit = Data_0;
    }
    break;
    case 415: //ECAN HeartBit
    {
        iECan_Heartbit = Data_0;

    }
    break;

    case 416: //ECAN Inputs
    {
        i416_Data0 = (Data_1 <<8|Data_0);
        i416_Data1 = (Data_3 <<8|Data_2);
        i416_Data2 = Data_4;
        i416_Data3 = Data_5;
    }
    break;

    case 700: //MPC330 B HeatBit
    {
        iHeartBit_MPC_B = Data_0;
    }
    break;

    case 702: //MPC330 B DI/DO
    {
        i702_Data0 = Data_0; // MPC B DI
        i702_Data2 = Data_2; // MPC B DO
        i702_Data3 = Data_3; // MPC A DO PWM
    }
    break;

    case 705: //MPC330 B PWM Set Current
    {
        i705_Data0 = (Data_1 <<8|Data_0);
        i705_Data1 = (Data_3 <<8|Data_2);
        i705_Data2 = (Data_5 <<8|Data_4);
        i705_Data3 = (Data_7 <<8|Data_6);
    }
    break;

    case 706: //MPC330 B PWM Set Current
    {
        i706_Data0 = (Data_1 <<8|Data_0);
    }
    break;

    case 707: //MPC330 B PWM Act Current
    {
        i707_Data0 = (Data_1 <<8|Data_0);
        i707_Data1 = (Data_3 <<8|Data_2);
        i707_Data2 = (Data_5 <<8|Data_4);
        i707_Data3 = (Data_7 <<8|Data_6);
    }
    break;

    case 708: //MPC330 B PWM Act Current
    {
        i708_Data0 = (Data_1 <<8|Data_0);
    }
    break;

    case 709: //MPC B Software version
    {
        iMPCB_Project_Version = (Data_1 <<8|Data_0);
    }
    break;



    case 64982: //Joystick Inputs
    {
        iJoystick_X_pos = (Data_1 <<8|Data_0);
        iJoystick_Y_pos = (Data_3 <<8|Data_2);
        bJoystick_Trigger = Data_7 >> 0;
        if (Data_5 >> 6 & 1){
        bJoystick_LH_Button = true;
        }
        else{ bJoystick_LH_Button = false;}
        if (Data_5 >> 4 & 1){
        bJoystick_RH_Button = true;
        }
        else{ bJoystick_RH_Button = false;}

    }
    break;

    default:
     break;

    }
}
void CAN_Handler3::sendCAN(int CAN_ID, int Data0, int Data1, int Data2, int Data3, int Data4, int Data5, int Data6, int Data7)
{
    //This is a short example of sending a CAN message.  It simply sends a message which incements the first byte of data each time sendCAN is called.
    //See the sendMsg function in the worker thread class to see what needs to be sent
 //   can_send_increment++;

    m_workerThread->sendMsg(CAN_ID,Data0,Data1,Data2,Data3,Data4,Data5,Data6,Data7);
 //   qDebug() << can_send_increment;
}


void CAN_Handler3::sendNMTStartup(int ID, int Data0, int Data1)
{
    m_workerThread->sendNMTStartupMsg(ID,Data0,Data1);
 // Zee   m_workerThread1->sendNMTStartupMsg(ID,Data0,Data1);
}
