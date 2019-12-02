#include "gpib.h"

GPIB::GPIB(QObject *parent) : QObject(parent)
{
    BoardIndex = 0;               /* Interface Index (GPIB0=0,GPIB1=1,etc.)  */
    SecondaryAddress = 0;    /* Secondary address of the device         */

    DMMaddr = 22;
    PWRaddr = 8;
    PRS0addr = 16;
    PRS1addr = 17;
}

string GPIB::convertToString(double d)
{
    ostringstream os;
    if (os << d)
        return os.str();
    return "invalid conversion";
}

double GPIB::convertFromString(string str)
{
    istringstream iss(str);
    double x;
    if (iss >> x)
        return x;
    return 0.0;
}

void GPIB::GpibError(const char *msg)
{
    printf("%s\n", msg);

    printf("Ibsta() = 0x%x  <", Ibsta());
    if (Ibsta() & ERR)  printf(" ERR");
    if (Ibsta() & TIMO)  printf(" TIMO");
    if (Ibsta() & END)  printf(" END");
    if (Ibsta() & SRQI)  printf(" SRQI");
    if (Ibsta() & RQS)  printf(" RQS");
    if (Ibsta() & CMPL)  printf(" CMPL");
    if (Ibsta() & LOK)  printf(" LOK");
    if (Ibsta() & REM)  printf(" REM");
    if (Ibsta() & CIC)  printf(" CIC");
    if (Ibsta() & ATN)  printf(" ATN");
    if (Ibsta() & TACS)  printf(" TACS");
    if (Ibsta() & LACS)  printf(" LACS");
    if (Ibsta() & DTAS)  printf(" DTAS");
    if (Ibsta() & DCAS)  printf(" DCAS");
    printf(" >\n");

    printf("Iberr() = %d", Iberr());
    if (Iberr() == EDVR) printf(" EDVR <Driver error>\n");
    if (Iberr() == ECIC) printf(" ECIC <Not Controller-In-Charge>\n");
    if (Iberr() == ENOL) printf(" ENOL <No Listener>\n");
    if (Iberr() == EADR) printf(" EADR <Address error>\n");
    if (Iberr() == EARG) printf(" EARG <Invalid argument>\n");
    if (Iberr() == ESAC) printf(" ESAC <Not System Controller>\n");
    if (Iberr() == EABO) printf(" EABO <Operation aborted>\n");
    if (Iberr() == ENEB) printf(" ENEB <No GPIB board>\n");
    if (Iberr() == EOIP) printf(" EOIP <Async I/O in progress>\n");
    if (Iberr() == ECAP) printf(" ECAP <No capability>\n");
    if (Iberr() == EFSO) printf(" EFSO <File system error>\n");
    if (Iberr() == EBUS) printf(" EBUS <Command error>\n");
    if (Iberr() == ESTB) printf(" ESTB <Status byte lost>\n");
    if (Iberr() == ESRQ) printf(" ESRQ <SRQ stuck on>\n");
    if (Iberr() == ETAB) printf(" ETAB <Table Overflow>\n");
    if (Iberr() == ELCK) printf(" ELCK <Lock error>\n");
    if (Iberr() == EARM) printf(" EARM <Ibnotify rearm error>\n");
    if (Iberr() == EHDL) printf(" EHDL <Invalid Handle>\n");
    if (Iberr() == EWIP) printf(" EWIP <Wait already in progress>\n");
    if (Iberr() == ERST) printf(" ERST <Notification cancelled due to reset>\n");
    if (Iberr() == EPWR) printf(" EPWR <Power error>\n");

    printf("Ibcnt() = %u\n", Ibcnt());
    printf("\n");

    /* Call ibonl to take the device and interface offline */
    ibonl(Device, 0);

    //    exit(1);
}

