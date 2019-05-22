// CDR�ֶζ����ͷ�ļ�
//
//////////////////////////////////////////////////////////////////////
#if !defined(_CDR_FIELD_H_)
#define _CDR_FIELD_H_


// CDR�ֶ�ͷ����
typedef struct CDR_FieldDesc
{
    char *szFieldName;    // �ֶ���
    int  iFldCharWidth;   // �ֶ���ʾռ�õ��ַ����
}FIELD_DESC;


// CDR�����ֶ�ö��
typedef enum CDR_BaseFieldName
{
    BFID_IMSI = 0,         // IMSI��ʶ
    BFID_SendNumber,       // ���ͺ���
    BFID_RcvNumber,        // ���պ���
    BFID_StartTime,        // ��ʼʱ��
    BFID_LAC,              // �����
    BFID_CELLID,           // С��ID��

    BFID_MAX
}CDR_BASE_FIELDNAME;

// ����CDR�ֶ�ö��
typedef enum CDR_SmsFieldName
{
    SFID_SmsType = BFID_MAX,    // ��Ϣ����
    SFID_SmsLength,             // ��Ϣ����
    
    SFID_ChargingType,          // �շ����� 
    SFID_ChargingSP,            // SPί���շ� 
    
    SFID_IsmgID,                // ���ش���
    SFID_ForwardIsmgID,         // ǰת���ش���
    SFID_SmscID,                // ����Ϣ���Ĵ���
     
   
    SFID_SPID,                  // SP��ҵ����
    SFID_SPServiceID,           // ҵ�����
    SFID_AccessNo,              // �������   

    SFID_MAX
}CDR_SMS_FIELDNAME;

// ����CDR�ֶ�ö��
typedef enum CDR_MmsFieldName
{
    MFID_MmsType = BFID_MAX,    // ��Ϣ����
    MFID_MmsLength,             // ��Ϣ����
    MFID_MmscID,                // ��Ϣ����ID

    MFID_MAX
}CDR_MMS_FIELDNAME;

// GPRS CDR�ֶ�ö��
typedef enum CDR_GprsFieldName
{
    GFID_XXX = BFID_MAX, 

    GFID_MAX
}CDR_GPRS_FIELDNAME;

// WAP CDR�ֶ�ö��
typedef enum CDR_WapFieldName
{
    WFID_XXX = BFID_MAX, 

    WFID_MAX
}CDR_WAP_FIELDNAME;

// KJAVA CDR�ֶ�ö��
typedef enum CDR_KjavaFieldName
{
    KFID_XXX = BFID_MAX, 

    KFID_MAX
}CDR_KJAVA_FIELDNAME;

// MAIL CDR�ֶ�ö��
typedef enum CDR_MailFieldName
{
    AFID_XXX = BFID_MAX, 

    AFID_MAX
}CDR_MAIL_FIELDNAME;


// �ֶθ�ʽ���
typedef enum CDR_FieldFormat
{
    FF_IMSI = 0,	
    FF_SendNum,
    FF_RcvNum,
    FF_StartTime,
    FF_LAC,
    FF_CELLID,

    FF_MsgType,
    FF_MsgLength,
    FF_CharingType,
    FF_CharingSP,
    FF_GatewayID,
    FF_ForwardGID,
    FF_SmscID,
    FF_SPID,
    FF_ServiceID,
    FF_AccessID,

    FF_Max
}CDR_FIELD_FORMAT;

#endif // !defined(_CDR_FIELD_H_)
