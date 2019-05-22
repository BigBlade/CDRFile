// CCDRFile����Ľӿ�
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CDR_FILE_H_)
#define _CDR_FILE_H_

#include <stdio.h>      // FILE�ṹ��
#include "cdr_field.h"  // �ֶ�ö��ֵ

#define WIN32  1 

// CDRͳһ�ֶγ���
#define CDR_STRLEN 32

// CDRͳһ�ֶ����Ͷ���
typedef char CDR_STR[CDR_STRLEN+1];

// CDR�ļ�����ö��
typedef enum CDR_FileType
{
    FT_CSV = 0,      // Excel��CSV��ʽ:�������ָ������س������з�
    FT_SPACE,        // �ո����ָ������س������з�
    FT_SPACESTREAM,  // �ո����ָ�����û�л��з�
    FT_SPLIT,        // �������ָ������س������з�
    FT_SPLITSTREAM   // �������ָ�����û�л��з�
}EM_CDR_FILETYPE;


// ����CDR�ļ�����
class CCDRFile  
{   
private:
    CDR_STR *m_pszFields;                // Ŀ���ֶμ���
    const FIELD_DESC **m_ppstFieldsDesc; // Ŀ���ֶ�����
    FILE *m_pTargetFile;          // Ŀ���ļ�����   
    int m_iFieldsCount;           // Ŀ���ֶ���Ŀ
    EM_CDR_FILETYPE m_emFileType; // Ŀ���ļ�����
    char m_cColSplitChar;         // �зָ���
    char m_cLineSplitChar;        // �зָ���
    char m_cColSpltCHContinue;    // �����зָ���������һ������
    CDR_STR m_szNullFieldFill;    // ���ֶ��������,ע�����治Ҫ�����зָ��� 

protected:
    const static FIELD_DESC m_astFieldsDescRes[]; // �����ֶ�������Դ


public:
    CCDRFile(CDR_STR *pFieldSet, FIELD_DESC **ppFieldDesc, int iFieldsCnt);
    virtual ~CCDRFile();

    // �ļ���������
    int Open(char *pszFileName, char *pszOptFlag, EM_CDR_FILETYPE emFileType = FT_CSV);
    int Close();
    
    // �ļ��������
    int Flush();

    // �ļ��Ļ�����¼�Ͳ����ӿ�
    int WriteRecord();
    int ReadRecord();

    // �ļ��ĸ�ʽ�������ӿ�
    int WriteFormatFieldNames();
    int WriteFormatRecord();

    // �õ�CDR�ļ�����
    EM_CDR_FILETYPE GetFileType();

    // �õ���ǰCDR�ļ������ֶ���Ŀ
    int GetCDRFieldsCount() { return(m_iFieldsCount); };

private:
    int ReadField(CDR_STR szFieldBuf);
    int WriteField(CDR_STR szField);
    int WriteFormatField(const FIELD_DESC *pstFormatField);
    
    void ClearCurRecord();

    int SetFileType(EM_CDR_FILETYPE emParFileType);

    // �ֶεĸ�ʽ������(ͬʱ����ֹ�û�����CDRFile�Ļ������)
    virtual void SetFieldsFormat() = 0;
};

 
// ����CDR�ļ�����
class CSmsCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[SFID_MAX]; // �ֶ�����ָ�뼯��
    CDR_STR m_aszFields[SFID_MAX];                // һ������CDR��¼���ֶμ�

    CSmsCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {SetFieldsFormat();};

private:
    // �ֶεĸ�ʽ������
    void SetFieldsFormat();
};

// ����CDR�ļ�����
class CMmsCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[MFID_MAX];  // �ֶ�����
    CDR_STR m_aszFields[MFID_MAX];                 // һ������CDR��¼���ֶμ�

    CMmsCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};

// GPRS CDR�ļ�����
class CGprsCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[GFID_MAX]; // �ֶ�����
    CDR_STR m_aszFields[GFID_MAX];    

    CGprsCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};

// WAP CDR�ļ�����
class CWapCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[WFID_MAX]; // �ֶ�����
    CDR_STR m_aszFields[WFID_MAX];    

    CWapCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};

// KJAVA CDR�ļ�����
class CKjavaCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[KFID_MAX]; // �ֶ�����
    CDR_STR m_aszFields[KFID_MAX];    

    CKjavaCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};

// MAIL CDR�ļ�����
class CMailCDRFile : public CCDRFile
{
public:
    const FIELD_DESC *m_apstFieldsDesc[AFID_MAX]; // �ֶ�����
    CDR_STR m_aszFields[AFID_MAX];    

    CMailCDRFile() : CCDRFile(m_aszFields, (FIELD_DESC **)m_apstFieldsDesc, (sizeof(m_aszFields) / sizeof(CDR_STR))) {};
};


#endif // !defined(_CDR_FILE_H_)
