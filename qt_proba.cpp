#include "qt_proba.h"
#include <QtGui/QTableView>
#include <Qt/qimage.h>
#include "imagedelegate.h"
#include <QtGui/qstyleoption.h>
#include <QtGui/QStyleOptionViewItem>
#include "imagemodel.h"
#include "resource.h"
qt_proba::qt_proba(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	QObject::connect(ui.pushButton_2,SIGNAL(clicked()),this,SLOT(updateLabel()));
	QObject::connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(updateLabel2()));



	
	//ui.tableView->setModel(new ImageModel(this));
	
	
	int size = sqrt((double)resource::globalTexture->instance()->GetTextureManager()->Size())+1;
	model = new QStandardItemModel(size,size,this);
	for(int row = 0;row<size;row++) {
		for(int column = 0;column<size;column++) {
			QModelIndex index = model->index(row,column,QModelIndex());
			model->setData(index,row*size+column);
		}
	}
	
	
	ui.tableView->setModel(model);
	ui.tableView->setItemDelegate(new ImageDelegate());
	ui.tableView->resizeColumnsToContents();
	ui.tableView->resizeRowsToContents();
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->horizontalHeader()->hide();
	ui.tableView->verticalHeader()->hide();


//	ui.tableView->model()->setData(model->index(0,0,QModelIndex()),0);

}

void qt_proba::updateLabel() {
	ui.pushButton_2->setText("Hello");
	QPrinter printer(QPrinter::HighResolution);
	QPainter painter;
	
	painter.save();

	

	QStyleOptionViewItem option;

	for(int row = 0;row<8;row++) {
		for(int column = 0;column<2;column++) {
			option.rect = rect();
			option.rect.setRect(1024+row*30,column*30,30,30);
		//	ui.tableView->model()->setData(ui.tableView->model()->index(row,column),1);
			painter.fillRect(option.rect,QColor(192,121,121));
		}
	}
	painter.restore();
	painter.end();
}

void qt_proba::updateLabel2() {
	ui.pushButton->setText("bello");
}

qt_proba::~qt_proba()
{

}
