#include "nivisagpib.h"

#include <QMessageBox>

NIVisaGPIB::NIVisaGPIB(QObject *parent) : QObject(parent)
{
    m_nCurrGPIBIndex=-1;
    m_numInstrs=0;
    m_mapGPIB.clear();
}

NIVisaGPIB::~NIVisaGPIB()
{
    ViStatus status;

    QMap<string,ViSession>::iterator it; //遍历map

    for ( it = m_mapGPIB.begin(); it != m_mapGPIB.end(); ++it ) {
//        qDebug()<<"key:"<<it.key().data()<<" "<<"value:"<<it.value();

        status = viClose(it.value());//用key()和data()分别获取“键”和“值”

    }
    m_mapGPIB.clear(); //清空map

    status = viClose(m_findList);
    status = viClose(m_defaultRM);
}

ViStatus NIVisaGPIB::sample_viFindRsrc()
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

    while (--numInstrs > 0)
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

    return status;
}

ViStatus NIVisaGPIB::sample_getCurrent()
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
#if 1
        //方法一
        static unsigned char buffer[100];
        static char stringinput[512];
        static ViUInt32 retCount;
        static ViUInt32 writeCount;


        status = viPrintf(instr,ViString("CONF:CURR:DC"));
        if (status != VI_SUCCESS){
            qDebug("CONF:CURR:DC setting fail");
        }

        strcpy_s(stringinput,"READ?\n");
        status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
        if (status < VI_SUCCESS)
        {
            qDebug("Error writing to the device\n");
        }

        status = viRead (instr, buffer, 100, &retCount);
        if (status < VI_SUCCESS)
        {
            qDebug("Error reading a response from the device\n");
        }
        else
        {
            qDebug("Data read: %*s\n",retCount,buffer);
        }

#else

        //方法二
        double resultDC;
        status = viQueryf(instr, ViString("MEAS:CURR:DC?\n"), ViString("%lf"), &resultDC); //OK
        if (status != VI_SUCCESS){
            qDebug("Error querying MEAS:CURR:DC?\n from the device\n");
        }
        else{
            qDebug()<<"resultDC:"<<resultDC;
        }
#endif


        /* Now close the session we just opened.                            */
        /* In actuality, we would probably use an attribute to determine    */
        /* if this is the instrument we are looking for.                    */
        viClose (instr);
    }

    status = viClose(findList);
    status = viClose (defaultRM);

    //caijx fix
    //      printf ("\nHit enter to continue.");
    //      fflush(stdin);
    //      getchar();

    return status;
}

