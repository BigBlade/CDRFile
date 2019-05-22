// CDRFile.cpp: implementation of the CCDRFile class.
//
//////////////////////////////////////////////////////////////////////
#include "cdr_file.h"
#include <memory.h>


CCDRFile::CCDRFile(CDR_STR *pFieldSet, FIELD_DESC **ppFieldDesc, int iFieldsCnt)
{
    int i = 0;

    // 初始化文件指针
    m_pTargetFile = 0;

    // 初始化字段集合指针
    m_pszFields = pFieldSet;
    m_iFieldsCount = iFieldsCnt;
    m_ppstFieldsDesc = (const FIELD_DESC **)ppFieldDesc;

    // 设置文件的默认类型
    SetFileType(FT_CSV);

    // 设置基本字段的格式
    for (i=0; i<BFID_MAX; i++)
    {
        m_ppstFieldsDesc[i] = &(CCDRFile::m_astFieldsDescRes[i]); 
    }

    // 初始化当前记录为空
    ClearCurRecord();
}
  
void CCDRFile::ClearCurRecord()
{
    memset(m_pszFields, 0, GetCDRFieldsCount() * sizeof(CDR_STR));
}

int CCDRFile::Open(char *pszFileName, char *pszType, EM_CDR_FILETYPE emFileType)
{
    // 检查是否有已经打开而没关闭的文件
    if ( 0 != Close() )
    {
        // 关闭之前打开的文件失败
        return -3;
    }

    if ( 0 != SetFileType(emFileType) )
    {
        // 设置CDR文件的类型失败
        return -2;
    }

    // 打开文件
    if ( 0 == (m_pTargetFile = fopen(pszFileName, pszType)) )
    {
        // 打开文件失败
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


    while ( iReadChCnt < CDR_STRLEN ) // 防止字段溢出
    {
        if ( EOF == (iReadChar = fgetc(m_pTargetFile)) )
        {
            // 读到文件结尾或分隔符号
            break;
        }
        else if ( m_cColSplitChar == (chRead = (char)iReadChar) )
        {// 读到列间隔符号

            if ( 0 == iReadChCnt  )
            {// 还没有读到字段内容
            
                 if ( '\0' != m_cColSpltCHContinue )
                {
                    // 连续分隔符被当作一个处理
                    continue;
                }
                else
                {
                    // 空字段
                    break;
                }
                
            }
            else
            {// 已经读到字段内容，遇到间隔符就跳出
                
                if ( (0 < iNullFlag) &&  ('\0' == m_szNullFieldFill[iNullChIdx]) )
                {// 匹配到空字段

                     // 清空已读内容
                     iReadChCnt = 0;
                }
                
                break;
            }

        }
        else if ( m_cLineSplitChar == chRead ) // 注:只有列分隔符与行分隔符不同，才会进入
        {// 读到行间隔符号
        
            if ( (iReadChCnt > 0) && (0 < iNullFlag) &&  ('\0' == m_szNullFieldFill[iNullChIdx]) )
            {// 匹配到空字段

                 // 清空已读内容
                 iReadChCnt = 0;
            }
            
            break;
        }
        else
        {
            szFieldBuf[iReadChCnt++] = chRead;

            if ( (1 == iNullFlag) && (m_szNullFieldFill[iNullChIdx] == chRead)  )
            {
                // 如果第一个分隔符后，空字段内容被匹配
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

    // 清空记录后，读新记录
    ClearCurRecord();
    
    // 依次从文件中读取字段
    for ( i = 0; (i < iFieldCount) && ( EOF != ReadField(m_pszFields[i]) ); i++ )
    {
        // 这里为空
    }

    // 返回已读取的字段数目
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
        // 字段为空，写入空填充串
        iRet = fputs(m_szNullFieldFill, m_pTargetFile);
    }

    return iRet;
}

int CCDRFile::WriteRecord()
{
    int i = -1;
    int iFieldCount = GetCDRFieldsCount() - 1;
    
    // 依次写字段到文件中
    for ( i = 0; (i < iFieldCount) && (EOF != WriteField(m_pszFields[i])); i++ )
    {
        // 字段后加分隔符
        fputc(m_cColSplitChar, m_pTargetFile);
    }

    // 写最后一列
    if ( i == iFieldCount )
    {
        WriteField(m_pszFields[i]);
 
        // 换行
        fputc(m_cLineSplitChar, m_pTargetFile);
    }

    // 写记录成功后,清空新记录
    ClearCurRecord();

    // 返回已写入的字段数目
    return i;
}

int CCDRFile::WriteFormatField(const FIELD_DESC *pstFormatField)
{
    int i = -1;
    int iCharLen = pstFormatField->iFldCharWidth;
    char *pszFieldStr = pstFormatField->szFieldName;

        
    // 写字段
    for ( i = 0; i < iCharLen; i++ )
    {
         if ( '\0' == pszFieldStr[i] )
         {
             if ( 0 == i )
             {
                 // 字段为空，写为'-'
                 fputc('-', m_pTargetFile);
                 i++;
             }
                        
             // 标志字段值已全读到
             pszFieldStr = 0;

             break;
        }

        fputc(pszFieldStr[i], m_pTargetFile);
    }
        
    if ( 0 != pszFieldStr )
    {// 字段值没全读到
                
        if ( 0 < iCharLen )
        {
            if ( '\0' != pszFieldStr[i] )
            {
                // 字段溢出则不分隔，以'~'凸显
                return fputc('~', m_pTargetFile);
            }
            else
            {
                // 字段长度与格式长度正好相等，也认为字段没溢出，不需要补空格，但需后面的空格分隔符
            }
        }
        else
        {
            // 格式长度为0，写为'~'表示字段都溢出，但仍需后面的空格分隔符
            fputc('~', m_pTargetFile);
        }

    }
    else
    {
        // 字段值全读到，补空格
        for (; i < iCharLen; i++ )
        {
            fputc(' ', m_pTargetFile);
        }

        // 字段没溢出，则后加空格分隔符
    }

        // 追加空格分隔符
    return fputc(' ', m_pTargetFile);
}

int  CCDRFile::WriteFormatRecord()
{
    int i = -1;
    int iFieldCount = GetCDRFieldsCount();
    FIELD_DESC stFormatField;

    
    // 依次写字段到文件中
    for ( i = 0; i < iFieldCount; i++ )
    {
        stFormatField.szFieldName = m_pszFields[i];
        stFormatField.iFldCharWidth = m_ppstFieldsDesc[i]->iFldCharWidth;

        if ( EOF == WriteFormatField(&stFormatField) )
        {
            break;
        }
    }
        
    // 换行
    fputc('\n', m_pTargetFile);

    // 写记录成功后,清空新记录
    ClearCurRecord();

    // 返回已写入的字段数目
    return i;
}

int  CCDRFile::WriteFormatFieldNames()
{
    int i = -1;
    int iFieldCount = GetCDRFieldsCount();
    
    // 依次写字段到文件中
    for ( i = 0; (i < iFieldCount) && (EOF != WriteFormatField(m_ppstFieldsDesc[i])); i++ )
    {
        // 这里为空
    }
        
    // 换行
    fputc('\n', m_pTargetFile);

    // 返回已写入的字段数目
    return i;
}


int CCDRFile::Close()
{
    // 检查是否有已经打开而没关闭的文件
    if ( 0 != m_pTargetFile )
    {
        int iRet = 0;

        // 恢复CDR文件的默认类型
        SetFileType(FT_CSV);

        if ( 0 == (iRet = fclose(m_pTargetFile)) )
        {
            // 关闭文件成功，清空文件指针
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
