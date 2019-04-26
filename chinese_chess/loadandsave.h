#ifndef LOADANDSAVE_H
#define LOADANDSAVE_H

class LoadAndSave
{
public:
    LoadAndSave();
    int		loadfromfile (const	char	*, char *&);
    int		savetofile (const	char *, char *&, int);
};

#endif // LOADANDSAVE_H