bool GPIB::write(int addr,string strWrite)
{
    Device = ibdev(              /* Create a unit descriptor handle         */
                                     BoardIndex,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
                                     addr,          /* Device primary address                  */
                                     SecondaryAddress,        /* Device secondary address                */
                                     T10s,                    /* Timeout setting (T10s = 10 seconds)     */
                                     1,                       /* Assert EOI line at end of write         */
                                     0);                      /* EOS termination mode                    */
    if (Ibsta() & ERR) {         /* Check for GPIB Error                    */
        GpibError("ibdev Error");
        QMessageBox::warning(nullptr, "warning", "Error in initializing the GPIB instrument.");

        return false;
    }

    ibclr(Device);                 /* Clear the device                        */
    if (Ibsta() & ERR) {
        GpibError("ibclr Error");
        QMessageBox::warning(nullptr, "warning", "Error in clearing the GPIB device.");

        return false;
    }

    ibwrt(Device, strWrite.c_str(), strWrite.length());     /* Send the identification query command   */
    if (Ibsta() & ERR) {
        GpibError("ibwrt Error");
        QMessageBox::warning(nullptr, "warning", "Error in writing the string command to the GPIB instrument.");

        return false;
    }

    ibonl(Device, 0);
    if (Ibsta() & ERR) {
        GpibError("ibonl Error");
        QMessageBox::warning(nullptr, "warning", "Error in offline the GPIB interface card.");


        return false;
    }

    return true;
}

bool GPIB::read(int addr,string strWrite, string &strRead)
{
    /*****************************************************************************
  * Initialization - Done only once at the beginning of your application.
  *****************************************************************************/

    Device = ibdev(                /* Create a unit descriptor handle         */
                                       BoardIndex,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
                                       addr,          /* Device primary address                  */
                                       SecondaryAddress,        /* Device secondary address                */
                                       T10s,                    /* Timeout setting (T10s = 10 seconds)     */
                                       1,                       /* Assert EOI line at end of write         */
                                       0);                      /* EOS termination mode                    */
    if (Ibsta() & ERR) {           /* Check for GPIB Error                    */
        GpibError("ibdev Error");
        QMessageBox::warning(nullptr, "warning", "Error in initializing the GPIB instrument.");

        return false;
    }

    ibclr(Device);                 /* Clear the device                        */
    if (Ibsta() & ERR) {
        GpibError("ibclr Error");
        QMessageBox::warning(nullptr, "warning", "Error in clearing the GPIB device.");

        return false;
    }

    /*****************************************************************************
     * Main Application Body - Write the majority of your GPIB code here.
     *****************************************************************************/

    ibwrt(Device, strWrite.c_str(), strWrite.length());     /* Send the identification query command   */
    if (Ibsta() & ERR) {
        GpibError("ibwrt Error");
        QMessageBox::warning(nullptr, "warning", "Error in writing the string command to the GPIB instrument.");

        return false;
    }

    ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device    */
    if (Ibsta() & ERR) {
        GpibError("ibrd Error");
        QMessageBox::warning(nullptr, "warning", "Error in reading the response string from the GPIB instrument.");
    }

    Buffer[Ibcnt()] = '\0';        /* Null terminate the ASCII string         */

    //printf("%s\n", Buffer);        /* Print the device identification         */

    strRead = Buffer;

    ibonl(Device, 0);
    if (Ibsta() & ERR) {
        GpibError("ibonl Error");
        QMessageBox::warning(nullptr, "warning", "Error in offline the GPIB interface card.");

        return false;
    }

    return true;
}

bool GPIB::DMM_ReadVoltage(double &value)
{
    try
    {
        string strRead = "";
        if (!write(DMMaddr, "CONF:VOLT:DC DEF")) return false;
        if (!read(DMMaddr, "READ?", strRead)) return false;
        printf("%s\n", strRead.c_str());
        value = convertFromString(strRead);

        return true;
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "Voltage Read Fail!");
        return false;
    }
}

bool GPIB::DMM_ReadCurrent(double &value)
{
    try
    {
        string strRead = "";
        if (!write(DMMaddr, "CONF:CURR:DC DEF")) return false;
        if (!read(DMMaddr, "READ?", strRead)) return false;
        printf("%s\n", strRead.c_str());
        value = convertFromString(strRead);

        return true;
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "Current Read Fail!");
        return false;
    }
}

