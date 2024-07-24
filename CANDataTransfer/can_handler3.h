#ifndef CAN_HANDLER3_H
#define CAN_HANDLER3_H

//Can Includes
#include <canworkerthread.h>
#include "CanSetting.h"

class CAN_Handler3 : public QObject
{
    //Need to add this to be able to add the QPROPERTY below
    Q_OBJECT
    //The Q_PROPERTY needs to be setup to expose the class signals and slots to QML as is done in the main.cpp file
   // Q_PROPERTY(int EngineSpeed READ getEngineSpeed NOTIFY EngineSpeedChanged)

public:
    explicit CAN_Handler3(QObject *parent = 0);
    ~CAN_Handler3();

    static CAN_Handler3 * CAN_Handler_instance;
    static CAN_Handler3 * CAN_Current_instance();


    int i200_Data0,i200_Data1,i200_Data2,i200_Data3,i200_Data4,i200_Data5;
    int i201_Data0,i201_Data1,i201_Data2,i201_Data3;
    int i202_Data0,i202_Data1,i202_Data2,i202_Data3;
    int iLeft_keypad_Heartbit, iRight_keypad_Heartbit;
    int iECan_Heartbit, iETU_Heartbit,iJoystick_Heartbit,iMPIO_HeartBit;
    int iMPC330A_DI_Data2;
    int iHeartBit_MPC_A, iHeartBit_MPC_B;
    int i206_Data0,i206_Data1,i206_Data2,i206_Data3;
    int i207_Data0,i207_Data1,i207_Data2,i207_Data3;
    int i208_Data0,i208_Data1,i208_Data2,i208_Data3;
    int i209_Data0;
    int i205_Data0;
    int i210_Data0,i210_Data1,i210_Data2,i210_Data3;
    int i211_Data0;
    int i212_Data0,i212_Data1,i212_Data2,i212_Data3;
    int i213_Data0,i213_Data1;
    int i218_Data0,i218_Data1,i218_Data2,i218_Data3;
    int i219_Data0,i219_Data1;
    double d214_Data0, d214_Data1;
    double d215_Data0, d215_Data1;
    int i702_Data0, i702_Data2, i702_Data3;
    int i705_Data0,i705_Data1,i705_Data2,i705_Data3;
    int i706_Data0;
    int i707_Data0, i707_Data1, i707_Data2,i707_Data3;
    int i708_Data0;
    int i416_Data0,i416_Data1,i416_Data2,i416_Data3;
    int iAlarm_1,iAlarm_2;
    int iJoystick_X_pos,iJoystick_X_nag,iJoystick_Y_pos,iJoystick_Y_nag;
    bool bJoystick_Trigger,bJoystick_LH_Button, bJoystick_RH_Button;
    int iMPCA_Project_Version,iMPCB_Project_Version;
    int i301_Data0,i301_Data1;
    int i305_Data0,i305_Data1,i305_Data2,i305_Data3,i305_Data4,i305_Data5,i305_Data6,i305_Data7;
    int iLh_Auger_Set_spd,iRh_Auger_Set_spd,iMixe_Set_spd;

public slots:
    void msgReceived(int ID, int Data_0, int Data_1, int Data_2, int Data_3, int Data_4, int Data_5, int Data_6, int Data_7);
    void sendCAN(int ID, int Data0, int Data1, int Data2, int Data3, int Data4, int Data5, int Data6, int Data7);
    void sendNMTStartup(int ID,int Data0,int Data1);

signals:
    //this needs to be setup to expose the class to QML.  This will tell the QML code when the engine speed value is changed so it is updated
     void Data0(int);
     void Data1(int);
     void Data2(int);
     void Data3(int);
     void RotationValueForDisplayChanged(QString);
     void RotarySensorValueChanged(long);


private:
    //CAN CCAux declarations
    CrossControl::CANSETTINGHANDLE pCanSetting;
    CanWrapper *can;                    // Can wrapper class
    CanWorkerThread *m_workerThread;    // Thread that blocks and listens for CAN messages




private slots:

};

#endif // CAN_HANDLER3_H
