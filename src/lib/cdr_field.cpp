// CDR字段的数据文件以及各类CDR文件的字段挑选实现
//
//////////////////////////////////////////////////////////////////////
#include "cdr_file.h"


// 字段格式资源
const FIELD_DESC CCDRFile::m_astFieldsDescRes[] = {
/* 注意：基本字段的格式与ID是自动匹配的 */
/* BFID_IMSI */         {"IMSI标识", 20},
/* BFID_SendNumber */   {"发送号码", 20},
/* BFID_RcvNumber */    {"接收号码", 20},
/* BFID_StartTime */    {"发送时间", 20},
/* BFID_LAC */          {"区域号",   20},
/* BFID_CELLID */       {"小区ID号", 20},

/* 其它扩展字段的格式，均在此定义 */
/* FF_MsgType */        {"消息类型", 10},
/* FF_MsgLength */      {"消息长度", 10},
/* FF_CharingType */    {"收费类型", 10},
/* FF_CharingSP */      {"SP委托收费", 10},
/* FF_GatewayID */      {"网关代码", 20},
/* FF_ForwardGID */     {"前转网关代码", 20},
/* FF_SmscID */         {"短消息中心代码", 20},
/* FF_SPID */           {"SP企业代码", 20},
/* FF_ServiceID */      {"业务代码", 20},
/* FF_AccessID */       {"服务代码", 20},

                        {"", 0}
                                                 };



// 短信字段格式设置
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
