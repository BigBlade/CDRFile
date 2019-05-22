// CDR字段定义的头文件
//
//////////////////////////////////////////////////////////////////////
#if !defined(_CDR_FIELD_H_)
#define _CDR_FIELD_H_


// CDR字段头描述
typedef struct CDR_FieldDesc
{
    char *szFieldName;    // 字段名
    int  iFldCharWidth;   // 字段显示占用的字符宽度
}FIELD_DESC;


// CDR公用字段枚举
typedef enum CDR_BaseFieldName
{
    BFID_IMSI = 0,         // IMSI标识
    BFID_SendNumber,       // 发送号码
    BFID_RcvNumber,        // 接收号码
    BFID_StartTime,        // 起始时间
    BFID_LAC,              // 区域号
    BFID_CELLID,           // 小区ID号

    BFID_MAX
}CDR_BASE_FIELDNAME;

// 短信CDR字段枚举
typedef enum CDR_SmsFieldName
{
    SFID_SmsType = BFID_MAX,    // 消息类型
    SFID_SmsLength,             // 消息长度
    
    SFID_ChargingType,          // 收费类型 
    SFID_ChargingSP,            // SP委托收费 
    
    SFID_IsmgID,                // 网关代码
    SFID_ForwardIsmgID,         // 前转网关代码
    SFID_SmscID,                // 短消息中心代码
     
   
    SFID_SPID,                  // SP企业代码
    SFID_SPServiceID,           // 业务代码
    SFID_AccessNo,              // 服务代码   

    SFID_MAX
}CDR_SMS_FIELDNAME;

// 彩信CDR字段枚举
typedef enum CDR_MmsFieldName
{
    MFID_MmsType = BFID_MAX,    // 消息类型
    MFID_MmsLength,             // 消息长度
    MFID_MmscID,                // 消息中心ID

    MFID_MAX
}CDR_MMS_FIELDNAME;

// GPRS CDR字段枚举
typedef enum CDR_GprsFieldName
{
    GFID_XXX = BFID_MAX, 

    GFID_MAX
}CDR_GPRS_FIELDNAME;

// WAP CDR字段枚举
typedef enum CDR_WapFieldName
{
    WFID_XXX = BFID_MAX, 

    WFID_MAX
}CDR_WAP_FIELDNAME;

// KJAVA CDR字段枚举
typedef enum CDR_KjavaFieldName
{
    KFID_XXX = BFID_MAX, 

    KFID_MAX
}CDR_KJAVA_FIELDNAME;

// MAIL CDR字段枚举
typedef enum CDR_MailFieldName
{
    AFID_XXX = BFID_MAX, 

    AFID_MAX
}CDR_MAIL_FIELDNAME;


// 字段格式标号
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
