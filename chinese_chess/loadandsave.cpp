#include "loadandsave.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <QDebug>
#include <basedefine.h>

using std::cout;
using std::endl;
using std::cin;

LoadAndSave::LoadAndSave()
{
}

int		LoadAndSave::loadfromfile (const	char	* filename, char *& databuffer)
{
	qDebug ()<<"loadfromfile: pdatabuffer:  "<<databuffer<<"    &"<<&databuffer<<"   *"<<*databuffer;
	cout<<"loadfromfile: filename"<<filename<<endl;
	int	fd = -1;
	if((fd = open(filename, O_RDONLY)) < 0)
		return		FAILURE;
	int filelength = lseek (fd, 0, SEEK_END);
	cout<<"loadfromfile: filelength: "<<filelength<<endl;
	lseek (fd, 0, SEEK_SET);
	if(read(fd, databuffer, filelength) < 0)
		return		FAILURE;
	close(fd);
	return		SUCCESS;
}
int		LoadAndSave::savetofile (const	char * filename, char *& databuffer, int length)
{
	cout<<"savetofile: pdatabuffer: "<<databuffer<<"   &"<<&databuffer<<"  *"<<*databuffer<<endl;
	cout<<"savetofile: length: "<<length<<endl;
	int	fd = -1;
	if((fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0755)) < 0)
		return		FAILURE;
	if(write (fd, databuffer, length) != length)
		return		FAILURE;
	cout<<"save successful"<<endl;
	close (fd);
	return		SUCCESS;
}
