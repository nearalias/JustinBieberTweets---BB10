// Default empty project template
#ifndef JustinBieberTweets_HPP_
#define JustinBieberTweets_HPP_

#include <QObject>
#include <QtNetwork>
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/ListView>
#include <bb/cascades/TextField>
#include <bb/cascades/ArrayDataModel>

using namespace bb::cascades;

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class JustinBieberTweets : public QObject
{
    Q_OBJECT
public:
    JustinBieberTweets(bb::cascades::Application *app);
    virtual ~JustinBieberTweets() {}
    Q_INVOKABLE void startSearch(QString input);

private slots:
	void jsonDownloaded(QNetworkReply *reply);

private:
	void downloadImage(QString link);
	QString parseLinks(QString msg);

	QString hintText;

    QNetworkAccessManager *jsonNetworkAccessManager;
    ActivityIndicator *spinner;
    ListView *listOfTweets;
    TextField *searchBar;
};


#endif /* JustinBieberTweets_HPP_ */
