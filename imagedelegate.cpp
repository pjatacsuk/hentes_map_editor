#include "imagedelegate.h"
#include "resource.h"
ImageDelegate::ImageDelegate(QObject * parent)
	: QAbstractItemDelegate(parent)
{
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	return QSize(32,32);
}

void ImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	int data = index.data(Qt::DisplayRole).toInt();
	QString path = QString(resource::globalTexture->instance()->GetTextureManager()->GetSource(data).c_str());
	QPixmap pm(path);
	painter->drawPixmap(option.rect,pm);
	return;
	/*
	switch (data)
	{
	case 0:
		{
			
			QPixmap pm("./data/images/block_cloud.png");
			painter->drawPixmap(option.rect, pm);
			return;
		}
	case 1:
		{
			QPixmap pm("./data/images/block_grass.png");
			painter->drawPixmap(option.rect, pm);
			return;
		}
	case 2:
		{
			QPixmap pm("./data/images/block_lava.png");
			painter->drawPixmap(option.rect, pm);
			return;
		}
	}*/
}

bool ImageDelegate::editorEvent( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index ) 
{
	int int_index = index.data().toInt();
	resource::bridgeToEditor->instance()->SetBlockType(int_index);
	
	return false;

}