// CDRFile.cpp: implementation of the CCDRFile class.
//
//////////////////////////////////////////////////////////////////////
#include "cdr_file.h"
#include <memory.h>


CCDRFile::CCDRFile(CDR_STR *pFieldSet, FIELD_DESC **ppFieldDesc, int iFieldsCnt)
{
    int i = 0;

    // ��ʼ���ļ�ָ��
    m_pTargetFile = 0;

    // ��ʼ���ֶμ���ָ��
    m_pszFields = pFieldSet;
    m_iFieldsCount = iFieldsCnt;
    m_ppstFieldsDesc = (const FIELD_DESC **)ppFieldDesc;

    // �����ļ���Ĭ������
    SetFileType(FT_CSV);

    // ���û����ֶεĸ�ʽ
    for (i=0; i<BFID_MAX; i++)
    {
        m_ppstFieldsDesc[i] = &(CCDRFile::m_astFieldsDescRes[i]); 
    }

    // ��ʼ����ǰ��¼Ϊ��
    ClearCurRecord();
}
  
void CCDRFile::ClearCurRecord()
{
    memset(m_pszFields, 0, GetCDRFieldsCount() * sizeof(CDR_STR));
}

int CCDRFile::Open(char *pszFileName, char *pszType, EM_CDR_FILETYPE emFileType)
{
    // ����Ƿ����Ѿ��򿪶�û�رյ��ļ�
    if ( 0 != Close() )
    {
        // �ر�֮ǰ�򿪵��ļ�ʧ��
        return -3;
    }

    if ( 0 != SetFileType(emFileType) )
    {
        // ����CDR�ļ�������ʧ��
        return -2;
    }

    // ���ļ�
    if ( 0 == (m_pTargetFile = fopen(pszFileName, pszType)) )
    {
        // ���ļ�ʧ��
        return -1;
    }

    return 0;
}

EM_CDR_FILETYPE CCDRFile::GetFileType()
{
    return m_emFileType;
}

int CCDRFile::SetFileType(EM_CDR_FILETYPE emParFileType)
{
    m_szNullFieldFill[0] = '\0';
    m_cColSpltCHContinue = '\0';
    
    m_emFileType = emParFileType;
    switch (m_emFileType)
    {
        case FT_CSV:
            m_cColSplitChar = ',';
            m_cLineSplitChar = '\n';

            break;
        case FT_SPACE:
            m_cColSpltCHContinue = ' ';
            m_cColSplitChar = ' ';
            m_cLineSplitChar = '\n';
            sprintf(m_szNullFieldFill, "%s", "-");

            break;
        case FT_SPACESTREAM:
            m_cColSpltCHContinue = ' ';
            m_cColSplitChar = ' ';
            m_cLineSplitChar = m_cColSplitChar;
            sprintf(m_szNullFieldFill, "%s", "-");

            break;
        case FT_SPLIT:
            m_cColSplitChar = '|';
            m_cLineSplitChar = '\n';

            break;
        case FT_SPLITSTREAM:
            m_cColSplitChar = '|';
            m_cLineSplitChar = m_cColSplitChar;

            break;
       default:
            return -1;
    }

    return 0;
}

int CCDRFile::ReadField(CDR_STR szFieldBuf)
{
    int iReadChar  = EOF;
    int iReadChCnt = 0;
    int iSplitFlag = 0;
    int iNullChIdx = 0;
    int iNullFlag  = 1;
    char chRead    = 0;


    while ( iReadChCnt < CDR_STRLEN ) // ��ֹ�ֶ����
    {
        if ( EOF == (iReadChar = fgetc(m_pTargetFile)) )
        {
            // �����ļ���β��ָ�����
            break;
        }
        else if ( m_cColSplitChar == (chRead = (char)iReadChar) )
        {// �����м������

            if ( 0 == iReadChCnt  )
            {// ��û�ж����ֶ�����
            
                 if ( '\0' != m_cColSpltCHContinue )
                {
                    // �����ָ���������һ������
                    continue;
                }
                else
                {
                    // ���ֶ�
                    break;
                }
                
            }
            else
            {// �Ѿ������ֶ����ݣ����������������
                
                if ( (0 < iNullFlag) &&  ('\0' == m_szNullFieldFill[iNullChIdx]) )
                {// ƥ�䵽���ֶ�

                     // ����Ѷ�����
                     iReadChCnt = 0;
                }
                
                break;
            }

        }
        else if ( m_cLineSplitChar == chRead ) // ע:ֻ���зָ������зָ�����ͬ���Ż����
        {// �����м������
        
            if ( (iReadChCnt > 0) && (0 < iNullFlag) &&  ('\0' == m_szNullFieldFill[iNullChIdx]) )
            {// ƥ�䵽���ֶ�

                 // ����Ѷ�����
                 iReadChCnt = 0;
            }
            
            break;
        }
        else
        {
            szFieldBuf[iReadChCnt++] = chRead;

            if ( (1 == iNullFlag) && (m_szNullFieldFill[iNullChIdx] == chRead)  )
            {
                // �����һ���ָ����󣬿��ֶ����ݱ�ƥ��
                iNullChIdx++;
            }
            else
            {
                iNullFlag = 0;
            }
        }

    }

    szFieldBuf[iReadChCnt] = '\0';

    return iReadChar;
}

