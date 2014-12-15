#ifndef QPDFDOCUMENT_H
#define QPDFDOCUMENT_H

#include <QObject>
#include <QImage>
#include "qtpdfglobal.h"

QT_BEGIN_NAMESPACE

class QPdfDocumentPrivate;
class QNetworkReply;

class Q_PDF_EXPORT QPdfDocument : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pageCount READ pageCount NOTIFY pageCountChanged FINAL)
    Q_PROPERTY(QString password READ password WRITE setPassword FINAL)
public:

    enum Error {
        NoError,
        UnknownError,
        FileNotFoundError,
        InvalidFileFormatError,
        IncorrectPasswordError,
        UnsupportedSecuritySchemeError
    };

    explicit QPdfDocument(QObject *parent = 0);
    ~QPdfDocument();

    Error load(const QString &fileName, const QString &password = QString());
    Error load(QIODevice *device, const QString &password = QString());

    void loadAsynchronously(QNetworkReply *device);
    void setPassword(const QString &password);
    QString password() const;

    Error error() const;

    int pageCount() const;

    QSizeF pageSize(int page) const;

    QImage render(int page, const QSizeF &pageSize);

Q_SIGNALS:
    void passwordRequired();
    void documentReady();
    void pageCountChanged();

private:
    Q_PRIVATE_SLOT(d, void _q_initiateAsyncLoad())
    Q_PRIVATE_SLOT(d, void _q_readFromDevice())
    QScopedPointer<QPdfDocumentPrivate> d;
};

QT_END_NAMESPACE

#endif // QPDFDOCUMENT_H