ViStatus NIVisaGPIB::initGPIB()
{
    char instrDescriptor[VI_FIND_BUFLEN];
    ViSession instr;
    ViStatus status;

    /* First we will need to open the default resource manager. */
    status = viOpenDefaultRM (&m_defaultRM);    
    if (status < VI_SUCCESS)
    {
        qDebug("Could not open a session to the VISA Resource Manager!\n");
//        exit (EXIT_FAILURE);

        QMessageBox::warning(nullptr,"warning","Could not open a session to the VISA Resource Manager!\n");

        //VI_ERROR_SYSTEM_ERROR The VISA system failed to initialize.
        return VI_ERROR_SYSTEM_ERROR;
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
    status = viFindRsrc(m_defaultRM,ViString("GPIB?*INSTR"), &m_findList, &m_numInstrs, instrDescriptor);

    if (status < VI_SUCCESS)
    {
        qDebug ("An error occurred while finding resources.\nHit enter to continue.");
        //caijx fix
        //         fflush(stdin);
        //         getchar();

        QMessageBox::warning(nullptr,"warning","An error occurred while finding the VISA resources.");

        viClose (m_defaultRM);
        return status;
    }

    qDebug("%d instruments, serial ports, and other resources found:\n\n",m_numInstrs);
    qDebug("%s \n",instrDescriptor);

    /* Now we will open a session to the instrument we just found. */
    status = viOpen (m_defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
    if (status < VI_SUCCESS)
    {
        qDebug ("An error occurred opening a session to %s\n",instrDescriptor);
        QMessageBox::warning(nullptr,"warning",QString().sprintf("An error occurred opening a session to %s\n",instrDescriptor));
    }
    else
    {
        m_mapGPIB.insert(instrDescriptor,instr);
        m_nCurrGPIBIndex=0;

        /* Now close the session we just opened.                            */
        /* In actuality, we would probably use an attribute to determine    */
        /* if this is the instrument we are looking for.                    */
//        viClose (instr);
    }

    while (--m_numInstrs > 0)
    {
        /* stay in this loop until we find all instruments */
        status = viFindNext (m_findList, instrDescriptor);  /* find next desriptor */
        if (status < VI_SUCCESS)
        {   /* did we find the next resource? */
            qDebug ("An error occurred finding the next resource.\nHit enter to continue.");
            //caijx fix
            //            fflush(stdin);
            //            getchar();
            viClose (m_defaultRM);

            QMessageBox::warning(nullptr,"warning","An error occurred finding the next VISA resource.");

            return status;
        }
        qDebug("%s \n",instrDescriptor);

        /* Now we will open a session to the instrument we just found */
        status = viOpen (m_defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
        if (status < VI_SUCCESS)
        {
            qDebug ("An error occurred opening a session to %s\n",instrDescriptor);
            QMessageBox::warning(nullptr,"warning",QString().sprintf("An error occurred opening a session to %s\n",instrDescriptor));
        }
        else
        {
            m_mapGPIB.insert(instrDescriptor,instr);

            /* Now close the session we just opened.                            */
            /* In actuality, we would probably use an attribute to determine    */
            /* if this is the instrument we are looking for.                    */
//            viClose (instr);
        }
    }    /* end while */

//    status = viClose(m_findList);
//    status = viClose (m_defaultRM);

    //caijx fix
    //      printf ("\nHit enter to continue.");
    //      fflush(stdin);
    //      getchar();

    return status;
}

bool NIVisaGPIB::getCurrent(string &value)
{
    ViStatus status;
    unsigned char buffer[100];
    char stringinput[512];
    ViUInt32 retCount=0;
    ViUInt32 writeCount;

    if(m_nCurrGPIBIndex >=0){

        int j=0;
        //用key()和data()分别获取“键”和“值”
        QMap<string,ViSession>::iterator it; //遍历map
        for ( it = m_mapGPIB.begin(); it != m_mapGPIB.end(); ++it ) {
    //        qDebug()<<"key:"<<it.key().data()<<" "<<"value:"<<it.value();
            if(j==m_nCurrGPIBIndex){
                ViSession instr;

                instr=it.value();

                status = viPrintf(instr,ViString("CONF:CURR:DC"));
                if (status != VI_SUCCESS){
                    qDebug("CONF:CURR:DC setting fail");
                    QMessageBox::warning(nullptr,"warning","An error occurred writing setting CONF:CURR:DC command.");
                }

                strcpy_s(stringinput,"READ?");
                status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
                if (status < VI_SUCCESS)
                {
                    qDebug("Error writing to the device\n");
                    QMessageBox::warning(nullptr,"warning","Error writing to the device\n");
                }

                status = viRead (instr, buffer, 100, &retCount);
                if (status < VI_SUCCESS)
                {
                    qDebug("Error reading a response from the device\n");
                    QMessageBox::warning(nullptr,"warning","Error reading a response from the device\n");
                }
                else
                {
                    if(retCount>0){
                        //                        qDebug("Data read: %s\n",buffer);

                        //                    value=atof((char*)buffer);

                        string str(buffer,buffer+sizeof(buffer)/sizeof(*buffer));//还可以利用string来转换
                        value=str;

//                        value=atof(str.c_str());
//                        qDebug()<<"value:"<<value;

                        return true;
                    }
                    else{
                        QMessageBox::warning(nullptr,"warning","Error reading a response from the device\n");
                    }
                }

                break;
            }
        }
    }

    return false;
}
