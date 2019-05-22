#include "CDRFile/cdr_file.h"

int main ()
{
    CSmsCDRFile clsSmsCDR;

    clsSmsCDR.Open("C:\\CDR.txt", "w");
    clsSmsCDR.WriteFormatFieldNames();

    sprintf(clsSmsCDR.m_aszFields[BFID_SendNumber], "%s", "13120302099");
    sprintf(clsSmsCDR.m_aszFields[BFID_RcvNumber], "%s", "13130302096");
    sprintf(clsSmsCDR.m_aszFields[BFID_StartTime], "%s", "2005-06-01 21:09:38");
    
    clsSmsCDR.WriteFormatRecord();

    sprintf(clsSmsCDR.m_aszFields[BFID_SendNumber], "%s", "13120302099");
    sprintf(clsSmsCDR.m_aszFields[BFID_RcvNumber], "%s", "13140302097");
    sprintf(clsSmsCDR.m_aszFields[SFID_SmsLength], "%s", "68");
    
    clsSmsCDR.WriteFormatRecord();

    clsSmsCDR.Open("C:\\CDR.txt", "r");
    clsSmsCDR.ReadRecord();
    printf("%s\n", clsSmsCDR.m_aszFields[BFID_StartTime]);
    printf("%s\n", clsSmsCDR.m_aszFields[SFID_SmsLength]);
    clsSmsCDR.ReadRecord();
    printf("%s\n", clsSmsCDR.m_aszFields[BFID_SendNumber]);
    printf("%s\n", clsSmsCDR.m_aszFields[SFID_SmsLength]);


    return 0;
}
