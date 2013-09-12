// Default empty project template
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>
#include "JustinBieberTweets.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
	void myMessageOutput(QtMsgType type, const char *msg);
    // this is where the server is started etc
    Application app(argc, argv);
	qInstallMsgHandler(myMessageOutput);

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "JustinBieberTweets_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

    new JustinBieberTweets(&app);

    // we complete the transaction started in the app constructor and start the client event loop here
    return Application::exec();
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}

void myMessageOutput(QtMsgType type, const char *msg) {
     //in this function, you can write the message to any stream!
     fprintf(stdout, "%s\n", msg);
     fflush(stdout);
}
