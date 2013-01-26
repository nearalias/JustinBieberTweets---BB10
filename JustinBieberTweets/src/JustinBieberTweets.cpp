// Default empty project template
#include "JustinBieberTweets.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/data/JsonDataAccess>
#include "MyListItemProvider.hpp"

using namespace bb::cascades;
using namespace bb::data;

JustinBieberTweets::JustinBieberTweets(bb::cascades::Application *app)
: QObject(app)
{
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("app",this);
    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    spinner = root->findChild<ActivityIndicator*>("spinner");
    listOfTweets = root->findChild<ListView*>("listOfTweets");
    listOfTweets->setListItemProvider(new MyListItemProvider());
    searchBar = root->findChild<TextField*>("searchBar");
    hintText = "#bieber";	// default search query

    jsonNetworkAccessManager = new QNetworkAccessManager(this);
    bool jsonRes = connect(jsonNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),
    						this, SLOT(jsonDownloaded(QNetworkReply*)));
    Q_ASSERT(jsonRes);
    Q_UNUSED(jsonRes);

    // set created root object as a scene
    app->setScene(root);
}

void JustinBieberTweets::startSearch(QString query){

	if (!query.contains("#") && query != "") query = "#" + query;
	if (query != "") hintText = query;
	if (!spinner->isRunning() && hintText != ""){
		spinner->start();
		QNetworkRequest request = QNetworkRequest();
		QUrl url = QUrl::fromEncoded("http://search.twitter.com/search.json?q="+ QUrl::toPercentEncoding(hintText) + "&rpp=100");
		request.setUrl(url);
		jsonNetworkAccessManager->get(request);
	}
}

void JustinBieberTweets::jsonDownloaded(QNetworkReply *reply){

    if (reply->error() == QNetworkReply::NoError) {
    	JsonDataAccess jda;
    	QVariantMap data = jda.loadFromBuffer(reply->readAll()).toMap();
    	if (jda.hasError()){
    		qDebug() << jda.error();
    		return;
    	}
    	QVariantList results = data["results"].toList();
    	ArrayDataModel *array = new ArrayDataModel(this);
    	for (int i = 0; i < results.size(); i ++){
    		QVariantMap tweetInfo = results[i].toMap();
			QStringList tweet;
			tweet << tweetInfo["from_user"].toString()
					<< tweetInfo["created_at"].toString().remove(tweetInfo["created_at"].toString().right(6))
					<< parseLinks(tweetInfo["text"].toString())
					<< tweetInfo["profile_image_url"].toString();
			array->append(tweet);
    	}
    	listOfTweets->setDataModel(array);
        searchBar->setHintText(hintText);

    } else qDebug() << "\n	Problem with the network\n" << reply->errorString();

    spinner->stop();
    searchBar->setText("");

    reply->deleteLater();
}

QString JustinBieberTweets::parseLinks(QString msg){

	QString result = msg;
	if (msg.contains("http://t.co/")){
		result = "";
		QStringList words = msg.split(" ");
		for (int i = 0; i < words.size(); i ++){
			if (words[i].length() > 12 && words[i].mid(0,12) == "http://t.co/")
				words[i] = "<a href=\"" + words[i] + "\">" + words[i] + "</a>";
			result += words[i] + " ";
		}
		result = result.remove(result.length()-1, 1);
	}
	return result;
}


