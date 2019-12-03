#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>            /* For printf(). */
#include <string.h>           /* For strcpy(), strcat(). */
#include <time.h>             /* For clock(). */
#include <visa.h>             /* Keysight VISA routines. */

#include <QtGlobal>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if 0
    ViStatus VISAstatus;                   /* VISA function return value. */

    ViSession defrm, session;        /* Device session ID. */


    char chStatusDesc[_MAX_DIR] = {0};
        int retCnt=0;
        char instrDesc[100]={0};
        ViFindList find_list;
        float voltSetting, currSetting;
//        voltSetting = atof(ini_powervolt);
//        currSetting = atof(ini_powercurrent);
        VISAstatus=viOpenDefaultRM(&defrm);
        if (VISAstatus != VI_SUCCESS)
        {
            return;
//            return false;
        }
        VISAstatus = viFindRsrc(defrm,"GPIB?*INSTR",&find_list,(ViPUInt32)&retCnt, instrDesc);

        VISAstatus=viOpen(defrm,instrDesc, VI_NULL, VI_NULL, &session);

        if (VISAstatus!=VI_SUCCESS)
        {
            return;
//            return false;
        }
//    ————————————————
//    版权声明：本文为CSDN博主「好儿郎-志在四方」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//    原文链接：https://blog.csdn.net/rl529014/article/details/79586993
//


        /* Close the vi session and the resource manager session. */
          viClose(session);
          viClose(defrm);



//https://blog.csdn.net/u013472106/article/details/52924033

//          ViChar buffer[255];
//          ViRsrc mathes=buffer;
//          ViUInt32 nmatched;
//          ViFindList list;


//          viFindRsrc(defaultRM,"GPIB?*INSTR",&list,&nmatched,matched);
//          viFindNext(list,matches);
//          viFindNext(list,matches);
//          ...
//          viClose(list);



          ////GPIB 自动查找设备代码
//          https://blog.csdn.net/a379039233/article/details/17469705

#endif

//          int retCnt=0;
//              char buf [256] = {0};
//              char instrDesc[100]={0};
//              ViSession defaultRM,vi;
//              ViStatus status;
//              ViFindList
//                      find_list;
//              viOpenDefaultRM (&defaultRM);
//              status = viFindRsrc(defaultRM, "USB0::?*INSTR",
//                                  &find_list, &retCnt, instrDesc);
//              status = viOpen(defaultRM,instrDesc,
//                              VI_NULL,VI_NULL, &vi);
//              if (status != VI_SUCCESS){
//                  printf("Can not find USBTMC device!\n");
//                  viClose(vi);
//                  viClose (defaultRM);
//                  return;
//              }
//              printf("USBTMC device : %s\n",instrDesc);
//              viPrintf(vi,"*idn?\n");
//              viScanf (vi, "%t", &buf);
//              printf("%s\n",buf);
//              viClose (vi);
//              viClose (defaultRM);

////          ————————————————
////          版权声明：本文为CSDN博主「宇宙379」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
////          原文链接：https://blog.csdn.net/a379039233/article/details/17469705
///
///
///
          ViUInt32 retCnt=0;
              char buf [256] = {0};
              char instrDesc[100]={0};
              ViSession defaultRM,vi;
              ViStatus status;
              ViFindList  find_list;
              status=viOpenDefaultRM (&defaultRM);
              if (status != VI_SUCCESS){
                  qDebug()<<"viOpenDefaultRM() fail";
                  return;
              }
              status = viFindRsrc(defaultRM,ViString("GPIB?*INSTR"),
                                  &find_list, &retCnt, instrDesc);

              if (status != VI_SUCCESS){
                  qDebug()<<"viFindRsrc() fail";
                  return;
              }
              else{
                  qDebug()<<"retCnt:"<<retCnt;
              }

              //          viFindNext(list,matches);
              //          viFindNext(list,matches);
              //          ...
              //          viClose(list);



