#ifndef QT_PROBA_H
#define QT_PROBA_H

#include <QtGui/QMainWindow>
#include "qt_ui.h"
#include <Qt/qstandarditemmodel.h>
class qt_proba : public QMainWindow
{
	Q_OBJECT

public:
	qt_proba(QWidget *parent = 0, Qt::WFlags flags = 0);
	~qt_proba();
	Ui::MainWindow& GetUi() {return ui;}
	//void updateLabel();

public slots:
		void updateLabel();
		void updateLabel2();
private:
	Ui::MainWindow ui;
	QStandardItemModel* model;
};

#endif // QT_PROBA_H
