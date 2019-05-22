// CDR�ֶε������ļ��Լ�����CDR�ļ����ֶ���ѡʵ��
//
//////////////////////////////////////////////////////////////////////
#include "cdr_file.h"


// �ֶθ�ʽ��Դ
const FIELD_DESC CCDRFile::m_astFieldsDescRes[] = {
/* ע�⣺�����ֶεĸ�ʽ��ID���Զ�ƥ��� */
/* BFID_IMSI */         {"IMSI��ʶ", 20},
/* BFID_SendNumber */   {"���ͺ���", 20},
/* BFID_RcvNumber */    {"���պ���", 20},
/* BFID_StartTime */    {"����ʱ��", 20},
/* BFID_LAC */          {"�����",   20},
/* BFID_CELLID */       {"С��ID��", 20},

/* ������չ�ֶεĸ�ʽ�����ڴ˶��� */
/* FF_MsgType */        {"��Ϣ����", 10},
/* FF_MsgLength */      {"��Ϣ����", 10},
/* FF_CharingType */    {"�շ�����", 10},
/* FF_CharingSP */      {"SPί���շ�", 10},
/* FF_GatewayID */      {"���ش���", 20},
/* FF_ForwardGID */     {"ǰת���ش���", 20},
/* FF_SmscID */         {"����Ϣ���Ĵ���", 20},
/* FF_SPID */           {"SP��ҵ����", 20},
/* FF_ServiceID */      {"ҵ�����", 20},
/* FF_AccessID */       {"�������", 20},

                        {"", 0}
                                                 };



// �����ֶθ�ʽ����
void CSmsCDRFile::SetFieldsFormat()
{
    m_apstFieldsDesc[SFID_SmsType]   = &(CCDRFile::m_astFieldsDescRes[FF_MsgType]);
    m_apstFieldsDesc[SFID_SmsLength] = &(CCDRFile::m_astFieldsDescRes[FF_MsgLength]);
    m_apstFieldsDesc[SFID_ChargingType]   = &(CCDRFile::m_astFieldsDescRes[FF_CharingType]);
    m_apstFieldsDesc[SFID_ChargingSP] = &(CCDRFile::m_astFieldsDescRes[FF_CharingSP]);
    m_apstFieldsDesc[SFID_IsmgID]    = &(CCDRFile::m_astFieldsDescRes[FF_GatewayID]);
    m_apstFieldsDesc[SFID_ForwardIsmgID]   = &(CCDRFile::m_astFieldsDescRes[FF_ForwardGID]);
    m_apstFieldsDesc[SFID_SmscID] = &(CCDRFile::m_astFieldsDescRes[FF_SmscID]);
    m_apstFieldsDesc[SFID_SPID]    = &(CCDRFile::m_astFieldsDescRes[FF_SPID]);
    m_apstFieldsDesc[SFID_SPServiceID] = &(CCDRFile::m_astFieldsDescRes[FF_ServiceID]);
    m_apstFieldsDesc[SFID_AccessNo]    = &(CCDRFile::m_astFieldsDescRes[FF_AccessID]);
    
    return;
}
