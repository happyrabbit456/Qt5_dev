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

    sample_viFindRsrc();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sample()
{

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
    char buf[256] = {0};
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


    ////              if(!write(DMMaddr, "CONF:CURR:DC DEF")) return false;
    ////              if(!read(DMMaddr, "READ?", strRead)) return false;


    double resultDC;

    //方法二
    status = viQueryf(vi, ViString("MEAS:CURR:DC?\n"), ViString("%lf"), &resultDC); //OK

    if (status != VI_SUCCESS){
        qDebug()<<"333";
    }
    else{
        qDebug()<<resultDC;
    }


    //方法一
    status = viPrintf(vi,ViString("CONF:CURR:DC"));
    if (status != VI_SUCCESS){
        qDebug()<<"viPrintf(vi,ViString(CONF:CURR:DC)) fail";
    }


    status = viPrintf(vi,ViString("READ?\n"));
    if (status != VI_SUCCESS){
        qDebug()<<"111";
    }
    status = viQueryf(vi,ViString("READ?\n"), ViString("%lf"), &resultDC);
    if (status != VI_SUCCESS){
        qDebug()<<"222";
    }
    else{
        qDebug()<<resultDC;
    }


    //方法三
    static unsigned char buffer[100];
    static char stringinput[512];
    static ViUInt32 retCount;
    static ViUInt32 writeCount;


    status = viPrintf(vi,ViString("CONF:CURR:DC"));
    if (status != VI_SUCCESS){
        qDebug()<<"viPrintf(vi,ViString(CONF:CURR:DC)) fail";
    }

    strcpy(stringinput,"READ?\n");
    status = viWrite (vi, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
    if (status < VI_SUCCESS)
    {
        qDebug("Error writing to the device\n");
    }

    status = viRead (vi, buffer, 100, &retCount);
    if (status < VI_SUCCESS)
    {
        qDebug("Error reading a response from the device\n");
    }
    else
    {
        qDebug("Data read: %*s\n",retCount,buffer);
    }


    //              5.291e-07
    //              4.673e-07
    //              Data read: +5.29100000E-07


    viClose (vi);
    viClose (defaultRM);

    //          ————————————————
    //          版权声明：本文为CSDN博主「宇宙379」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
    //          原文链接：https://blog.csdn.net/a379039233/article/details/17469705


}

ViStatus MainWindow::sample_viFindRsrc()
{
    static char instrDescriptor[VI_FIND_BUFLEN];
    static ViUInt32 numInstrs;
    static ViFindList findList;
    static ViSession defaultRM, instr;
    static ViStatus status;

    /* First we will need to open the default resource manager. */
      status = viOpenDefaultRM (&defaultRM);
      if (status < VI_SUCCESS)
      {
         qDebug("Could not open a session to the VISA Resource Manager!\n");
         exit (EXIT_FAILURE);
      }

       /*
        * Find all the VISA resources in our system and store the number of resources
        * in the system in numInstrs.  Notice the different query descriptions a
        * that are available.
           Interface         Expression
       --------------------------------------
           GPIB              "GPIB[0-9]*::?*INSTR"
           VXI               "VXI?*INSTR"
           GPIB-VXI          "GPIB-VXI?*INSTR"
           Any VXI           "?*VXI[0-9]*::?*INSTR"
           Serial            "ASRL[0-9]*::?*INSTR"
           PXI               "PXI?*INSTR"
           All instruments   "?*INSTR"
           All resources     "?*"
       */
      //caijx fix
//      status = viFindRsrc (defaultRM, ViString("?*INSTR"), &findList, &numInstrs, instrDescriptor);
      status = viFindRsrc(defaultRM,ViString("GPIB?*INSTR"), &findList, &numInstrs, instrDescriptor);

      if (status < VI_SUCCESS)
      {
         qDebug ("An error occurred while finding resources.\nHit enter to continue.");
         //caijx fix
//         fflush(stdin);
//         getchar();
         viClose (defaultRM);
         return status;
      }

      qDebug("%d instruments, serial ports, and other resources found:\n\n",numInstrs);
      qDebug("%s \n",instrDescriptor);

      /* Now we will open a session to the instrument we just found. */
      status = viOpen (defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
      if (status < VI_SUCCESS)
      {
         qDebug ("An error occurred opening a session to %s\n",instrDescriptor);
      }
      else
      {
        /* Now close the session we just opened.                            */
        /* In actuality, we would probably use an attribute to determine    */
        /* if this is the instrument we are looking for.                    */
        viClose (instr);
      }

      while (--numInstrs)
      {
         /* stay in this loop until we find all instruments */
         status = viFindNext (findList, instrDescriptor);  /* find next desriptor */
         if (status < VI_SUCCESS)
         {   /* did we find the next resource? */
            qDebug ("An error occurred finding the next resource.\nHit enter to continue.");
            //caijx fix
//            fflush(stdin);
//            getchar();
            viClose (defaultRM);
            return status;
         }
         qDebug("%s \n",instrDescriptor);

         /* Now we will open a session to the instrument we just found */
         status = viOpen (defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
         if (status < VI_SUCCESS)
         {
             qDebug ("An error occurred opening a session to %s\n",instrDescriptor);
         }
         else
         {
            /* Now close the session we just opened.                            */
            /* In actuality, we would probably use an attribute to determine    */
            /* if this is the instrument we are looking for.                    */
            viClose (instr);
         }
      }    /* end while */

      status = viClose(findList);
      status = viClose (defaultRM);

      //caijx fix
//      printf ("\nHit enter to continue.");
//      fflush(stdin);
//      getchar();



}