bool GPIB::DMM_ReadRes(double &value)
{
    try
    {
        string strRead = "";
        if(!write(DMMaddr, "CONF:RES DEF")) return false;
        if(!read(DMMaddr, "READ?", strRead)) return false;
        printf("%s\n", strRead.c_str());
        value = convertFromString(strRead);
        return true;
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "Resistor Read Fail!");
        return false;
    }
}

bool GPIB::DMM_ReadFreq(double &value)
{
    try
    {
        string strRead = "";
        if (!write(DMMaddr, "CONF:FRES:DC DEF")) return false;
        if (!read(DMMaddr, "READ?", strRead)) return false;
        printf("%s\n", strRead.c_str());
        value = convertFromString(strRead);
        return true;
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "Frequency Read Fail!");
        return false;
    }
}

bool GPIB::DMM_SetDCRange(double VRange, double VDelta)
{
    try
    {
        QString strWrite=QString("CONF:VOLT:DC ") + QString("%1").arg(VRange) + "," + QString("%1").arg(VDelta);
        return write(DMMaddr, strWrite.toStdString());
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "Voltage DC Range Setting Fail!");
        return false;
    }
}

bool GPIB::DMM_Reset()
{
    try
    {
        if (!write(DMMaddr, "*RST")) return false;
        return write(DMMaddr, "*CLS");
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "DMM Reset Fail!");
        return false;
    }
}

bool GPIB::DMM_AutoZero(bool autoZero)
{
    try
    {
        if (autoZero) return write(DMMaddr, "ZERO:AUTO ON");
        else return write(DMMaddr, "ZERO:AUTO OFF");
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "DMM Auto Zero Setting Fail!");
        return false;
    }
}

bool GPIB::DMM_TrigDelay(double trigDelay)
{
    try
    {
        QString strWrite=QString("TRIG:DEL ") + QString("%1").arg(trigDelay);
        return write(DMMaddr, strWrite.toStdString());
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "DMM Trig Delay Setting Fail!");
        return false;
    }
}

bool GPIB::DMM_SampleCounts(uint sampleCount)
{
    try
    {
        QString strWrite=QString("SAMP:COUN ") + QString("%1").arg(sampleCount);
        return write(DMMaddr, strWrite.toStdString());
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "DMM Sample Counts Setting Fail!");
        return false;
    }
}

bool GPIB::PWR_SetVoltage(double voltageSet)
{
    try
    {
        QString strWrite=QString(":CHAN1:VOLT ") + QString("%1").arg(voltageSet) + "/n";
        return write(PWRaddr, strWrite.toStdString());
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Voltage Setting Fail");
        return false;
    }
}

bool GPIB::PWR_SetCurrent(double currentSet)
{
    try
    {
        QString strWrite=QString(":CHAN1:CURR ") + QString("%1").arg(currentSet) + "/n";
        return write(PWRaddr, strWrite.toStdString());
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Current Setting Fail");
        return false;
    }
}

bool GPIB::PWR_LimitCurrent(bool currentLimit)
{
    try
    {
        QString strWrite=QString(":CHAN1:PROT:CURR ") + QString("%1").arg(currentLimit) + "/n";
        return write(PWRaddr, strWrite.toStdString());
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Current (Un)Limit Fail");
        return false;
    }
}

bool GPIB::PWR_LimitVoltage(bool voltageLimit)
{
    try
    {
        QString strWrite=QString(":CHAN1:PROT:VOLT ") + QString("%1").arg(voltageLimit) + "/n";
        return write(PWRaddr, strWrite.toStdString());
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Voltage (Un)Limit Fail");
        return false;
    }
}

bool GPIB::PWR_Output(bool output)
{
    try
    {
        if (output)
        {
            if(!write(PWRaddr, "OUTP:PROT:CLE/n")) return false;
            return write(PWRaddr, "OUTP:STAT 1/n");
        }
        else return write(PWRaddr, "OUTP:STAT 0/n");
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR (Un)Output Fail");
        return false;
    }
}

bool GPIB::PWR_GetOutput(bool &output)
{
    string strRead = "";
    output = false;
    try
    {
        if(!read(PWRaddr, "OUTP:STAT?/n", strRead)) return false;
        if (strRead == "1/n") output = true;
        return true;
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Get Output Stat Fail");
        return false;
    }
}

