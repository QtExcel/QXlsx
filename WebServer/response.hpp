#ifndef RECURSE_RESPONSE_HPP
#define RECURSE_RESPONSE_HPP

#include <QtGlobal>
#include <QHash>
#include <QJsonDocument>

#include <functional>

class Response
{

public:
    //!
    //! \brief get
    //! Returns the HTTP response header specified by key
    //!
    //! \param QString case-insensitive key of the header
    //! \return QString header
    //!
    QString getHeader(const QString &key)
    {
        return m_headers[key.toLower()];
    }

    //!
    //! \brief set
    //! Sets the response HTTP header to value.
    //!
    //! \param QString key of the header
    //! \param QString value for the header
    //! \return Response chainable
    //!
    Response &setHeader(const QString &key, const QString &value)
    {
        m_headers[key] = value;
        return *this;
    }

    //!
    //! \brief status
    //! Get HTTP response status
    //!
    //! \return quint16 status
    //!
    quint16 status() const
    {
        return m_status;
    }

    //!
    //! \brief status
    //! Set HTTP response status
    //!
    //! \param quint16 status
    //! \return Response chainable
    //!
    Response &status(quint16 status)
    {
        m_status = status;
        return *this;
    }

    //!
    //! \brief type
    //! Get the Content-Type HTTP header
    //!
    //! \return QString MIME content-type
    //!
    QString type() const
    {
        return m_headers["content-type"];
    }

    //!
    //! \brief type
    //! Sets Content-Type HTTP header
    //!
    //! \param QString MIME type
    //! \return Response chainable
    //!
    Response &type(const QString &type)
    {
        m_headers["content-type"] = type;
        return *this;
    }

    //!
    //! \brief body
    //! Get current response body data content, useful for upstream middleware
    //!
    //! \return QString response content
    //!
    QString body() const
    {
        return m_body;
    }

    //!
    //! \brief body
    //! Set response content, overrides existing
    //!
    //! \param QString body
    //! \return  Response chainable
    //!
    Response &body(const QString &body)
    {
        m_body = body;
        return *this;
    }

    //!
    //! \brief write
    //! Appends data to existing content (set by write() or body())
    //!
    //! \param QString data to be added
    //! \return Response chainable
    //!
    Response &write(const QString &data)
    {
        m_body += data;
        return *this;
    }

    //!
    //! \brief send
    //! Sends actual data to client
    //!
    //! \param QString body optional, if provided this is sent instead of current data in buffer
    //!
    void send(const QString &body = "")
    {
        if (body.size())
            m_body = body;

        end();
    }

    //!
    //! \brief send
    //! Overloaded function, allows sending QJsonDocument
    //!
    //! \param body
    //!
    void send(const QJsonDocument &body)
    {
        type("application/json");
        m_body = body.toJson(QJsonDocument::Compact);

        end();
    }

    //! \brief redirect
    //! Perform a 302 redirect to `url`.
    //!
    //! the string "back" is used to provide Referrer support
    //! when Referrer is not present `alt` is used
    //!
    //! Examples:
    //!
    //!    redirect('back');
    //!    redirect('back', '/index.html');
    //!    redirect('/login');
    //!    redirect('http://google.com');
    //!
    //! To override status or body set them before calling redirect
    //!
    //!     status(301).body("Redirecting...").redirect("http://www.google.com")
    //!
    //! \param url to redirect to
    //! \param alt used when referrer is not present, "/" by default

    void redirect(const QString &url, const QString &alt = "/")
    {
        // set location
        if (url == "back")
        {
            const QString &referrer = getHeader("referrer");

            if (!referrer.isEmpty())
                setHeader("Location", referrer);
            else
                setHeader("Location", alt);
        }
        else
        {
            setHeader("Location", url);
        }

        // set redirect status if not set
        // https://tools.ietf.org/html/rfc7231#section-6.4
        if (status() < 300 || status() > 308)
            status(302);

        // set body if not set
        if (body().isEmpty())
            body("This page has moved to " % url);

        end();
    }

    //!
    //! \brief end
    //! final function responsible for sending data
    //! this is bound to Recurse::end function, from recurse.hpp
    //! ctx->response.end = std::bind(&Recurse::end, this, ctx);
    //!
    std::function<void()> end;

    //!
    //! \brief method
    //! Response method, eg: GET
    //!
    QString method;

    //!
    //! \brief protocol
    //! Response protocol, eg: HTTP
    //!
    QString protocol;

    //!
    //! \brief http codes
    //!
    QHash<quint16, QString> http_codes{
        { 100, "Continue" },
        { 101, "Switching Protocols" },
        { 200, "OK" },
        { 201, "Created" },
        { 202, "Accepted" },
        { 203, "Non-Authoritative Information" },
        { 204, "No Content" },
        { 205, "Reset Content" },
        { 206, "Partial Content" },
        { 300, "Multiple Choices" },
        { 301, "Moved Permanently" },
        { 302, "Found" },
        { 303, "See Other" },
        { 304, "Not Modified" },
        { 305, "Use Proxy" },
        { 307, "Temporary Redirect" },
        { 400, "Bad Request" },
        { 401, "Unauthorized" },
        { 402, "Payment Required" },
        { 403, "Forbidden" },
        { 404, "Not Found" },
        { 405, "Method Not Allowed" },
        { 406, "Not Acceptable" },
        { 407, "Proxy Authentication Required" },
        { 408, "Request Time-out" },
        { 409, "Conflict" },
        { 410, "Gone" },
        { 411, "Length Required" },
        { 412, "Precondition Failed" },
        { 413, "Request Entity Too Large" },
        { 414, "Request-URI Too Large" },
        { 415, "Unsupported Media Type" },
        { 416, "Requested range not satisfiable" },
        { 417, "Expectation Failed" },
        { 500, "Internal Server Error" },
        { 501, "Not Implemented" },
        { 502, "Bad Gateway" },
        { 503, "Service Unavailable" },
        { 504, "Gateway Time-out" },
        { 505, "HTTP Version not supported" }
    };

    //!
    //! \brief create_reply
    //! create reply for sending to client
    //!
    //! \return QString reply to be sent
    //!
    QString create_reply();

private:
    //!
    //! \brief m_status
    //! HTTP response status
    //!
    quint16 m_status = 200;

    //!
    //! \brief header
    //! holds all header data as key/value
    //!

    QHash<QString, QString> m_headers;
    //!
    //! \brief m_body
    //! HTTP response content
    //!
    QString m_body;
};

// https://tools.ietf.org/html/rfc7230#page-19
inline QString Response::create_reply()
{
    QString reply = this->protocol % " " % QString::number(this->status()) % " "
    % this->http_codes[this->status()] % "\r\n";

    // set content length
    m_headers["content-length"] = QString::number(this->body().size());

    // set content type if not set
    if (!m_headers.contains("content-type"))
    {
        // Fixed by j2doll.
        // m_headers["content-type"] = "text/plain";
        m_headers["content-type"] = "text/html";
    }

    // set custom header fields
    for (auto i = m_headers.constBegin(); i != m_headers.constEnd(); ++i)
        reply = reply % i.key() % ": " % i.value() % "\r\n";

    reply += "\r\n";

    if (this->body().size())
        reply += this->body();

    return reply;
}

#endif
