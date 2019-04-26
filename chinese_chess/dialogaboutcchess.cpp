/***************************************************************************
  * Description:    关于中国象棋弹窗的实现
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#include "dialogaboutcchess.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QMessageBox>
#include <QTextCodec>

DialogAboutCChess::DialogAboutCChess(QWidget *parent) :
    QDialog(parent)
{
    //设置编码为UTF_8 支持中文
    //QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF_8"));
    //QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("GBK"));
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    textedit = new QTextEdit(this);
    QString lines;
    QFile file( "./aboutcchess.txt" );//读取关于中国象棋的文档
    if ( file.open(QFile::ReadOnly) ) //读取成功
    {
        QTextStream stream( &file );	//将文件内容读取到 QTextStream对象
        QString line;
        while ( !stream.atEnd ())	// 读到末尾结束
        {
            line = stream.readLine(); // 不包括“\n”的一行文本
            line += "\n"; //追加换行符
            //printf( "%3d: %s/n", n++, line.latin1() );
            lines += line;	//存储到QString对象
        }
    }
    else		//读取不成功
    {
        QMessageBox::information (this, "警告", "帮助文档不存在或损坏");
        this->close ();
    }
    file.close();

    //在文本框中显示读到的文本内容
    textedit->setText (lines);
    textedit->setReadOnly (true);//设置为不可读

    btn_know = new QPushButton("知道了", this);

    QVBoxLayout * dialoglayout = new QVBoxLayout;
    dialoglayout->addWidget (textedit);
    dialoglayout->addWidget (btn_know, 0, Qt::AlignCenter);	//按钮布局到中央

    this->setLayout (dialoglayout);
    this->resize (370, 430);

    connect (btn_know, SIGNAL(clicked()), this, SLOT(close()));
}
