#pragma once

#include <string>

namespace yt
{

enum LogPriority
{
        /// \brief �������� �˼���һ�㲻�á�
        LP_BASE          =  1,

        //=============================================================================


        /*! \name ac�ڲ���־����
        */
        // \{
        
        /// \brief ���ټ������ں����Ľ���/�˳�ʱ����¼�ã�һ��ֻ������ǰ�ڵ�debug�档\n
        /// ����release��ʱһ��Ҫ���˼������Ϣ���� (ʹ��NullLogger����)
        LP_AC_TRACE        = LP_BASE << 1,          

        /// \brief ���Լ��𡣳������debug��Ϣʱ�á�\n
        /// ����release��ʱһ��Ҫ���˼������Ϣ���� (ʹ��NullLogger����)
        LP_AC_DEBUG       = LP_BASE << 2,

        /// \brief ��ͨ���𡣼�¼һ���ԵķǴ���Ϣ
        LP_AC_INFO          = LP_BASE << 3,

        /// \brief ������Ϣ��
        LP_AC_WARNING   =  LP_BASE << 4,

        /// \brief ��ͨ���󡣴󲿷ִ�����Ϣ���ô˼����¼��
        LP_AC_ERROR       =   LP_BASE << 5,

        /// \brief ���ش���ֻ��ϵͳ�㷢�����ش���ʱ�����ô˼����������Ӳ�����ϵ������
        LP_AC_CRITICAL  =   LP_BASE << 6,


        // \}

        //=============================================================================

        /*! \name �û�����־����
        */
        // \{

        
        /// \brief ���ټ������ں����Ľ���/�˳�ʱ����¼�ã�һ��ֻ������ǰ�ڵ�debug�档\n
        /// ����release��ʱһ��Ҫ���˼������Ϣ���� (ʹ��NullLogger����)
        LP_TRACE        = LP_BASE << 7,          

        /// \brief ���Լ��𡣳������debug��Ϣʱ�á�\n
        /// ����release��ʱһ��Ҫ���˼������Ϣ���� (ʹ��NullLogger����)
        LP_DEBUG       = LP_BASE << 8,

        /// \brief ��ͨ���𡣼�¼һ���ԵķǴ���Ϣ
        LP_INFO          = LP_BASE << 9,

        /// \brief �û�����1������˵�������ս���Ȩ��Ӧ�ó������С�
        LP_USER1        = LP_BASE << 10,

        /// \brief �û�����2������˵�������ս���Ȩ��Ӧ�ó������С�
        LP_USER2        = LP_BASE << 11,

        /// \brief ������Ϣ��
        LP_WARNING   =  LP_BASE << 12,

        /// \brief ��ͨ���󡣴󲿷ִ�����Ϣ���ô˼����¼��
        LP_ERROR       =   LP_BASE << 13,

        /// \brief ���ش���ֻ��ϵͳ�㷢�����ش���ʱ�����ô˼����������Ӳ�����ϵ������
        LP_CRITICAL  =   LP_BASE << 14,

        // \}

};

std::string FormatLog(const std::string & sFormat, LogPriority iLogPriority, const char * szFile, int iLine, const char * szFunction, const char * szFmt, ...);

}

