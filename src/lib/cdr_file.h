// CCDRFile对象的接口
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CDR_FILE_H_)
#define _CDR_FILE_H_

#include <stdio.h>      // FILE结构体
#include "cdr_field.h"  // 字段枚举值

#define WIN32  1 

// CDR统一字段长度
#define CDR_STRLEN 32

// CDR统一字段类型定义
typedef char CDR_STR[CDR_STRLEN+1];

// CDR文件类型枚举
typedef enum CDR_FileType
{
    FT_CSV = 0,      // Excel的CSV格式:逗号作分隔符，回车作换行符
    FT_SPACE,        // 空格作分隔符，回车作换行符
    FT_SPACESTREAM,  // 空格作分隔符，没有换行符
    FT_SPLIT,        // 竖线作分隔符，回车作换行符
    FT_SPLITSTREAM   // 竖线作分隔符，没有换行符
}EM_CDR_FILETYPE;


// 基本CDR文件对象
class CCDRFile  
{   
private:
    CDR_STR *m_pszFields;                // 目标字段集合
    const FIELD_DESC **m_ppstFieldsDesc; // 目标字段描述
    FILE *m_pTargetFile;          // 目标文件对象   
    int m_iFieldsCount;           // 目标字段数目
    EM_CDR_FILETYPE m_emFileType; // 目标文件类型
    char m_cColSplitChar;         // 列分隔符
    char m_cLineSplitChar;        // 行分隔符
    char m_cColSpltCHContinue;    // 连续列分隔符被当作一个处理
    CDR_STR m_szNullFieldFill;    // 空字段填充内容,注意里面不要存在列分隔符 

protected:
    const static FIELD_DESC m_astFieldsDescRes[]; // 所有字段描述资源


public:
    CCDRFile(CDR_STR *pFieldSet, FIELD_DESC **ppFieldDesc, int iFieldsCnt);
    virtual ~CCDRFile();

    // 文件基本操作
    int Open(char *pszFileName, char *pszOptFlag, EM_CDR_FILETYPE emFileType = FT_CSV);
    int Close();
    
    // 文件缓存操作
    int Flush();

    // 文件的基本记录型操作接口
    int WriteRecord();
    int ReadRecord();

    // 文件的格式化操作接口
    int WriteFormatFieldNames();
    int WriteFormatRecord();

    // 得到CDR文件类型
    EM_CDR_FILETYPE GetFileType();

    // 得到当前CDR文件所有字段数目
    int GetCDRFieldsCount() { return(m_iFieldsCount); };

private:
    int ReadField(CDR_STR szFieldBuf);
    int WriteField(CDR_STR szField);
    int WriteFormatField(const FIELD_DESC *pstFormatField);
    
    void ClearCurRecord();

    int SetFileType(EM_CDR_FILETYPE emParFileType);

    // 字段的格式化设置(同时，防止用户生成CDRFile的基类对象)
    virtual void SetFieldsFormat() = 0;
};

 
// 短信CDR文件对象
class CSmsCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[SFID_MAX]; // 字段描述指针集合
    CDR_STR m_aszFields[SFID_MAX];                // 一条短信CDR记录的字段集

    CSmsCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {SetFieldsFormat();};

private:
    // 字段的格式化设置
    void SetFieldsFormat();
};

// 彩信CDR文件对象
class CMmsCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[MFID_MAX];  // 字段描述
    CDR_STR m_aszFields[MFID_MAX];                 // 一条彩信CDR记录的字段集

    CMmsCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};

// GPRS CDR文件对象
class CGprsCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[GFID_MAX]; // 字段描述
    CDR_STR m_aszFields[GFID_MAX];    

    CGprsCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};

// WAP CDR文件对象
class CWapCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[WFID_MAX]; // 字段描述
    CDR_STR m_aszFields[WFID_MAX];    

    CWapCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};

// KJAVA CDR文件对象
class CKjavaCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[KFID_MAX]; // 字段描述
    CDR_STR m_aszFields[KFID_MAX];    

    CKjavaCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};

// MAIL CDR文件对象
class CMailCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[AFID_MAX]; // 字段描述
    CDR_STR m_aszFields[AFID_MAX];    

    CMailCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};


#endif // !defined(_CDR_FILE_H_)
