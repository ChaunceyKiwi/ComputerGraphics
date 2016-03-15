#include <QtCore>
#include <QDebug>

class MediaThread : public QThread
{
public:
    VideoPlayer player;
    MediaThread();
    void run();
};

MediaThread::MediaThread()
{
    player.setGeometry(750,100,320,240);
    player.show();
}

void MediaThread::run()
{
}
