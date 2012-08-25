
#include <Qt\qitemdelegate.h>
#include <Qt\qsize.h>
#include <Qt\qpixmap.h>
#include <Qt\qpainter.h>
#include <Qt\qprinter.h>

#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H



class ImageDelegate : public QAbstractItemDelegate
{
public:
	ImageDelegate(QObject* parent = 0);

	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
	QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
	bool editorEvent( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index);
};

#endif // IMAGEDELEGATE_H