int CCDRFile::ReadRecord()
{
    int i = -1;
    int iFieldCount = GetCDRFieldsCount();

    // ��ռ�¼�󣬶��¼�¼
    ClearCurRecord();
    
    // ���δ��ļ��ж�ȡ�ֶ�
    for ( i = 0; (i < iFieldCount) && ( EOF != ReadField(m_pszFields[i]) ); i++ )
    {
        // ����Ϊ��
    }

    // �����Ѷ�ȡ���ֶ���Ŀ
    return i;
}

int CCDRFile::WriteField(CDR_STR szField)
{
    int iRet = 0;

    if ( '\0' != szField[0] )
    {
        iRet = fputs(szField, m_pTargetFile);
    }
    else
    {
        // �ֶ�Ϊ�գ�д�����䴮
        iRet = fputs(m_szNullFieldFill, m_pTargetFile);
    }

    return iRet;
}

int CCDRFile::WriteRecord()
{
    int i = -1;
    int iFieldCount = GetCDRFieldsCount() - 1;
    
    // ����д�ֶε��ļ���
    for ( i = 0; (i < iFieldCount) && (EOF != WriteField(m_pszFields[i])); i++ )
    {
        // �ֶκ�ӷָ���
        fputc(m_cColSplitChar, m_pTargetFile);
    }

    // д���һ��
    if ( i == iFieldCount )
    {
        WriteField(m_pszFields[i]);
 
        // ����
        fputc(m_cLineSplitChar, m_pTargetFile);
    }

    // д��¼�ɹ���,����¼�¼
    ClearCurRecord();

    // ������д����ֶ���Ŀ
    return i;
}

int CCDRFile::WriteFormatField(const FIELD_DESC *pstFormatField)
{
    int i = -1;
    int iCharLen = pstFormatField->iFldCharWidth;
    char *pszFieldStr = pstFormatField->szFieldName;

        
    // д�ֶ�
    for ( i = 0; i < iCharLen; i++ )
    {
         if ( '\0' == pszFieldStr[i] )
         {
             if ( 0 == i )
             {
                 // �ֶ�Ϊ�գ�дΪ'-'
                 fputc('-', m_pTargetFile);
                 i++;
             }
                        
             // ��־�ֶ�ֵ��ȫ����
             pszFieldStr = 0;

             break;
        }

        fputc(pszFieldStr[i], m_pTargetFile);
    }
        
    if ( 0 != pszFieldStr )
    {// �ֶ�ֵûȫ����
                
        if ( 0 < iCharLen )
        {
            if ( '\0' != pszFieldStr[i] )
            {
                // �ֶ�����򲻷ָ�����'~'͹��
                return fputc('~', m_pTargetFile);
            }
            else
            {
                // �ֶγ������ʽ����������ȣ�Ҳ��Ϊ�ֶ�û���������Ҫ���ո񣬵������Ŀո�ָ���
            }
        }
        else
        {
            // ��ʽ����Ϊ0��дΪ'~'��ʾ�ֶζ���������������Ŀո�ָ���
            fputc('~', m_pTargetFile);
        }

    }
    else
    {
        // �ֶ�ֵȫ���������ո�
        for (; i < iCharLen; i++ )
        {
            fputc(' ', m_pTargetFile);
        }

        // �ֶ�û��������ӿո�ָ���
    }

        // ׷�ӿո�ָ���
    return fputc(' ', m_pTargetFile);
}

int  CCDRFile::WriteFormatRecord()
{
    int i = -1;
    int iFieldCount = GetCDRFieldsCount();
    FIELD_DESC stFormatField;

    
    // ����д�ֶε��ļ���
    for ( i = 0; i < iFieldCount; i++ )
    {
        stFormatField.szFieldName = m_pszFields[i];
        stFormatField.iFldCharWidth = m_ppstFieldsDesc[i]->iFldCharWidth;

        if ( EOF == WriteFormatField(&stFormatField) )
        {
            break;
        }
    }
        
    // ����
    fputc('\n', m_pTargetFile);

    // д��¼�ɹ���,����¼�¼
    ClearCurRecord();

    // ������д����ֶ���Ŀ
    return i;
}

int  CCDRFile::WriteFormatFieldNames()
{
    int i = -1;
    int iFieldCount = GetCDRFieldsCount();
    
    // ����д�ֶε��ļ���
    for ( i = 0; (i < iFieldCount) && (EOF != WriteFormatField(m_ppstFieldsDesc[i])); i++ )
    {
        // ����Ϊ��
    }
        
    // ����
    fputc('\n', m_pTargetFile);

    // ������д����ֶ���Ŀ
    return i;
}


int CCDRFile::Close()
{
    // ����Ƿ����Ѿ��򿪶�û�رյ��ļ�
    if ( 0 != m_pTargetFile )
    {
        int iRet = 0;

        // �ָ�CDR�ļ���Ĭ������
        SetFileType(FT_CSV);

        if ( 0 == (iRet = fclose(m_pTargetFile)) )
        {
            // �ر��ļ��ɹ�������ļ�ָ��
            m_pTargetFile = 0;
        }

        return iRet;
    }

    return 0;
}

int CCDRFile::Flush()
{
    return fflush(m_pTargetFile);
}

CCDRFile::~CCDRFile()
{
    Close();
}
