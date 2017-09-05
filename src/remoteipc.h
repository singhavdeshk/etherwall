#ifndef REMOTEIPC_H
#define REMOTEIPC_H

#include <QtWebSockets/QtWebSockets>
#include <QObject>
#include "gethlog.h"
#include "etheripc.h"

namespace Etherwall {

    class RemoteIPC: public EtherIPC
    {
        Q_OBJECT
        Q_PROPERTY(bool thinClient READ isThinClient NOTIFY thinClientChanged)
    public:
        RemoteIPC(GethLog& gethLog);
        virtual ~RemoteIPC();
        virtual void getLogs(const QStringList& addresses, const QStringList& topics, quint64 fromBlock);
        virtual bool isThinClient() const;

        Q_INVOKABLE virtual void init();
        Q_INVOKABLE virtual bool closeApp();
        Q_INVOKABLE virtual void setInterval(int interval);
    protected slots:
        // override
        virtual void connectedToServer();
        virtual bool endpointWritable();
        virtual qint64 endpointWrite(const QByteArray& data);
        virtual const QByteArray endpointRead();
        virtual const QStringList buildGethArgs();

        void onConnectedWS();
        void onDisconnectedWS();
        void onErrorWS(QAbstractSocket::SocketError error);
        void onTextMessageReceivedWS(const QString& msg);
        void httpRequestDone(QNetworkReply *reply);
    signals:
        void thinClientChanged();
    private:
        QWebSocket fWebSocket;
        QNetworkAccessManager fNetManager;
        QString fEndpoint;
        QByteArray fReceivedMessage;
        bool fIsThinClient;

        bool isRemoteRequest() const;
        void connectWebsocket();
    };

}

#endif // REMOTEIPC_H