//              ViChar buffer[255];
//              ViRsrc mathes=buffer;
//              ViUInt32 nmatched;
//              status = viFindNext(find_list,instrDesc);
//              if (status != VI_SUCCESS){
//                  qDebug("viFindNext fail!\n");
////                  viClose(vi);
////                  viClose (defaultRM);
////                  return;
//              }
//              else{
//                  qDebug("viFindNext ok!\n");
//                  qDebug("viFindNext instrDesc  : %s\n",instrDesc);
//              }


              status = viOpen(defaultRM,instrDesc,
                              VI_NULL,VI_NULL, &vi);
              if (status != VI_SUCCESS){
                  qDebug("Can not find GPIB device!\n");
                  viClose(vi);
                  viClose (defaultRM);
                  return;
              }


//              GPIB仪器控制属性：
//              VI_ATTR_GPIB_PRIMARY_ADDR   GPIB主地址
//              VI_ATTR_GPIB_SECONDARY_ADDR       GPIB副地址

//              VI_ATTR_INTF_PAERNT_NUM GPIB板号

//              VI_ATTR_INTF_NUM 板号

//              ViUInt32 moduleID;
//              viGetAttribute (vi, VI_ATTR_MODEL_CODE, &moduleID);
//              qDebug()<<"moduleID:"<<moduleID;


              ViUInt16 intf_num;
              status = viGetAttribute (vi, VI_ATTR_INTF_NUM, &intf_num);
              if (status != VI_SUCCESS){
                  qDebug("VI_ATTR_INTF_NUM fail!\n");
                  viClose(vi);
                  viClose (defaultRM);
                  return;
              }
              qDebug()<<"intf_num:"<<intf_num;
              ViUInt16 primary;
              viGetAttribute (vi, VI_ATTR_GPIB_PRIMARY_ADDR, &primary);
              qDebug()<<"primary:"<<primary;
              ViUInt16 second;
              status = viGetAttribute (vi, VI_ATTR_GPIB_SECONDARY_ADDR, &second);
              if (status != VI_SUCCESS){
                  qDebug("VI_ATTR_GPIB_SECONDARY_ADDR fail!\n");
                  viClose(vi);
                  viClose (defaultRM);
                  return;
              }
              qDebug()<<"second:"<<second;


//              qDebug("GPIB device : %s\n",instrDesc);
//              viPrintf(vi,ViString("*idn?\n"));
//              viScanf (vi, ViString("%t"), &buf);
//              qDebug("%s\n",buf);


//              char receiveBufferArrary[256] = {0};
////              if(!write(DMMaddr, "CONF:CURR:DC DEF")) return false;
////              if(!read(DMMaddr, "READ?", strRead)) return false;
//              status = viPrintf(vi,ViString("CONF:CURR:DC DEF"));
//              if (status != VI_SUCCESS){
//                  qDebug("CONF:CURR:DC DEF fail");
//              }
////              viPrintf(vi,ViString("READ?"));

              double resultDC;
//              status = viQueryf(vi, ViString("FETCH:CURR?\n"), ViString("%lf"), &resultDC);
//              status = viQueryf(vi,ViString("READ ?"),ViString("%t"),receiveBufferArrary);
              viQueryf(vi, ViString("MEAS:CURR?\n"), ViString("%lf"), &resultDC);
//              viScanf(vi,ViString("%t"), receiveBufferArrary);
//              status = viQueryf(vi, ViString("MEAS:CURR?\n"),ViString("%lf"), &resultDC);
              if (status != VI_SUCCESS){
                  qDebug("READ? fail");
              }
              else{

              }




              qDebug()<<resultDC;
                         //              viScanf (vi, ViString("%t"), &receiveBufferArrary);
//              qDebug("%s\n",receiveBufferArrary);




              viClose (vi);
              viClose (defaultRM);

//          ————————————————
//          版权声明：本文为CSDN博主「宇宙379」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//          原文链接：https://blog.csdn.net/a379039233/article/details/17469705

}

MainWindow::~MainWindow()
{
    delete ui;
}

