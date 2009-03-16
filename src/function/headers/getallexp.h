#ifndef __GETALLEXP_H__
#define __GETALLEXP_H__

#include "GetEFromNet.h"

class GetAllExp : public QDialog
{
	Q_OBJECT
public:
	GetAllExp( QString TN );
	int getallexplain();
private:
	QString TableName;
	QString Letter;
};

#endif // __GETALLEXP_H__
