/*
 * MyItemClass.cpp
 *
 *  Created on: 2013-01-19
 *      Author: Tony
 */

#include "MyItemClass.hpp"
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/VerticalAlignment>
#include <bb/cascades/Divider>
#include <bb/cascades/SystemDefaults>
#include <QtGlobal>

MyItemClass::MyItemClass(Container *parent) : CustomControl(parent) {

    imageNetworkAccessManager = new QNetworkAccessManager(this);
    bool imageRes = connect(imageNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),
    						this, SLOT(imageDownloaded(QNetworkReply*)));
    Q_ASSERT(imageRes);
    Q_UNUSED(imageRes);

    Container *itemContainer = new Container();
    itemContainer->setLayout(new DockLayout());

    Container *contentContainer = new Container();
    contentContainer->setVerticalAlignment(VerticalAlignment::Center);
    contentContainer->setLayout(new StackLayout());
    contentContainer->setPreferredWidth(1760.0f);
    contentContainer->setLeftPadding(20.0f);
    contentContainer->setRightPadding(20.0f);
    contentContainer->setBottomPadding(20.0f);
    contentContainer->setTopPadding(20.0f);

    Container *firstRow = new Container();
    firstRow->setLayout(StackLayout::create().orientation(LayoutOrientation::LeftToRight));
    firstRow->setVerticalAlignment(VerticalAlignment::Center);
    firstRow->setTopPadding(10.0f);

    profile_image = ImageView::create("asset:///images/default_profile_image.png");
    profile_image->setPreferredSize(200.0f, 200.0f);
    profile_image->setScalingMethod(ScalingMethod::AspectFill);

    Container *nameAndDate = new Container();
    nameAndDate->setLayout(new StackLayout());
    nameAndDate->setVerticalAlignment(VerticalAlignment::Center);
    nameAndDate->setLeftPadding(20.0f);
    nameAndDate->setRightPadding(20.0f);

    from_user = Label::create().text("");
    from_user->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
    from_user->textStyle()->setFontSize(FontSize::Medium);
    from_user->textStyle()->setColor(Color::White);
    from_user->setMultiline(true);
    from_user->setVerticalAlignment(VerticalAlignment::Center);

    created_at = Label::create().text("");
    created_at->textStyle()->setColor(Color::Cyan);
    created_at->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
    created_at->textStyle()->setFontSize(FontSize::XSmall);
    created_at->setMultiline(true);

    nameAndDate->add(from_user);
    nameAndDate->add(created_at);
    firstRow->add(profile_image);
    firstRow->add(nameAndDate);

    text = Label::create().text("");
    text->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
    text->textStyle()->setFontSize(FontSize::XSmall);
    text->textStyle()->setColor(Color::White);
    text->setTextFormat(TextFormat::Html);
    text->setMultiline(true);

    contentContainer->add(firstRow);
    contentContainer->add(text);

    itemContainer->add(contentContainer);
    itemContainer->add(new Divider());

    setRoot(itemContainer);
}

void MyItemClass::updateItem(const QStringList data) {
	from_user->setText(data[0]);
	created_at->setText(data[1]);
	text->setText(data[2]);
	profile_image->setImage(NULL);
	downloadImage(data[3]);
}

void MyItemClass::downloadImage(QString link){
	QUrl url(link);
	imageNetworkAccessManager->get(QNetworkRequest(QUrl(url)));
}

void MyItemClass::imageDownloaded(QNetworkReply *reply){
	if (reply->error() == QNetworkReply::NoError){
		Image image = Image(reply->readAll());
		profile_image->setImage(image);
    } else qDebug() << "\n	Problem with the network\n" << reply->errorString();
	reply->deleteLater();
}

void MyItemClass::select(bool select) {
}

void MyItemClass::reset(bool selected, bool activated) {
    Q_UNUSED(activated);

    select(selected);
}

void MyItemClass::activate(bool activate) {
    select(activate);
}