bool GPIB::PWR_GetVoltage(double &value)
{
    string strRead = "";
    try
    {
        if(!read(PWRaddr, ":CHAN1:MEAS:VOLT?/n", strRead)) return false;
        printf("%s\n", strRead.c_str());
        value = convertFromString(strRead);
        return true;
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Get Voltage Fail");
        return false;
    }
}

bool GPIB::PWR_GetCurrent(double &value)
{
    string strRead = "";
    try
    {
        if (!read(PWRaddr, ":CHAN1:MEAS:CURR?/n", strRead)) return false;
        printf("%s\n", strRead.c_str());
        value = convertFromString(strRead);
        return true;
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Get Current Fail");
        return false;
    }
}

bool GPIB::PWR_Reset()
{
    try
    {
        return write(PWRaddr, "*RST/n");
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Reset Fail");
        return false;
    }
}

bool GPIB::PWR_Clear()
{
    try
    {
        return write(PWRaddr, "*CLS/n");
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PWR Clear Fail");
        return false;
    }
}

bool GPIB::PRS0_SetResistance(ulong resSet)
{
    try
    {
        QString resString="";
        QString resStringAdd=QString::number(resSet);
        if(resStringAdd.length()<2) resString = "SOURce:DATA 200000000000";
        else if (resStringAdd.length() > 8) resString = "SOURce:DATA 100000000000";
        else
        {
            for (short i = 12; i > resStringAdd.length(); i--) resString += "0";
            //resStringAdd.PadRight(12, '0');
            resString += resStringAdd;
            resString = "SOURce:DATA " + resString;
        }
        return (write(PRS0addr,resString.toStdString()));
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PRS0 Resistance Setting Fail");
        return false;
    }
}

bool GPIB::PRS1_SetResistance(ulong resSet)
{
    try
    {
        QString resString = "";
        QString resStringAdd = QString::number(resSet);
        if (resStringAdd.length() < 2) resString = "SOURce:DATA 200000000000";
        else if (resStringAdd.length() > 8) resString = "SOURce:DATA 100000000000";
        else
        {
            for (short i = 12; i > resStringAdd.length(); i--) resString += "0";
            //resStringAdd.PadRight(12, '0');
            resString += resStringAdd;
            resString = "SOURce:DATA " + resString;
        }
        return (write(PRS1addr, resString.toStdString()));
    }
    catch(...)
    {
        QMessageBox::warning(nullptr, "warning", "PRS1 Resistance Setting Fail");
        return false;
    }
}

void GPIB::sample()
{
    /*****************************************************************************
      * Initialization - Done only once at the beginning of your application.
      *****************************************************************************/

    Device = ibdev(                /* Create a unit descriptor handle         */
                                   BoardIndex,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
                                   DMMaddr,          /* Device primary address                  */
                                   SecondaryAddress,        /* Device secondary address                */
                                   T10s,                    /* Timeout setting (T10s = 10 seconds)     */
                                   1,                       /* Assert EOI line at end of write         */
                                   0);                      /* EOS termination mode                    */
    if (Ibsta() & ERR) {           /* Check for GPIB Error                    */
        GpibError("ibdev Error");
    }

    ibclr(Device);                 /* Clear the device                        */
    if (Ibsta() & ERR) {
        GpibError("ibclr Error");
    }

    /*****************************************************************************
         * Main Application Body - Write the majority of your GPIB code here.
         *****************************************************************************/

    ibwrt(Device, "*IDN?", 5);     /* Send the identification query command   */
    if (Ibsta() & ERR) {
        GpibError("ibwrt Error");
    }

    ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device    */
    if (Ibsta() & ERR) {
        GpibError("ibrd Error");
    }

    Buffer[Ibcnt()] = '\0';        /* Null terminate the ASCII string         */

    printf("%s\n", Buffer);        /* Print the device identification         */


    /*****************************************************************************
      * Uninitialization - Done only once at the end of your application.
      *****************************************************************************/

    ibonl(Device, 0);              /* Take the device offline                 */
    if (Ibsta() & ERR) {
        GpibError("ibonl Error");
    }

}
