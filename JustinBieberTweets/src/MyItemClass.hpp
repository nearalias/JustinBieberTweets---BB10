/*
 * MyItemClass.hpp
 *
 *  Created on: 2013-01-19
 *      Author: Tony
 */

#ifndef MYITEMCLASS_HPP_
#define MYITEMCLASS_HPP_

#include <bb/cascades/ListItemListener>
#include <bb/cascades/CustomControl>
#include <QObject>
#include <bb/cascades/Label>
#include <bb/cascades/ImageView>

using namespace bb::cascades;

class MyItemClass : public bb::cascades::CustomControl, public ListItemListener {
	Q_OBJECT

public:
    MyItemClass(Container *parent=0);

    void updateItem(const QStringList data);

    void select(bool select);

    void reset(bool selected, bool activated);

    void activate(bool activate);

public slots:
	void imageDownloaded(QNetworkReply *reply);

private:
    void downloadImage(QString link);
    QNetworkAccessManager *imageNetworkAccessManager;

    ImageView *profile_image;
    Label *from_user;
    Label *created_at;
    Label *text;
    Container *mHighlighContainer;
};

#endif /* MYITEMCLASS_HPP_ */
